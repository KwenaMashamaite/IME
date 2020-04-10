#include "Window.h"
#include "input/Mouse.h"
#include "input/Keyboard.h"
#include <cassert>

Common::Dimensions Gui::Window::dimensions_{0u, 0u};

Gui::Window::Window(){
    assert(!isInstantiated_ && "Only a single instance of window can be instantiated");
    isInstantiated_ = true;
    subscribeToEvents();
}

void Gui::Window::create(const std::string& name, float width, float height){
    assert(width >= minWidth && "Specified width must be greater than the minimum window width");
    assert(height >= minHeight && "Specified height must be greater than the minimum window height");
    dimensions_.width = width;
    dimensions_.height = height;
    window_.create(sf::VideoMode(static_cast<unsigned int>(dimensions_.width),
        static_cast<unsigned int>(dimensions_.height)),
        name,
        sf::Style::Close
    );
    window_.setFramerateLimit(60);
    window_.setVerticalSyncEnabled(true);
}

bool Gui::Window::isOpen() const{
    return window_.isOpen();
}

void Gui::Window::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type){
            case sf::Event::Closed:
                eventEmitter_.emit("Closed");
                break;
            case sf::Event::KeyPressed:
                eventEmitter_.emit("keyPressed",
                     static_cast<Keyboard::Key>(static_cast<unsigned int>(event.key.code))
                );
                break;
            case sf::Event::KeyReleased:
                eventEmitter_.emit("keyReleased",
                     static_cast<Keyboard::Key>(static_cast<unsigned int>(event.key.code))
                );
                break;
            case sf::Event::MouseMoved:
                eventEmitter_.emit("mouseMoved", event.mouseMove.x, event.mouseMove.y);
                break;
            case sf::Event::MouseButtonPressed:
                eventEmitter_.emit("mouseButtonPressed",
                     static_cast<Mouse::Button>(static_cast<unsigned int>(event.mouseButton.button))
                );
                break;
            case sf::Event::MouseButtonReleased:
                eventEmitter_.emit("mouseButtonReleased",
                     static_cast<Mouse::Button>(static_cast<unsigned int>(event.mouseButton.button))
                );
                break;
            default:
                break;
        }
    }
}

void Gui::Window::close(){
    window_.close();
}

void Gui::Window::display(){
    window_.display();
}

void Gui::Window::clear(sf::Color colour){
    window_.clear(colour);
}

Common::Position Gui::Window::getMouseCursorPosition() const {
    return {
        static_cast<float>(sf::Mouse::getPosition(window_).x),
        static_cast<float>(sf::Mouse::getPosition(window_).y)
    };
}

Gui::Window::~Window(){
    isInstantiated_ = false;
}

void Gui::Window::subscribeToEvents() {
    eventEmitter_.addOnceListener("Closed", Callback<>([this]() {
        close();
    }));
}
