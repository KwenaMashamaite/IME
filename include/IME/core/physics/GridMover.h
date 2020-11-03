/**
 * @brief Class to perform grid based movement on an entity in a grid
 *
 * This class monitors the movement of an entity in a grid and ensures that
 * it always moves from one cell to the next and never between grid cells.
 * The entities direction cannot be changed until it has completed it current
 * movement
 */

#ifndef GRIDMOVER_H
#define GRIDMOVER_H

#include "IME/core/tilemap/TileMap.h"
#include "IME/core/entity/Entity.h"
#include "IME/core/event/EventEmitter.h"

namespace IME {
    class GridMover {
    public:
        using EntityPtr = std::shared_ptr<Entity>;
        /**
         * @brief Create a grid mover object
         * @param tileMap Grid to move a target entity in
         * @param target Entity to be moved in the grid
         *
         * The target must be placed in the grid prior to grid mover construction
         */
        GridMover(TileMap &tileMap, EntityPtr target);

        /**
         * @brief Change the direction of the target entity
         * @param newDir The new direction of the target
         * @return True if the direction was changed, otherwise false
         *
         * The direction cannot be changed while the entity is moving to another
         * tile. This function does not remember any direction change requests
         * that were made while the entity was moving. This function must be
         * called even if the entity is to be moved in its current direction
         * as motion is triggered by a target direction change @see update()
         */
        bool requestDirectionChange(Direction newDir);

        /**
         * @brief Change the controlled entity
         * @param target New target
         *
         * Set to nullptr to remove the target from the grid mover
         */
        void setTarget(EntityPtr target);

        /**
         * @brief Get access to the controlled entity
         * @return The controlled entity, or a nullptr if there is no entity to
         *         control
         */
        EntityPtr getTarget() const;

        /**
         * @brief Update entity movement in the grid
         * @param deltaTime Time passed since movement was last updated
         *
         * The target can only move one tile at a time. After the entity moves
         * to the target tile it stops moving until instructed to move again and
         * its target direction is set to None. Therefore if the entity is to be
         * moved multiple tiles, the request to change direction must be made
         * immediately after the target reaches its destination
         * @see onDestinationReached() and requestDirectionChange()
         */
        void update(float deltaTime);

        /**
         * @brief Force the target entity to reach his destination
         */
        void teleportTargetToDestination();

        /**
         * @brief Add an event listener to a grid/tilemap border collision
         * @param callback Function to execute when the target collides with
         *         the borders of the grid/tilemap
         * @return The event listeners identification number
         *
         * @note The target will be prevented from leaving the grid. That is,
         * it will occupy the same tile it occupied before the collision
         */
        int onGridBorderCollision(Callback<> callback);

        /**
         * @brief Add an event listener to a destination reached event
         * @param callback Function to execute when the target reaches its destination
         *
         * The destination is always the adjacent tile in the specified direction.
         * The callback function will be invoked only if the entity starts moving
         * and reaches its destination tile @see update()
         */
        int onDestinationReached(Callback<float, float> callback);

        /**
         * @brief Add an event listener to an obstacle collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with an obstacle tile
         * in the grid. The target will be prevented from occupying the same tile
         * as an obstacle. @warning If a tile is marked as an obstacle and has
         * no obstacle object, the callback will be passed a nullptr for the
         * obstacle object
         */
        int onObstacleCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Add an event listener to a collectable collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a collectable
         * object the grid. This event will be emitted when the target entity
         * and the collectable object occupy the same tile, not when they start
         * colliding with each other
         */
        int onCollectableCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Add an event listener to an enemy collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with an enemy object
         * in the grid. This event will be emitted when the target entity and
         * the enemy object occupy the same tile, not when they start colliding
         * with each other
         */
        int onEnemyCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Add an event listener to a player collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a player object
         * in the grid. This event will be emitted when the target entity and
         * the player object occupy the same tile, not when they start colliding
         * with each other
         */
        int onPlayerCollision(Callback<EntityPtr, EntityPtr> callback);

    private:
        /**
         * @brief Perfectly align target with the target destination
         */
        void snap();

    private:
        //Grid to move entity in
        TileMap& tileMap_;
        //Target to be moved in the grid
        EntityPtr target_;
        //Stores the direction in which the target wishes to go
        Direction targetDirection_;
        //The grid tile the target wishes to reach in the current frame
        Graphics::Tile targetTile_;
        //Collision event publisher
        EventEmitter eventEmitter_;
        //Tracks if controlled entity has reached target tile or not
        bool reachedTarget_;
    };
}

#endif