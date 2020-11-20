////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

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

    void Window::draw(const IDrawable &drawable) {
        drawable.draw(*this);
    }

    Window::~Window() {
        isInstantiated_ = false;
    }

    Vector2u Window::getSize() {
        return {window_.getSize().x, window_.getSize().y};
    }
}
