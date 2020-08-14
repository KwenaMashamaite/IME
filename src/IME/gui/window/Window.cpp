#include "IME/gui/window/Window.h"
#include "IME/gui/input/Mouse.h"
#include "IME/gui/input/Keyboard.h"
#include "IME/utility/Helpers.h"
#include <SFML/Window/Event.hpp>
#include <cassert>

namespace IME::Gui {
    Dimensions Window::dimensions_{0u, 0u};

    Window::Window() {
        assert(!isInstantiated_ && "Only a single instance of Window can be instantiated");
        isInstantiated_ = true;
    }

    void Window::create(const std::string& title, float width, float height, Style style) {
        assert(width >= 0.0f && "Window width cannot be negative");
        assert(height >= 0.0f && "Window height cannot be negative");
        dimensions_ = {width, height};
        window_.create(sf::VideoMode(static_cast<unsigned int>(width),
            static_cast<unsigned int>(height)), title, static_cast<unsigned int>(style)
        );
    }

    void Window::setFramerateLimit(unsigned int framerateLimit) {
        window_.setFramerateLimit(framerateLimit);
    }

    void Window::setCursorType(Window::CursorType cursorType) {
        auto static cursor = sf::Cursor();
        if (cursor.loadFromSystem(static_cast<sf::Cursor::Type>(cursorType)))
            window_.setMouseCursor(cursor);
    }

    bool Window::isOpen() const{
        return window_.isOpen();
    }

    void Window::processEvents() {
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
                    eventEmitter_.emit("textEntered", static_cast<char>(event.text.unicode));
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

    void Window::close() {
        window_.close();
    }

    void Window::display() {
        window_.display();
    }

    void Window::clear(Colour colour) {
        window_.clear(Utility::convertTo3rdPartyColour(colour));
    }

    void Window::draw(const sf::Drawable &drawable) {
        window_.draw(drawable);
    }

    void Window::draw(IDrawable &drawable) {
        drawable.draw(*this);
    }

    Window::~Window() {
        isInstantiated_ = false;
    }

    Dimensions Window::getDimensions() {
        return dimensions_;
    }
}
