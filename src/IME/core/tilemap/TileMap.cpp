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
    TileMap::TileMap(unsigned int tileWidth, unsigned int tileHeight)
        : isGridVisible_(true), isBackgroundDrawable_(false), isTilesDrawable_(true),
          isObjectsDrawable_(true), invalidTile_({0, 0}, {-1, -1})
    {
        invalidTile_.setId('!'); //Any tile returned from a function with this token is invalid
        invalidTile_.setPosition({-99, -99});
        invalidTile_.setIndex({-1, -1});
        mapPos_ = {0, 0};
        numOfRows_ = numOfColms_ = 0;
        if (tileWidth <= 0)
            tileWidth = 8;

        if (tileHeight <= 0)
            tileHeight = 8;

        tileSize_ = Dimensions{static_cast<float>(tileWidth), static_cast<float>(tileHeight)};
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

    Graphics::Tile& TileMap::getTile(const Position &position) {
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

    void TileMap::setBackground(const std::string &filename, Position position) {
        background_.setTexture(filename);
        background_.setPosition(position);
        if (background_.getSize().width > mapSizeInPixels_.width
            && background_.getSize().height > mapSizeInPixels_.height)
            background_.setTextureRect(0, 0, mapSizeInPixels_.width, mapSizeInPixels_.height);
        else if (background_.getSize().width > mapSizeInPixels_.width)
            background_.setTextureRect(0, 0, mapSizeInPixels_.width, background_.getSize().height);
        else if (background_.getSize().height > mapSizeInPixels_.height)
            background_.setTextureRect(0, 0, background_.getSize().width, mapSizeInPixels_.height);
        isBackgroundDrawable_ = true;
    }

    void TileMap::scaleBackground(float xOffset, float yOffset) {
        background_.scale(xOffset, yOffset);
    }

    bool TileMap::isIndexValid(const Index &index) const {
        auto [row, colm] = index;
        return !(row >= numOfRows_ || row < 0 || colm >= numOfColms_ || colm < 0);
    }

    void TileMap::loadFromFile(const std::string &filename, const char& separator) {
        mapData_ = TileMapParser().parse(filename, separator);
        computeDimensions();
        createTiledMap();
    }

    void TileMap::loadFromVector(Map map) {
        mapData_ = std::move(map);
        computeDimensions();
        createTiledMap();
    }

    void TileMap::computeDimensions() {
        numOfRows_ = mapData_.size();
        numOfColms_ = mapData_[0].size();
        mapSizeInPixels_ = {numOfColms_ * tileSize_.height, numOfRows_ * tileSize_.width};
    }

    void TileMap::setPosition(int x, int y) {
        mapPos_.x = x;
        mapPos_.y = y;

        for (auto i = 0u; i < tiledMap_.size(); i++) {
            for (auto j = 0u; j < mapData_[i].size(); j++) {
                if (i == 0 && j == 0)
                    tiledMap_[i][j].setPosition(mapPos_);
                else if (j == 0)
                    tiledMap_[i][j].setPosition( {mapPos_.x, tiledMap_[i - 1][j].getPosition().y + tileSize_.height});
                else
                    tiledMap_[i][j].setPosition( {tiledMap_[i][j - 1].getPosition().x + tileSize_.width, tiledMap_[i][j - 1].getPosition().y});
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

    Position TileMap::getPosition() const {
        return mapPos_;
    }

    void TileMap::createTiledMap() {
        auto tileSpacing = 1;
        for (auto i = 0u; i < mapData_.size(); i++) {
            auto row = std::vector<Graphics::Tile>{};
            for (auto j = 0u; j < mapData_[i].size(); j++) {
                auto tile = Graphics::Tile(tileSize_, {-99, -99});
                if (i == 0 && j == 0)
                    tile.setPosition(mapPos_);
                else if (j == 0)
                    tile.setPosition( {mapPos_.x, tiledMap_[i - 1][j].getPosition().y + tileSize_.height + tileSpacing});
                else
                    tile.setPosition( {row[j - 1].getPosition().x + tileSize_.width + tileSpacing, row[j - 1].getPosition().y});

                tile.setId(mapData_[i][j]);
                tile.setIndex({static_cast<int>(i), static_cast<int>(j)});
                row.emplace_back(tile);
            }
            tiledMap_.push_back(row);
        }
        //Accommodate tile spacing in overall tilemap size
        mapSizeInPixels_.width += (numOfColms_ - 1) * tileSpacing;
        mapSizeInPixels_.height += (numOfRows_ - 1) * tileSpacing;
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

    void TileMap::setTile(Index index, Graphics::Tile &&tile) {
        if (isIndexValid(index))
            tiledMap_[index.row][index.colm] = std::move(tile);
    }

    void TileMap::setCollidableByIndex(const Index &index, bool isCollidable) {
        if (isIndexValid(index))
            tiledMap_[index.row][index.colm].setCollidable(isCollidable);
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

    void TileMap::setCollidableById(const char &id, bool isCollidable) {
        forEachTile([=](Graphics::Tile& tile) {
            if (tile.getId() == id)
                tile.setCollidable(isCollidable);
        });
    }

    void TileMap::setCollidableByExclusion(const char &id, bool isCollidable) {
        forEachTile([=](Graphics::Tile& tile) {
            if (tile.getId() != id)
                tile.setCollidable(isCollidable);
        });
    }

    Graphics::Tile& TileMap::getTile(const Index &index) {
        if (isIndexValid(index))
            return tiledMap_[index.row][index.colm];
        return invalidTile_;
    }

    void TileMap::hide(const std::string &layer) {
        if (layer == "background")
            isBackgroundDrawable_ = false;
        else if (layer == "tiles")
            isTilesDrawable_ = false;
        else if (layer == "objects")
            isObjectsDrawable_ = false;
    }

    void TileMap::show(const std::string &layer) {
        if (layer == "background")
            isBackgroundDrawable_ = true;
        else if (layer == "tiles")
            isTilesDrawable_ = true;
        else if (layer == "objects")
            isObjectsDrawable_ = true;
    }

    bool TileMap::isHidden(const std::string &layer) const {
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

    bool TileMap::addChild(Index index, std::shared_ptr<IME::Entity> child) {
        assert(child && "Object added to the tilemap cannot be null");
        if (isIndexValid(index) && !hasChild(child)) {
            auto& targetTile = getTile(index);
            child->setPosition(targetTile.getPosition().x, targetTile.getPosition().y);
            children_.emplace_back(index, std::move(child));
            return true;
        }
        return false;
    }

    bool TileMap::hasChild(std::shared_ptr<Entity> child) {
        if (!child)
            return false;

        auto hasChild = false;
        std::for_each(children_.begin(), children_.end(), [&](auto& childPtr) {
            if (childPtr.second == child)
                hasChild = true;
        });
        return hasChild;
    }

    std::shared_ptr<Entity> TileMap::getChild(Index index) const {
        for (auto& [childIndex, child] : children_) {
            if (childIndex == index)
                return child;
        }
        return nullptr;
    }

    bool TileMap::removeChild(Index index) {
        for (auto& child : children_) {
            if (child.first == index) {
                child.first = {-1, -1};
                return true;
            }
        }
        return false;
    }

    void TileMap::updateChild(std::shared_ptr<IME::Entity> child, Index index) {
        for (auto& childInGrid : children_) {
            if (childInGrid.second == child) {
                childInGrid.first = index;
                childInGrid.second->setPosition(getTile(index).getPosition().x,
                getTile(index).getPosition().y);
            }
        }
    }

    Dimensions TileMap::getTileSize() const {
        return tileSize_;
    }

    void TileMap::addTilesetImageData(const char &id, Position startPos, Dimensions size) {
        imagesData_.insert({id, {tileSet_, startPos, size}});
    }

    bool TileMap::isIdLinkedToImage(const char &id) const {
        return imagesData_.find(id) != imagesData_.end();
    }

    void TileMap::applyImages() {
        forEachTile([this](Graphics::Tile& tile) {
            if (auto tileId = tile.getId(); isIdLinkedToImage(tileId)) {
                auto [tileset, startPos, size] = imagesData_.at(tileId);
                auto sprite = Graphics::Sprite();
                sprite.setTexture(tileset);
                sprite.setTextureRect(startPos.x, startPos.y, size.width, size.height);
                tile.addSprite(std::move(sprite));
            }
        });
    }

    void TileMap::forEachTile(Callback<Graphics::Tile&> callback) {
        std::for_each(tiledMap_.begin(), tiledMap_.end(), [&](auto& row) {
            std::for_each(row.begin(), row.end(), callback);
        });
    }


    void TileMap::forEachTile(const char &id, Callback<Graphics::Tile&> callback) {
        forEachTile([&](Graphics::Tile& tile) {
            if (tile.getId() == id)
                callback(tile);
        });
    }

    void TileMap::forEachTile(Index startPos, Index endPos, Callback<Graphics::Tile&> callback) {
        if (isIndexValid(startPos) && isIndexValid(endPos)) {
            std::for_each(tiledMap_[startPos.row].begin() + startPos.colm,
                tiledMap_[startPos.row].begin() + endPos.colm,
                [&](Graphics::Tile& tile) { callback(tile);}
            );
        }
    }

    void TileMap::forEachChild(Callback<Entity&> callback) {
        std::for_each(children_.begin(), children_.end(), [&](auto& child) {
            if (child.second)
                callback(*child.second);
        });
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

    Dimensions TileMap::getSize() const {
        return mapSizeInPixels_;
    }

    Dimensions TileMap::getSizeInTiles() const {
        return {static_cast<float>(numOfColms_), static_cast<float>(numOfRows_)};
    }
}
