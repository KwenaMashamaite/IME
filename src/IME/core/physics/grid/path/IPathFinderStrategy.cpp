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

#include "IME/core/physics/grid/path/IPathFinderStrategy.h"

namespace ime {
    std::stack<Index> IPathFinderStrategy::backtrack(const std::vector<Node> &exploredNodes, const Index& targetTile)
    {
        if (exploredNodes.back().index != targetTile) //Target tile not found
            return std::stack<Index>{};

        std::stack<Index> path;
        path.push(exploredNodes.back().index);
        Index tileParent = exploredNodes.back().parent;

        for (auto i = exploredNodes.size() - 2; i > 0; i--) { //.size() -2 because we already saved the last node
            if (exploredNodes[i].index == tileParent) {
                path.push(exploredNodes[i].index);
                tileParent = exploredNodes.at(i).parent;
            }
        }

        return path;
    }
}

