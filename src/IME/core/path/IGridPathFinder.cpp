#include "IME/core/path/IGridPathFinder.h"

namespace IME {
    void IGridPathFinder::backtrack(const std::vector<Node> &exploredNodes,
        std::stack<Index> &path)
    {
        path.push(exploredNodes.back().index);
        auto tileParent = exploredNodes.back().parent;
        for (auto i = exploredNodes.size() - 2; i > 0; i--) { //.size() -2 because we already saved the last node
            if (exploredNodes[i].index == tileParent) {
                path.push(exploredNodes[i].index);
                tileParent = exploredNodes.at(i).parent;
            }
        }
    }
}

