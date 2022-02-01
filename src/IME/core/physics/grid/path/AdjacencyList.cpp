////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/core/physics/grid/path/AdjacencyList.h"
#include "IME/core/object/GridObject.h"
#include "IME/core/grid/Grid2D.h"

namespace ime {
    namespace {
        bool tileHasObstacle(const Grid2D& grid, Index index) {
            bool hasObstacle = false;
            grid.forEachChildInTile(grid.getTile(index), [&hasObstacle](const GridObject* child) {
                if (child->isObstacle() && child->isActive()) {
                    hasObstacle = true;
                    return;
                }
            });
            return hasObstacle;
        }
    }

    void AdjacencyList::generateFrom(const Grid2D &grid) {
        adjacencyList_.clear();
        auto static addNeighbour = [](const Grid2D& grid2D, std::vector<Index>& neighboursVec, int row, int colm) {
            if (grid2D.isIndexValid({row, colm})
                && !grid2D.getTile(Index{row, colm}).isCollidable()
                && !tileHasObstacle(grid2D, Index{row, colm}))
            {
                neighboursVec.push_back({row, colm});
            }
        };

        for (auto i = 0; i < static_cast<int>(grid.getSizeInTiles().y); i++) {
            for (auto j = 0 ; j < static_cast<int>(grid.getSizeInTiles().x); j++) {
                if (grid.getTile(Index{i, j}).isCollidable() || tileHasObstacle(grid, Index{i, j}))
                    continue;

                std::vector<Index> neighbours;
                addNeighbour(grid, neighbours, i - 1, j); //Left neighbour
                addNeighbour(grid, neighbours, i, j - 1); //Top neighbour
                addNeighbour(grid, neighbours, i + 1, j); //Right neighbour
                addNeighbour(grid, neighbours, i, j + 1); //Bottom neighbour
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
