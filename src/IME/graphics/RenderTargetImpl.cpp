////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/graphics/RenderTargetImpl.h"

namespace ime::priv {
    bool RenderTargetImpl::isInstantiated_{false};

    RenderTargetImpl::RenderTargetImpl()
    {
        IME_ASSERT(!isInstantiated_, "Only a single instance of Window can be instantiated")
        isInstantiated_ = true;
    }

    void RenderTargetImpl::create(const std::string& title, unsigned int width, unsigned int height, Uint32 style) {
        title_ = title;
        window_.create(sf::VideoMode(width, height), title, static_cast<sf::Uint32>(style));
    }

    void RenderTargetImpl::setIcon(const std::string &filename) {
        std::string currentImageDir = ResourceManager::getInstance()->getPathFor(ResourceType::Image);
        ResourceManager::getInstance()->setPathFor(ResourceType::Image, "");
        try {
            const sf::Image& icon = ResourceManager::getInstance()->getImage(filename);
            window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        } catch (...) {} // No rethrow, Use current icon if set otherwise use OS icon
        ResourceManager::getInstance()->setPathFor(ResourceType::Image, currentImageDir);
    }

    void RenderTargetImpl::setTitle(const std::string &title) {
        title_ = title;
        window_.setTitle(title);
    }

    const std::string &RenderTargetImpl::getTitle() const {
        return title_;
    }

    bool RenderTargetImpl::isOpen() const{
        return window_.isOpen();
    }

    bool RenderTargetImpl::pollEvent(Event& event) {
        sf::Event sfmlEvent;
        bool eventPopped = window_.pollEvent(sfmlEvent);

        if (eventPopped)
            event = utility::convertToOwnEvent(sfmlEvent);

        return eventPopped;
    }

    void RenderTargetImpl::close() {
        window_.close();
    }

    void RenderTargetImpl::display() {
        window_.display();
    }

    void RenderTargetImpl::clear(Colour colour) {
        window_.clear(utility::convertToSFMLColour(colour));
    }

    void RenderTargetImpl::draw(const sf::Drawable &drawable) {
        window_.draw(drawable);
    }

    Vector2u RenderTargetImpl::getSize() {
        return {window_.getSize().x, window_.getSize().y};
    }

    RenderTargetImpl::~RenderTargetImpl() {
        isInstantiated_ = false;
    }
}

