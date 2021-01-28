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
    int InputManager::addKeyListener(KeyEvent event, Keyboard::Key key,
        Callback<> callback)
    {
        switch (event) {
            case KeyEvent::KeyDown:
                return keyboard_.onKeyDown(key, std::move(callback));
            case KeyEvent::KeyUp:
                return keyboard_.onKeyUp(key, std::move(callback));
            default:
                return -1;
        }
    }

    int InputManager::addAnyKeyUpListener(Callback<Keyboard::Key> callback) {
        return keyboard_.onKeyUp(std::move(callback));
    }

    int InputManager::addAnyKeyDownListener(Callback<Keyboard::Key> callback) {
        return keyboard_.onKeyDown(std::move(callback));
    }

    int InputManager::addMouseButtonListener(MouseEvent event, Mouse::Button button,
        Callback<int, int> callback)
    {
        switch(event) {
            case MouseEvent::MouseDown:
                return mouse_.onButtonDown(button, std::move(callback));
            case MouseEvent::MouseUp:
                return mouse_.onButtonUp(button, std::move(callback));
            default:
                return -1;
        }
    }

    bool InputManager::removeKeyListener(KeyEvent event, Keyboard::Key key, int id) {
        return keyboard_.removeEventListener(event, key, id);
    }

    bool InputManager::removeKeyListener(KeyEvent event, int id) {
        return keyboard_.removeEventListener(event, id);
    }

    int InputManager::addMouseMovedListener(Callback<int, int> callback) {
        return mouse_.onMouseMove(std::move(callback));
    }

    bool InputManager::isKeyPressed(Keyboard::Key key) const {
        return keyboard_.isKeyPressed(key);
    }

    bool InputManager::isMouseDown(Mouse::Button button) const {
        return mouse_.isButtonPressed(button);
    }

    bool InputManager::removeMouseListener(MouseEvent event,
        Mouse::Button button, int id)
    {
        return mouse_.removeEventListener(event, button, id);
    }

    void InputManager::handleEvent(Event event) {
        keyboard_.handleEvent(event);
        mouse_.handleEvent(event);
    }

    bool InputManager::removeMouseMovedListener(int id) {
        return mouse_.removeMouseMovedListener(id);
    }
}
