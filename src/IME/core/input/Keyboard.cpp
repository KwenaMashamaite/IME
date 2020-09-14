#include "IME/core/input/Keyboard.h"
#include <SFML/Window/Keyboard.hpp>

namespace IME::Input {
    void Keyboard::update(sf::Event event) {
        if (event.type == sf::Event::KeyPressed)
            eventEmitter_.emit(std::to_string(static_cast<int>(event.key.code)) + "Down");
        else if (event.type == sf::Event::KeyReleased) {
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

    bool Keyboard::removeEventListener(const std::string &event, Key key, int callbackId){
        if (event == "keyUp")
            return eventEmitter_.removeEventListener(
                std::to_string(static_cast<int>(key)) + "Up", callbackId);
        else if (event == "keyDown")
            return eventEmitter_.removeEventListener(
                std::to_string(static_cast<int>(key)) + "Down", callbackId);
        return false;
    }

    int Keyboard::onAnyKeyPressed(Callback<Key> callback) {
        return eventEmitter_.addEventListener("anyKeyPressed", std::move(callback));
    }
}
