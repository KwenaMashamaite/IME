#include "IME/core/tile/TileMap.h"
#include "IME/core/tile/TileMapParser.h"
#include "IME/gui/window/Window.h"

namespace IME {
    TileMap::TileMap(const std::string& tileSet, unsigned int tileWidth, unsigned int tileHeight)
    {
        tileSet_ = tileSet;
        mapPos_ = {0, 0};
        tileSize_ = Dimensions{static_cast<float>(tileWidth), static_cast<float>(tileHeight)};
    }

    Tile& TileMap::getTile(const Position &position) {
        if (auto index = getIndexFromPosition(position); isIndexValid(index))
            return getTile(index);
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
            for (auto j = 0u; j < mapData_[i].size(); j++)
                row.emplace_back(Tile(tileSize_, {j * tileSize_.width, i * tileSize_.height}));
            tiledMap_.push_back(row);
        }
    }

    void TileMap::draw(Gui::Window &renderTarget) {
        std::for_each(tiledMap_.begin(), tiledMap_.end(), [&](auto& row) {
            std::for_each(row.begin(), row.end(), [&](auto& tile) {
                renderTarget.draw(tile);
            });
        });
    }

    void TileMap::hide() {

    }

    void TileMap::show() {

    }

    bool TileMap::isHidden() const {
        return false;
    }

    void TileMap::setTile(Index index, Tile &&tile) {
        tiledMap_[index.row][index.colm] = tile;
    }

    Tile& TileMap::getTile(const Index &index) {
        return tiledMap_[index.row][index.colm];
    }
}
