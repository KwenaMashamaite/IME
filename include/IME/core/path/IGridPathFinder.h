/**
 * @brief Interface for grid path finder algorithms
 */

#ifndef GRIDPATHFINDER_H
#define GRIDPATHFINDER_H

#include "IME/core/tilemap/TileMap.h"
#include <stack>

namespace IME {
    class IGridPathFinder {
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
    };
}

#endif
