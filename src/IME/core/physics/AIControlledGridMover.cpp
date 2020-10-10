#include "IME/core/physics/AIControlledGridMover.h"
#include "IME/utility/Helpers.h"
#include "IME/core/entity/IMovable.h"

namespace IME {
    AIControlledGridMover::AIControlledGridMover(std::shared_ptr<GridMover> gridMover,
            TileMap& grid, std::shared_ptr<Entity> target)
         : gridMover_(std::move(gridMover)), grid_(grid), controlledEntity_(target),
           pathFinder_(grid.getSizeInTiles()),
           prevDirection_(target->getDirection()),
           movementType_(MovementType::None)
    {
        gridMover_->onDestinationReached([this](float x, float y) {
            if (movementType_ == MovementType::Random)
                generateNewDirOfMotion();
            else if (movementType_ == MovementType::TargetEntity && target_) {
                auto pathToPlayer = pathFinder_.findPath(grid_,
                    grid_.getTile(Position{x, y}).getIndex(), grid_.getTile(target_->getPosition()).getIndex());
                if (!pathToPlayer.empty())
                    generateNewDirOfMotion(pathToPlayer.front());
            }
        });

        gridMover_->onObstacleCollision([this](auto target, auto obstacle) {
            controlledEntity_->setDirection(prevDirection_);
            generateNewDirOfMotion();
        });
        gridMover_->requestDirectionChange(Direction::Left);
    }

    void AIControlledGridMover::setMovementType(MovementType movementType,
            std::shared_ptr<Entity> target) {
        if (movementType == MovementType::TargetEntity) {
            if (target)
                target_ = std::move(target);
            else {
                movementType_ = MovementType::None;
                return;
            }
        } else
            target_ = nullptr;

        movementType_ = movementType;
    }

    void AIControlledGridMover::generateNewDirOfMotion(Index nextPos) {
        prevDirection_ = controlledEntity_->getDirection();
        auto newDirection = Direction::None;
        auto currentPosIndex = grid_.getTile(controlledEntity_->getPosition()).getIndex();
        if (Index{currentPosIndex.row, currentPosIndex.colm + 1} == nextPos)
            newDirection = Direction::Right;
        else if (Index{currentPosIndex.row, currentPosIndex.colm - 1} == nextPos)
            newDirection = Direction::Left;
        else if (Index{currentPosIndex.row - 1, currentPosIndex.colm} == nextPos)
            newDirection = Direction::Up;
        else if (Index{currentPosIndex.row + 1, currentPosIndex.colm} == nextPos)
            newDirection = Direction::Down;
        else
            newDirection = Direction::None;
        gridMover_->requestDirectionChange(newDirection);
    }

    void AIControlledGridMover::generateNewDirOfMotion() {
        prevDirection_ = controlledEntity_->getDirection();
        auto newDirection = Direction::None;
        auto oppositeDirection = Direction::None;

        if (prevDirection_ == Direction::Left)
            oppositeDirection = Direction::Right;
        else if (prevDirection_ == Direction::Right)
            oppositeDirection = Direction::Left;
        else if (prevDirection_ == Direction::Up)
            oppositeDirection = Direction::Down;
        else if (prevDirection_ == Direction::Down)
            oppositeDirection = Direction::Up;

        do {
            newDirection = static_cast<Direction>(Utility::generateRandomNum(1, 4));
        } while (newDirection == oppositeDirection);
        gridMover_->requestDirectionChange(newDirection);
    }

    void AIControlledGridMover::update(float deltaTime) {
        gridMover_->update(deltaTime);
        if (!std::dynamic_pointer_cast<IMovable>(controlledEntity_)->isMoving()) {
            if (movementType_ == MovementType::Random)
                generateNewDirOfMotion();
            else if (movementType_ == MovementType::TargetEntity) {
                auto pathToPlayer = pathFinder_.findPath(grid_,
                     grid_.getTile(controlledEntity_->getPosition()).getIndex(),
                     grid_.getTile(target_->getPosition()).getIndex());
                if (!pathToPlayer.empty())
                    generateNewDirOfMotion(pathToPlayer.front());
            }
        }
    }

    void AIControlledGridMover::teleportTargetToDestination() {
        gridMover_->teleportTargetToDestination();
    }
}
