#include "IME/core/path/AdjacencyList.h"

namespace IME {
    void AdjacencyList::generateFrom(TileMap &tileMap) {
        auto static addNeighbour = [](auto& tilemap, auto& neighbours, int row, int colm) {
            if (tilemap.isIndexValid({row, colm}) && tilemap.getTile(Index{row, colm}).getType() != Graphics::TileType::Obstacle)
                neighbours.push_back({row, colm});
        };

        for (auto i = 0; i < tileMap.getSizeInTiles().height; i++) {
            for (auto j = 0 ; j < tileMap.getSizeInTiles().width; j++) {
                if (tileMap.getTile(Index{i, j}).getType() == Graphics::TileType::Obstacle)
                    continue;
                auto neighbours = std::vector<Index>{};
                addNeighbour(tileMap, neighbours, i - 1, j); //Left neighbour
                addNeighbour(tileMap, neighbours, i, j - 1); //Top neighbour
                addNeighbour(tileMap, neighbours, i + 1, j); //Right neighbour
                addNeighbour(tileMap, neighbours, i, j + 1); //Bottom neighbour
                adjacencyList_.push_back({{i, j}, neighbours});
            }
        }
    }

    const std::vector<Index>& AdjacencyList::getNeighbours(const Index &index) const {
        for (const auto& collection : adjacencyList_) {
            const auto& [tile, neighbours] = collection;
            if (tile.row == index.row && tile.colm == index.colm)
                return neighbours;
        }
        return emptyVec;
    }
}
