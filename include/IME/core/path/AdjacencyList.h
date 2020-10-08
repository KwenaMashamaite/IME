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
        std::vector<Index> getNeighbours(const Index& index) const;

    private:
        using AdjList = std::vector<std::pair<Index, std::vector<Index>>>;
        /**
         * @brief Generate an adjacency list for a tile map
         * @param tileMap Tilemap to generate adjacency list for
         * @return The generated adjacency list
         */
         AdjList generateAdjacencyList(TileMap &tileMap);

    private:
        //Adjacency list data
        AdjList adjacencyList_;
    };
}

#endif
