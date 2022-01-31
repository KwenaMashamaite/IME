////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
    RandomGridMover::RandomGridMover(TileMap &tileMap, GridObject* target) :
        GridMover(Type::Random, tileMap, target),
        movementStarted_{false}
    {
        // Automatically move the new target
        onPropertyChange("target", [this](const Property& property) {
            if (auto* newTarget = property.getValue<GridObject*>(); newTarget) {
                if (movementStarted_)
                    generateNewDirection();
            }
        });

        // Automatically keep the target moving
        onMoveEnd([this](Index) {
           if (movementStarted_)
                generateNewDirection();
        });
    }

    RandomGridMover::Ptr RandomGridMover::create(TileMap &tileMap, GridObject *target) {
        return std::make_unique<RandomGridMover>(tileMap, target);
    }

    std::string RandomGridMover::getClassName() const {
        return "RandomGridMover";
    }

    void RandomGridMover::startMovement() {
        IME_ASSERT(getTarget(), "A grid mover target is required before starting movement")

        if (!movementStarted_) {
            movementStarted_ = true;
            generateNewDirection();
        }
    }

    void RandomGridMover::stopMovement() {
        if (movementStarted_)
            movementStarted_ = false;
    }

    void RandomGridMover::generateNewDirection() {
        ime::Direction reverseGhostDir = getDirection() * (-1);

        switch (getMovementRestriction()) {
            case MoveRestriction::None:
                possibleDirections_ = {Left, UpLeft, Up, UpRight, Right, DownRight, Down, DownLeft};
                break;
            case MoveRestriction::All:
                return;
            case MoveRestriction::Vertical:
                possibleDirections_ = {Up, Down};
                break;
            case MoveRestriction::Horizontal:
                possibleDirections_ = {Left, Right};
                break;
            case MoveRestriction::Diagonal:
                possibleDirections_ = {UpLeft, UpRight, DownLeft, DownRight};
                break;
            case MoveRestriction::NonDiagonal:
                possibleDirections_ = {Left, Right, Up, Down};
                break;
        }

        // Initialize possible directions
        for (const auto& dir : possibleDirections_) {
            // Prevent target from going backwards
            if (dir == reverseGhostDir)
                continue;

            directionAttempts_.emplace_back(dir);
        }

        // Randomize the directions so that the direction the target chooses
        // to go in is not predictable
        auto static randomEngine = std::default_random_engine{std::random_device{}()};
        std::shuffle(directionAttempts_.begin(), directionAttempts_.end(), randomEngine);

        do {
            // Tried all possible non-reverse directions with no luck (target in stuck in a dead-end)
            // Attempt to reverse direction and go backwards. This an exception to the no reverse
            // direction rule. Without the exception, the target will be stuck in an infinite loop
            if (directionAttempts_.empty()) {
                requestMove(reverseGhostDir);
                break;
            }

            Vector2i dir = directionAttempts_.back();
            directionAttempts_.pop_back(); // Prevent the same direction from being evaluated more than once

            if (!isBlockedInDirection(dir).first) {
                directionAttempts_.clear();
                requestMove(dir);
                break;
            }

        } while(true);
    }

    RandomGridMover::~RandomGridMover() = default;
}
