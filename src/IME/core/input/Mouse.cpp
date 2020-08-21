#include "IME/core/input/Mouse.h"
#include <SFML/Window/Mouse.hpp>

namespace IME::Input {
    bool Mouse::isButtonPressed(Button button){
        return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
    }

    void Mouse::update(sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed)
            eventEmitter_.emit(std::to_string(static_cast<int>(event.mouseButton.button)) + "Down");
        else if (event.type == sf::Event::MouseButtonReleased)
            eventEmitter_.emit(std::to_string(static_cast<int>(event.mouseButton.button)) + "Up");
        else if (event.type == sf::Event::MouseMoved)
            eventEmitter_.emit("mouseMoved", event.mouseMove.x, event.mouseMove.y);
    }

    int Mouse::onButtonUp(Button button, Callback<> callback) {
        return  eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(button)) + "Up", std::move(callback));
    }

    int Mouse::onButtonDown(Button button, Callback<> callback) {
        return eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(button)) + "Down", std::move(callback));
    }

    int Mouse::onMouseMove(Callback<int, int> callback) {
        return eventEmitter_.addEventListener("mouseMoved", std::move(callback));
    }

    bool Mouse::removeEventListener(const std::string& event, Button button,int listenerId) {
        if (event == "mouseButtonDown")
            return eventEmitter_.removeEventListener(
                std::to_string(static_cast<int>(button)) + "Down", listenerId);
        else if (event == "mouseButtonUp")
            return eventEmitter_.removeEventListener(
                std::to_string(static_cast<int>(button)) + "Up", listenerId);
        return false;
    }
}
