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

#ifndef IME_GRIDMOVER_H
#define IME_GRIDMOVER_H

#include "IME/Config.h"
#include "IME/core/tilemap/TileMap.h"
#include "IME/core/entity/Entity.h"
#include "IME/core/event/EventEmitter.h"

namespace IME {
    /**
     * @brief Class for performing grid based movement on an entity in a grid
     *
     * This class monitors the movement of an entity in a grid and ensures that
     * it always moves from one cell to the next and never between grid cells.
     * The entities direction cannot be changed until it has completed it's
     * current movement
     */
    class IME_API GridMover {
    public:
        using EntityPtr = std::shared_ptr<Entity>; //!< Shared pointer to Entity alias
        /**
         * @brief Create a grid mover
         * @param tileMap Grid to move a target entity in
         * @param target Entity to be moved in the grid
         *
         * @warning if the target is not a nullptr, then it must be placed
         * in the grid prior to instantiation of this class
         */
        GridMover(TileMap &tileMap, EntityPtr target);

        /**
         * @brief Change the direction of the target entity
         * @param newDir The new direction of the target
         * @return True if the direction was changed or false if the target
         *         is in motion or there is no target at all
         *
         * The direction cannot be changed while the entity is moving to another
         * tile. This function does not remember any direction change requests
         * that were made while the target was moving. This function must be
         * called even if the target is to be moved in its current direction
         * as the target stops moving after reaching its destination
         *
         * @see update
         */
        bool requestDirectionChange(Direction newDir);

        /**
         * @brief Change the controlled entity
         * @param target New target
         *
         * Provide nullptr as argument to remove current target
         *
         * @warning if the target is not a nullptr, then it must exist in
         * the grid prior to function call
         */
        void setTarget(EntityPtr target);

        /**
         * @brief Get access to the controlled entity
         * @return The controlled entity, or a nullptr if there is no entity to
         *         control
         */
        EntityPtr getTarget() const;

        /**
         * @brief Get access to the grid in which the target is moved in
         * @return The grid in which the target is being moved in
         */
        TileMap& getGrid();

        /**
         * @brief Check if target is moving or not
         * @return True if target is moving otherwise false
         *
         * @warning This function will return false if the target is not moving
         * or there is no target set. Therefore, the existence of the
         * target should be checked first for accurate results
         *
         * @see getTarget
         */
        bool isTargetMoving() const;

        /**
         * @brief Update entity movement in the grid
         * @param deltaTime Time passed since movement was last updated
         *
         * The target can only move one tile at a time and cannot be instructed
         * to move to another tile while it is currently moving to one of its
         * adjacent tiles. After it reaching it's target tile it stops moving
         * until instructed to move again. Therefore if the target is to be
         * moved multiple tiles, the request to change direction must be made
         * immediately after the target reaches its destination
         *
         * @see onAdjacentTileReached and requestDirectionChange
         *
         * @warning The target will never move if this function is never called
         */
        virtual void update(float deltaTime);

        /**
         * @brief Force the target to reach it's destination
         *
         * The destination in this context is always the adjacent tile the
         * target is headed towards. This function has no effect if the
         * target is not moving towards any tile
         */
        void teleportTargetToDestination();

        /**
         * @brief Add an event listener to a target change event
         * @param callback Function to execute when the target changes
         * @return The event listeners identification number
         *
         * @warning The callback will be passed the new target which may be a
         * nullptr
         */
        int onTargetChanged(Callback<EntityPtr> callback);

        /**
         * @brief Add an event listener to an adjacent tile reached event
         * @param callback Function to execute when the target reaches its
         *        target tile
         * @return The event listeners identification number
         *
         * This event is emitted when the target moves from its current tile
         * to any of its adjacent tiles.
         *
         * @note When controlled by a grid mover, the target will always move
         * one tile at a time, regardless of how fast the target is moving
         *
         * The callback is passed the tile the target moved to
         */
        int onAdjacentTileReached(Callback<Graphics::Tile> callback);

        /**
         * @brief Add an event listener to a tilemap border collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target tries to go beyond the bounds
         * of the grid. By default the event is handled internally before it's
         * emitted to the outside. The internal handler prevents the target
         * from leaving the grid. That is, the target will occupy the same tile
         * it occupied before the collision. This behaviour is not removable,
         * however, it may be overridden since the internal handler is called
         * first before alerting external handlers
         */
        int onGridBorderCollision(Callback<> callback);

        /**
         * @brief Add an event listener to a tile collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a solid tile
         * in the grid (Solid tiles are always collidable). By default, the
         * event is handled internally before its emitted to the outside. The
         * internal handler prevents the target from occupying the solid tile
         * by moving it back to its previous tile after the collision. This
         * behaviour may be removed if not desired by calling
         * @see removeInternalCollisionHandlerFor() with "solidTiles" as the
         * argument
         *
         * The callback is passed the tile the target collided with
         */
        int onSolidTileCollision(Callback<IME::Graphics::Tile> callback);

        /**
         * @brief Add an event listener to an obstacle collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with an obstacle
         * in the grid. By default the event is handled internally before
         * its emitted to the outside. The internal handler prevents the
         * target from occupying the same tile as the obstacle by moving it
         * back to its previous tile after the collision. This behaviour may
         * be removed if not desired by invoking
         * @see removeInternalCollisionHandlerFor() with "obstacles" as the
         * argument
         *
         * The callback is passed the target as the first argument and the
         * obstacle it collided with as the second argument
         */
        int onObstacleCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Add an event listener to a collectable collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a collectable
         * in the grid. The callback is passed the target as the first argument
         * and the collectable it collided with as the second argument
         */
        int onCollectableCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Add an event listener to an enemy collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with an enemy in the
         * grid. The callback is passed the target as the first argument and
         * the enemy it collided with as the second argument
         */
        int onEnemyCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Add an event listener to a player collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a player in the
         * grid. The callback is passed the target as the first argument and
         * the player it collided with as the second argument
         */
        int onPlayerCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Remove an external collision handler
         * @param handlerId Identification number of the handler
         * @return True if the handler was removed or false if no such handler
         *         exits
         *
         * The identification number is the number returned when a handler
         * is added to a collision event
         */
        bool removeCollisionHandler(int handlerId);

        /**
         * @brief Remove the internal handler for a given collision event
         * @param handler Name of the handler to remove
         * @return True if the handler was removed or false if no such handler
         *         exists
         */
        bool removeInternalCollisionHandlerFor(const std::string& handler);

        /**
         * @brief Check if the internal collision handler is removed or not
         * @param handler Name of the handler to check
         * @return True if the handler is removed, otherwise false
         */
        bool isInternalHandlerRemoved(const std::string& handler);

        /**
         * @brief Destructor
         */
        virtual ~GridMover() = default;

    protected:
        /**
         * @brief Execute a callback when an internal handler is removed
         * @param callback Function to execute
         *
         * This event is useful if derived classes rely on the internal
         * collision handler behavior because they can adapt themselves
         * when the handler is removed.
         *
         * The callback is passed the name of the handler that got removed
         */
        void onInternalHandlerRemove(Callback<std::string> callback);

    private:
        /**
         * @brief Set the targets target tile
         */
        void setTargetTile();

        /**
         * @brief Check for a solid tile collision and handle if it occurs
         * @return True if the collision was handled, otherwise false
         *
         * The collision is only handled if the internal solid tile handler
         * is not removed
         */
        bool handleSolidTileCollision();

        /**
         * @brief Check for a grid border collision and handle if it occurs
         * @return True if the collision was handled, otherwise false
         */
        bool handleGridBorderCollision();

        /**
         * @brief Stop target and notify event listeners
         */
        void onDestinationReached();

        /**
         * @brief Check if the target tile has any obstacle objects or not
         * @return A pair, of which the first element is a bool that is true if
         *         the target tile is occupied by an obstacle, otherwise false
         *         and the second is a pointer to the first encountered obstacle
         *         in the target tile or a nullptr if the first element is false
         */
        std::pair<bool, EntityPtr> targetTileHasObstacle();

        /**
         * @brief Perfectly align target with the target destination
         */
        void snapTargetToTargetTile();

    private:
        TileMap& tileMap_;                     //!< Grid to move entity in
        EntityPtr target_;                     //!< Target to be moved in the grid
        Direction targetDirection_;            //!< Stores the direction in which the target wishes to go
        Graphics::Tile targetTile_;            //!< The grid tile the target wishes to reach
        Graphics::Tile prevTile_;              //!< Tile target was in before moving to adjacent tile
        EventEmitter eventEmitter_;            //!< Collision event publisher
        bool reachedTarget_;                   //!< Tracks if controlled entity has reached target tile or not
        Callback<> obstacleCollisionHandler_;  //!< Function called when targets collides with an obstacle
        Callback<> solidTileCollisionHandler_; //!< Function called when a target collides with a solid tile
    };
}

#endif // IME_GRIDMOVER_H
