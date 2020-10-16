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

    std::vector<Index> BFSPathFinder::findPath(TileMap& grid, Index sourceTile, Index targetTile) {
        if (sourceTile == targetTile)
            return std::vector<Index>{};
        adjacencyList_.generateFrom(grid);
        auto exploredPath = std::vector<Node>{};
        auto nodeToVisit = std::queue<Node>(); //Keeps a list of nodes to be visited
        nodeToVisit.push({sourceTile, sourceTile});
        while (!nodeToVisit.empty()) {
            auto node = nodeToVisit.front();
            nodeToVisit.pop();
            bfs(node, targetTile, nodeToVisit, exploredPath);
        }

        reset();
        if (exploredPath.back().index == targetTile) { //Found target
            auto path = std::vector<Index>{};
            backtrack(exploredPath, path);
            return path;
        } else
            return std::vector<Index>{};
    }

    void BFSPathFinder::reset() {
        for (auto i = 0; i < visited_.size(); i++) {
            for (auto j = 0; j < visited_[0].size(); j++)
                visited_[i][j] = false;
        }
    }

    void BFSPathFinder::bfs(Node source, Index target, std::queue<Node> &nodeToVisit, std::vector<Node> &exploredNodes) {
        if (visited_.at(source.index.row).at(source.index.colm)) //Don't explore a node more than twice
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

    void BFSPathFinder::backtrack(const std::vector<Node> &exploredNodes, std::vector<Index>& path) {
        path.push_back(exploredNodes.back().index);
        auto tileParent = exploredNodes.back().parent;
        for (auto i = exploredNodes.size() - 2; i > 0; i--) { //-2 because we already saved the last node
            if (exploredNodes[i].index == tileParent) {
                path.push_back(exploredNodes[i].index);
                tileParent = exploredNodes.at(i).parent;
            }
        }
        std::reverse(path.begin(), path.end());
    }
}