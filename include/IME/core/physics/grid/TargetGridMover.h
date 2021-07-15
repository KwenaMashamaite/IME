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

#include "IME/core/physics/grid/GridMover.h"
#include "IME/core/physics/grid/path/IPathFinderStrategy.h"

namespace ime {

    /// @internal
    namespace priv {
        class RenderTarget;
    }

    /**
     * @brief Class for moving a game object to a specific position in the grid
     */
    class IME_API TargetGridMover : public GridMover {
    public:
        using Ptr = std::unique_ptr<TargetGridMover>; //!< Unique grid mover pointer

        /**
         * @brief Create a random grid mover object
         * @param tileMap Grid to move target in
         * @param target GameObject to be moved in the grid
         *
         * @warning The tilemap must be loaded before constructing this
         * grid mover
         */
        explicit TargetGridMover(TileMap &tileMap, GameObject* target = nullptr);

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Set the path finder
         * @param pathFinder New path finder
         *
         * The default path finder is Breadth First Search
         */
        void setPathFinder(std::unique_ptr<IPathFinderStrategy> pathFinder);

        /**
         * @brief Set the index of the tile the target should go to
         * @param index The targets new destination
         *
         * The specified index must be within the the bounds of the grid and
         * the tile at index must be reachable from the targets current tile,
         * otherwise, the target will not move, since it cannot establish a
         * path to the destination
         *
         * @see getDestination, getPath and onPathGenFinish
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
         *
         * @see getDestination, getPath and onPathGenFinish
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
         * @brief Reset the destination tile to a tile outside the bounds of the grid
         *
         * @note This function will clear the current path. To clear the path
         * without resetting the destination tile see clearPath() function
         */
        void resetDestination();

        /**
         * @brief Get the path of the target
         * @return The path of the target
         */
        const std::stack<Index>& getPath() const;

        /**
         * @brief Clear the current path of the target
         *
         * If the target is currently en route on this path, it will stop
         * when it gets to its currently targeted adjacent tile. In addition,
         * if the targets movement was stopped while he was moving to an
         * adjacent tile and is resumed after the path is cleared the target
         * will resume the move to an adjacent tile and stop thereafter
         */
        void clearPath();

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
         * @brief Enable or disable adaptive movement
         * @param enable True to enable, otherwise false
         *
         * This function affects how the target behaves when its current path
         * to a destination tile is blocked by a solid tile or an obstacle.
         *
         * When smart move is enabled, the target immediately attempts to find
         * another path to its destination, in other words it can see ahead.
         * When smart move is disabled the target will continue to move along
         * the blocked path until it gets to the roadblock. Only then will it
         * attempt to find another path
         *
         * Note that if the grid is static, its advised to keep adaptive move
         * disabled for performance reasons
         *
         * By default, adaptive movement is disabled
         */
        void setAdaptiveMoveEnable(bool enable);

        /**
         * @brief Check if adaptive movement is enabled or not
         * @return True if enabled, otherwise false
         *
         * @see setAdaptiveMoveEnable
         */
        bool isAdaptiveMoveEnabled() const;

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
         * @see onAdjacentMoveEnd
         */
        int onDestinationReached(Callback<Index> callback);

        /**
         * @brief Set whether or not the targets path should be shown or not
         * @param showPath True to show path, otherwise false
         *
         * By default, the path is not shown
         */
        void setPathViewEnable(bool showPath);

        /**
         * @brief Check if the targets path is shown or not
         * @return True if path view is enabled, otherwise false
         *
         * @see setPathViewEnable
         */
        bool isPathViewEnabled() const;

        /**
         * @brief Add an event listener to a path generation finish event
         * @param callback The callback to be executed when the event is raised
         *
         * The path generation event is triggered when the targets destination
         * is set. If the target is currently not moving, the event will be
         * triggered immediately. However, if the target is moving, the event
         * will be triggered the next time the path is generated
         *
         * On invocation the callback is passed the generated path (which may
         * be empty - see setDestination()). Note that, only one event listener
         * may be registered to this event at a time. To remove the event
         * listener, pass @a nullptr as the argument
         *
         * @see setPathFinder and setDestination
         */
        void onPathGenFinish(const Callback<const std::stack<Index>&>& callback);

        /**
         * @internal
         * @brief Render the targets path
         * @param window Window to render path on
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void renderPath(priv::RenderTarget& window) const;

        /**
         * @brief Destructor
         */
        ~TargetGridMover() override;

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
        std::unique_ptr<IPathFinderStrategy> pathFinder_; //!< Finds the path from the source to the target
        Index targetTileIndex_;                           //!< Index of the tile the game object wishes to go to
        std::stack<Index> pathToTargetTile_;              //!< Stores the path from the current tile to the target tile
        Colour pathColour_;                               //!< The colour of the targets path when rendered
        bool renderPath_;                                 //!< A flag indicating whether or not to render the targets path
        bool movementStarted_;                            //!< Flags whether the target has been stopped or not
        bool targetTileChangedWhileMoving_;               //!< Flags whether the target tile was changed while target was in motion
        bool isAdaptiveMoveEnabled_;                      //!< A flag indicating whether or not adaptive movement is enabled
        Callback<const std::stack<Index>&> onPathGen_;    //!< A function executed after path generation
    };
}

#endif // IME_TARGETGRIDMOVER_H
