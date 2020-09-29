#include "IME/core/managers/InputManager.h"

namespace IME::Input {
    int InputManager::addKeyListener(Keyboard::Event event, Keyboard::Key key,
        Callback<> callback)
    {
        if (event == Keyboard::Event::KeyDown)
            return keyboard_.onKeyDown(key, std::move(callback));
        else if (event == Keyboard::Event::KeyUp)
            return keyboard_.onKeyUp(key, std::move(callback));
        return -1;
    }

    int InputManager::addAnyKeyUpListener(Callback<Keyboard::Key> callback) {
        return keyboard_.onKeyUp(std::move(callback));
    }

    int InputManager::addAnyKeyDownListener(Callback<Keyboard::Key> callback) {
        return keyboard_.onKeyDown(std::move(callback));
    }

    int InputManager::addMouseButtonListener(Mouse::Event event, Mouse::Button button,
        Callback<> callback)
    {
        if (event == Mouse::Event::MouseDown)
            mouse_.onButtonDown(button, std::move(callback));
        else if (event == Mouse::Event::MouseUp)
            mouse_.onButtonUp(button, std::move(callback));
        return 0;
    }

    bool InputManager::removeKeyListener(Keyboard::Event event, Keyboard::Key key, int id) {
        return keyboard_.removeEventListener(event, key, id);
    }

    bool InputManager::removeKeyListener(Keyboard::Event event, int id) {
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

    bool InputManager::removeMouseListener(Mouse::Event event,
        Mouse::Button button, int id)
    {
        return mouse_.removeEventListener(event, button, id);
    }

    void InputManager::handleEvent(sf::Event event) {
        keyboard_.handleEvent(event);
        mouse_.handleEvent(event);
    }

    bool InputManager::removeMouseMovedListener(int id) {
        return mouse_.removeMouseMovedListener(id);
    }
}
