#include "IME/gui/input/Keyboard.h"
#include "IME/gui/window/Window.h"
#include <SFML/Window/Keyboard.hpp>

namespace IME::Input {
    Keyboard::Keyboard() {
        initEventEmitter();
    }

    void Keyboard::initEventEmitter() {
        Gui::Window::addEventListener("keyPressed", Callback<Key>([](Key key){
            eventEmitter_.emit(std::to_string(static_cast<int>(key)) + "Down");
        }));

        Gui::Window::addEventListener("keyReleased", Callback<Key>([](Key key){
            eventEmitter_.emit(std::to_string(static_cast<int>(key)) + "Up");
        }));

        isEventEmitterInitialized_ = true;
    }

    bool Keyboard::isKeyPressed(Key keyId){
        return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyId));
    }

    int Keyboard::onKeyUp(Key key, Callback<> callback) {
        if (!isEventEmitterInitialized_) //Function accessed without instantiation
            initEventEmitter();
        return eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(key)) + "Up", std::move(callback));
    }

    int Keyboard::onKeyDown(Key key, Callback<> callback) {
        if (!isEventEmitterInitialized_) //Function accessed without instantiation
            initEventEmitter();
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
}
