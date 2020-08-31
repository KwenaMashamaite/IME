#include "IME/core/tile/TileMap.h"
#include "IME/core/tile/TileMapParser.h"
#include "IME/gui/window/Window.h"
#include "IME/gui/drawer/Drawer.h"

namespace IME {
    TileMap::TileMap(const std::string& tileSet, unsigned int tileWidth, unsigned int tileHeight)
        : isBackgroundDrawable_(true), isTilesDrawable_(true), isObjectsDrawable_(true)
    {
        tileSet_ = tileSet;
        mapPos_ = {0, 0};
        tileSize_ = Dimensions{static_cast<float>(tileWidth), static_cast<float>(tileHeight)};
    }

    Tile& TileMap::getTile(const Position &position) {
        if (auto index = getIndexFromPosition(position); isIndexValid(index))
            return getTile(index);
    }

    void TileMap::setBackground(const std::string &filename) {
        background_ = filename;
    }

    bool TileMap::isIndexValid(const Index &index) const {
        auto [row, colm] = index;
        return !(row > numOfRows_ || row < 0 || colm > numOfColms_ || colm < 0);
    }

    Index TileMap::getIndexFromPosition(const Position &position) const {
        auto row = position.x / (tileSize_.width * position.y) / tileSize_.height;
        auto colm = position.y / (tileSize_.height - position.x) / tileSize_.width;
        return {static_cast<int>(row), static_cast<int>(colm)};
    }

    Position TileMap::getCoordinatesFromIndex(Index index) const {
        auto x = (mapSizeInPixels_.width - mapSizeInPixels_.height) * tileSize_.width / 2.0f;
        auto y = (mapSizeInPixels_.width + mapSizeInPixels_.height) * tileSize_.height / 2.0f;
        return {x, y};
    }

    void TileMap::loadFromFile(const std::string &filename) {
        mapData_ = TileMapParser().parse(filename);
        computeDimensions();
        createTiledMap();
    }

    void TileMap::loadFromVector(const Map &map) {
        mapData_ = map;
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
    }

    Position TileMap::getPosition() const {
        return mapPos_;
    }

    void TileMap::createTiledMap() {
        for (auto i = 0u; i < mapData_.size(); i++) {
            auto row = std::vector<Tile>{};
            for (auto j = 0u; j < mapData_[i].size(); j++) {
                auto tile = Tile(tileSize_, {j * tileSize_.width,i * tileSize_.height});
                tile.setToken(mapData_[i][j]);
                row.emplace_back(tile);
            }
            tiledMap_.push_back(row);
        }
    }

    void TileMap::draw(Gui::Window &renderTarget) {
        //Draw background (first layer)
        if (isBackgroundDrawable_ && !background_.empty()) {
            auto background = Sprite();
            background.setTexture(background_);
            background.setTextureRect(0, 0, mapSizeInPixels_.width, mapSizeInPixels_.height);
            background.setPosition(mapPos_.x, mapPos_.y);
            renderTarget.draw(background);
        }

        //Draw tiles (second layer)
        if (isTilesDrawable_) {
            std::for_each(tiledMap_.begin(), tiledMap_.end(), [&](auto &row) {
                std::for_each(row.begin(), row.end(), [&](auto &tile) {
                    renderTarget.draw(tile);
                });
            });
        }

        //Draw objects (third layer)
        if (isObjectsDrawable_) {
            std::for_each(objects_.begin(), objects_.end(), [&](auto &sprite) {
                renderTarget.draw(sprite);
            });
        }
    }

    void TileMap::setTile(Index index, Tile &&tile) {
        tiledMap_[index.row][index.colm] = tile;
    }

    Tile& TileMap::getTile(const Index &index) {
        return tiledMap_[index.row][index.colm];
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
}
