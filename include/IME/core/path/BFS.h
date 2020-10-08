/**
 * @brief Class for finding the path from a source tile to a destination tile
 *        using the Breadth First Search algorithm
 */

#ifndef BFS_H
#define BFS_H

#include "IGridPathFinder.h"
#include "AdjacencyList.h"
#include <initializer_list>
#include <queue>

namespace IME {
    class BFSPathFinder {
    public:
        /**
         * @brief Initialize the algorithm
         * @param grid Grid to find path in
         *
         * The @see findPath() method will not work if the algorithm is not
         * initialized, The initialization is done only once.
         */
        void initialize(IME::TileMap& grid);

        /**
         * @brief Generate a path from a source tile to a target tile in a grid
         * @param sourceTile The position of the starting position in tiles
         * @param targetTile The position of the destination in tiles
         * @return A vector containing the path from the source to the destination
         *         if reachable, otherwise an empty vector
         */
        std::vector<Index> findPath(Index sourceTile, Index targetTile);

    private:
        struct Node {
            Index parent; //Index of this nodes parent in the grid
            Index index; //Position of this node in the grid
        };

        //A list containing a list of adjacent nodes for each accessible node in the grid
        AdjacencyList adjacencyList_;
        //Vector storing the visited state of a grid node
        std::vector<std::vector<bool>> visited_;

        /**
         * @brief Finds the target using bfs algorithm
         * @param source The starting position
         * @param target The position to be found
         * @param nodeToVisit This vector will be populated with a list of nodes
         * @param exploredNodes A vec
         */
        void bfs(Node source, Index target, std::queue<Node>& nodeToVisit, std::vector<Node>& exploredNodes);
    };
}

#endif
