#include "IME/core/path/BFS.h"
#include <queue>
#include <algorithm>

namespace IME {
    void BFSPathFinder::initialize(TileMap &grid) {
        adjacencyList_.generateFrom(grid);
        for (auto i = 0; i < grid.getSizeInTiles().height; i++) {
            auto innerVector = std::vector<bool>{};
            for (auto j = 0; j < grid.getSizeInTiles().width; j++)
                innerVector.push_back(false);
            visited_.push_back(innerVector);
        }
    }

    std::vector<Index> BFSPathFinder::findPath(Index sourceTile, Index targetTile) {
        if (sourceTile == targetTile)
            return std::vector<Index>{};
        auto exploredPath = std::vector<Node>{};
        auto path = std::vector<Index>{}; //Stores the shortest path to the target
        auto nodeToVisit = std::queue<Node>(); //Keeps a list of nodes to be visited
        nodeToVisit.push({sourceTile, sourceTile});
        while (!nodeToVisit.empty()) {
            auto node = nodeToVisit.front();
            nodeToVisit.pop();
            bfs(node, targetTile, nodeToVisit, exploredPath);
        }

        //Backtracking
        if (exploredPath.back().index == targetTile) { //Found target
            path.push_back(targetTile);
            auto tileParent = exploredPath.back().parent;
            for (auto i = exploredPath.size() - 2; i > 0; i--) { //-2 because we already saved the last node
                if (exploredPath[i].index == tileParent) {
                    path.push_back(exploredPath[i].index);
                    tileParent = exploredPath.at(i).parent;
                }
            }
            std::reverse(path.begin(), path.end());
        } else
            return std::vector<Index>{};

        //Clear flags
        for (auto i = 0; i < visited_.size(); i++) {
            for (auto j = 0; j < visited_[0].size(); j++)
                visited_[i][j] = false;
        }

        return path;
    }

    void BFSPathFinder::bfs(Node source, Index target, std::queue<Node> &nodeToVisit, std::vector<Node> &exploredNodes) {
        if (visited_.at(source.index.row).at(source.index.colm)) //Don't explore a node more than twice
            return;

        if (source.index == target) {
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
}