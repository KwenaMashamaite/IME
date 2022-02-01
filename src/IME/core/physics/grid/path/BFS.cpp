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

#include "IME/core/physics/grid/path/BFS.h"
#include "IME/core/grid/Grid2D.h"
#include <algorithm>

namespace ime {
    BFS::BFS(const Vector2u& gridSize) {
        visited_ = std::vector<std::vector<bool>>(gridSize.y, std::vector<bool>(gridSize.x, false));
    }

    std::stack<Index> BFS::findPath(const Grid2D& grid, const Index& sourceTile, const Index& targetTile) {
        if (sourceTile == targetTile || !grid.isIndexValid(sourceTile)
            || !grid.isIndexValid(targetTile))
            return std::stack<Index>{};

        adjacencyList_.generateFrom(grid);
        std::vector<Node> exploredPath;
        std::queue<Node> nodesToVisit;
        nodesToVisit.push({sourceTile, sourceTile});

        while (!nodesToVisit.empty()) {
            Node node = nodesToVisit.front();
            nodesToVisit.pop();
            bfs(node, targetTile, nodesToVisit, exploredPath);
        }

        reset();
        return backtrack(exploredPath, targetTile);
    }

    void BFS::reset() {
        for (auto& innerVec : visited_) {
            std::fill(innerVec.begin(), innerVec.end(), false);
        }
    }

    void BFS::bfs(const Node& source, const Index& target, std::queue<Node> &nodeToVisit, std::vector<Node> &exploredNodes) {
        if (visited_.at(source.index.row).at(source.index.colm)) //Don't explore a node more than once
            return;
        else if (source.index == target) {
            exploredNodes.push_back(source);
            while (!nodeToVisit.empty())
                nodeToVisit.pop();
        } else {
            exploredNodes.push_back(source);
            visited_[source.index.row][source.index.colm] = true;
            for (auto& neighbour : adjacencyList_.getNeighbours(source.index))
                nodeToVisit.push({source.index, neighbour});
        }
    }

    std::string BFS::getType() const {
        return "BFS";
    }
}