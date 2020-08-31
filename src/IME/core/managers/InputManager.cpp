#include "IME/core/managers/InputManager.h"

namespace IME::Input {
    int InputManager::addKeyListener(const std::string &event, Keyboard::Key key,
        Callback<> callback)
    {
        if (event == "keyDown")
            return keyboard_.onKeyDown(key, std::move(callback));
        else if (event == "keyUp")
            return keyboard_.onKeyUp(key, std::move(callback));
        return -1;
    }

    int InputManager::addAnyKeyPressedListener(Callback<> callback) {
        return keyboard_.onAnyKeyPressed(std::move(callback));
    }

    int InputManager::addMouseButtonListener(const std::string &event, Mouse::Button button,
        Callback<> callback)
    {
        if (event == "mouseButtonDown")
            mouse_.onButtonDown(button, std::move(callback));
        else if (event == "mouseButtonUp")
            mouse_.onButtonUp(button, std::move(callback));
        return 0;
    }

    bool InputManager::removeKeyListener(const std::string &event, Keyboard::Key key, int id) {
        return keyboard_.removeEventListener(event, key, id);
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

    bool InputManager::removeMouseListener(const std::string &event,
        Mouse::Button button, int id)
    {
        return mouse_.removeEventListener(event, button, id);
    }

    void InputManager::handleEvent(sf::Event event) {
        keyboard_.update(event);
        mouse_.update(event);
    }

    bool InputManager::removeMouseMovedListener(int id) {
        return mouse_.removeMouseMovedListener(id);
    }
}
