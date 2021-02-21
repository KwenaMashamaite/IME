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

#ifndef IME_TARGETGRIDMOVER_H
#define IME_TARGETGRIDMOVER_H

#include "IME/core/physics/tilemap/GridMover.h"
#include "IME/core/path/IGridPathFinder.h"

namespace ime {
    /**
     * @brief Class for moving a game object to a specific position in the grid
     */
    class IME_API TargetGridMover : public GridMover {
    public:
        /**
         * @brief Create a random grid mover object
         * @param tileMap Grid to move target in
         * @param target GameObject to be moved in the grid
         *
         * @warning The tilemap must be loaded before constructing this
         * grid mover
         */
        explicit TargetGridMover(TileMap &tileMap, GameObject::sharedPtr target = nullptr);

        /**
         * @brief Set the path finder
         * @param pathFinder New path finder
         *
         * The default path finder is Breadth First Search
         */
        void setPathFinder(std::unique_ptr<IGridPathFinder> pathFinder);

        /**
         * @brief Set the index of the tile the target should go to
         * @param index The targets new destination
         *
         * The specified index must be within the the bounds of the grid and
         * the tile at index must be reachable from the targets current tile,
         * otherwise, the target will not move, since it cannot establish a
         * path to the destination
         */
        void setDestination(Index index);

        /**
         * @brief Set the position the target should go to
         * @param position New target position
         *
         * The specified position must be within the grid and the tile at that
         * position must be reachable from the targets current tile, otherwise
         * the target will not move since it cannot establish a path to the
         * destination
         */
        void setDestination(Vector2f position);

        /**
         * @brief Get the destination position of the target
         * @return The position that the target must reach
         *
         * This destination will be returned even if the target has reached it
         */
        Index getDestination() const;

        /**
         * @brief Check whether or not a destination is reachable
         * @param index Destination to be checked
         * @return True if the destination is reachable from the targets
         *         current position otherwise false
         *
         * @warning This function is expensive when the tilemap has a lot of
         * accessible tiles because the path is regenerated every time the
         * function is called to accommodate changes in position since the
         * destination was set
         *
         * @see setDestination
         */
        bool isDestinationReachable(Index index);

        /**
         * @brief Start moving the target to its destination tile
         *
         * This function has no effect if the targets movement is not
         * stopped
         *
         * @see stopMovement
         */
        void startMovement();

        /**
         * @brief Stop the targets movement
         *
         * Since a child in the grid can never be in between tiles, the
         * targets movement will be stopped after it completes its current
         * move. The targets movement is stopped by default
         *
         * @see startMovement
         */
        void stopMovement();

        /**
         * @brief Adaptively avoid solid tiles and obstacles
         * @param isAdaptive True to enable, otherwise false
         *
         * When enabled, the target will adaptively avoid collisions with
         * solid tiles and obstacles. The targets path is updated every
         * time it moves from one tile to the next. This makes the target
         * aware of tile state changes as they happen
         *
         * When disabled, the target will continue moving in its current
         * path to the destination until it either collides with something
         * or reaches the destination. The targets path is updated each
         * time the destination changes. Therefore if it remains fixed the
         * target will not know of any tile state changes until it gets to
         * that tile
         *
         * Adaptive movement is disabled by default
         */
        void enableAdaptiveMovement(bool isAdaptive);

        /**
         * @brief Add an event listener to a destination reached event
         * @param callback Function to execute when the target reaches its
         *          destination tile
         * @return The event listeners identification number
         *
         * This event is fired when the target reaches the final target tile
         *
         * The callback is passed the destination tile of the target after it
         * reaches it
         *
         * @see onAdjacentTileReached
         */
        int onDestinationReached(Callback<Tile> callback);

    private:
        /**
         * @brief Generates the targets new direction of motion based on the
         *         next target position
         * @param nextPos The next target position
         */
        void generateNewDirOfMotion(Index nextPos);

        /**
         * @brief Generate path to target
         */
        void generatePath();

        /**
         * @brief Move the target
         */
        void moveTarget();

    private:
        std::unique_ptr<IGridPathFinder> pathFinder_; //!< Finds the path from the source to the target
        Index targetTileIndex_;                       //!< Index of the tile the game object wishes to go to
        std::stack<Index> pathToTargetTile_;          //!< Stores the path from the current tile to the target tile
        bool movementStarted_;                        //!< Flags whether the target has been stopped or not
        bool targetTileChangedWhileMoving_;           //!< Flags whether the target tile was changed while target was in motion
        Callback<> adjacentTileHandler_;              //!< Function executed every time target reaches adjacent tile
    };
}

#endif // IME_TARGETGRIDMOVER_H
