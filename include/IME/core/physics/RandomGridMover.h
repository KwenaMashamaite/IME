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

/**
 * @brief Class for moving an entity randomly in a grid/tilemap
 */

#ifndef RANDOMGRIDMOVER_H
#define RANDOMGRIDMOVER_H

#include "GridMover.h"

namespace IME {
    class RandomGridMover {
    public:
        using EntityPtr = std::shared_ptr<Entity>;
        /**
         * @brief Create a random grid mover object
         * @param tileMap Grid to target in
         * @param target Entity to be moved in the grid
         *
         * The target must be placed in the grid prior to grid mover construction
         */
        explicit RandomGridMover(TileMap &tileMap, EntityPtr target = nullptr);

        /**
         * @brief Change the controlled entity
         * @param target New target
         *
         * Set to nullptr to remove the target from the grid mover
         */
        void setTarget(EntityPtr target);

        /**
         * @brief Get access to the controlled entity
         * @return The controlled entity, or a nullptr if there is no entity
         *         to control
         */
        EntityPtr getTarget() const;

        /**
         * @brief Start moving the target in the grid
         *
         * This function will move the target if it hasn't been moved for the
         * first time or the movement was stopped @see stopMovement()
         */
        void startMovement();

        /**
         * @brief Stop moving the target in the grid
         *
         * If the target was moving prior to function call, it will be
         * teleported to it's destination
         */
        void stopMovement();

        /**
         * @brief Update the targets movement in the grid
         * @param deltaTime Time passed since targets movement was last updated
         *
         * This function must be called at least once per frame for consistent
         * movement of the target otherwise the target will not move
         */
        void update(float deltaTime);

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
         * This event is emitted when the target collides with an obstacle object
         * in the grid. The target will be prevented from occupying the same tile
         * as an obstacle
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
         * @brief Generate the targets new direction of motion
         */
        void generateNewDirection();

    private:
        //Moves the target in the grid
        GridMover gridMover_;
        //Keeps track of the targets prev direction
        Direction prevDirection_;
        //Tracks whether the target movement has been initiated or not
        bool movementStarted_;
    };
}

#endif
