////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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
#include "IME/core/managers/ResourceManager.h"
#include "IME/graphics/Window.h"
#include <cassert>

namespace IME {
    TileMap::TileMap(unsigned int tileWidth, unsigned int tileHeight) :
        tileSpacing_{1u},
        isGridVisible_(true),
        isBackgroundDrawable_(false),
        isTilesDrawable_(true),
        isObjectsDrawable_(true),
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
    }

    void TileMap::setGridVisible(bool isVisible) {
        if (isGridVisible_ == isVisible)
            return;

        forEachTile([=](Graphics::Tile& tile) {
            tile.setBorderVisible(isVisible);
        });

        isGridVisible_ = isVisible;
    }

    Graphics::Tile& TileMap::getTile(const Vector2f &position) {
        for (auto& tileRows : tiledMap_) {
            for (auto& tile : tileRows)
                if (tile.contains(position.x, position.y))
                    return tile;
        }
        return invalidTile_;
    }

    Graphics::Tile &TileMap::getTileAbove(const Graphics::Tile &tile) {
        return getTileAbove(tile.getIndex());
    }

    Graphics::Tile &TileMap::getTileBelow(const Graphics::Tile &tile) {
        return getTileBelow(tile.getIndex());
    }

    Graphics::Tile &TileMap::getTileLeftOf(const Graphics::Tile &tile) {
        return getTileLeftOf(tile.getIndex());
    }

    Graphics::Tile &TileMap::getTileRightOf(const Graphics::Tile &tile) {
        return getTileRightOf(tile.getIndex());
    }

    Graphics::Sprite &TileMap::getBackground() {
        return background_;
    }

    bool TileMap::isIndexValid(const Index &index) const {
        auto [row, colm] = index;
        return !(row >= numOfRows_ || row < 0 || colm >= numOfColms_ || colm < 0);
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
            auto row = std::vector<Graphics::Tile>{};
            for (auto j = 0u; j < mapData_[i].size(); j++) {
                auto tile = Graphics::Tile(tileSize_, {-99, -99});
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
    }

    void TileMap::createObjectList() {
        forEachTile([this](Graphics::Tile& tile) {
            children_.emplace(tile.getIndex(), std::vector<std::shared_ptr<Entity>>{});
        });
    }

    void TileMap::draw(Graphics::Window &renderTarget) {
        //Draw background (first layer)
        if (isBackgroundDrawable_)
            renderTarget.draw(background_);

        //Draw tiles (second layer)
        if (isTilesDrawable_) {
            forEachTile([&](Graphics::Tile &tile) {
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
        forEachTile([=](Graphics::Tile& tile) {
            if (tile.getId() == id)
                tile.setSolid(isCollidable);
        });
    }

    void TileMap::setCollidableByExclusion(char id, bool isCollidable) {
        forEachTile([=](Graphics::Tile& tile) {
            if (tile.getId() != id)
                tile.setSolid(isCollidable);
        });
    }

    Graphics::Tile& TileMap::getTile(const Index &index) {
        if (isIndexValid(index))
            return tiledMap_[index.row][index.colm];
        return invalidTile_;
    }

    void TileMap::hideLayer(const std::string &layer) {
        if (layer == "background")
            isBackgroundDrawable_ = false;
        else if (layer == "tiles")
            isTilesDrawable_ = false;
        else if (layer == "objects")
            isObjectsDrawable_ = false;
    }

    void TileMap::showLayer(const std::string &layer) {
        if (layer == "background")
            isBackgroundDrawable_ = true;
        else if (layer == "tiles")
            isTilesDrawable_ = true;
        else if (layer == "objects")
            isObjectsDrawable_ = true;
    }

    bool TileMap::isLayerHidden(const std::string &layer) const {
        if (layer == "background")
            return isBackgroundDrawable_;
        else if (layer == "tiles")
            return isTilesDrawable_;
        else if (layer == "objects")
            return isObjectsDrawable_;
        return false;
    }

    bool TileMap::isCollidable(const Index &index) const {
        if (!isIndexValid(index))
            return tiledMap_[index.row][index.colm].isCollidable();
        return false;
    }

    bool TileMap::addChild(std::shared_ptr<IME::Entity> child, Index index) {
        assert(child && "Object added to the tilemap cannot be null");
        if (isIndexValid(index) && !hasChild(child)) {
            child->setPosition(getTile(index).getPosition().x, getTile(index).getPosition().y);
            children_[index].push_back(std::move(child));
            return true;
        }
        return false;
    }

    bool TileMap::hasChild(std::shared_ptr<Entity> child) {
        if (!child)
            return false;

        for (auto& [index, childList] : children_) {
            for (auto i = 0u; i < childList.size(); ++i)
                if (childList[i] == child)
                    return true;
        }
        return false;
    }

    std::shared_ptr<Entity> TileMap::getChildWithId(std::size_t id) const {
        for (const auto& [index, childList] : children_) {
            for (auto i = 0u; i < childList.size(); ++i)
                if (childList[i]->getObjectId() == id) {
                    return childList[i];
                }
        }
        return nullptr;
    }

    bool TileMap::isTileOccupied(const Graphics::Tile& tile) const {
        return !children_.at(tile.getIndex()).empty();
    }

    bool TileMap::tileHasVisitors(const Graphics::Tile &tile) const {
        return children_.at(tile.getIndex()).size() > 1;
    }

    std::shared_ptr<Entity> TileMap::getOccupant(const Graphics::Tile& tile) {
        if (isTileOccupied(tile))
            return children_[tile.getIndex()].front();
        return nullptr;
    }

    void TileMap::forEachChild(Callback<std::shared_ptr<Entity>> callback) {
        std::for_each(children_.begin(), children_.end(), [&callback](auto& childList) {
            std::for_each(childList.second.begin(), childList.second.end(), [&callback] (auto child) {
                callback(child);
            });
        });
    }

    void TileMap::forEachChildInTile(const Graphics::Tile& tile, Callback<std::shared_ptr<Entity>> callback) {
        if (isTileOccupied(tile)) {
            std::for_each(children_[tile.getIndex()].begin(), children_[tile.getIndex()].end(),
                [&callback](std::shared_ptr<Entity> child) { callback(child);}
            );
        }
    }

    std::size_t TileMap::getNumOfOccupants(const Graphics::Tile &tile) const {
        if (isTileOccupied(tile))
            return children_.at(tile.getIndex()).size();
        return 0;
    }

    bool TileMap::removeChildFromTile(const IME::Graphics::Tile& tile, const std::shared_ptr<Entity> &child) {
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

    bool TileMap::removeOccupant(const Graphics::Tile &tile) {
        if (isTileOccupied(tile)) {
            children_[tile.getIndex()].erase(children_[tile.getIndex()].begin());
            return true;
        }
        return false;
    }

    bool TileMap::removeChildWithId(std::size_t id) {
        for (auto& [index, childList] : children_) {
            for (auto i = 0u; i < childList.size(); ++i)
                if (childList[i]->getObjectId() == id) {
                    childList.erase(childList.begin() + i);
                    return true;
                }
        }
        return false;
    }

    bool TileMap::removeChild(std::shared_ptr<Entity> child) {
        if (!child)
            return false;
        return removeChildWithId(child->getObjectId());
    }

    void TileMap::removeChildrenIf(std::function<bool(std::shared_ptr<Entity>)> callback) {
        for (auto& [index, childList] : children_)
            childList.erase(std::remove_if(childList.begin(), childList.end(), callback), childList.end());
    }

    bool TileMap::removeAllVisitors(const Graphics::Tile &tile) {
        if (!tileHasVisitors(tile))
            return false;
        else {
            auto occupant = std::move(children_[tile.getIndex()].front());
            children_[tile.getIndex()].clear();
            children_[tile.getIndex()].push_back(std::move(occupant));
            return true;
        }
    }

    bool TileMap::removeAllChildren(const Graphics::Tile &tile) {
        if (isTileOccupied(tile)) {
            children_[tile.getIndex()].clear();
            return true;
        }
        return false;
    }

    void TileMap::moveChild(std::shared_ptr<IME::Entity> child, Index index) {
        if (hasChild(child) && isIndexValid(index) && index != getTileOccupiedByChild(child).getIndex()) {
            removeChildFromTile(getTileOccupiedByChild(child), child);
            addChild(child, index);
        }
    }

    void TileMap::moveChild(std::shared_ptr<IME::Entity> child, const Graphics::Tile &tile) {
        moveChild(std::move(child), tile.getIndex());
    }

    Vector2u TileMap::getTileSize() const {
        return tileSize_;
    }

     void TileMap::textureTile(Index index, FloatRect rect) {
        assert(!tilesets_.empty() && "Cannot texture tile with an empty tileset, set tileset to be used first");
        if (isIndexValid(index)) {
            auto& sprite = tiledMap_[index.row][index.colm].getSprite();
            sprite.setTexture(tileSet_);
            sprite.setTextureRect(rect.left, rect.top, rect.width, rect.height);
        }
    }

    void TileMap::textureTilesById(char id, FloatRect rect) {
        forEachTile([&](Graphics::Tile& tile) {
            if (tile.getId() == id)
                textureTile(tile.getIndex(), rect);
        });
    }

    void TileMap::textureTilesById(char id, const Graphics::Sprite &sprite) {
        forEachTile([&](Graphics::Tile& tile) {
            if (tile.getId() == id)
                tile.addSprite(sprite);
        });
    }

    void TileMap::forEachTile(Callback<Graphics::Tile&> callback) {
        std::for_each(tiledMap_.begin(), tiledMap_.end(), [&](auto& row) {
            std::for_each(row.begin(), row.end(), callback);
        });
    }

    void TileMap::forEachTileWithId(char id, Callback<Graphics::Tile&> callback) {
        forEachTile([&](Graphics::Tile& tile) {
            if (tile.getId() == id)
                callback(tile);
        });
    }

    void TileMap::forEachTileExcept(char id, Callback<Graphics::Tile &> callback) {
        forEachTile([&](Graphics::Tile& tile) {
            if (tile.getId() != id)
                callback(tile);
        });
    }

    void TileMap::forEachTileInRange(Index startPos, Index endPos, Callback<Graphics::Tile&> callback) {
        if (isIndexValid(startPos) && isIndexValid(endPos)) {
            std::for_each(tiledMap_[startPos.row].begin() + startPos.colm,
                tiledMap_[startPos.row].begin() + endPos.colm,
                [&](Graphics::Tile& tile) { callback(tile);}
            );
        }
    }

    Graphics::Tile &TileMap::getTileAbove(const Index &index) {
        return getTile(Index{index.row - 1, index.colm});
    }

    Graphics::Tile& TileMap::getTileBelow(const Index &index) {
        return getTile(Index{index.row + 1, index.colm});
    }

    Graphics::Tile& TileMap::getTileLeftOf(const Index &index) {
        return getTile(Index{index.row, index.colm - 1});
    }

    Graphics::Tile& TileMap::getTileRightOf(const Index &index) {
        return getTile(Index{index.row, index.colm + 1});
    }

    bool TileMap::isGridVisible() const {
        return isGridVisible_;
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

    Graphics::Tile& TileMap::getTileOccupiedByChild(std::shared_ptr<Entity> child) {
        return getTile(child->getPosition());
    }
}
