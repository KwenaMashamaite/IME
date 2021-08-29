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

#include "IME/graphics/Window.h"
#include "IME/graphics/RenderTarget.h"
#include "IME/graphics/RenderTargetImpl.h"

namespace ime {
    Window::Window(priv::RenderTarget &renderTarget) :
        renderTarget_{renderTarget},
        windowStyle_{WindowStyle::Default},
        windowStyleBeforeFullScreen_{WindowStyle::Default},
        frameRateLimit_{60},
        isVSyncEnabled_{false},
        isFullScreen_{false},
        clearColour_{ime::Colour::Black}
    {}

    void Window::setStyle(Uint32 windowStyle) {
        if (isOpen())
            windowStyle_ |= windowStyle;
        else
            windowStyle_ = windowStyle;

        auto [width, height] = getSize();
        renderTarget_.create(getTitle(), width, height, windowStyle);
    }

    Uint32 Window::getStyle() const {
        return windowStyle_;
    }

    void Window::setTitle(const std::string &title) {
       renderTarget_.getImpl()->setTitle(title);
    }

    const std::string &Window::getTitle() const {
        return renderTarget_.getImpl()->getTitle();
    }

    void Window::setPosition(const Vector2i &position) {
        renderTarget_.getImpl()->getSFMLWindow().setPosition(sf::Vector2i{position.x, position.y});
    }

    Vector2i Window::getPosition() const {
        auto [x, y] = renderTarget_.getImpl()->getSFMLWindow().getPosition();
        return {x, y};
    }

    void Window::setSize(const Vector2u &size) {
        renderTarget_.getImpl()->getSFMLWindow().setSize(sf::Vector2u{size.x, size.y});
    }

    Vector2u Window::getSize() const {
        auto [x, y] = renderTarget_.getImpl()->getSFMLWindow().getSize();
        return {x, y};
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
            auto[width, height] = Window::getFullScreenSize();
            renderTarget_.create(getTitle(), width, height, windowStyle_);
        } else {
            windowStyle_ = windowStyleBeforeFullScreen_;
            renderTarget_.create(getTitle(), sizeBeforeFullScreen_.x, sizeBeforeFullScreen_.y, windowStyleBeforeFullScreen_);
        }

        if (onFullScreenToggle_)
            onFullScreenToggle_();
    }

    bool Window::isFullScreen() const {
        return isFullScreen_;
    }

    void Window::toggleFullScreen() {
        setFullScreen(!isFullScreen_);
    }

    void Window::setVisible(bool visible) {
        renderTarget_.getImpl()->getSFMLWindow().setVisible(visible);
    }

    void Window::setMouseCursorVisible(bool visible) {
        renderTarget_.getImpl()->getSFMLWindow().setMouseCursorVisible(visible);
    }

    void Window::setMouseCursorGrabbed(bool grabbed) {
        renderTarget_.getImpl()->getSFMLWindow().setMouseCursorGrabbed(grabbed);
    }

    void Window::setFrameRateLimit(unsigned int limit) {
        if (frameRateLimit_ == limit)
            return;

        frameRateLimit_ = limit;
        renderTarget_.getImpl()->getSFMLWindow().setFramerateLimit(limit);
    }

    unsigned int Window::getFrameRateLimit() const {
        return frameRateLimit_;
    }

    void Window::setVerticalSyncEnable(bool vSyncEnable) {
        if (isVSyncEnabled_ == vSyncEnable)
            return;

        isVSyncEnabled_ = vSyncEnable;
        renderTarget_.getImpl()->getSFMLWindow().setVerticalSyncEnabled(vSyncEnable);
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
        renderTarget_.getImpl()->getSFMLWindow().close();
    }

    void Window::onClose(const Callback& callback) {
        onWindowClose_ = callback;
    }

    bool Window::isOpen() const {
        return renderTarget_.getImpl()->isOpen();
    }

    void Window::emitCloseEvent() {
        if (onWindowClose_)
            onWindowClose_();
    }

    void Window::onFullScreenToggle(const Callback &callback) {
        onFullScreenToggle_ = callback;
    }
}
