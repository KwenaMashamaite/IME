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

#include "IME/core/physics/grid/path/DFS.h"
#include "IME/core/grid/Grid2D.h"

namespace ime {
    DFS::DFS(const Vector2u& gridSize) {
        visited_ = std::vector<std::vector<bool>>(gridSize.y, std::vector<bool>(gridSize.x, false));
    }

    std::stack<Index>
    DFS::findPath(const Grid2D &grid, const Index& sourceTile, const Index& targetTile) {
        if (sourceTile == targetTile || !grid.isIndexValid(sourceTile)
            || !grid.isIndexValid(targetTile))
            return std::stack<Index>{};

        adjacencyList_.generateFrom(grid);
        std::vector<Node> exploredPath;
        std::stack<Node> nodesToVisit;
        nodesToVisit.push({sourceTile, sourceTile});

        while (!nodesToVisit.empty()) {
            Node node = nodesToVisit.top();
            visited_[node.index.row][node.index.colm] = true;
            nodesToVisit.pop();

            if (node.index == targetTile) {
                exploredPath.push_back(node);
                break;
            } else {
                exploredPath.push_back(node);
                for (auto& neighbour : adjacencyList_.getNeighbours(node.index)) {
                    if (!visited_[neighbour.row][neighbour.colm])
                        nodesToVisit.push({node.index, neighbour});
                }
            }
        }

        reset();
        return backtrack(exploredPath, targetTile);
    }

    void DFS::reset() {
        for (auto& innerVec : visited_) {
            std::fill(innerVec.begin(), innerVec.end(), false);
        }
    }

    std::string DFS::getType() const {
        return "DFS";
    }
}
