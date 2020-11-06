#include "IME/core/physics/RandomGridMover.h"
#include "IME/utility/Helpers.h"

namespace IME {
    RandomGridMover::RandomGridMover(TileMap &tileMap, RandomGridMover::EntityPtr target)
        : gridMover_(tileMap, target), prevDirection_(Direction::None), movementStarted_{false}
    {
        gridMover_.onObstacleCollision([this](auto target, auto obstacle) {
            if (movementStarted_) {
                gridMover_.getTarget()->setDirection(prevDirection_);
                generateNewDirection();
            }
        });

        gridMover_.onDestinationReached([this](float x, float y) {
            if (movementStarted_)
                generateNewDirection();
        });

        gridMover_.onGridBorderCollision([this] {
            generateNewDirection();
        });
    }

    void RandomGridMover::setTarget(RandomGridMover::EntityPtr target) {
        gridMover_.setTarget(target);
    }

    RandomGridMover::EntityPtr RandomGridMover::getTarget() const {
        return gridMover_.getTarget();
    }

    void RandomGridMover::startMovement() {
        if (!movementStarted_) {
            movementStarted_ = true;
            generateNewDirection();
        }
    }

    void RandomGridMover::stopMovement() {
        movementStarted_ = false;
    }

    void RandomGridMover::update(float deltaTime) {
        gridMover_.update(deltaTime);
    }

    void RandomGridMover::generateNewDirection() {
        prevDirection_ = gridMover_.getTarget()->getDirection();
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
        gridMover_.requestDirectionChange(newDirection);
    }

    int RandomGridMover::onDestinationReached(Callback<float, float> callback) {
        return gridMover_.onDestinationReached(std::move(callback));
    }

    int RandomGridMover::onObstacleCollision(Callback<RandomGridMover::EntityPtr,
        RandomGridMover::EntityPtr> callback)
    {
        return gridMover_.onObstacleCollision(std::move(callback));
    }

    int RandomGridMover::onCollectableCollision(Callback<RandomGridMover::EntityPtr,
        RandomGridMover::EntityPtr> callback)
    {
        return gridMover_.onCollectableCollision(std::move(callback));
    }

    int RandomGridMover::onEnemyCollision(Callback<RandomGridMover::EntityPtr,
        RandomGridMover::EntityPtr> callback)
    {
        return gridMover_.onEnemyCollision(std::move(callback));
    }

    int RandomGridMover::onPlayerCollision(Callback<RandomGridMover::EntityPtr,
        RandomGridMover::EntityPtr> callback)
    {
        return gridMover_.onPlayerCollision(std::move(callback));
    }
}