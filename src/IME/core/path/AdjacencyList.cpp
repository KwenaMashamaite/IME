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

#include "IME/core/path/AdjacencyList.h"

namespace IME {
    void AdjacencyList::generateFrom(TileMap &tileMap) {
        auto static addNeighbour = [](auto& tilemap, auto& neighbours, int row, int colm) {
            if (tilemap.isIndexValid({row, colm}) && tilemap.getTile(Index{row, colm}).getType() != Graphics::TileType::Obstacle)
                neighbours.push_back({row, colm});
        };

        for (auto i = 0; i < tileMap.getSizeInTiles().y; i++) {
            for (auto j = 0 ; j < tileMap.getSizeInTiles().x; j++) {
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
