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

#include "IME/core/input/InputManager.h"

namespace ime::input {
    bool InputManager::isKeyPressed(Keyboard::Key key) {
        return input::Keyboard::isKeyPressed(key);
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

    void InputManager::handleEvent(Event event) {
        keyboard_.handleEvent(event);
        mouse_.handleEvent(event);
    }
}
