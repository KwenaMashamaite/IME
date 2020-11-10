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
 * @brief Construct a list of neighbours for each accessible node/cell in a grid
 *
 * An accessible node is one that is not an obstacle
 */

#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include "IME/core/tilemap/TileMap.h"

namespace IME {
    class AdjacencyList {
    public:
        /**
         * @brief Generate adjacency list from a tilemap
         * @param tilemap Tilemap to generate adjacency list for
         *
         * This function will generate a list of neighbouring tiles for each node
         * in the tilemap. This functions assumes that the grid nodes are bidirectional
         */
        void generateFrom(TileMap& tilemap);

        /**
         * @brief Get the neighbours of a node at a certain position in the grid
         * @param index Location of the tile to get the neighbours of
         * @return The tiles neighbours or an empty vector if the index is invalid
         */
        const std::vector<Index>& getNeighbours(const Index& index) const;

    private:
        //Adjacency list data
        std::vector<std::pair<Index, std::vector<Index>>> adjacencyList_;
        //An empty vector
        const std::vector<Index> emptyVec{};
    };
}

#endif
