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

#include "IME/ui/widgets/Button.h"
#include <cassert>

namespace ime::ui {
    Button::Button(const std::string &buttonText) :
        button_{tgui::Button::create(buttonText)},
        renderer_{std::make_shared<ButtonRenderer>()}
    {
        renderer_->setInternalPtr(button_->getRenderer());
        initEvents();
    }

    Button::sharedPtr Button::create(const std::string &text) {
        return std::make_shared<Button>(text);
    }

    void Button::setRenderer(std::shared_ptr<ButtonRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        button_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<ButtonRenderer> Button::getRenderer() {
        return renderer_;
    }

    void Button::setPosition(float x, float y) {
        button_->setPosition({x, y});
    }

    void Button::setRotation(float angle) {
        button_->setRotation(angle);
    }

    void Button::setScale(float factorX, float factorY) {
        button_->setScale({factorX, factorY});
    }

    void Button::setOrigin(float x, float y) {
        button_->setOrigin({x, y});
    }

    Vector2f Button::getPosition() const {
        return {button_->getPosition().x, button_->getPosition().y};
    }

    Vector2f Button::getAbsolutePosition() const {
        return {button_->getAbsolutePosition().x, button_->getAbsolutePosition().y};
    }

    Vector2f Button::getOrigin() const {
        return {button_->getOrigin().x, button_->getOrigin().y};
    }

    float Button::getRotation() const {
        return button_->getRotation();
    }

    void Button::move(float xOffset, float yOffset) {
        button_->setPosition(getPosition().x + xOffset,
                             getPosition().y + yOffset);
    }

    void Button::rotate(float offset) {
        button_->setRotation(button_->getRotation() + offset);
    }

    void Button::scale(float factorX, float factorY) {
        button_->setScale({button_->getScale().x + factorX,
            button_->getScale().y + factorY});
    }

    void Button::setEnabled(bool isEnable) {
        button_->setEnabled(isEnable);
    }

    bool Button::isEnabled() const {
        return button_->isEnabled();
    }

    void Button::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    void Button::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void Button::setPosition(const std::string &x, const std::string &y) {
        button_->setPosition({x.c_str(), y.c_str()});
    }

    void Button::setTextSize(unsigned int charSize) {
        button_->setTextSize(charSize);
    }

    void Button::setText(const std::string &content) {
        button_->setText(content);
    }

    void Button::setSize(float width, float height) {
        button_->setSize({width, height});
    }

    void Button::setSize(const std::string &width, const std::string &height) {
        button_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f Button::getSize() const {
        return {button_->getSize().x, button_->getSize().y};
    }

    std::string Button::getText() const {
        return button_->getText().toAnsiString();
    }

    Vector2f Button::getAbsoluteSize() {
        return {button_->getFullSize().x, button_->getFullSize().y};
    }

    void Button::setWidth(float width) {
        button_->setWidth(width);
    }

    void Button::setWidth(const std::string &width) {
        button_->setWidth(width.c_str());
    }

    void Button::setHeight(float height) {
        button_->setHeight(height);
    }

    void Button::setHeight(const std::string &height) {
        button_->setHeight(height.c_str());
    }

    unsigned int Button::getTextSize() const {
        return button_->getTextSize();
    }

    std::string Button::getWidgetType() const {
        return "Button";
    }

    void Button::showWithEffect(ShowAnimationType type, int duration) {
        button_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void Button::hideWithEffect(ShowAnimationType type, int duration) {
        button_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool Button::isAnimationPlaying() const {
        return button_->isAnimationPlaying();
    }

    void Button::setVisible(bool visible) {
        button_->setVisible(visible);
    }

    bool Button::isVisible() const {
        return button_->isVisible();
    }

    void Button::toggleVisibility() {
        button_->setVisible(!button_->isVisible());
    }

    bool Button::contains(float x, float y) const {
        return button_->isMouseOnWidget({x, y});
    }

    void Button::setFocused(bool isFocused) {
        button_->setFocused(isFocused);
    }

    bool Button::isFocused() const {
        return button_->isFocused();
    }

    std::shared_ptr<tgui::Widget> Button::getInternalPtr() {
        return button_;
    }

    void Button::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void Button::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    void Button::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void Button::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    void Button::initEvents() {
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

    Vector2f Button::getScale() const {
        return {button_->getScale().x, button_->getScale().y};
    }
}
