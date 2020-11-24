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
    RandomGridMover::RandomGridMover(TileMap &tileMap, RandomGridMover::EntityPtr target) :
        GridMover(tileMap, target), prevDirection_(Direction::None),
        obstacleHandlerId_{-1},
        solidTileHandlerId_{-1},
        movementStarted_{false}
    {
        onTargetChanged([this](EntityPtr target) {
            if (target) {
                movementStarted_ = true;
                generateNewDirection();
            } else
                movementStarted_ = false;
        });

        solidTileHandlerId_ = onSolidTileCollision([this](Graphics::Tile tile) {
            revertAndGenerateDirection();
        });

        obstacleHandlerId_ = onObstacleCollision([this](auto, auto) {
            revertAndGenerateDirection();
        });

        onAdjacentTileReached([this](Graphics::Tile) {
            if (movementStarted_)
                generateNewDirection();
        });

        onGridBorderCollision([this] {
            generateNewDirection();
        });

        onInternalHandlerRemove([this](std::string handler) {
            if (handler == "solidTiles")
                removeCollisionHandler(solidTileHandlerId_);
            else if (handler == "obstacles")
                removeCollisionHandler(obstacleHandlerId_);
        });
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

    void RandomGridMover::generateNewDirection() {
        if (!getTarget())
            return;

        prevDirection_ = getTarget()->getDirection();
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
        requestDirectionChange(newDirection);
    }

    void RandomGridMover::revertAndGenerateDirection() {
        if (getTarget() && movementStarted_) {
            getTarget()->setDirection(prevDirection_);
            generateNewDirection();
        }
    }
}