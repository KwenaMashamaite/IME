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

#include "IME/core/path/BFS.h"
#include <algorithm>

namespace IME {
    BFSPathFinder::BFSPathFinder(Vector2u gridSize) {
        for (auto i = 0; i < gridSize.y; i++) {
            auto innerVector = std::vector<bool>{};
            for (auto j = 0; j < gridSize.x; j++)
                innerVector.push_back(false);
            visited_.push_back(innerVector);
        }
    }

    std::stack<Index> BFSPathFinder::findPath(TileMap& grid, Index sourceTile, Index targetTile) {
        if (sourceTile == targetTile || !grid.isIndexValid(sourceTile)
            || !grid.isIndexValid(targetTile))
            return std::stack<Index>{};

        adjacencyList_.generateFrom(grid);
        auto exploredPath = std::vector<Node>{};
        auto nodesToVisit = std::queue<Node>();
        nodesToVisit.push({sourceTile, sourceTile});
        while (!nodesToVisit.empty()) {
            auto node = nodesToVisit.front();
            nodesToVisit.pop();
            bfs(node, targetTile, nodesToVisit, exploredPath);
        }

        reset();
        if (exploredPath.back().index == targetTile) { //Found target
            auto path = std::stack<Index>{};
            backtrack(exploredPath, path);
            return path;
        } else
            return std::stack<Index>{};
    }

    void BFSPathFinder::reset() {
        for (auto i = 0; i < visited_.size(); i++) {
            for (auto j = 0; j < visited_[0].size(); j++)
                visited_[i][j] = false;
        }
    }

    void BFSPathFinder::bfs(Node source, Index target, std::queue<Node> &nodeToVisit, std::vector<Node> &exploredNodes) {
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

    std::string BFSPathFinder::getType() const {
        return "BFS";
    }
}