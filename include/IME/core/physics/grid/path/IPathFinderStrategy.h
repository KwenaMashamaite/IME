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

#ifndef IME_GRIDPATHFINDER_H
#define IME_GRIDPATHFINDER_H

#include "IME/Config.h"
#include "IME/core/grid/Index.h"
#include <stack>
#include <string>

namespace ime {
    class Grid2D;

    /**
     * @brief Interface for grid path finder algorithms
     */
    class IME_API IPathFinderStrategy {
    public:
        /**
         * @brief Find a path from a source tile to a target tile in a grid
         * @param grid Grid to find path in
         * @param sourceNode The starting tile
         * @param source The destination tile
         * @return The path from the source to the destination if the
         *         destination is reachable from the source, otherwise
         *         an empty path
         */
        virtual std::stack<Index> findPath(const Grid2D& grid, const Index& sourceNode,
            const Index& source) = 0;

        /**
         * @brief Get the type of path finding algorithm
         * @return The type of the path finding algorithm
         */
        virtual std::string getType() const = 0;

        /**
         * @brief Destructor
         */
        virtual ~IPathFinderStrategy() = default;

    protected:
        /**
         * @brief A node in the grid
         */
        struct Node {
            Index parent; //!< Index of this nodes parent in the grid
            Index index;  //!< Position of this node in the grid
        };

        /**
         * @brief Generate path from the source to the target
         * @param exploredNodes Nodes explored after algorithm termination
         * @param target The index of the target tile in the grid
         * @return The path from the source to the target tile if found,
         *         otherwise an empty path
         */
        std::stack<Index> backtrack(const std::vector<Node>& exploredNodes, const Index& target);
    };
}

#endif
