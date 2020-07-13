#include "Mouse.h"
#include "gui/window//Window.h"
#include <SFML/Graphics.hpp>

void Mouse::initEventEmitter() {
    Gui::Window::addEventListener("mouseMoved", Callback<int, int>([](int x, int y){
        eventEmitter_.emit("mouseMoved", x, y);
    }));

    Gui::Window::addEventListener("mouseButtonPressed", Callback<Mouse::Button>(
        [](Mouse::Button button) {
            auto wasButtonDown = prevButtonStateMap_[button];
            if (wasButtonDown)
                eventEmitter_.emit(std::to_string(static_cast<int>(button)) + "Held");
            else
                eventEmitter_.emit(std::to_string(static_cast<int>(button)) + "Down");
            prevButtonStateMap_[button] = true;
        }
    ));

    Gui::Window::addEventListener("mouseButtonReleased", Callback<Button>(
        [](Mouse::Button button) {
            if (button == Button::Left)
                eventEmitter_.emit("click");
            else
                eventEmitter_.emit(std::to_string(static_cast<int>(button)) + "Up");
            prevButtonStateMap_[button] = false;
        }
    ));

    isEventEmitterInitialized_ = true;
}

bool Mouse::isButtonPressed(Button button){
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
}

int Mouse::onMouseDown(Mouse::Button button, Callback<> callback) {
    if (!isEventEmitterInitialized_) //Initialize event publishing
        initEventEmitter();
    return eventEmitter_.addEventListener(
        std::to_string(static_cast<int>(button)) + "Down", std::move(callback));
}

int Mouse::onButtonUp(Mouse::Button button, Callback<> callback) {
    if (!isEventEmitterInitialized_) //Initialize event publishing
        initEventEmitter();
    return  eventEmitter_.addEventListener(
        std::to_string(static_cast<int>(button)) + "Up", std::move(callback));
}

int Mouse::onMouseClick(Callback<> callback) {
    if (!isEventEmitterInitialized_) //Initialize event publishing
        initEventEmitter();
    return eventEmitter_.addEventListener("click", std::move(callback));
}

int Mouse::onMouseMove(Callback<int, int> callback) {
    if (!isEventEmitterInitialized_) //Initialize event publishing
        initEventEmitter();
    return eventEmitter_.addEventListener("mouseMoved", std::move(callback));
}

int Mouse::onMouseHeld(Mouse::Button button, Callback<> callback) {
    if (!isEventEmitterInitialized_) //Initialize event publishing
        initEventEmitter();
    return eventEmitter_.addEventListener(
        std::to_string(static_cast<int>(button)) + "Held", std::move(callback));
}

bool Mouse::removeEventListener(const std::string& event, Mouse::Button button,int listenerId) {
    if (event == "click")
        return eventEmitter_.removeEventListener("click", listenerId);
    else if (event == "mouseButtonDown")
        return eventEmitter_.removeEventListener(
            std::to_string(static_cast<int>(button)) + "Down", listenerId);
    else if (event == "mouseButtonHeld")
        return eventEmitter_.removeEventListener(
            std::to_string(static_cast<int>(button)) + "Held", listenerId);
    return false;
}
