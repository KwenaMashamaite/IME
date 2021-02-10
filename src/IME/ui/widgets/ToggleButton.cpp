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

#include "IME/ui/widgets/ToggleButton.h"
#include <TGUI/Widgets/ToggleButton.hpp>

namespace ime::ui {
    ToggleButton::ToggleButton(const std::string &text, bool checked) :
        button_{tgui::ToggleButton::create(text, checked)},
        renderer_{std::make_shared<ButtonRenderer>()}
    {
        renderer_->setInternalPtr(button_->getRenderer());
        initEvents();
    }

    ToggleButton::sharedPtr ToggleButton::create(const std::string &text, bool checked) {
        return std::make_shared<ToggleButton>(text, checked);
    }

    ToggleButton::sharedPtr ToggleButton::copy(ToggleButton::constSharedPtr other, bool shareRenderer) {
        auto widget = create();
        widget->button_ = widget->button_->copy(other->button_);

        if (!shareRenderer)
            widget->button_->setRenderer(other->button_->getRenderer()->clone());
        widget->renderer_->setInternalPtr(other->button_->getRenderer());

        return widget;
    }

    void ToggleButton::setRenderer(ButtonRenderer::sharedPtr renderer) {
        IME_ASSERT(renderer, "Cannot set nullptr as renderer");
        renderer_ = renderer;
        button_->setRenderer(renderer->getInternalPtr()->getData());
    }

    ButtonRenderer::sharedPtr ToggleButton::getRenderer() {
        return renderer_;
    }

    void ToggleButton::setText(const std::string &text) {
        button_->setText(text);
    }

    std::string ToggleButton::getText() const {
        return button_->getText().toStdString();
    }

    void ToggleButton::setChecked(bool checked) {
        button_->setDown(checked);
    }

    bool ToggleButton::isChecked() const {
        return button_->isDown();
    }

    void ToggleButton::setTextSize(unsigned int charSize) {
        button_->setTextSize(charSize);
    }

    unsigned int ToggleButton::getTextSize() const {
        return button_->getTextSize();
    }

    void ToggleButton::setSize(float width, float height) {
        button_->setSize({width, height});
    }

    void ToggleButton::setSize(const std::string &width, const std::string &height) {
        button_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f ToggleButton::getSize() const {
        return {button_->getSize().x, button_->getSize().y};
    }

    Vector2f ToggleButton::getAbsoluteSize() {
        return {button_->getFullSize().x, button_->getFullSize().y};
    }

    void ToggleButton::setWidth(float width) {
        button_->setWidth(width);
    }

    void ToggleButton::setWidth(const std::string &width) {
        button_->setWidth(width.c_str());
    }

    void ToggleButton::setHeight(float height) {
        button_->setHeight(height);
    }

    void ToggleButton::setHeight(const std::string &height) {
        button_->setHeight(height.c_str());
    }

    void ToggleButton::setMouseCursor(CursorType cursor) {
        button_->setMouseCursor(static_cast<tgui::Cursor::Type>(cursor));
    }

    CursorType ToggleButton::getMouseCursor() const {
        return static_cast<CursorType>(button_->getMouseCursor());
    }

    std::string ToggleButton::getWidgetType() const {
        return "ToggleButton";
    }

    void ToggleButton::showWithEffect(ShowAnimationType type, int duration) {
        button_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void ToggleButton::hideWithEffect(ShowAnimationType type, int duration) {
        button_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool ToggleButton::isAnimationPlaying() const {
        return button_->isAnimationPlaying();
    }

    void ToggleButton::setVisible(bool visible) {
        button_->setVisible(visible);
    }

    bool ToggleButton::isVisible() const {
        return button_->isVisible();
    }

    void ToggleButton::toggleVisibility() {
        button_->setVisible(!button_->isVisible());
    }

    bool ToggleButton::contains(float x, float y) const {
        return button_->isMouseOnWidget({x, y});
    }

    void ToggleButton::setPosition(float x, float y) {
        button_->setPosition({x, y});
    }

    void ToggleButton::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void ToggleButton::setPosition(const std::string &x, const std::string &y) {
        button_->setPosition({x.c_str(), y.c_str()});
    }

    Vector2f ToggleButton::getPosition() const {
        return {button_->getPosition().x, button_->getPosition().y};
    }

    Vector2f ToggleButton::getAbsolutePosition() const {
        return {button_->getAbsolutePosition().x, button_->getAbsolutePosition().y};
    }

    void ToggleButton::setRotation(float angle) {
        button_->setRotation(angle);
    }

    void ToggleButton::rotate(float angle) {
        button_->setRotation(button_->getRotation() + angle);
    }

    float ToggleButton::getRotation() const {
        return button_->getRotation();
    }

    void ToggleButton::setScale(float factorX, float factorY) {
        button_->setScale({factorX, factorY});
    }

    void ToggleButton::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void ToggleButton::scale(float factorX, float factorY) {
        button_->setScale({button_->getScale().x + factorX,
            button_->getScale().y + factorY});
    }

    void ToggleButton::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f ToggleButton::getScale() const {
        return {button_->getScale().x, button_->getScale().y};
    }

    void ToggleButton::setOrigin(float x, float y) {
        button_->setOrigin({x, y});
    }

    void ToggleButton::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f ToggleButton::getOrigin() const {
        return {button_->getOrigin().x, button_->getOrigin().y};
    }

    void ToggleButton::move(float offsetX, float offsetY) {
        button_->setPosition(getPosition().x + offsetX,
            getPosition().y + offsetY);
    }

    void ToggleButton::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void ToggleButton::setEnabled(bool isEnable) {
        button_->setEnabled(isEnable);
    }

    bool ToggleButton::isEnabled() const {
        return button_->isEnabled();
    }

    void ToggleButton::toggleEnabled() {
        button_->setEnabled(!button_->isEnabled());
    }

    void ToggleButton::setFocused(bool isFocused) {
        button_->setFocused(isFocused);
    }

    bool ToggleButton::isFocused() const {
        return button_->isFocused();
    }

    std::shared_ptr<tgui::Widget> ToggleButton::getInternalPtr() {
        return button_;
    }

    void ToggleButton::initEvents() {
        button_->onMouseEnter([this]{emit("mouseEnter");});
        button_->onMouseLeave([this]{emit("mouseLeave");});
        button_->onFocus([this]{emit("focus");});
        button_->onUnfocus([this]{emit("unfocus");});
        button_->onAnimationFinish([this]{emit("animationFinish");});
        button_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        button_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });

        //Events triggered by left mouse button
        button_->onClick([this](tgui::Vector2f mousePos){
            emit("click");
            emit("click", mousePos.x, mousePos.y);
        });

        button_->onToggle([this](bool checked) {
            emit("toggle");
            emit("toggle", checked);
        });

        button_->onMousePress([this](tgui::Vector2f mousePos) {
            emit("leftMouseDown");
            emit("leftMouseDown", mousePos.x, mousePos.y);
        });

        button_->onMouseRelease([this](tgui::Vector2f mousePos) {
            emit("leftMouseUp");
            emit("leftMouseUp", mousePos.x, mousePos.y);
        });

        //Events triggered by right mouse button
        button_->onRightMousePress([this](tgui::Vector2f mousePos){
            emit("rightMouseDown");
            emit("rightMouseDown", mousePos.x, mousePos.y);
        });

        button_->onRightMouseRelease([this](tgui::Vector2f mousePos){
            emit("rightMouseUp");
            emit("rightMouseUp", mousePos.x, mousePos.y);
        });

        button_->onRightClick([this](tgui::Vector2f mousePos){
            emit("rightClick");
            emit("rightClick", mousePos.x, mousePos.y);
        });
    }
}
