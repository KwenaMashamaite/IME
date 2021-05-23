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

#ifndef IME_BFS_H
#define IME_BFS_H

#include "IPathFinderStrategy.h"
#include "AdjacencyList.h"
#include "IME/common/Vector2.h"
#include <queue>
#include <vector>

namespace ime {
    /**
     * @brief Finds a path in a TileMap using the Breadth First Search algorithm
     */
    class IME_API BFS : public IPathFinderStrategy {
    public:
        /**
         * @brief Initialize the algorithm
         * @param gridSize Size of the grid
         */
        explicit BFS(Vector2u gridSize);

        /**
         * @brief Generate a path from a source tile to a target tile in a grid
         * @param grid Grid to generate path in
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
         * @brief Finds the target using bfs algorithm
         * @param source The starting position
         * @param target The destination
         * @param nodeToVisit Container to store nodes that must be visited on
         *                    the next run
         * @param exploredNodes A vector to stores nodes that have been visited
         */
        void bfs(Node source, Index target, std::queue<Node>& nodeToVisit,
             std::vector<Node>& exploredNodes);

        /**
         * @brief Set all visited nodes as not visited
         */
        void reset();

    private:
        AdjacencyList adjacencyList_;            //!< Stores a list of adjacent nodes for each accessible node in the grid
        std::vector<std::vector<bool>> visited_; //!< Vector storing the visited state of a node
    };
}

#endif // IME_BFS_H
