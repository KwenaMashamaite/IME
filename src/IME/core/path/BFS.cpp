#include "IME/core/path/BFS.h"
#include <algorithm>

namespace IME {
    BFSPathFinder::BFSPathFinder(Dimensions gridSize) {
        for (auto i = 0; i < gridSize.height; i++) {
            auto innerVector = std::vector<bool>{};
            for (auto j = 0; j < gridSize.width; j++)
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