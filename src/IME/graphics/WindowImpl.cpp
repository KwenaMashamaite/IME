////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "WindowImpl.h"

namespace ime::priv {
    bool WindowImpl::isInstantiated_{false};

    WindowImpl::WindowImpl() :
        frameRateLimit_(0)
    {
        IME_ASSERT(!isInstantiated_, "Only a single instance of Window can be instantiated");
        isInstantiated_ = true;
    }

    void WindowImpl::create(const std::string& title, unsigned int width, unsigned int height, Window::Style style) {
        window_.create(sf::VideoMode(width, height), title, static_cast<unsigned int>(style));
    }

    void WindowImpl::setIcon(const std::string &filename) {
        auto currentImageDir = ResourceManager::getInstance()->getPathFor(ResourceType::Image);
        ResourceManager::getInstance()->setPathFor(ResourceType::Image, "");
        try {
            auto icon = ResourceManager::getInstance()->getImage(filename);
            window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        } catch (...) {} // No rethrow, Use current icon if set otherwise use OS icon
        ResourceManager::getInstance()->setPathFor(ResourceType::Image, currentImageDir);
    }

    void WindowImpl::setFramerateLimit(unsigned int framerateLimit) {
        frameRateLimit_ = framerateLimit;
        window_.setFramerateLimit(frameRateLimit_);
    }

    unsigned int WindowImpl::getFramerateLimit() const {
        return frameRateLimit_;
    }

    void WindowImpl::setVsyncEnabled(bool isVsyncEnabled) {
        window_.setVerticalSyncEnabled(isVsyncEnabled);
    }

    bool WindowImpl::isOpen() const{
        return window_.isOpen();
    }

    bool WindowImpl::pollEvent(Event& event) {
        sf::Event sfmlEvent;
        auto eventPopped = window_.pollEvent(sfmlEvent);
        if (eventPopped)
            event = utility::convertToOwnEvent(sfmlEvent);
        return eventPopped;
    }

    void WindowImpl::close() {
        window_.close();
    }

    void WindowImpl::display() {
        window_.display();
    }

    void WindowImpl::clear(Colour colour) {
        window_.clear(utility::convertToSFMLColour(colour));
    }

    void WindowImpl::draw(const sf::Drawable &drawable) {
        window_.draw(drawable);
    }

    Vector2u WindowImpl::getSize() {
        return {window_.getSize().x, window_.getSize().y};
    }

    WindowImpl::~WindowImpl() {
        isInstantiated_ = false;
    }
}

