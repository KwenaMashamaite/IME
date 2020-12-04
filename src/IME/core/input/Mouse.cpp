////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

#include "IME/core/input/Mouse.h"
#include <SFML/Window/Mouse.hpp>

namespace IME::Input {
    bool Mouse::isButtonPressed(Button button){
        return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
    }

    void Mouse::handleEvent(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            eventEmitter_.emit(std::to_string(static_cast<int>(event.mouseButton.button)) + "Down");
            eventEmitter_.emit(std::to_string(static_cast<int>(event.mouseButton.button)) + "Down",
                event.mouseButton.x, event.mouseButton.y);
        } else if (event.type == sf::Event::MouseButtonReleased) {
            eventEmitter_.emit(std::to_string(static_cast<int>(event.mouseButton.button)) + "Up");
            eventEmitter_.emit(std::to_string(static_cast<int>(event.mouseButton.button)) + "Up",
                event.mouseButton.x, event.mouseButton.y);
        } else if (event.type == sf::Event::MouseMoved)
            eventEmitter_.emit("mouseMoved", event.mouseMove.x, event.mouseMove.y);
    }

    int Mouse::onButtonUp(Button button, Callback<int, int> callback) {
        return  eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(button)) + "Up", std::move(callback));
    }

    int Mouse::onButtonUp(Mouse::Button button, Callback<> callback) {
        return  eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(button)) + "Up", std::move(callback));
    }

    int Mouse::onButtonDown(Button button, Callback<int, int> callback) {
        return eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(button)) + "Down", std::move(callback));
    }

    int Mouse::onButtonDown(Mouse::Button button, Callback<> callback) {
        return eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(button)) + "Down", std::move(callback));
    }

    int Mouse::onMouseMove(Callback<int, int> callback) {
        return eventEmitter_.addEventListener("mouseMoved", std::move(callback));
    }

    bool Mouse::removeEventListener(Event event, Button button,int id) {
        if (event == Event::MouseDown)
            return eventEmitter_.removeEventListener(
                std::to_string(static_cast<int>(button)) + "Down", id);
        else if (event == Event::MouseUp)
            return eventEmitter_.removeEventListener(
                std::to_string(static_cast<int>(button)) + "Up", id);
        return false;
    }


    bool Mouse::removeMouseMovedListener(int id) {
        return eventEmitter_.removeEventListener("mouseMoved", id);
    }
}
