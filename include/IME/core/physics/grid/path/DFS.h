////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_DFS_H
#define IME_DFS_H

#include "IPathFinderStrategy.h"
#include "AdjacencyList.h"
#include "IME/common/Vector2.h"

namespace ime {
    /**
     * @brief Finds a path in a TileMap using the Depth First Search algorithm
     */
    class IME_API DFS : public IPathFinderStrategy {
    public:
        /**
         * @brief Initialize the algorithm
         * @param gridSize Size of the grid
         */
        explicit DFS(Vector2u gridSize);

        /**
         * @brief Generate a path from a source tile to a target tile in a grid
         * @param grid Grid to find path in
         * @param sourceTile The position of the starting position in tiles
         * @param targetTile The position of the destination in tiles
         * @return The path from the source to the destination if reachable,
         *         otherwise an empty path
         */
        std::stack<Index> findPath(TileMap& grid, Index sourceTile,
            Index targetTile) override;

        /**
         * @brief Get the type of path finding algorithm
         * @return The type of the path finding algorithm
         */
        std::string getType() const override;

    private:
        /**
         * @brief Set all visited nodes as not visited
         */
        void reset();

    private:
        AdjacencyList adjacencyList_;            //!< Stores a list of adjacent nodes for each accessible node in the grid
        std::vector<std::vector<bool>> visited_; //!< Vector storing the visited state of a node
    };
}

#endif // IME_DFS_H
