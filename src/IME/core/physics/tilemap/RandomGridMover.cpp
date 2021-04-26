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

#include "IME/core/physics/tilemap/RandomGridMover.h"
#include "IME/utility/Utils.h"

namespace ime {
    RandomGridMover::RandomGridMover(TileMap &tileMap, GameObject::Ptr target) :
        GridMover(Type::Random, tileMap, std::move(target)),
        currDirection_(Unknown),
        prevDirection_(Unknown),
        movementStarted_{false},
        isAdvance_{false},
        switchToAdvanced_{false},
        switchToNormal_{false},
        targetGridMover_(tileMap, target)
    {
        onTargetChanged([this](GameObject::Ptr newTarget) {
            if (newTarget) {
                prevDirection_ = currDirection_;
                if (movementStarted_)
                    generateNewDirection();
                // A grid mover sets the velocity of the target to zero after receiving
                // it so that it can be set when it is time to move the target.
                //
                // The RandomGrid mover will set the velocity of the target to zero
                // (before emitting a "targetChange" event). So we need to set it back so that
                // the TargetGridMover can also initialize properly, otherwise it will initialize
                // with a move velocity of zero and the target will not move when advanced
                // movement is enabled (Normal random movement uses this class while advanced
                // random movement delegates to a TargetGridMover class).
                newTarget->getRigidBody()->setLinearVelocity(getMaxLinearSpeed());
            }
            targetGridMover_.setTarget(std::move(newTarget));
        });

        onTileCollision([this](Index) {
            revertAndGenerateDirection();
        });

        onObstacleCollision([this](GameObject::Ptr , GameObject::Ptr) {
            revertAndGenerateDirection();
        });

        onAdjacentTileReached([this](Index) {
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

        targetGridMover_.onDestinationReached([this](Index) {
            setRandomPosition();
        });

        targetGridMover_.onAdjacentTileReached([this](Index) {
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

    std::string RandomGridMover::getClassName() const {
        return "RandomGridMover";
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

    Index RandomGridMover::getTargetTileIndex() const {
        if (isAdvance_)
            return targetGridMover_.getTargetTileIndex();

        return GridMover::getTargetTileIndex();
    }

    void RandomGridMover::generateNewDirection() {
        if (!getTarget() || getMovementRestriction() == GridMover::MoveRestriction::All)
            return;

        prevDirection_ = getDirection();
        auto oppositeDirection = getDirection() * (-1);
        auto newDirection = Direction();
        static auto gen_random_num_between_neg_1_and_1 = utility::createRandomNumGenerator(-1, 1);

        while (true) {
            newDirection = {gen_random_num_between_neg_1_and_1(), gen_random_num_between_neg_1_and_1()};
            // Prohibit going in opposite direction to prevent back and forth movement between two tiles
            if (newDirection != oppositeDirection && requestDirectionChange(newDirection))
                break;
        }
    }

    void RandomGridMover::revertAndGenerateDirection() {
        if (getTarget()) {
            currDirection_ = prevDirection_;
            generateNewDirection();
        }
    }

    void RandomGridMover::enableAdvancedMovement(bool enable) {
        if (!isAdvance_ && enable) {
            IME_ASSERT(targetGridMover_.getTarget(), "Cannot enable advanced movement without a target")
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

        Index newDestination;
        do {
            newDestination = Index{generateRandomRow(), generateRandomColm()};
        } while(!targetGridMover_.isDestinationReachable(newDestination));

        targetGridMover_.setDestination(newDestination);
    }

    void RandomGridMover::update(Time deltaTime) {
        if (isAdvance_)
            targetGridMover_.update(deltaTime);
        else
            GridMover::update(deltaTime);
    }

    RandomGridMover::~RandomGridMover() {
        emit("destruction");
    }
}
