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
        explicit BFSPathFinder(Dimensions gridSize);

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
