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

#include "IME/core/input/InputManager.h"
#include "IME/core/exceptions/Exceptions.h"
#include <algorithm>

namespace ime::input {
    InputManager::InputManager() {
        for (unsigned int joyId = 0; joyId < Joystick::Count; joyId++)
            joysticks_.emplace_back(joyId);
    }

    void InputManager::setInputEnable(InputType inputType, bool enable) {
        switch (inputType) {
            case InputType::Keyboard:
                keyboard_.setEnable(enable);
                break;
            case InputType::Mouse:
                mouse_.setEnable(enable);
                break;
            case InputType::Joystick:
                for (auto& joystick : joysticks_)
                    joystick.setEnable(enable);
                break;
        }
    }

    bool InputManager::isInputEnabled(InputType inputType) const {
        switch (inputType) {
            case InputType::Keyboard:
                return keyboard_.isEnabled();
            case InputType::Mouse:
                return mouse_.isEnabled();
            case InputType::Joystick:
                return std::any_of(joysticks_.begin(), joysticks_.end(), [](const Joystick& joystick) {
                    return joystick.isEnabled();
                });
            default:
                return false;
        }
    }

    void InputManager::setAllInputEnable(bool enable) {
        keyboard_.setEnable(enable);
        mouse_.setEnable(enable);

        for (auto& joystick : joysticks_)
            joystick.setEnable(enable);
    }

    bool InputManager::isAllInputEnabled() const {
        return keyboard_.isEnabled() && mouse_.isEnabled() && std::all_of(joysticks_.begin(), joysticks_.end(), [](const Joystick& joystick) {return joystick.isEnabled();});
    }

    bool InputManager::isAllInputDisabled() const {
        return !keyboard_.isEnabled() && !mouse_.isEnabled() && std::none_of(joysticks_.begin(), joysticks_.end(), [](const Joystick& joystick) {return joystick.isEnabled();});
    }

    bool InputManager::isKeyPressed(Keyboard::Key key) {
        return input::Keyboard::isKeyPressed(key);
    }

    int InputManager::bindKey(Keyboard::Key key, KeyBindType type, const KeybindAction &action) {
        switch (type) {
            case KeyBindType::KeyUp:
                return keyboard_.onKeyUp([key, action](Keyboard::Key upKey) {
                    if (key == upKey)
                        action();
                });
            case KeyBindType::KeyDown:
                return keyboard_.onKeyDown([key, action](Keyboard::Key downKey) {
                    if (key == downKey)
                        action();
                });
            case KeyBindType::KeyHeld:
                return keyboard_.onKeyHeld([key, action](Keyboard::Key heldKey) {
                    if (key == heldKey)
                        action();
                });
            default:
                return -1;
        }
    }

    int InputManager::bindKeys(Keyboard::Key keyA, Keyboard::Key keyB, KeyBindType keyBindType, const KeybindAction &action) {
        switch (keyBindType) {
            case KeyBindType::KeyDown:
                return keyboard_.onKeyDown([=](Keyboard::Key key) {
                    if ((key == keyA && isKeyPressed(keyB)) || (key == keyB && isKeyPressed(keyA)))
                        action();
                });
            case KeyBindType::KeyHeld:
                return keyboard_.onKeyHeld([=](Keyboard::Key key) {
                    if ((key == keyA && isKeyPressed(keyB)) || (key == keyB && isKeyPressed(keyA)))
                        action();
                });
            default:
                return -1;
        }
    }

    bool InputManager::unbindKey(KeyBindType keyBindType, int id) {
        return unsubscribe(static_cast<KeyboardEvent>(keyBindType), id);
    }

    int InputManager::onKeyUp(Callback<Keyboard::Key> callback) {
        return keyboard_.onKeyUp(std::move(callback));
    }

    int InputManager::onKeyDown(Callback<Keyboard::Key> callback) {
        return keyboard_.onKeyDown(std::move(callback));
    }

    int InputManager::onKeyHeld(Callback<Keyboard::Key> callback) {
        return keyboard_.onKeyHeld(std::move(callback));
    }

    bool InputManager::unsubscribe(KeyboardEvent event, int id) {
        return keyboard_.unsubscribe(event, id);
    }

    bool InputManager::isMouseDown(Mouse::Button button) {
        return input::Mouse::isButtonPressed(button);
    }

    int InputManager::onMouseUp(Callback<Mouse::Button, int, int> callback) {
        return mouse_.onButtonUp(std::move(callback));
    }

    int InputManager::onMouseUp(Callback<Mouse::Button> callback) {
        return mouse_.onButtonUp(std::move(callback));
    }

    int InputManager::onMouseDown(Callback<Mouse::Button, int, int> callback) {
        return mouse_.onButtonDown(std::move(callback));
    }

    int InputManager::onMouseDown(Callback<Mouse::Button> callback) {
        return mouse_.onButtonDown(std::move(callback));
    }

    int InputManager::onMouseMove(Callback<int, int> callback) {
        return mouse_.onMouseMove(std::move(callback));
    }

    int InputManager::onMouseWheelScroll(Callback<Mouse::Wheel, float, int, int> callback) {
        return mouse_.onWheelScroll(std::move(callback));
    }

    bool InputManager::unsubscribe(MouseEvent event, int id) {
        return mouse_.unsubscribe(event, id);
    }

    int InputManager::onJoyConnect(const Callback<unsigned int> &callback) {
        return eventEmitter_.on("anyJoystickConnect", callback);
    }

    int InputManager::onJoyDisconnect(const Callback<unsigned int> &callback) {
        return eventEmitter_.on("anyJoystickDisconnect", callback);
    }

    int InputManager::onJoyButtonPress(const Callback<unsigned int, unsigned int> &callback) {
        return eventEmitter_.on("anyJoystickButtonPress", callback);
    }

    int InputManager::onJoyButtonRelease(const Callback<unsigned int, unsigned int> &callback) {
        return eventEmitter_.on("anyJoystickButtonRelease", callback);
    }

    int InputManager::onJoyAxisMove(const Callback<unsigned int, Joystick::Axis, float> &callback) {
        return eventEmitter_.on("anyJoystickAxisMove", callback);
    }

    Joystick &InputManager::getJoystick(unsigned int index) {
        return const_cast<Joystick&>(std::as_const(*this).getJoystick(index));
    }

    const Joystick &InputManager::getJoystick(unsigned int index) const {
        if (index < joysticks_.size())
            return joysticks_.at(index);
        else
            throw InvalidArgument("Joystick index out of bounds");
    }

    bool InputManager::unsubscribe(JoystickEvent event, int id) {
        bool removed = std::any_of(joysticks_.begin(), joysticks_.end(), [=](Joystick& joystick) {
           return joystick.unsubscribe(event, id);
        });
        
        if (!removed) {
            switch (event) {
                case JoystickEvent::Connect:
                    return eventEmitter_.removeEventListener("anyJoystickConnect", id);
                case JoystickEvent::Disconnect:
                    return eventEmitter_.removeEventListener("anyJoystickDisconnect", id);
                case JoystickEvent::ButtonPress:
                    return eventEmitter_.removeEventListener("anyJoystickButtonPress", id);
                case JoystickEvent::ButtonRelease:
                    return eventEmitter_.removeEventListener("anyJoystickButtonRelease", id);
                case JoystickEvent::AxisMove:
                    return eventEmitter_.removeEventListener("anyJoystickAxisMove", id);
                default:
                    break;
            }
        }
        
        return removed;
    }

    void InputManager::handleEvent(Event event) {
        keyboard_.handleEvent(event);
        mouse_.handleEvent(event);

        for (auto& joystick : joysticks_)
            joystick.handleEvent(event);

        switch (event.type) {
            case Event::JoystickButtonPressed:
                if (getJoystick(event.joystickButton.joystickId).isEnabled())
                    eventEmitter_.emit("anyJoystickButtonPress", event.joystickButton.joystickId, event.joystickButton.button);

                break;
            case Event::JoystickButtonReleased:
                if (getJoystick(event.joystickButton.joystickId).isEnabled())
                    eventEmitter_.emit("anyJoystickButtonRelease", event.joystickButton.joystickId, event.joystickButton.button);

                break;
            case Event::JoystickMoved:
                if (getJoystick(event.joystickButton.joystickId).isEnabled())
                    eventEmitter_.emit("anyJoystickAxisMove", event.joystickButton.joystickId, event.joystickMove.axis, event.joystickMove.position);

                break;
            case Event::JoystickConnected:
                eventEmitter_.emit("anyJoystickConnect", event.joystickButton.joystickId);
                break;
            case Event::JoystickDisconnected:
                eventEmitter_.emit("anyJoystickDisconnect", event.joystickButton.joystickId);
                break;
            default:
                break;
        }
    }

    void InputManager::update() {
        std::for_each(joysticks_.begin(), joysticks_.end(), [](Joystick& joystick) {
            joystick.update();
        });
    }
}
