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

#include "IME/ui/widgets/Widget.h"
#include "IME/ui/widgets/WidgetImpl.h"

namespace ime::ui {
    Widget::Widget(std::unique_ptr<priv::IWidgetImpl> impl) :
        pimpl_{std::move(impl)}
    {
        auto widget = pimpl_->getInternalPtr();

        widget->onMouseEnter([this]{
            emit("mouseEnter");
        });
        
        widget->onMouseLeave([this]{
            emit("mouseLeave");
        });
        
        widget->onFocus([this]{
            emit("focus");
        });

        widget->onUnfocus([this]{
            emit("unfocus");
        });
        
        widget->onAnimationFinish([this]{
            emit("animationFinish");
        });

        widget->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        widget->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });
    }

    Widget::Widget(const Widget& other) :
        pimpl_{other.pimpl_->clone()},
        eventEmitter_{other.eventEmitter_},
        isContainer_{other.isContainer_}
    {}

    Widget &Widget::operator=(const Widget& rhs) {
        if (this != &rhs) {
            pimpl_ = rhs.pimpl_->clone();
            eventEmitter_ = rhs.eventEmitter_;
            isContainer_ = rhs.isContainer_;
        }

        return *this;
    }

    Widget::Widget(Widget&&) noexcept = default;
    Widget &Widget::operator=(Widget&&) noexcept = default;

    void Widget::setRenderer(IWidgetRenderer::Ptr renderer) {
        pimpl_->setRenderer(std::move(renderer));
    }

    IWidgetRenderer* Widget::getRenderer() {
        return pimpl_->getRenderer();
    }

    const IWidgetRenderer* Widget::getRenderer() const {
        return pimpl_->getRenderer();
    }

    void Widget::setPosition(float x, float y) {
        pimpl_->setPosition(x, y);
    }

    void Widget::setPosition(Vector2f position) {
        pimpl_->setPosition(position);
    }

    void Widget::setPosition(const std::string &x, const std::string &y) {
        pimpl_->setPosition(x, y);
    }

    Vector2f Widget::getPosition() const {
        return pimpl_->getPosition();
    }

    Vector2f Widget::getAbsolutePosition() const {
        return pimpl_->getAbsolutePosition();
    }

    void Widget::setRotation(float angle) {
        pimpl_->setRotation(angle);
    }

    void Widget::rotate(float angle) {
        pimpl_->rotate(angle);
    }

    float Widget::getRotation() const {
        return pimpl_->getRotation();
    }

    void Widget::setScale(float factorX, float factorY) {
        pimpl_->setScale(factorX, factorY);
    }

    void Widget::setScale(Vector2f scale) {
        pimpl_->setScale(scale);
    }

    void Widget::scale(float factorX, float factorY) {
        pimpl_->scale(factorX, factorY);
    }

    void Widget::scale(Vector2f factor) {
        pimpl_->scale(factor);
    }

    Vector2f Widget::getScale() const {
        return pimpl_->getScale();
    }

    void Widget::setOrigin(float x, float y) {
        pimpl_->setOrigin(x, y);
    }

    void Widget::setOrigin(Vector2f origin) {
        pimpl_->setOrigin(origin);
    }

    Vector2f Widget::getOrigin() const {
        return pimpl_->getOrigin();
    }

    void Widget::move(float offsetX, float offsetY) {
        pimpl_->move(offsetX, offsetY);
    }

    void Widget::move(Vector2f offset) {
        pimpl_->move(offset);
    }

    void Widget::setTextSize(unsigned int size) {
        pimpl_->setTextSize(size);
    }

    unsigned int Widget::getTextSize() const {
        return pimpl_->getTextSize();
    }

    void Widget::setSize(float width, float height) {
        pimpl_->setSize(width, height);
    }

    void Widget::setSize(const std::string &width, const std::string &height) {
        pimpl_->setSize(width, height);
    }

    Vector2f Widget::getSize() const {
        return pimpl_->getSize();
    }

    Vector2f Widget::getAbsoluteSize() {
        return pimpl_->getAbsoluteSize();
    }

    void Widget::setWidth(float width) {
        pimpl_->setWidth(width);
    }

    void Widget::setWidth(const std::string &width) {
        pimpl_->setWidth(width);
    }

    void Widget::setHeight(float height) {
        pimpl_->setHeight(height);
    }

    void Widget::setHeight(const std::string &height) {
        pimpl_->setHeight(height);
    }

    void Widget::setMouseCursor(CursorType cursor) {
        pimpl_->setMouseCursor(cursor);
    }

    CursorType Widget::getMouseCursor() const {
        return pimpl_->getMouseCursor();
    }

    void Widget::showWithEffect(ShowAnimationType type, Time duration) {
        pimpl_->showWithEffect(type, duration);
    }

    void Widget::hideWithEffect(ShowAnimationType type, Time duration) {
        pimpl_->hideWithEffect(type, duration);
    }

    bool Widget::isAnimationPlaying() const {
        return pimpl_->isAnimationPlaying();
    }

    void Widget::setVisible(bool visible) {
        pimpl_->setVisible(visible);
    }

    bool Widget::isVisible() const {
        return pimpl_->isVisible();
    }

    void Widget::toggleVisibility() {
        pimpl_->toggleVisibility();
    }

    void Widget::setAsContainer(bool container) {
        isContainer_ = container;
    }

    bool Widget::isContainer() const {
        return isContainer_;
    }

    bool Widget::contains(float x, float y) const {
        return pimpl_->contains(x, y);
    }

    bool Widget::unsubscribe(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }

    const std::shared_ptr<void> Widget::getInternalPtr() const {
        return pimpl_->getInternalPtr();
    }

    Widget::~Widget() = default;
}