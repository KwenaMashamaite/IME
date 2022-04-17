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

#include "IME/graphics/Window.h"
#include "IME/graphics/RenderTarget.h"
#include "IME/graphics/Texture.h"
#include "IME/utility/Helpers.h"
#include <SFML/Window/Mouse.hpp>

namespace ime {
    Window::Window(priv::RenderTarget &renderTarget) :
        renderTarget_{renderTarget},
        windowStyle_{WindowStyle::Default},
        windowStyleBeforeFullScreen_{WindowStyle::Default},
        frameRateLimit_{60},
        isVSyncEnabled_{false},
        isFullScreen_{false},
        isVisible_{false},
        isCursorVisible_{false},
        isCursorGrabbed_{false},
        clearColour_{ime::Colour::Black},
        defaultWinCloseHandlerId_{-1}
    {
        renderTarget.onCreate([this] {
            isVisible_ = true;
            isCursorVisible_ = true;
        });
    }

    void Window::setStyle(Uint32 windowStyle) {
        if (isOpen())
            windowStyle_ |= windowStyle;
        else
            windowStyle_ = windowStyle;

        Vector2u size = getSize();
        renderTarget_.create(getTitle(), size.x, size.y, windowStyle);
    }

    Uint32 Window::getStyle() const {
        return windowStyle_;
    }

    void Window::setTitle(const std::string &title) {
       renderTarget_.setTitle(title);
    }

    const std::string &Window::getTitle() const {
        return renderTarget_.getTitle();
    }

    void Window::setIcon(const std::string &filename) {
        renderTarget_.setIcon(filename);
    }

    std::string Window::getIcon() const {
        return renderTarget_.getIcon();
    }

    void Window::setPosition(const Vector2i &position) {
        renderTarget_.getThirdPartyWindow().setPosition(sf::Vector2i{position.x, position.y});
    }

    Vector2i Window::getPosition() const {
        sf::Vector2i pos = renderTarget_.getThirdPartyWindow().getPosition();
        return Vector2i{pos.x, pos.y};
    }

    void Window::setRelativeMousePosition(const Vector2i &position) {
        sf::Mouse::setPosition(sf::Vector2i{position.x, position.y}, renderTarget_.getThirdPartyWindow());
    }

    Vector2i Window::getRelativeMousePosition() const {
        sf::Vector2i position = sf::Mouse::getPosition(renderTarget_.getThirdPartyWindow());
        return {position.x, position.y};
    }

    void Window::setSize(const Vector2u &size) {
        Vector2u boundedSize = boundSize(size);

        if (getSize() != boundedSize) {
            renderTarget_.getThirdPartyWindow().setSize(sf::Vector2u{boundedSize.x, boundedSize.y});
            emitResize(boundedSize);
        }
    }

    Vector2u Window::getSize() const {
        sf::Vector2u size = renderTarget_.getThirdPartyWindow().getSize();
        return Vector2u{size.x, size.y};
    }

    void Window::setMinSize(const Vector2u &size) {
        minSize_ = size;
    }

    Vector2u Window::getMinSize() const {
        return minSize_;
    }

    void Window::setMaxSize(const Vector2u &size) {
        maxSize_ = size;
    }

    Vector2u Window::getMaxSize() const {
        return maxSize_;
    }

    bool Window::hasMinBound() const {
        return minSize_.x != 0 && minSize_.y != 0;
    }

    bool Window::hasMaxBound() const {
        return maxSize_.x != 0 && maxSize_.y != 0;
    }

    Vector2u Window::getFullScreenSize() {
        return {sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height};
    }

    void Window::setFullScreen(bool fullScreen) {
        if (isFullScreen_ == fullScreen)
            return;

        isFullScreen_ = fullScreen;

        if (fullScreen) {
            windowStyleBeforeFullScreen_ = windowStyle_;
            sizeBeforeFullScreen_ = getSize();
            windowStyle_ = WindowStyle::Fullscreen;
            Vector2u fullScreenSize = Window::getFullScreenSize();
            renderTarget_.create(getTitle(), fullScreenSize.x, fullScreenSize.y, windowStyle_);
        } else {
            windowStyle_ = windowStyleBeforeFullScreen_;
            renderTarget_.create(getTitle(), sizeBeforeFullScreen_.x, sizeBeforeFullScreen_.y, windowStyleBeforeFullScreen_);
        }

        eventEmitter_.emit("fullScreenToggle", fullScreen);
    }

    bool Window::isFullScreen() const {
        return isFullScreen_;
    }

    void Window::toggleFullScreen() {
        setFullScreen(!isFullScreen_);
    }

    void Window::setVisible(bool visible) {
        if (isVisible_ != visible) {
            isVisible_ = visible;
            renderTarget_.getThirdPartyWindow().setVisible(visible);
        }
    }

    bool Window::isVisible() const {
        return isVisible_;
    }

    void Window::setMouseCursorVisible(bool visible) {
        if (isCursorVisible_ != visible) {
            isCursorVisible_ = visible;
            renderTarget_.getThirdPartyWindow().setMouseCursorVisible(visible);
        }
    }

    bool Window::isMouseCursorVisible() const {
        return isCursorVisible_;
    }

    void Window::setMouseCursorGrabbed(bool grabbed) {
        if (isCursorGrabbed_ != grabbed) {
            isCursorGrabbed_ = grabbed;
            renderTarget_.getThirdPartyWindow().setMouseCursorGrabbed(grabbed);
        }
    }

    bool Window::isMouseCursorGrabbed() const {
        return isCursorGrabbed_;
    }

    void Window::setFrameRateLimit(unsigned int limit) {
        if (frameRateLimit_ == limit)
            return;
        else if (limit == 0)
            throw InvalidArgumentException("The frame rate limit of ime::Window must be greater than 0");

        frameRateLimit_ = limit;
        renderTarget_.getThirdPartyWindow().setFramerateLimit(limit);
    }

    unsigned int Window::getFrameRateLimit() const {
        return frameRateLimit_;
    }

    void Window::setVerticalSyncEnable(bool vSyncEnable) {
        if (isVSyncEnabled_ == vSyncEnable)
            return;

        isVSyncEnabled_ = vSyncEnable;
        renderTarget_.getThirdPartyWindow().setVerticalSyncEnabled(vSyncEnable);
    }

    bool Window::isVerticalSyncEnabled() const {
        return isVSyncEnabled_;
    }

    void Window::setClearColour(const Colour &colour) {
        clearColour_ = colour;
    }

    const Colour &Window::getClearColour() const {
        return clearColour_;
    }

    std::unique_ptr<Texture> Window::takeScreenshot() {
        IME_ASSERT(isOpen(), "The window must be created first before taking a screenshot, see ime::Engine::initialize")
        auto texture = std::make_unique<Texture>();
        texture->create(getSize());
        texture->update(renderTarget_, 0, 0);

        return texture;
    }

    void Window::takeScreenshot(const std::string &filename) {
        takeScreenshot()->saveToFile(filename);
    }

    void Window::close() {
        if (isOpen()) {
            renderTarget_.getThirdPartyWindow().close();
            emitCloseEvent();
        }
    }

    bool Window::isOpen() const {
        return renderTarget_.isOpen();
    }

    void Window::suspendedEventListener(int id, bool suspend) {
        eventEmitter_.suspendEventListener(id, suspend);
    }

    bool Window::isEventListenerSuspended(int id) const {
        return eventEmitter_.isEventListenerSuspended(id);
    }

    void Window::setDefaultOnCloseHandlerEnable(bool enable) {
        eventEmitter_.suspendEventListener("close", defaultWinCloseHandlerId_, !enable);
    }

    int Window::onClose(const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "close", callback, oneTime);
    }

    int Window::onLoseFocus(const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "loseFocus", callback, oneTime);
    }

    int Window::onGainFocus(const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "gainFocus", callback, oneTime);
    }

    int Window::onMouseEnter(const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "mouseEnter", callback, oneTime);
    }

    int Window::onMouseExit(const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "mouseExit", callback, oneTime);
    }

    int Window::onFullScreenToggle(const Callback<bool> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "fullScreenToggle", callback, oneTime);
    }

    int Window::onResize(const Callback<Vector2u>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "resize", callback, oneTime);
    }

    bool Window::removeEventListener(int id) {
        return eventEmitter_.removeEventListener(id);
    }

    Vector2u Window::boundSize(const Vector2u &size) const {
        Vector2u boundedSize = size;

        if (hasMinBound()) {
            if (size.x < minSize_.x)
                boundedSize.x = minSize_.x;

            if (size.y < minSize_.y)
                boundedSize.y = minSize_.y;
        }

        if (hasMaxBound()) {
            if (size.x > maxSize_.x)
                boundedSize.x = maxSize_.x;

            if (boundedSize.y > maxSize_.y)
                boundedSize.y = maxSize_.y;
        }

        return boundedSize;
    }

    void Window::emitCloseEvent() {
        eventEmitter_.emit("close");
    }

    void Window::emitFocusChange(bool focused) {
        if (focused)
            eventEmitter_.emit("gainFocus");
        else
            eventEmitter_.emit("loseFocus");
    }

    void Window::emitMouseCursor(bool entered) {
        if (entered)
            eventEmitter_.emit("mouseEnter");
        else
            eventEmitter_.emit("mouseExit");
    }

    void Window::emitResize(const Vector2u &newSize) {
        eventEmitter_.emit("resize", newSize);
    }
}
