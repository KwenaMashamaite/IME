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
        movementStarted_{false}
    {
        // Invoke internal event handlers first before raising event externally
        setHandlerIntakeAsInternal(true);

        onPropertyChange("target", [this](const Property& property) {
            if (auto* newTarget = property.getValue<GameObject*>(); newTarget) {
                if (movementStarted_)
                    generateNewDirection();
            }
        });

        onAdjacentMoveEnd([this](Index) {
           if (movementStarted_)
                generateNewDirection();
        });

        // Register subsequent event handlers as external
        setHandlerIntakeAsInternal(false);
    }

    std::string RandomGridMover::getClassName() const {
        return "RandomGridMover";
    }

    void RandomGridMover::startMovement() {
        if (!movementStarted_) {
            movementStarted_ = true;
            generateNewDirection();
            emit("startMovement");
        }
    }

    void RandomGridMover::stopMovement() {
        if (movementStarted_) {
            movementStarted_ = false;
            emit("stopMovement");
        }
    }

    void RandomGridMover::generateNewDirection() {
        ime::Direction reverseGhostDir = getDirection() * (-1);

        // Initialize possible directions
        for (const auto& dir : {Left, Up, Right, Down}) {
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
                requestDirectionChange(reverseGhostDir);
                break;
            }

            Vector2i dir = directionAttempts_.back();
            directionAttempts_.pop_back(); // Prevent the same direction from being evaluated more than once

            if (!isBlockedInDirection(dir).first) {
                directionAttempts_.clear();
                requestDirectionChange(dir);
                break;
            }

        } while(true);
    }

    RandomGridMover::~RandomGridMover() {
        emit("destruction");
    }
}
