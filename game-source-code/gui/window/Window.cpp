#include "Window.h"
#include "../input/Mouse.h"
#include "../input/Keyboard.h"
#include <cassert>

Common::Dimensions Gui::Window::dimensions_{0u, 0u};

Gui::Window::Window(){
    assert(!isInstantiated_ && "Only a single instance of Window can be instantiated");
    isInstantiated_ = true;
}

void Gui::Window::create(const std::string& name, float width, float height){
    assert(width >= 0.0f && "Window width cannot be negative");
    assert(height >= 0.0f && "Window height cannot be negative");
    dimensions_ = {width, height};
    window_.create(sf::VideoMode(static_cast<unsigned int>(width),
        static_cast<unsigned int>(height)),name,sf::Style::Close
    );
}

void Gui::Window::setFramerateLimit(unsigned int framerateLimit) {
    window_.setFramerateLimit(framerateLimit);
}

bool Gui::Window::isOpen() const{
    return window_.isOpen();
}

void Gui::Window::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type){
            case sf::Event::Closed:
                eventEmitter_.emit("closed");
                break;
            case sf::Event::MouseEntered:
                eventEmitter_.emit("mouseEntered");
                break;
            case sf::Event::MouseLeft:
                eventEmitter_.emit("mouseLeft");
                break;
            case sf::Event::LostFocus:
                eventEmitter_.emit("lostFocus");
                break;
            case sf::Event::GainedFocus:
                eventEmitter_.emit("gainedFocus");
                break;
            case sf::Event::Resized:
                eventEmitter_.emit("resized", event.size.width, event.size.height);
                break;
            case sf::Event::TextEntered:
                eventEmitter_.emit("textEntered", event.text);
                break;
            case sf::Event::KeyPressed:
                eventEmitter_.emit("keyPressed",
                     static_cast<Input::Keyboard::Key>(static_cast<unsigned int>(event.key.code))
                );
                break;
            case sf::Event::KeyReleased:
                eventEmitter_.emit("keyReleased",
                     static_cast<Input::Keyboard::Key>(static_cast<unsigned int>(event.key.code))
                );
                break;
            case sf::Event::MouseMoved:
                eventEmitter_.emit("mouseMoved", event.mouseMove.x, event.mouseMove.y);
                break;
            case sf::Event::MouseButtonPressed:
                eventEmitter_.emit("mouseButtonPressed",
                     static_cast<Input::Mouse::Button>(static_cast<unsigned int>(event.mouseButton.button))
                );
                break;
            case sf::Event::MouseButtonReleased:
                eventEmitter_.emit("mouseButtonReleased",
                     static_cast<Input::Mouse::Button>(static_cast<unsigned int>(event.mouseButton.button))
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

void Gui::Window::draw(const sf::Drawable &drawable) {
    window_.draw(drawable);
}

void Gui::Window::draw(Gui::IDrawable &drawable) {
    drawable.draw(*this);
}

Gui::Window::~Window(){
    isInstantiated_ = false;
}
