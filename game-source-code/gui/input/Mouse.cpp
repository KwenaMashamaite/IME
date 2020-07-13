#include "Mouse.h"
#include "gui/window/Window.h"
#include <SFML/Graphics.hpp>

void Input::Mouse::initEventEmitter() {
    Gui::Window::addEventListener("mouseMoved", Callback<int, int>([](int x, int y){
        eventEmitter_.emit("mouseMoved", x, y);
    }));

    Gui::Window::addEventListener("mouseButtonPressed", Callback<Button>(
        [](Input::Mouse::Button button) {
                eventEmitter_.emit(std::to_string(static_cast<int>(button)) + "Down");
        }
    ));

    Gui::Window::addEventListener("mouseButtonReleased", Callback<Button>(
        [](Input::Mouse::Button button) {
            eventEmitter_.emit(std::to_string(static_cast<int>(button)) + "Up");
        }
    ));

    isEventEmitterInitialized_ = true;
}

bool Input::Mouse::isButtonPressed(Button button){
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
}

int Input::Mouse::onButtonUp(Mouse::Button button, Callback<> callback) {
    if (!isEventEmitterInitialized_) //Initialize event publishing
        initEventEmitter();
    return  eventEmitter_.addEventListener(
            std::to_string(static_cast<int>(button)) + "Up", std::move(callback));
}

int Input::Mouse::onButtonDown(Mouse::Button button, Callback<> callback) {
    if (!isEventEmitterInitialized_) //Initialize event publishing
        initEventEmitter();
    return eventEmitter_.addEventListener(
        std::to_string(static_cast<int>(button)) + "Down", std::move(callback));
}

int Input::Mouse::onMouseMove(Callback<int, int> callback) {
    if (!isEventEmitterInitialized_) //Initialize event publishing
        initEventEmitter();
    return eventEmitter_.addEventListener("mouseMoved", std::move(callback));
}

bool Input::Mouse::removeEventListener(const std::string& event, Mouse::Button button,int listenerId) {
    if (event == "mouseButtonDown")
        return eventEmitter_.removeEventListener(
            std::to_string(static_cast<int>(button)) + "Down", listenerId);
    else if (event == "mouseButtonUp")
        return eventEmitter_.removeEventListener(
            std::to_string(static_cast<int>(button)) + "Up", listenerId);
    return false;
}
