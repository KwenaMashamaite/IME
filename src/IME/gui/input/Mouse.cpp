#include "IME/gui/input/Mouse.h"
#include "IME/gui/window/Window.h"
#include <SFML/Window/Mouse.hpp>

namespace IME::Input {
    void Mouse::initEventEmitter() {
        Gui::Window::addEventListener("mouseMoved", Callback<int, int>([](int x, int y){
            eventEmitter_.emit("mouseMoved", x, y);
        }));

        Gui::Window::addEventListener("mouseButtonPressed", Callback<Button>(
            [](Button button) {
                eventEmitter_.emit(std::to_string(static_cast<int>(button)) + "Down");
            }
        ));

        Gui::Window::addEventListener("mouseButtonReleased", Callback<Button>(
            [](Button button) {
                eventEmitter_.emit(std::to_string(static_cast<int>(button)) + "Up");
            }
        ));

        isEventEmitterInitialized_ = true;
    }

    bool Mouse::isButtonPressed(Button button){
        return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
    }

    int Mouse::onButtonUp(Button button, Callback<> callback) {
        if (!isEventEmitterInitialized_) //Initialize event publishing
            initEventEmitter();
        return  eventEmitter_.addEventListener(
                std::to_string(static_cast<int>(button)) + "Up", std::move(callback));
    }

    int Mouse::onButtonDown(Button button, Callback<> callback) {
        if (!isEventEmitterInitialized_) //Initialize event publishing
            initEventEmitter();
        return eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(button)) + "Down", std::move(callback));
    }

    int Mouse::onMouseMove(Callback<int, int> callback) {
        if (!isEventEmitterInitialized_) //Initialize event publishing
            initEventEmitter();
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
