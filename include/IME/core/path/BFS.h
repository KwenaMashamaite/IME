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
 * @brief Class for finding the path from a source tile to a destination tile
 *        using the Breadth First Search algorithm
 */

#ifndef BFS_H
#define BFS_H

#include "IGridPathFinder.h"
#include "AdjacencyList.h"
#include <queue>

namespace IME {
    class BFSPathFinder : public IGridPathFinder {
    public:
        /**
         * @brief Initialize the algorithm
         * @param gridSize Size of the grid
         */
        explicit BFSPathFinder(Vector2u gridSize);

        /**
         * @brief Generate a path from a source tile to a target tile in a grid
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
         * @brief Set visited nodes as not visited
         */
        void reset();

    private:
        //A list containing a list of adjacent nodes for each accessible node in the grid
        AdjacencyList adjacencyList_;
        //Vector storing the visited state of a grid node
        std::vector<std::vector<bool>> visited_;
    };
}

#endif
