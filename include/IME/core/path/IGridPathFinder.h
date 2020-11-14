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

/**
 * @brief Interface for grid path finder algorithms
 */

#ifndef IME_GRIDPATHFINDER_H
#define IME_GRIDPATHFINDER_H

#include "IME/Config.h"
#include "IME/core/tilemap/TileMap.h"
#include <stack>

namespace IME {
    class IME_API IGridPathFinder {
    public:
        /**
         * @brief Find a path from a source tile to a target tile in a grid
         * @param gird Grid to find path in
         * @param sourceNode The starting tile
         * @param source The destination tile
         * @return The path from the source to the destination if the destination
         *         is reachable from the source, otherwise an empty vector
         */
        virtual std::stack<Index> findPath(TileMap& grid, Index sourceNode, Index source) = 0;

        /**
         * @brief Get the type of path finding algorithm
         * @return The type of the path finding algorithm
         */
        virtual std::string getType() const = 0;

        /**
         * @brief Destructor
         */
        virtual ~IGridPathFinder() = default;

    protected:
        struct Node {
            Index parent; //Index of this nodes parent in the grid
            Index index; //Position of this node in the grid
        };

        /**
         * @brief Generate path from the source to the target
         * @param exploredNodes Nodes explored before the target was found
         * @param path Vector to populate with path
         * @return The path from the source to the target
         *
         * @warning This function will backtrack from the destination to the
         * source in order to generate the path. As such, it assumes that the
         * last node in the @param exploredNodes container is the target node.
         * Therefore, it must only be called when the target was reached/found
         */
        void backtrack(const std::vector<Node>& exploredNodes, std::stack<Index>& path);
    };
}

#endif
