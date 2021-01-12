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

#include "IME/ui/widgets/RadioButton.h"

namespace ime::ui {
    RadioButton::RadioButton(const std::string &buttonText) :
        button_{tgui::RadioButton::create()},
        renderer_{std::make_shared<RadioButtonRenderer>()}
    {
        renderer_->setInternalPtr(button_->getRenderer());
        button_->setText(buttonText);
        initEvents();
    }

    RadioButton::sharedPtr RadioButton::create(const std::string &text) {
        return std::make_shared<RadioButton>(text);
    }

    void RadioButton::setRenderer(std::shared_ptr<RadioButtonRenderer> renderer) {
        IME_ASSERT(renderer, "Cannot set nullptr as renderer");
        renderer_ = renderer;
        button_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<RadioButtonRenderer> RadioButton::getRenderer() {
        return renderer_;
    }

    void RadioButton::setTextClickable(bool acceptTextClick) {
        button_->setTextClickable(acceptTextClick);
    }

    bool RadioButton::isTextClickable() const {
        return button_->isTextClickable();
    }

    void RadioButton::setChecked(bool isChecked) {
        button_->setChecked(isChecked);
    }

    bool RadioButton::isChecked() const {
        return button_->isChecked();
    }

    void RadioButton::setText(const std::string &text) {
        button_->setText(text);
    }

    std::string RadioButton::getText() const {
        return button_->getText().toAnsiString();
    }

    void RadioButton::setTextSize(unsigned int charSize) {
        button_->setTextSize(charSize);
    }

    unsigned int RadioButton::getTextSize() const {
        return button_->getTextSize();
    }

    void RadioButton::setSize(float width, float height) {
        button_->setSize({width, height});
    }

    void RadioButton::setSize(const std::string &width, const std::string &height) {
        button_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f RadioButton::getSize() const {
        return {button_->getSize().x, button_->getSize().y};
    }

    Vector2f RadioButton::getAbsoluteSize() {
        return {button_->getFullSize().x, button_->getFullSize().y};
    }

    void RadioButton::setWidth(float width) {
        button_->setWidth(width);
    }

    void RadioButton::setWidth(const std::string &width) {
        button_->setWidth(width.c_str());
    }

    void RadioButton::setHeight(float height) {
        button_->setHeight(height);
    }

    void RadioButton::setHeight(const std::string &height) {
        button_->setHeight(height.c_str());
    }

    std::string RadioButton::getWidgetType() const {
        return "RadioButton";
    }

    void RadioButton::showWithEffect(ShowAnimationType type, int duration) {
        button_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void RadioButton::hideWithEffect(ShowAnimationType type, int duration) {
        button_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool RadioButton::isAnimationPlaying() const {
        return button_->isAnimationPlaying();
    }

    void RadioButton::setVisible(bool visible) {
        button_->setVisible(visible);
    }

    bool RadioButton::isVisible() const {
        return button_->isVisible();
    }

    void RadioButton::toggleVisibility() {
        button_->setVisible(!button_->isVisible());
    }

    bool RadioButton::contains(float x, float y) const {
        return button_->isMouseOnWidget({x, y});
    }

    void RadioButton::setPosition(float x, float y) {
        button_->setPosition({x, y});
    }

    void RadioButton::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void RadioButton::setPosition(const std::string &x, const std::string &y) {
        button_->setPosition({x.c_str(), y.c_str()});
    }

    Vector2f RadioButton::getPosition() const {
        return {button_->getPosition().x, button_->getPosition().y};
    }

    Vector2f RadioButton::getAbsolutePosition() const {
        return {button_->getAbsolutePosition().x, button_->getAbsolutePosition().y};
    }

    void RadioButton::setRotation(float angle) {
        button_->setRotation(angle);
    }

    void RadioButton::rotate(float angle) {
        button_->setRotation(button_->getRotation() + angle);
    }

    float RadioButton::getRotation() const {
        return button_->getRotation();
    }

    void RadioButton::setScale(float factorX, float factorY) {
        button_->setScale({factorX, factorY});
    }

    void RadioButton::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void RadioButton::scale(float factorX, float factorY) {
        button_->setScale({button_->getScale().x + factorX,
            button_->getScale().y + factorY});
    }

    void RadioButton::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f RadioButton::getScale() const {
        return {button_->getScale().x, button_->getScale().y};
    }

    void RadioButton::setOrigin(float x, float y) {
        button_->setOrigin({x, y});
    }

    void RadioButton::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f RadioButton::getOrigin() const {
        return {button_->getOrigin().x, button_->getOrigin().y};
    }

    void RadioButton::move(float offsetX, float offsetY) {
        button_->setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    }

    void RadioButton::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void RadioButton::setEnabled(bool isEnable) {
        button_->setEnabled(isEnable);
    }

    bool RadioButton::isEnabled() const {
        return button_->isEnabled();
    }

    void RadioButton::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    void RadioButton::setFocused(bool isFocused) {
        button_->setFocused(isFocused);
    }

    bool RadioButton::isFocused() const {
        return button_->isFocused();
    }

    std::shared_ptr<tgui::Widget> RadioButton::getInternalPtr() {
        return button_;
    }

    void RadioButton::initEvents() {
        button_->onMouseEnter([this]{emit("mouseEnter");});
        button_->onMouseLeave([this]{emit("mouseLeave");});
        button_->onFocus([this]{emit("focus");});
        button_->onUnfocus([this]{emit("unfocus");});
        button_->onCheck([this]{emit("check");});
        button_->onUncheck([this]{emit("uncheck");});
        button_->onChange([this](bool checked) {emit("checkedChanged", checked);});
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
}