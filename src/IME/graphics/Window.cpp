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
#include "IME/graphics/WindowImpl.h"

namespace ime {
    Window::Window() :
        pImpl_{std::make_unique<priv::WindowImpl>()}
    {}

    void Window::create(const std::string& title, unsigned int width, unsigned int height, Style style) {
        pImpl_->create(title, width, height, style);
    }

    void Window::setIcon(const std::string &filename) {
        pImpl_->setIcon(filename);
    }

    void Window::setFramerateLimit(unsigned int framerateLimit) {
        pImpl_->setFramerateLimit(framerateLimit);
    }

    void Window::setVsyncEnabled(bool isVsyncEnabled) {
        pImpl_->setVsyncEnabled(isVsyncEnabled);
    }

    unsigned int Window::getFramerateLimit() const {
        return pImpl_->getFramerateLimit();
    }

    Vector2u Window::getSize() {
        return pImpl_->getSize();
    }

    bool Window::isOpen() const{
        return pImpl_->isOpen();
    }

    bool Window::pollEvent(Event& event, WindowPassKey) {
        return pImpl_->pollEvent(event);
    }

    void Window::close() {
        pImpl_->close();
    }

    void Window::display() {
        pImpl_->display();
    }

    void Window::clear(Colour colour) {
        pImpl_->clear(colour);
    }

    const std::unique_ptr<priv::WindowImpl> &Window::getImpl() const {
        return pImpl_;
    }

    void Window::draw(const Drawable &drawable) {
        drawable.draw(*this);
    }

    Window::~Window() = default;
}
