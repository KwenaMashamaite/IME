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

#include "IME/core/physics/tilemap/KeyboardGridMover.h"
#include "IME/core/event/Event.h"

namespace ime {
    KeyboardGridMover::KeyboardGridMover(TileMap &tileMap, GameObject* target) :
        GridMover(Type::KeyboardControlled, tileMap, target),
        trigger_(MovementTrigger::None), onTriggerHandlerId_{-1}
    {
        onAdjacentTileReached([this](Index) {
            if (auto& [changeDir, newDir] = newDir_; changeDir) { //Direction switch was requested while target was moving
                changeDir = false;
                requestDirectionChange(newDir);
                newDir = Unknown;
            }
        });

        setMovementTrigger(MovementTrigger::OnKeyDown);
        setKeys(Key::A, Key::D, Key::W, Key::S);
    }

    std::string KeyboardGridMover::getClassName() const {
        return "KeyboardGridMover";
    }

    void KeyboardGridMover::setMovementTrigger(MovementTrigger trigger) {
        if (trigger_ != trigger) {
            trigger_ = trigger;
            removeInputEventListeners();
            attachInputEventListeners();
        }
    }

    MovementTrigger KeyboardGridMover::getMovementTrigger() const {
        return trigger_;
    }

    void KeyboardGridMover::setKeys(input::Keyboard::Key leftKey,
        input::Keyboard::Key rightKey, input::Keyboard::Key upKey,
        input::Keyboard::Key downKey)
    {
        goLeftKey_ = leftKey;
        goRightKey_ = rightKey;
        goUpKey_ = upKey;
        goDownKey_ = downKey;
    }

    void KeyboardGridMover::attachInputEventListeners() {
        if (trigger_ == MovementTrigger::None)
            return;

        auto moveEntity = [this](input::Keyboard::Key key) {
            moveTarget(key);
        };

        if (trigger_ == MovementTrigger::OnKeyDown)
            onTriggerHandlerId_ = keyboard_.onKeyDown(moveEntity);
        else if (trigger_ == MovementTrigger::OnKeyUp)
            onTriggerHandlerId_ = keyboard_.onKeyUp(moveEntity);
        else if (trigger_ == MovementTrigger::OnKeyHeld)
            onTriggerHandlerId_ = keyboard_.onKeyHeld(moveEntity);
    }

    void KeyboardGridMover::removeInputEventListeners() {
        if (onTriggerHandlerId_ != -1) {
            if (!keyboard_.unsubscribe(KeyboardEvent::KeyDown, onTriggerHandlerId_)
                && !keyboard_.unsubscribe(KeyboardEvent::KeyUp, onTriggerHandlerId_))
            {
                keyboard_.unsubscribe(KeyboardEvent::KeyHeld, onTriggerHandlerId_);
            }

            onTriggerHandlerId_ = -1;
        }
    }

    void KeyboardGridMover::moveTarget(input::Keyboard::Key key) {
        Direction targetDirection;
        if (key == goLeftKey_) {
            if (Keyboard::isKeyPressed(goUpKey_)) //Up key + left key currently pressed
                targetDirection = UpLeft;
            else if (Keyboard::isKeyPressed(goDownKey_))
                targetDirection = DownLeft;
            else
                targetDirection = Left;
        } else if (key == goRightKey_) {
            if (Keyboard::isKeyPressed(goUpKey_))
                targetDirection = UpRight;
            else if (Keyboard::isKeyPressed(goDownKey_))
                targetDirection = DownRight;
            else
                targetDirection = Right;
        } else if (key == goUpKey_) {
            if (Keyboard::isKeyPressed(goLeftKey_))
                targetDirection = UpLeft;
            else if (Keyboard::isKeyPressed(goRightKey_))
                targetDirection = UpRight;
            else
                targetDirection = Up;
        } else if (key == goDownKey_) {
            if (Keyboard::isKeyPressed(goLeftKey_))
                targetDirection = DownLeft;
            else if (Keyboard::isKeyPressed(goRightKey_))
                targetDirection = DownRight;
            else
                targetDirection = Down;
        }

        if (getTarget() && isTargetMoving()) {
            newDir_.first = true;
            newDir_.second = targetDirection;
        } else if (targetDirection != Vector2i{0, 0})
            requestDirectionChange(targetDirection);
    }

    void KeyboardGridMover::handleEvent(Event event) {
        keyboard_.handleEvent(event);
    }

    KeyboardGridMover::~KeyboardGridMover() {
        emit("destruction");
    }
}
