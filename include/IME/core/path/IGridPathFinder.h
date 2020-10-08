/**
 * @brief Interface for grid path finder algorithms
 */

#ifndef GRIDPATHFINDER_H
#define GRIDPATHFINDER_H

#include "IME/core/tilemap/TileMap.h"

namespace IME {
    class IGridPathFinder {
    public:

        /**
         * @brief Find a path from a source tile to a target tile in a grid
         * @param gird Grid to find path for
         * @param sourceNode The starting tile
         * @param source The destination tile
         */
        virtual void findPath(Index sourceNode, Index source) = 0;
    };
}

#endif
