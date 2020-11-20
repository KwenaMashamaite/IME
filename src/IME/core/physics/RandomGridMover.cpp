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

#include "IME/core/physics/RandomGridMover.h"
#include "IME/utility/Utils.h"

namespace IME {
    RandomGridMover::RandomGridMover(TileMap &tileMap, RandomGridMover::EntityPtr target)
        : gridMover_(tileMap, target), prevDirection_(Direction::None), movementStarted_{false}
    {
        gridMover_.onTargetChanged([this](EntityPtr target) {
            if (target) {
                movementStarted_ = true;
                generateNewDirection();
            } else
                movementStarted_ = false;
        });

        gridMover_.onObstacleCollision([this](auto target, auto obstacle) {
            if (target && movementStarted_) {
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
        if (!gridMover_.getTarget())
            return;

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