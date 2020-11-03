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

        /**
         * @brief Get the type of path finding algorithm
         * @return The type of the path finding algorithm
         */
        virtual std::string getType() const = 0;

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
