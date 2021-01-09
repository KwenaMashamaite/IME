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

#include "IME/core/physics/RandomGridMover.h"
#include "IME/utility/Utils.h"

namespace ime {
    RandomGridMover::RandomGridMover(TileMap &tileMap, RandomGridMover::EntityPtr target) :
        GridMover(tileMap, target),
        prevDirection_(Direction::Unknown),
        movementStarted_{false},
        isAdvance_{false},
        switchToAdvanced_{false},
        switchToNormal_{false},
        targetGridMover_(tileMap, target)
    {
        onTargetChanged([this](EntityPtr newTarget) {
            if (newTarget) {
                prevDirection_ = newTarget->getDirection();
                if (movementStarted_)
                    generateNewDirection();
            }
            targetGridMover_.setTarget(newTarget);
        });

        onSolidTileCollision([this](Tile) {
            revertAndGenerateDirection();
        });

        onObstacleCollision([this](EntityPtr, EntityPtr) {
            revertAndGenerateDirection();
        });

        onAdjacentTileReached([this](Tile) {
            if (!isAdvance_ && switchToAdvanced_) {
                switchToAdvanced_ = false;
                isAdvance_ = true;
                targetGridMover_.resetTargetTile();
                setRandomPosition();
                targetGridMover_.startMovement();
            } else if (movementStarted_ && !isAdvance_) {
                resetTargetTile();
                generateNewDirection();
            }
        });

        onGridBorderCollision([this] {
            revertAndGenerateDirection();
        });

        targetGridMover_.onDestinationReached([this](Tile) {
            setRandomPosition();
        });

        targetGridMover_.onAdjacentTileReached([this](Tile) {
            if (isAdvance_ && switchToNormal_) {
                switchToNormal_ = false;
                isAdvance_ = false;
                resetTargetTile();
                if (movementStarted_)
                    generateNewDirection();
            }
        });

        enableAdvancedMovement(false);
    }

    void RandomGridMover::startMovement() {
        if (!movementStarted_) {
            movementStarted_ = true;
            if (isAdvance_)
                targetGridMover_.startMovement();
            else
                generateNewDirection();
        }
    }

    void RandomGridMover::stopMovement() {
        movementStarted_ = false;
        if (isAdvance_)
            targetGridMover_.stopMovement();
    }

    void RandomGridMover::generateNewDirection() {
        if (!getTarget())
            return;

        prevDirection_ = getTarget()->getDirection();
        auto newDirection = Direction::Unknown;
        auto oppositeDirection = Direction::Unknown;

        if (prevDirection_ == Direction::Left)
            oppositeDirection = Direction::Right;
        else if (prevDirection_ == Direction::Right)
            oppositeDirection = Direction::Left;
        else if (prevDirection_ == Direction::Up)
            oppositeDirection = Direction::Down;
        else if (prevDirection_ == Direction::Down)
            oppositeDirection = Direction::Up;

        do {
            static auto gen_random_num_between_1_and_4 = utility::createRandomNumGenerator(1, 4);
            newDirection = static_cast<Direction>(gen_random_num_between_1_and_4());
        } while (newDirection == oppositeDirection);
        requestDirectionChange(newDirection);
    }

    void RandomGridMover::revertAndGenerateDirection() {
        if (getTarget()) {
            getTarget()->setDirection(prevDirection_);
            generateNewDirection();
        }
    }

    void RandomGridMover::enableAdvancedMovement(bool enable) {
        if (!isAdvance_ && enable) {
            if (isTargetMoving())
                switchToAdvanced_ = true;
            else {
                isAdvance_ = true;
                targetGridMover_.resetTargetTile();
                setRandomPosition();
                if (movementStarted_)
                    targetGridMover_.startMovement();
            }
        } else if (isAdvance_ && !enable) {
            if (targetGridMover_.isTargetMoving())
                switchToNormal_ = true;
            else {
                isAdvance_ = false;
                resetTargetTile();
            }
        }
    }

    void RandomGridMover::setRandomPosition() {
        static auto generateRandomRow = utility::createRandomNumGenerator(0, getGrid().getSizeInTiles().y);
        static auto generateRandomColm = utility::createRandomNumGenerator(0, getGrid().getSizeInTiles().x);

        auto newDestination = Index{generateRandomRow(), generateRandomColm()};
        while(!targetGridMover_.isDestinationReachable(newDestination))
            newDestination = Index{generateRandomRow(), generateRandomColm()};
        targetGridMover_.setDestination(newDestination);
    }

    void RandomGridMover::update(float deltaTime) {
        if (isAdvance_)
            targetGridMover_.update(deltaTime);
        else
            GridMover::update(deltaTime);
    }
}
