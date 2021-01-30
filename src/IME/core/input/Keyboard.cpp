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
#include "IME/core/event/Event.h"
#include <SFML/Window/Keyboard.hpp>

namespace ime::input {
    bool Keyboard::isKeyPressed(Key keyId) {
        return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyId));
    }

    int Keyboard::onKeyUp(Callback<Key> callback) {
        return eventEmitter_.on("keyUp", std::move(callback));
    }

    int Keyboard::onKeyDown(Callback<Keyboard::Key> callback) {
        return eventEmitter_.on("keyDown", std::move(callback));
    }

    bool Keyboard::unsubscribe(KeyboardEvent event, int id) {
        switch (event) {
            case KeyboardEvent::KeyDown:
                return eventEmitter_.removeEventListener("keyDown", id);
            case KeyboardEvent::KeyUp:
                return eventEmitter_.removeEventListener("keyPressed", id);
            default:
                return false;
        }
    }

    void Keyboard::handleEvent(Event event) {
        switch (event.type) {
            case Event::KeyPressed:
                eventEmitter_.emit("keyDown", event.key.code);
                break;
            case Event::KeyReleased:
                eventEmitter_.emit("keyUp", event.key.code);
                break;
            default:
                break;
        }
    }
}
