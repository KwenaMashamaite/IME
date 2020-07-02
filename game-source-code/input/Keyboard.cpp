#include "Keyboard.h"
#include "gui/window/Window.h"
#include <SFML/Graphics.hpp>

Keyboard::Keyboard() {
    initEventEmitter();
}

bool Keyboard::isKeyPressed(Key keyId){
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyId));
}

void Keyboard::initEventEmitter() {
    //A key is considered down if it is pressed and remains pressed
    Gui::Window::addEventListener("keyPressed", Callback<Key>([](Key key){
        auto wasKeyPressed = prevKeyStateMap_[key];
        if(wasKeyPressed)
            eventEmitter_.emit(std::to_string(static_cast<int>(key)) + "Down");
        prevKeyStateMap_[key] = true;
    }));

    //A key is considered pressed if it was down and released
    Gui::Window::addEventListener("keyReleased", Callback<Key>([](Key key){
        eventEmitter_.emit(std::to_string(static_cast<int>(key)) + "Pressed");
        prevKeyStateMap_[key] = false;
    }));

    isEventEmitterInitialized_ = true;
}
