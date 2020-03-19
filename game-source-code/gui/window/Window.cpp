#include "Window.h"
#include <cassert>

Globals::Dimensions Gui::Window::dimensions_{0u, 0u};

Gui::Window::Window(){
    assert(!isInstantiated_ && "Only a single instance of window can be instantiated");
    isInstantiated_ = true;
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

bool Gui::Window::pollEvent(sf::Event& event){
    return window_.pollEvent(event);
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

Globals::Position Gui::Window::getMousePosition() const {
    return {
        static_cast<float>(sf::Mouse::getPosition(window_).x),
        static_cast<float>(sf::Mouse::getPosition(window_).y)
    };
}

Gui::Window::~Window(){
    isInstantiated_ = false;
}