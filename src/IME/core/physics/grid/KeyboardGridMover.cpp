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

#include "IME/core/physics/grid/KeyboardGridMover.h"
#include "IME/core/event/Event.h"

namespace ime {
    KeyboardGridMover::KeyboardGridMover(TileMap &tileMap, GameObject* target) :
        GridMover(Type::KeyboardControlled, tileMap, target),
        trigger_(MovementTrigger::None),
        onTriggerHandlerId_{-1, -1},
        triggerKeys_{Key::A, Key::D, Key::W, Key::S}
    {

        // Invoke internal event handlers first before raising event externally
        setHandlerIntakeAsInternal(true);

        onAdjacentMoveEnd([this](Index) {
            if (auto& [changeDir, newDir] = newDir_; changeDir) { //Direction switch was requested while target was moving
                changeDir = false;
                requestMove(newDir);
                newDir = Unknown;
            }
        });

        setMovementTrigger(MovementTrigger::OnKeyDown);

        // Register subsequent event handlers as external
        setHandlerIntakeAsInternal(false);
    }

    KeyboardGridMover::Ptr KeyboardGridMover::create(TileMap &tileMap, GameObject *target) {
        return std::make_unique<KeyboardGridMover>(tileMap, target);
    }

    std::string KeyboardGridMover::getClassName() const {
        return "KeyboardGridMover";
    }

    void KeyboardGridMover::setMovementTrigger(MovementTrigger trigger) {
        if (trigger_ != trigger) {
            removeInputEventListeners();

            trigger_ = trigger;
            attachInputEventListeners();
            emitChange(Property{"movementTrigger", trigger});
        }
    }

    MovementTrigger KeyboardGridMover::getMovementTrigger() const {
        return trigger_;
    }

    void KeyboardGridMover::setKeys(const TriggerKeys &triggerKeys) {
        if (triggerKeys_ != triggerKeys) {
            triggerKeys_ = triggerKeys;
            emitChange(Property{"keys", triggerKeys});
        }
    }

    TriggerKeys &KeyboardGridMover::getTriggerKeys() {
        return triggerKeys_;
    }

    const TriggerKeys &KeyboardGridMover::getTriggerKeys() const {
        return triggerKeys_;
    }

    void KeyboardGridMover::onInput(const KeyboardGridMover::InputCallback &callback) {
        onInput_ = callback;
    }

    void KeyboardGridMover::attachInputEventListeners() {
        if (trigger_ == MovementTrigger::None)
            return;

        auto moveEntity = [this](input::Keyboard::Key key) {
            if (key == triggerKeys_.leftKey || key == triggerKeys_.rightKey ||
                key == triggerKeys_.upKey || key == triggerKeys_.downKey)
            {
                if (!onInput_ || onInput_(key))
                    moveTarget(key);
            }
        };

        if (trigger_ == MovementTrigger::OnKeyDownHeld) {
            onTriggerHandlerId_.first = keyboard_.onKeyDown(moveEntity);
            onTriggerHandlerId_.second = keyboard_.onKeyHeld(moveEntity);
        } else if (trigger_ == MovementTrigger::OnKeyDown)
            onTriggerHandlerId_.first = keyboard_.onKeyDown(moveEntity);
        else if (trigger_ == MovementTrigger::OnKeyUp)
            onTriggerHandlerId_.first = keyboard_.onKeyUp(moveEntity);
        else if (trigger_ == MovementTrigger::OnKeyHeld)
            onTriggerHandlerId_.first = keyboard_.onKeyHeld(moveEntity);
    }

    void KeyboardGridMover::removeInputEventListeners() {
        if (onTriggerHandlerId_.first != -1) {
            switch (trigger_) {
                case MovementTrigger::None:
                    IME_ASSERT(false, "Internal Error: KeyboardGridMover event handler subscribed with no movement trigger")
                    break;
                case MovementTrigger::OnKeyDown:
                    keyboard_.unsubscribe(KeyboardEvent::KeyDown, onTriggerHandlerId_.first);
                    break;
                case MovementTrigger::OnKeyUp:
                    keyboard_.unsubscribe(KeyboardEvent::KeyUp, onTriggerHandlerId_.first);
                    break;
                case MovementTrigger::OnKeyHeld:
                    keyboard_.unsubscribe(KeyboardEvent::KeyHeld, onTriggerHandlerId_.first);
                    break;
                case MovementTrigger::OnKeyDownHeld:
                    keyboard_.unsubscribe(KeyboardEvent::KeyDown, onTriggerHandlerId_.first);
                    keyboard_.unsubscribe(KeyboardEvent::KeyHeld, onTriggerHandlerId_.second);
                    break;
            }

            onTriggerHandlerId_ = std::pair{-1, -1};
        }
    }

    void KeyboardGridMover::moveTarget(input::Keyboard::Key key) {
        Direction targetDirection;
        if (key == triggerKeys_.leftKey) {
            if (Keyboard::isKeyPressed(triggerKeys_.upKey)) //Up key + left key currently pressed
                targetDirection = UpLeft;
            else if (Keyboard::isKeyPressed(triggerKeys_.downKey))
                targetDirection = DownLeft;
            else
                targetDirection = Left;
        } else if (key == triggerKeys_.rightKey) {
            if (Keyboard::isKeyPressed(triggerKeys_.upKey))
                targetDirection = UpRight;
            else if (Keyboard::isKeyPressed(triggerKeys_.downKey))
                targetDirection = DownRight;
            else
                targetDirection = Right;
        } else if (key == triggerKeys_.upKey) {
            if (Keyboard::isKeyPressed(triggerKeys_.leftKey))
                targetDirection = UpLeft;
            else if (Keyboard::isKeyPressed(triggerKeys_.rightKey))
                targetDirection = UpRight;
            else
                targetDirection = Up;
        } else if (key == triggerKeys_.downKey) {
            if (Keyboard::isKeyPressed(triggerKeys_.leftKey))
                targetDirection = DownLeft;
            else if (Keyboard::isKeyPressed(triggerKeys_.rightKey))
                targetDirection = DownRight;
            else
                targetDirection = Down;
        } else
            return;

        if (getTarget() && isTargetMoving()) {
            newDir_.first = true;
            newDir_.second = targetDirection;
        } else if (targetDirection != Vector2i{0, 0})
            requestMove(targetDirection);
    }

    void KeyboardGridMover::handleEvent(Event event) {
        keyboard_.handleEvent(event);
    }

    KeyboardGridMover::~KeyboardGridMover() {
        emit("destruction");
    }

    bool operator==(const ime::TriggerKeys &lhs, const ime::TriggerKeys &rhs) {
        return (lhs.leftKey == rhs.leftKey) &&
                (lhs.rightKey == rhs.rightKey) &&
                (lhs.upKey == rhs.upKey) &&
                (lhs.downKey == rhs.downKey);
    }

    bool operator!=(const ime::TriggerKeys &lhs, const ime::TriggerKeys &rhs) {
        return !(lhs == rhs);
    }
} //namespace ime
