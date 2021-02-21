////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "IME/core/tilemap/TileMap.h"
#include "IME/core/tilemap/TileMapParser.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/graphics/Window.h"

namespace ime {
    TileMap::TileMap(unsigned int tileWidth, unsigned int tileHeight) :
        tileSpacing_{1u},
        isVisible_(true),
        isBackgroundDrawable_(false),
        isTilesDrawable_(true),
        invalidTile_({0, 0}, {-1, -1})
    {
        invalidTile_.setId('!'); //Any tile returned from a function with this token is invalid
        invalidTile_.setPosition({-99, -99});
        invalidTile_.setIndex({-1, -1});
        mapPos_ = {0, 0};
        numOfRows_ = numOfColms_ = 0u;
        if (tileWidth <= 0)
            tileWidth = 8;

        if (tileHeight <= 0)
            tileHeight = 8;

        tileSize_ = Vector2u{tileWidth, tileHeight};
        background_.setPosition(0, 0);
        backgroundTile_.setFillColour(Colour::Grey);
    }

    void TileMap::setVisible(bool visible) {
        if (isVisible_ == visible)
            return;

        isVisible_ = visible;

        forEachTile([=](Tile& tile) {
            tile.setVisible(visible);
        });

        if (isVisible_)
            backgroundTile_.setFillColour(Colour::Grey);
        else
            backgroundTile_.setFillColour(ime::Colour::Transparent);
    }

    bool TileMap::isVisible() const {
        return isVisible_;
    }

    void TileMap::toggleVisibility() {
        setVisible(!isVisible_);
    }

    Tile& TileMap::getTile(const Vector2f &position) {
        for (auto& tileRows : tiledMap_) {
            for (auto& tile : tileRows)
                if (tile.contains(position.x, position.y))
                    return tile;
        }
        return invalidTile_;
    }

    Tile &TileMap::getTileAbove(const Tile &tile) {
        return getTileAbove(tile.getIndex());
    }

    Tile &TileMap::getTileBelow(const Tile &tile) {
        return getTileBelow(tile.getIndex());
    }

    Tile &TileMap::getTileLeftOf(const Tile &tile) {
        return getTileLeftOf(tile.getIndex());
    }

    Tile &TileMap::getTileRightOf(const Tile &tile) {
        return getTileRightOf(tile.getIndex());
    }

    Sprite &TileMap::getBackground() {
        return background_;
    }

    bool TileMap::isIndexValid(const Index &index) const {
        auto [row, colm] = index;
        return !(row >= static_cast<int>(numOfRows_) || row < 0 || colm >= static_cast<int>(numOfColms_) || colm < 0);
    }

    void TileMap::loadFromFile(const std::string &filename, const char& separator) {
        mapData_ = TileMapParser().parse(filename, separator);
        computeDimensions();
        createTiledMap();
        createObjectList();
    }

    void TileMap::loadFromVector(Map map) {
        mapData_ = std::move(map);
        computeDimensions();
        createTiledMap();
        createObjectList();
    }

    void TileMap::computeDimensions() {
        numOfRows_ = mapData_.size();
        numOfColms_ = mapData_[0].size();
        mapSizeInPixels_ = {numOfColms_ * tileSize_.y, numOfRows_ * tileSize_.x};
    }

    void TileMap::setPosition(int x, int y) {
        mapPos_.x = x;
        mapPos_.y = y;
        backgroundTile_.setPosition(mapPos_);

        for (auto i = 0u; i < tiledMap_.size(); i++) {
            for (auto j = 0u; j < mapData_[i].size(); j++) {
                if (i == 0 && j == 0)
                    tiledMap_[i][j].setPosition(mapPos_);
                else if (j == 0)
                    tiledMap_[i][j].setPosition( {mapPos_.x, tiledMap_[i - 1][j].getPosition().y + tileSize_.y + tileSpacing_});
                else
                    tiledMap_[i][j].setPosition( {tiledMap_[i][j - 1].getPosition().x + tileSize_.x + tileSpacing_, tiledMap_[i][j - 1].getPosition().y});
            }
        }
    }

    void TileMap::setTileset(const std::string& name, const std::string &filename) {
        ResourceManager::getInstance()->loadFromFile(ResourceType::Texture, filename);
        tilesets_.insert({name, filename});
    }

    void TileMap::setCurrentTileset(const std::string &name) {
        if (tilesets_.find(name) != tilesets_.end())
            tileSet_ = tilesets_.at(name);
    }

    Vector2f TileMap::getPosition() const {
        return mapPos_;
    }

    void TileMap::createTiledMap() {
        for (auto i = 0u; i < mapData_.size(); i++) {
            auto row = std::vector<Tile>{};
            for (auto j = 0u; j < mapData_[i].size(); j++) {
                auto tile = Tile(tileSize_, {-99, -99});
                if (i == 0 && j == 0)
                    tile.setPosition(mapPos_);
                else if (j == 0)
                    tile.setPosition( {mapPos_.x, tiledMap_[i - 1][j].getPosition().y + tileSize_.y + tileSpacing_});
                else
                    tile.setPosition( {row[j - 1].getPosition().x + tileSize_.x + tileSpacing_, row[j - 1].getPosition().y});

                tile.setId(mapData_[i][j]);
                tile.setIndex({static_cast<int>(i), static_cast<int>(j)});
                row.emplace_back(tile);
            }
            tiledMap_.push_back(row);
        }
        //Accommodate tile spacing in overall tilemap size
        mapSizeInPixels_.x += (numOfColms_ - 1) * tileSpacing_;
        mapSizeInPixels_.y += (numOfRows_ - 1) * tileSpacing_;
        backgroundTile_.setSize({static_cast<float>(mapSizeInPixels_.x), static_cast<float>(mapSizeInPixels_.y)});
    }

    void TileMap::createObjectList() {
        forEachTile([this](Tile& tile) {
            children_.emplace(tile.getIndex(), std::vector<std::shared_ptr<GameObject>>{});
        });
    }

    void TileMap::draw(Window &renderTarget) {
        // Draw tile background
        renderTarget.draw(backgroundTile_);

        // Draw user background
        if (isBackgroundDrawable_)
            renderTarget.draw(background_);

        //Draw tiles (second layer)
        if (isTilesDrawable_) {
            forEachTile([&](Tile &tile) {
                renderTarget.draw(tile);
            });
        }
    }

    void TileMap::setCollidableByIndex(const Index &index, bool isCollidable) {
        if (isIndexValid(index))
            tiledMap_[index.row][index.colm].setSolid(isCollidable);
    }

    void TileMap::setCollidableByIndex(const std::initializer_list<Index> &locations, bool isCollidable) {
        std::for_each(locations.begin(), locations.end(), [=](const Index& index) {
            setCollidableByIndex(index, isCollidable);
        });
    }

    void TileMap::setCollidableByIndex(Index startPos, Index endPos, bool isCollidable) {
        if (isIndexValid(startPos) && isIndexValid(endPos)){
            for (auto i = startPos.colm; i < endPos.colm; i++)
                setCollidableByIndex({startPos.row, i}, isCollidable);
        }
    }

    void TileMap::setCollidableById(char id, bool isCollidable) {
        forEachTile([=](Tile& tile) {
            if (tile.getId() == id)
                tile.setSolid(isCollidable);
        });
    }

    void TileMap::setCollidableByExclusion(char id, bool isCollidable) {
        forEachTile([=](Tile& tile) {
            if (tile.getId() != id)
                tile.setSolid(isCollidable);
        });
    }

    Tile& TileMap::getTile(const Index &index) {
        if (isIndexValid(index))
            return tiledMap_[index.row][index.colm];
        return invalidTile_;
    }

    void TileMap::hideLayer(const std::string &layer) {
        if (layer == "background")
            isBackgroundDrawable_ = false;
        else if (layer == "tiles")
            isTilesDrawable_ = false;
    }

    void TileMap::showLayer(const std::string &layer) {
        if (layer == "background")
            isBackgroundDrawable_ = true;
        else if (layer == "tiles")
            isTilesDrawable_ = true;
    }

    bool TileMap::isLayerHidden(const std::string &layer) const {
        if (layer == "background")
            return isBackgroundDrawable_;
        else if (layer == "tiles")
            return isTilesDrawable_;
        return false;
    }

    bool TileMap::isCollidable(const Index &index) const {
        if (isIndexValid(index))
            return tiledMap_[index.row][index.colm].isCollidable();
        return false;
    }

    bool TileMap::addChild(std::shared_ptr<GameObject> child, Index index) {
        IME_ASSERT(child, "Cannot add nullptr to a tilemap");
        if (isIndexValid(index) && !hasChild(child)) {
            child->getTransform().setPosition(getTile(index).getWorldCentre());
            children_[index].push_back(std::move(child));
            return true;
        }
        return false;
    }

    bool TileMap::hasChild(std::shared_ptr<GameObject> child) {
        if (!child)
            return false;

        for (auto& childList : children_) {
            for (auto i = 0u; i < childList.second.size(); ++i)
                if (childList.second[i] == child)
                    return true;
        }
        return false;
    }

    std::shared_ptr<GameObject> TileMap::getChildWithId(std::size_t id) const {
        for (const auto& childList : children_) {
            for (auto i = 0u; i < childList.second.size(); ++i)
                if (childList.second[i]->getObjectId() == id) {
                    return childList.second[i];
                }
        }
        return nullptr;
    }

    bool TileMap::isTileOccupied(const Tile& tile) const {
        return !children_.at(tile.getIndex()).empty();
    }

    bool TileMap::tileHasVisitors(const Tile &tile) const {
        return children_.at(tile.getIndex()).size() > 1;
    }

    std::shared_ptr<GameObject> TileMap::getOccupant(const Tile& tile) {
        if (isTileOccupied(tile))
            return children_[tile.getIndex()].front();
        return nullptr;
    }

    void TileMap::forEachChild(Callback<std::shared_ptr<GameObject>> callback) {
        std::for_each(children_.begin(), children_.end(), [&callback](auto& childList) {
            std::for_each(childList.second.begin(), childList.second.end(), [&callback] (auto child) {
                callback(child);
            });
        });
    }

    void TileMap::forEachChildInTile(const Tile& tile, Callback<std::shared_ptr<GameObject>> callback) {
        if (isTileOccupied(tile)) {
            std::for_each(children_[tile.getIndex()].begin(), children_[tile.getIndex()].end(),
                [&callback](std::shared_ptr<GameObject> child) { callback(child);}
            );
        }
    }

    std::size_t TileMap::getNumOfOccupants(const Tile &tile) const {
        if (isTileOccupied(tile))
            return children_.at(tile.getIndex()).size();
        return 0;
    }

    bool TileMap::removeChildFromTile(const Tile& tile, const std::shared_ptr<GameObject> &child) {
        if (isTileOccupied(tile)) {
            if (!tileHasVisitors(tile) && getOccupant(tile) == child)
                return removeOccupant(tile);

            for (auto i = 0u; i < children_[tile.getIndex()].size(); ++i) {
                if (children_[tile.getIndex()][i] == child) {
                    children_[tile.getIndex()].erase(children_[tile.getIndex()].begin() + i);
                    return true;
                }
            }
        }
        return false;
    }

    bool TileMap::removeOccupant(const Tile &tile) {
        if (isTileOccupied(tile)) {
            children_[tile.getIndex()].erase(children_[tile.getIndex()].begin());
            return true;
        }
        return false;
    }

    bool TileMap::removeChildWithId(std::size_t id) {
        for (auto& childList : children_) {
            for (auto i = 0u; i < childList.second.size(); ++i)
                if (childList.second[i]->getObjectId() == id) {
                    childList.second.erase(childList.second.begin() + i);
                    return true;
                }
        }
        return false;
    }

    bool TileMap::removeChild(std::shared_ptr<GameObject> child) {
        if (!child)
            return false;
        return removeChildWithId(child->getObjectId());
    }

    void TileMap::removeChildrenIf(std::function<bool(std::shared_ptr<GameObject>)> callback) {
        for (auto& childList : children_)
            childList.second.erase(std::remove_if(childList.second.begin(), childList.second.end(), callback), childList.second.end());
    }

    bool TileMap::removeAllVisitors(const Tile &tile) {
        if (!tileHasVisitors(tile))
            return false;
        else {
            auto occupant = std::move(children_[tile.getIndex()].front());
            children_[tile.getIndex()].clear();
            children_[tile.getIndex()].push_back(std::move(occupant));
            return true;
        }
    }

    bool TileMap::removeAllChildren(const Tile &tile) {
        if (isTileOccupied(tile)) {
            children_[tile.getIndex()].clear();
            return true;
        }
        return false;
    }

    void TileMap::moveChild(std::shared_ptr<GameObject> child, Index index) {
        if (hasChild(child) && isIndexValid(index) && index != getTileOccupiedByChild(child).getIndex()) {
            removeChildFromTile(getTileOccupiedByChild(child), child);
            addChild(child, index);
        }
    }

    void TileMap::moveChild(std::shared_ptr<GameObject> child, const Tile &tile) {
        moveChild(std::move(child), tile.getIndex());
    }

    Vector2u TileMap::getTileSize() const {
        return tileSize_;
    }

     void TileMap::textureTile(Index index, FloatRect rect) {
        IME_ASSERT(!tilesets_.empty(), "Cannot texture tile with an empty tileset, set tileset to be used first");
        if (isIndexValid(index)) {
            auto& sprite = tiledMap_[index.row][index.colm].getSprite();
            sprite.setTexture(tileSet_);
            sprite.setTextureRect(rect.left, rect.top, rect.width, rect.height);
        }
    }

    void TileMap::textureTilesById(char id, FloatRect rect) {
        forEachTile([&](Tile& tile) {
            if (tile.getId() == id)
                textureTile(tile.getIndex(), rect);
        });
    }

    void TileMap::textureTilesById(char id, const Sprite &sprite) {
        forEachTile([&](Tile& tile) {
            if (tile.getId() == id)
                tile.addSprite(sprite);
        });
    }

    void TileMap::forEachTile(Callback<Tile&> callback) {
        std::for_each(tiledMap_.begin(), tiledMap_.end(), [&](auto& row) {
            std::for_each(row.begin(), row.end(), callback);
        });
    }

    void TileMap::forEachTileWithId(char id, Callback<Tile&> callback) {
        forEachTile([&](Tile& tile) {
            if (tile.getId() == id)
                callback(tile);
        });
    }

    void TileMap::forEachTileExcept(char id, Callback<Tile &> callback) {
        forEachTile([&](Tile& tile) {
            if (tile.getId() != id)
                callback(tile);
        });
    }

    void TileMap::forEachTileInRange(Index startPos, Index endPos, Callback<Tile&> callback) {
        if (isIndexValid(startPos) && isIndexValid(endPos)) {
            std::for_each(tiledMap_[startPos.row].begin() + startPos.colm,
                tiledMap_[startPos.row].begin() + endPos.colm,
                [&](Tile& tile) { callback(tile);}
            );
        }
    }

    Tile &TileMap::getTileAbove(const Index &index) {
        return getTile(Index{index.row - 1, index.colm});
    }

    Tile& TileMap::getTileBelow(const Index &index) {
        return getTile(Index{index.row + 1, index.colm});
    }

    Tile& TileMap::getTileLeftOf(const Index &index) {
        return getTile(Index{index.row, index.colm - 1});
    }

    Tile& TileMap::getTileRightOf(const Index &index) {
        return getTile(Index{index.row, index.colm + 1});
    }

    Vector2u TileMap::getSize() const {
        return mapSizeInPixels_;
    }

    unsigned int TileMap::getSpaceBetweenTiles() const {
        return tileSpacing_;
    }

    Vector2u TileMap::getSizeInTiles() const {
        return {numOfColms_, numOfRows_};
    }

    Tile& TileMap::getTileOccupiedByChild(std::shared_ptr<GameObject> child) {
        return getTile(child->getTransform().getPosition());
    }
}
