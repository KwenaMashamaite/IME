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

#include "IME/core/physics/tilemap/KeyboardControlledGridMover.h"
#include "IME/core/event/Event.h"

namespace ime {
    KeyboardControlledGridMover::KeyboardControlledGridMover(TileMap &tileMap, std::shared_ptr<GameObject> target) :
        GridMover(tileMap, target),
        trigger_(MovementTrigger::None), onTriggerHandlerId_{-1}
    {
        onAdjacentTileReached([this](Tile) {
            if (auto& [changeDir, newDir] = newDir_; changeDir) { //Direction switch was requested while target was moving
                changeDir = false;
                requestDirectionChange(newDir);
                newDir = Direction::Unknown;
            }
        });

        setMovementTrigger(MovementTrigger::OnKeyDown);
        setKeys(Key::A, Key::D, Key::W, Key::S);
    }

    void KeyboardControlledGridMover::setMovementTrigger(MovementTrigger trigger) {
        if (trigger_ != trigger) {
            trigger_ = trigger;
            removeInputEventListeners();
            attachInputEventListeners();
        }
    }

    MovementTrigger KeyboardControlledGridMover::getMovementTrigger() const {
        return trigger_;
    }

    void KeyboardControlledGridMover::setKeys(input::Keyboard::Key leftKey,
        input::Keyboard::Key rightKey, input::Keyboard::Key upKey,
        input::Keyboard::Key downKey)
    {
        goLeftKey_ = leftKey;
        goRightKey_ = rightKey;
        goUpKey_ = upKey;
        goDownKey_ = downKey;
    }

    void KeyboardControlledGridMover::attachInputEventListeners() {
        if (trigger_ == MovementTrigger::None)
            return;

        auto moveEntity = [this](input::Keyboard::Key key) {
            moveTarget(key);
        };

        if (trigger_ == MovementTrigger::OnKeyDown)
            onTriggerHandlerId_ = keyboard_.onKeyDown(moveEntity);
        else if (trigger_ == MovementTrigger::OnKeyUp)
            onTriggerHandlerId_ = keyboard_.onKeyUp(moveEntity);
    }

    void KeyboardControlledGridMover::removeInputEventListeners() {
        if (onTriggerHandlerId_ != -1) {
            if (!keyboard_.unsubscribe(KeyboardEvent::KeyDown, onTriggerHandlerId_))
                keyboard_.unsubscribe(KeyboardEvent::KeyUp, onTriggerHandlerId_);

            onTriggerHandlerId_ = -1;
        }
    }

    void KeyboardControlledGridMover::moveTarget(input::Keyboard::Key key) {
        auto targetDirection = Direction::Unknown;
        if (key == goLeftKey_)
            targetDirection = Direction::Left;
        else if (key == goRightKey_)
            targetDirection = Direction::Right;
        else if (key == goUpKey_)
            targetDirection = Direction::Up;
        else if (key == goDownKey_)
            targetDirection = Direction::Down;
        else
            return;

        if (getTarget() && isTargetMoving()) {
            newDir_.first = true;
            newDir_.second = targetDirection;
        } else
            requestDirectionChange(targetDirection);
    }

    void KeyboardControlledGridMover::handleEvent(Event event) {
        keyboard_.handleEvent(event);
    }
}
