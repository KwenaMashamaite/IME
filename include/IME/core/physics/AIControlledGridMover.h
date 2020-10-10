/**
 * @brief This class controls the movement of an entity in a grid using a
 *        a specified movement type.
 */

#ifndef AICONTROLLEDGRIDMOVER_H
#define AICONTROLLEDGRIDMOVER_H

#include "IME/core/entity/Entity.h"
#include "IME/core/path/BFS.h"
#include "GridMover.h"

namespace IME {
    enum class MovementType {
        None,
        Random,
        TargetEntity,
    };

    class AIControlledGridMover {
    public:
        /**
         * @brief Constructor
         * @param gridMover Moves entity in a grid
         * @param target Entity to control in the grid
         */
        AIControlledGridMover(std::shared_ptr<GridMover> gridMover, TileMap& grid,
              std::shared_ptr<Entity> target);

        /**
         * @brief Set how the target moves in the grid
         * @param movementType The type of movement to set
         * @param target Entity to be targeted when the movement type is TargetEntity
         *
         * @note The second argument must only be specified when the movement type
         * is MovementType::TargetEntity. If the second argument is not provided
         * or is a nullptr when the specified movement type is MovementType::TargetEntity
         * then the movement type will be set to MovementType::None
         */
        void setMovementType(MovementType movementType, std::shared_ptr<Entity> target = nullptr);

        /**
         * @brief Update the target entities movement in the grid
         * @param deltaTime Time passed since entity movement was last updated
         */
        void update(float deltaTime);

        /**
         * @brief Teleports the entity to its target destination
         */
        void teleportTargetToDestination();

    private:
        /**
         * @brief Generates the targets new direction of motion based on the
         *         next target position
         * @param nextPos The next target position
         */
        void generateNewDirOfMotion(Index nextPos);

        /**
         * @brief Generates the targets new direction of motion
         */
        void generateNewDirOfMotion();

    private:
        //Moves entity in the grid
        std::shared_ptr<GridMover> gridMover_;
        //Grid
        TileMap& grid_;
        //Entity to be controlled
        std::shared_ptr<Entity> controlledEntity_;
        //Entity to be targeted when movement type is set to target
        std::shared_ptr<Entity> target_;
        //AI Path finder
        BFSPathFinder pathFinder_;
        //Keeps track of the entities direction before moving
        Direction prevDirection_;
        //The entity's movement type
        MovementType movementType_;
    };
}

#endif
