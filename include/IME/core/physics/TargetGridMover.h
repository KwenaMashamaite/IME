/**
 * @brief Class for moving an entity to a specific position in the grid
 */

#ifndef TARGETGRIDMOVER_H
#define TARGETGRIDMOVER_H

#include "GridMover.h"
#include "IME/core/path/IGridPathFinder.h"

namespace IME {
    class TargetGridMover {
    public:
        using EntityPtr = std::shared_ptr<Entity>;

        /**
         * @brief Create a random grid mover object
         * @param tileMap Grid to target in
         * @param target Entity to be moved in the grid
         *
         * The target must be placed in the grid prior to grid mover construction
         */
        explicit TargetGridMover(TileMap &tileMap, EntityPtr target = nullptr);

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
         * @brief Set the path finder
         * @param pathFinder New path finder
         *
         * The default path finder is Breadth First Search (BFSPathFinder)
         */
        void setPathFinder(std::unique_ptr<IGridPathFinder> pathFinder);

        /**
         * @brief Set the index of the tile the target should go to
         *
         * The specified index must be within the the bounds of the grid and
         * the tile at index must be reachable from the targets current tile,
         * otherwise, the target will not move, since it cannot establish a
         * path to the destination
         */
        void setDestination(Index index);

        /**
         * @brief Get the destination position of the target
         * @return The position that the target must reach
         *
         * This destination will be returned event if the target has reached it
         */
        Index getDestination() const;

        /**
         * @brief Set the position the target should go to
         * @param position New target position
         *
         * The specified position must be within the grid and the tile at that
         * position must be reachable from the targets current tile, otherwise
         * the target will not move since it cannot establish a path to the
         * destination
         */
        void setDestination(Position position);

        /**
         * @brief Resume moving target to the destination tile
         */
        void resumeMovement();

        /**
         * @brief Pause target movement moving the target in the grid
         *
         * If the target was moving prior to function call, it will be
         * teleported to the adjacent tile it was headed towards
         */
        void pauseMovement();

        /**
         * @brief Update the targets movement in the grid
         * @param deltaTime Time passed since targets movement was last updated
         *
         * This function must be called at least once per frame for consistent
         * movement of the target otherwise the target will not move
         */
        void update(float deltaTime);

        /**
         * @brief Add an event listener to an to an adjacent tile reached event
         * @param callback Function to execute when the event is fired
         * @return The identification number of the listener
         *
         * This event is fired as the target moves from one tile to the next.
         * To get notified when the target reaches the final destination
         * @see onDestinationReached()
         */
        int onAdjacentTileReached(Callback<float, float> callback);

        /**
         * @brief Add an event listener to a destination reached event
         * @param callback Function to execute when the target reaches its
         *          destination tile
         *
         * This event is fired when the target reaches the final target tile.
         * To get notified as the target progresses towards the destination
         * #see onAdjacentTileReached()
         */
        int onDestinationReached(Callback<float, float> callback);

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
        //Moves the target in the grid
        GridMover gridMover_;
        //Finds the path from the source to the target
        std::unique_ptr<IGridPathFinder> pathFinder_;
        //Target tile position
        Index targetTile_;
        //Stores the path to the target tile
        std::stack<Index> pathToTargetTile_;
        //Flags whether the target has been stopped or not
        bool targetStopped_;
        //Flags whether the target tile was changed while target in motion
        bool targetTileChangedWhileMoving_;
    };
}

#endif
