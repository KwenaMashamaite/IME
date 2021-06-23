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

#include "IME/core/physics/grid/RandomGridMover.h"
#include "IME/utility/Utils.h"

namespace ime {
    RandomGridMover::RandomGridMover(TileMap &tileMap, GameObject* target) :
        GridMover(Type::Random, tileMap, target),
        currDirection_(Unknown),
        prevDirection_(Unknown),
        movementStarted_{false},
        isSmartMoveEnabled_{false},
        switchToSmartMove_{false},
        switchToNormal_{false},
        smartMover_(tileMap, target)
    {
        // Invoke internal event handlers first before raising event externally
        setHandlerIntakeAsInternal(true);

        smartMover_.setMaxLinearSpeed(getMaxLinearSpeed());

        onPropertyChange("target", [this](const Property& property) {
            if (auto* newTarget = property.getValue<GameObject*>(); newTarget) {
                prevDirection_ = currDirection_;
                smartMover_.setTarget(newTarget);
                smartMover_.setMaxLinearSpeed(getMaxLinearSpeed());

                if (movementStarted_)
                    generateNewDirection();
            }
        });

        onTileCollision([this](Index) {
            revertAndGenerateDirection();
        });

        onGameObjectCollision([this](GameObject*, GameObject* other) {
            if (other->isObstacle())
                revertAndGenerateDirection();
        });

        onAdjacentMoveEnd([this](Index) {
            if (switchToSmartMove_) {
                switchToSmartMove_ = false;
                isSmartMoveEnabled_ = true;
                smartMover_.resetTargetTile();
                setRandomPosition();
                smartMover_.startMovement();
            } else if (movementStarted_) {
                resetTargetTile();
                generateNewDirection();
            }
        });

        onGridBorderCollision([this] {
            revertAndGenerateDirection();
        });

        // Register subsequent event handlers as external
        setHandlerIntakeAsInternal(false);

        smartMover_.onDestinationReached([this](Index) {
            setRandomPosition();
        });

        smartMover_.onAdjacentMoveEnd([this](Index) {
            if (switchToNormal_) {
                switchToNormal_ = false;
                isSmartMoveEnabled_ = false;
                resetTargetTile();
                if (movementStarted_)
                    generateNewDirection();
            }
        });
    }

    std::string RandomGridMover::getClassName() const {
        return "RandomGridMover";
    }

    void RandomGridMover::startMovement() {
        if (!movementStarted_) {
            movementStarted_ = true;
            if (isSmartMoveEnabled_)
                smartMover_.startMovement();
            else
                generateNewDirection();
        }
    }

    void RandomGridMover::stopMovement() {
        movementStarted_ = false;
        if (isSmartMoveEnabled_)
            smartMover_.stopMovement();
    }

    Index RandomGridMover::getTargetTileIndex() const {
        if (isSmartMoveEnabled_)
            return smartMover_.getTargetTileIndex();

        return GridMover::getTargetTileIndex();
    }

    void RandomGridMover::generateNewDirection() {
        if (!getTarget() || getMovementRestriction() == GridMover::MoveRestriction::All)
            return;

        prevDirection_ = getDirection();
        auto oppositeDirection = getDirection() * (-1);
        Direction newDirection;
        static auto gen_random_num_between_neg_1_and_1 = utility::createRandomNumGenerator(-1, 1);

        while (true) {
            newDirection = {gen_random_num_between_neg_1_and_1(), gen_random_num_between_neg_1_and_1()};
            if (newDirection == Unknown)
                continue;

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

    void RandomGridMover::setSmartMoveEnable(bool enable) {
        if (!isSmartMoveEnabled_ && enable) {
            IME_ASSERT(smartMover_.getTarget(), "Cannot enable advanced movement without a target")
            if (isTargetMoving())
                switchToSmartMove_ = true;
            else {
                isSmartMoveEnabled_ = true;
                smartMover_.resetTargetTile();
                setRandomPosition();
                if (movementStarted_)
                    smartMover_.startMovement();
            }
        } else if (isSmartMoveEnabled_ && !enable) {
            if (smartMover_.isTargetMoving())
                switchToNormal_ = true;
            else {
                isSmartMoveEnabled_ = false;
                resetTargetTile();
            }
        }
    }

    bool RandomGridMover::isSmartMoveEnabled() const {
        return isSmartMoveEnabled_;
    }

    void RandomGridMover::setRandomPosition() {
        static auto generateRandomRow = utility::createRandomNumGenerator(0, getGrid().getSizeInTiles().y);
        static auto generateRandomColm = utility::createRandomNumGenerator(0, getGrid().getSizeInTiles().x);

        Index newDestination;
        do {
            newDestination = Index{generateRandomRow(), generateRandomColm()};
        } while(!smartMover_.isDestinationReachable(newDestination));

        smartMover_.setDestination(newDestination);
    }

    void RandomGridMover::update(Time deltaTime) {
        if (isSmartMoveEnabled_)
            smartMover_.update(deltaTime);
        else
            GridMover::update(deltaTime);
    }

    RandomGridMover::~RandomGridMover() {
        emit("destruction");
    }
}
