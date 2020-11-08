#include "IME/graphics/Window.h"
#include "IME/utility/Helpers.h"
#include "IME/core/managers/ResourceManager.h"
#include <cassert>

namespace IME::Graphics {
    Window::Window() : frameRateLimit_(0) {
        assert(!isInstantiated_ && "Only a single instance of Window can be instantiated");
        isInstantiated_ = true;
    }

    void Window::create(const std::string& title, unsigned int width, unsigned int height, Style style) {
        assert(width >= 0 && "Window width cannot be negative");
        assert(height >= 0 && "Window height cannot be negative");
        window_.create(sf::VideoMode(width, height), title, static_cast<unsigned int>(style));
    }

    void Window::setIcon(const std::string &filename) {
        try {
            auto icon = ResourceManager::getInstance()->getImage(filename);
            window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        } catch (...) {} // No rethrow, Use current icon if set otherwise use OS icon
    }

    void Window::setFramerateLimit(unsigned int framerateLimit) {
        frameRateLimit_ = framerateLimit;
        window_.setFramerateLimit(frameRateLimit_);
    }

    void Window::setVsyncEnabled(bool isVsyncEnabled) {
        window_.setVerticalSyncEnabled(isVsyncEnabled);
    }

    unsigned int Window::getFramerateLimit() const {
        return frameRateLimit_;
    }

    bool Window::isOpen() const{
        return window_.isOpen();
    }

    bool Window::pollEvent(sf::Event& event){
        return window_.pollEvent(event);
    }

    void Window::close() {
        window_.close();
    }

    void Window::display() {
        window_.display();
    }

    void Window::clear(Colour colour) {
        window_.clear(Utility::convertToSFMLColour(colour));
    }

    void Window::draw(const sf::Drawable &drawable) {
        window_.draw(drawable);
    }

    void Window::draw(IDrawable &drawable) {
        drawable.draw(*this);
    }

    void Window::draw(IDrawable &&drawable) {
        draw(drawable);
    }

    Window::~Window() {
        isInstantiated_ = false;
    }

    Dimensions Window::getSize() {
        return {static_cast<float>(window_.getSize().x),
                static_cast<float>(window_.getSize().y)};
    }
}
