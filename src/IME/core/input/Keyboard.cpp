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

#include "IME/core/input/Keyboard.h"
#include <SFML/Window/Keyboard.hpp>

namespace IME::Input {
    void Keyboard::handleEvent(sf::Event event) {
        if (event.type == sf::Event::KeyPressed) {
            eventEmitter_.emit("anyKeyDown", static_cast<Key>(event.key.code));
            eventEmitter_.emit(std::to_string(static_cast<int>(event.key.code)) + "Down");
        } else if (event.type == sf::Event::KeyReleased) {
            eventEmitter_.emit("anyKeyPressed", static_cast<Key>(event.key.code));
            eventEmitter_.emit(std::to_string(static_cast<int>(event.key.code)) + "Up");
        }
    }

    bool Keyboard::isKeyPressed(Key keyId) {
        return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyId));
    }

    int Keyboard::onKeyUp(Key key, Callback<> callback) {
        return eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(key)) + "Up", std::move(callback));
    }

    int Keyboard::onKeyDown(Key key, Callback<> callback) {
        return eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(key)) + "Down", std::move(callback));
    }

    bool Keyboard::removeEventListener(Event event, Key key, int id){
        if (event == Event::KeyUp)
            return eventEmitter_.removeEventListener(
                std::to_string(static_cast<int>(key)) + "Up", id);
        else if (event == Event::KeyDown)
            return eventEmitter_.removeEventListener(
                std::to_string(static_cast<int>(key)) + "Down", id);
        return false;
    }

    bool Keyboard::removeEventListener(Keyboard::Event event, int id) {
        switch (event) {
            case Event::KeyDown:
                return eventEmitter_.removeEventListener("anyKeyDown", id);
            case Event::KeyUp:
                return eventEmitter_.removeEventListener("anyKeyPressed", id);
            default:
                return false;
        }
    }

    int Keyboard::onKeyUp(Callback<Key> callback) {
        return eventEmitter_.addEventListener("anyKeyPressed", std::move(callback));
    }

    int Keyboard::onKeyDown(Callback<Keyboard::Key> callback) {
        return eventEmitter_.addEventListener("anyKeyDown", std::move(callback));
    }
}
