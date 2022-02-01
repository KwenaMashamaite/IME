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

#ifndef IME_ADJACENCYLIST_H
#define IME_ADJACENCYLIST_H

#include "IME/Config.h"
#include "IME/core/grid/Index.h"
#include <vector>

namespace ime {
    class Grid2D;

    /**
     * @brief Construct a list of neighbours for each accessible node/cell
     *        in a grid
     *
     * An accessible node is one that does not contain an obstacle and it is
     * not a solid tile
     */
    class IME_API AdjacencyList {
    public:
        /**
         * @brief Generate adjacency list from a grid
         * @param grid grid to generate adjacency list for
         *
         * This function will generate a list of neighbouring tiles for
         * each node/tile in the grid. This functions assumes that the
         * grid nodes are bidirectional
         */
        void generateFrom(const Grid2D& grid);

        /**
         * @brief Get the neighbours of a node at a certain position in the grid
         * @param index Location of the tile to get the neighbours of
         * @return The tiles neighbours or an empty vector if the index is
         *         invalid
         */
        const std::vector<Index>& getNeighbours(const Index& index) const;

    private:
        std::vector<std::pair<Index, std::vector<Index>>> adjacencyList_; //!< Adjacency list data
        const std::vector<Index> emptyVec{};                              //!< Dummy vector
    };
}

#endif // IME_ADJACENCYLIST_H
