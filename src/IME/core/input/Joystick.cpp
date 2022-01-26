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

#include "IME/core/input/Joystick.h"
#include "IME/core/event/Event.h"
#include <SFML/Window/Joystick.hpp>

namespace ime::input {
    Joystick::Joystick(unsigned int index) :
        isEnabled_{true},
        index_{index}
    {
        for (auto i = 0u; i < Joystick::ButtonCount - 1; ++i)
            wasDown_[i] = false;
    }

    unsigned int Joystick::getIndex() const {
        return index_;
    }

    void Joystick::setEnable(bool enable) {
        isEnabled_ = enable;
    }

    bool Joystick::isEnabled() const {
        return isEnabled_;
    }

    bool Joystick::isConnected() const{
        return sf::Joystick::isConnected(index_);
    }

    unsigned int Joystick::getButtonCount() const {
        return sf::Joystick::getButtonCount(index_);
    }

    bool Joystick::hasAxis(Joystick::Axis axis) const {
        return sf::Joystick::hasAxis(index_, static_cast<sf::Joystick::Axis>(axis));
    }

    bool Joystick::isButtonPressed(unsigned int button) const {
        return sf::Joystick::isButtonPressed(index_, button);
    }

    float Joystick::getAxisPosition(Joystick::Axis axis) const {
        return sf::Joystick::getAxisPosition(index_, static_cast<sf::Joystick::Axis>(axis));
    }

    Joystick::Identification Joystick::getIdentification() const {
        sf::Joystick::Identification sfId = sf::Joystick::getIdentification(index_);
        Identification id{};
        id.name = sfId.name;
        id.vendorId = sfId.vendorId;
        id.productId = sfId.productId;
        return id;
    }

    Joystick::Identification::Identification() :
        name{"No Joystick"},
        vendorId{0},
        productId{0}
    {}

    int Joystick::onConnect(const Callback<>& callback) {
        return emitter_.on("connect", callback);
    }

    int Joystick::onDisconnect(const Callback<>& callback) {
        return emitter_.on("disconnect", callback);
    }

    int Joystick::onButtonPress(const Callback<unsigned int>& callback) {
        return emitter_.on("buttonPress", callback);
    }

    int Joystick::onButtonRelease(const Callback<unsigned int>& callback) {
        return emitter_.on("buttonRelease", callback);
    }

    int Joystick::onButtonHeld(const Callback<unsigned int> &callback) {
        return emitter_.on("buttonHeld", callback);
    }

    int Joystick::onAxisMove(const Callback<Joystick::Axis, float> &callback) {
        return emitter_.on("axisMove", callback);
    }

    bool Joystick::unsubscribe(JoystickEvent event, int id) {
        switch (event) {
            case JoystickEvent::Connect:
                return emitter_.removeEventListener("connect", id);
            case JoystickEvent::Disconnect:
                return emitter_.removeEventListener("disconnect", id);
            case JoystickEvent::ButtonPress:
                return emitter_.removeEventListener("buttonPress", id);
            case JoystickEvent::ButtonRelease:
                return emitter_.removeEventListener("buttonRelease", id);
            case JoystickEvent::ButtonHeld:
                return emitter_.removeEventListener("buttonHeld", id);
            case JoystickEvent::AxisMove:
                return emitter_.removeEventListener("axisMove", id);
            default:
                return false;
        }
    }

    void Joystick::handleEvent(Event event) {
        if (event.joystickButton.joystickId == index_) {
            if (event.type == Event::JoystickConnected || event.type == Event::JoystickDisconnected) {
                emitter_.emit(event.type == Event::JoystickConnected ? "connect" : "disconnect");
            } else if (isEnabled_) {
                switch (event.type) {
                    case Event::JoystickButtonPressed:
                        if (!wasDown_[event.joystickButton.button]) {
                            wasDown_[event.joystickButton.button] = true;
                            emitter_.emit("buttonPress", event.joystickButton.button);
                        }
                        break;
                    case Event::JoystickButtonReleased:
                        wasDown_[event.joystickButton.button] = false;
                        emitter_.emit("buttonRelease", event.joystickButton.button);
                        break;
                    case Event::JoystickMoved:
                        emitter_.emit("axisMove", event.joystickMove.axis, event.joystickMove.position);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    void Joystick::update() {
        if (isEnabled() && isConnected()) {
            for (auto& [button, wasBtnDown] : wasDown_) {
                if (wasBtnDown && isButtonPressed(button))
                    emitter_.emit("buttonHeld", button);
            }
        }
    }
}
