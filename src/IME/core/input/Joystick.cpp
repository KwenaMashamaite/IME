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
    void Joystick::setEnable(bool enable) {
        emitter_.setActive(enable);
    }

    bool Joystick::isEnabled() const {
        return emitter_.isActive();
    }

    bool Joystick::isConnected(unsigned int joystick) {
        return sf::Joystick::isConnected(joystick);
    }

    unsigned int Joystick::getButtonCount(unsigned int joystick) {
        return sf::Joystick::getButtonCount(joystick);
    }

    bool Joystick::hasAxis(unsigned int joystick, Joystick::Axis axis) {
        return sf::Joystick::hasAxis(joystick, static_cast<sf::Joystick::Axis>(axis));
    }

    bool Joystick::isButtonPressed(unsigned int joystick, unsigned int button) {
        return sf::Joystick::isButtonPressed(joystick, button);
    }

    float Joystick::getAxisPosition(unsigned int joystick, Joystick::Axis axis) {
        return sf::Joystick::getAxisPosition(joystick, static_cast<sf::Joystick::Axis>(axis));
    }

    Joystick::Identification Joystick::getIdentification(unsigned int joystick) {
        sf::Joystick::Identification sfId = sf::Joystick::getIdentification(joystick);
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

    int Joystick::onConnect(const Callback<unsigned int>& callback) {
        return emitter_.on("connect", callback);
    }

    int Joystick::onDisconnect(const Callback<unsigned int>& callback) {
        return emitter_.on("disconnect", callback);
    }

    int Joystick::onButtonPress(const Callback<unsigned int, unsigned int>& callback) {
        return emitter_.on("buttonPress", callback);
    }

    int Joystick::onButtonRelease(const Callback<unsigned int, unsigned int>& callback) {
        return emitter_.on("buttonRelease", callback);
    }

    int Joystick::onAxisMove(const Callback<unsigned int, Joystick::Axis, float> &callback) {
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
            case JoystickEvent::AxisMove:
                return emitter_.removeEventListener("axisMove", id);
            default:
                return false;
        }
    }

    void Joystick::handleEvent(Event event) {
        switch (event.type) {
            case Event::JoystickButtonPressed:
                emitter_.emit("buttonPress", event.joystickButton.joystickId, event.joystickButton.button);
                break;
            case Event::JoystickButtonReleased:
                emitter_.emit("buttonRelease", event.joystickButton.joystickId, event.joystickButton.button);
                break;
            case Event::JoystickMoved:
                emitter_.emit("axisMove", event.joystickMove.joystickId, event.joystickMove.axis, event.joystickMove.position);
                break;
            case Event::JoystickConnected:
                emitter_.emit("connect", event.joystickConnect.joystickId);
                break;
            case Event::JoystickDisconnected:
                emitter_.emit("disconnect", event.joystickConnect.joystickId);
                break;
            default:
                return;
        }
    }
}
