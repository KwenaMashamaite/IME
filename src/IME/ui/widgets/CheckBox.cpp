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

#include "IME/ui/widgets/CheckBox.h"

namespace ime::ui {
    CheckBox::CheckBox(const std::string &text) :
        checkBox_{tgui::CheckBox::create(text)},
        renderer_{std::make_shared<CheckBoxRenderer>()}
    {
        renderer_->setInternalPtr(checkBox_->getRenderer());
        initEvents();
    }

    CheckBox::sharedPtr CheckBox::create(const std::string &text) {
        return std::make_shared<CheckBox>(text);
    }

    CheckBox::sharedPtr CheckBox::copy(CheckBox::constSharedPtr other,
        bool shareRenderer)
    {
        auto widget = create();
        widget->checkBox_ = widget->checkBox_->copy(other->checkBox_);

        if (!shareRenderer)
            widget->checkBox_->setRenderer(other->checkBox_->getRenderer()->clone());
        widget->renderer_->setInternalPtr(other->checkBox_->getRenderer());

        return widget;
    }

    void CheckBox::setRenderer(std::shared_ptr<CheckBoxRenderer> renderer) {
        IME_ASSERT(renderer, "Cannot set nullptr as renderer");
        renderer_ = renderer;
        checkBox_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<CheckBoxRenderer> CheckBox::getRenderer() {
        return renderer_;
    }

    void CheckBox::setTextClickable(bool acceptTextClick) {
        checkBox_->setTextClickable(acceptTextClick);
    }

    bool CheckBox::isTextClickable() const {
        return checkBox_->isTextClickable();
    }

    void CheckBox::setChecked(bool isChecked) {
        checkBox_->setChecked(isChecked);
    }

    bool CheckBox::isChecked() const {
        return checkBox_->isChecked();
    }

    void CheckBox::setPosition(float x, float y) {
        checkBox_->setPosition({x, y});
    }

    void CheckBox::setRotation(float angle) {
        checkBox_->setRotation(angle);
    }

    void CheckBox::setScale(float factorX, float factorY) {
        checkBox_->setScale({factorX, factorY});
    }

    void CheckBox::setOrigin(float x, float y) {
        checkBox_->setOrigin({x, y});
    }

    Vector2f CheckBox::getPosition() const {
        return {checkBox_->getPosition().x, checkBox_->getPosition().y};
    }

    Vector2f CheckBox::getAbsolutePosition() const {
        return {checkBox_->getAbsolutePosition().x, checkBox_->getAbsolutePosition().y};
    }

    Vector2f CheckBox::getOrigin() const {
        return {checkBox_->getOrigin().x, checkBox_->getOrigin().y};
    }

    float CheckBox::getRotation() const {
        return checkBox_->getRotation();
    }

    void CheckBox::move(float xOffset, float yOffset) {
        checkBox_->setPosition(getPosition().x + xOffset,
            getPosition().y + yOffset);
    }

    void CheckBox::rotate(float offset) {
        checkBox_->setRotation(checkBox_->getRotation() + offset);
    }

    void CheckBox::scale(float factorX, float factorY) {
        checkBox_->setScale({checkBox_->getScale().x + factorX,
            checkBox_->getScale().y + factorY});
    }

    void CheckBox::setEnabled(bool isEnable) {
        checkBox_->setEnabled(isEnable);
    }

    bool CheckBox::isEnabled() const {
        return checkBox_->isEnabled();
    }

    void CheckBox::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    void CheckBox::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void CheckBox::setPosition(const std::string &x, const std::string &y) {
        checkBox_->setPosition({x.c_str(), y.c_str()});
    }

    void CheckBox::setTextSize(unsigned int charSize) {
        checkBox_->setTextSize(charSize);
    }

    void CheckBox::setText(const std::string &content) {
        checkBox_->setText(content);
    }

    void CheckBox::setSize(float width, float height) {
        checkBox_->setSize({width, height});
    }

    void CheckBox::setSize(const std::string &width, const std::string &height) {
        checkBox_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f CheckBox::getSize() const {
        return {checkBox_->getSize().x, checkBox_->getSize().y};
    }

    std::string CheckBox::getText() const {
        return checkBox_->getText().toStdString();
    }

    unsigned int CheckBox::getTextSize() const {
        return checkBox_->getTextSize();
    }

    std::string CheckBox::getWidgetType() const {
        return "CheckBox";
    }

    void CheckBox::showWithEffect(ShowAnimationType type, int duration) {
        checkBox_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void CheckBox::hideWithEffect(ShowAnimationType type, int duration) {
        checkBox_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool CheckBox::isAnimationPlaying() const {
        return checkBox_->isAnimationPlaying();
    }

    void CheckBox::setVisible(bool visible) {
        checkBox_->setVisible(visible);
    }

    bool CheckBox::isVisible() const {
        return checkBox_->isVisible();
    }

    void CheckBox::toggleVisibility() {
        checkBox_->setVisible(!checkBox_->isVisible());
    }

    bool CheckBox::contains(float x, float y) const {
        return checkBox_->isMouseOnWidget({x, y});
    }

    void CheckBox::setFocused(bool isFocused) {
        checkBox_->setFocused(isFocused);
    }

    bool CheckBox::isFocused() const {
        return checkBox_->isFocused();
    }

    std::shared_ptr<tgui::Widget> CheckBox::getInternalPtr() {
        return checkBox_;
    }

    Vector2f CheckBox::getAbsoluteSize() {
        return {checkBox_->getFullSize().x, checkBox_->getFullSize().y};
    }

    void CheckBox::setWidth(float width) {
        checkBox_->setWidth(width);
    }

    void CheckBox::setWidth(const std::string &width) {
        checkBox_->setWidth(width.c_str());
    }

    void CheckBox::setHeight(float height) {
        checkBox_->setHeight(height);
    }

    void CheckBox::setHeight(const std::string &height) {
        checkBox_->setHeight(height.c_str());
    }

    void CheckBox::setMouseCursor(CursorType cursor) {
        checkBox_->setMouseCursor(static_cast<tgui::Cursor::Type>(static_cast<int>(cursor)));
    }

    CursorType CheckBox::getMouseCursor() const {
        return static_cast<CursorType>(static_cast<int>(checkBox_->getMouseCursor()));
    }

    void CheckBox::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void CheckBox::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    void CheckBox::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void CheckBox::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    void CheckBox::initEvents() {
        checkBox_->onMouseEnter([this]{emit("mouseEnter");});
        checkBox_->onMouseLeave([this]{emit("mouseLeave");});
        checkBox_->onFocus([this]{emit("focus");});
        checkBox_->onUnfocus([this]{emit("unfocus");});
        checkBox_->onCheck([this]{emit("check");});
        checkBox_->onUncheck([this]{emit("uncheck");});
        checkBox_->onChange([this](bool checked) {emit("checkedChanged", checked);});
        checkBox_->onAnimationFinish([this]{emit("animationFinish");});
        checkBox_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        checkBox_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });

        //Events triggered by left mouse button
        checkBox_->onClick([this](tgui::Vector2f mousePos){
            emit("click");
            emit("click", mousePos.x, mousePos.y);
        });

        checkBox_->onMousePress([this](tgui::Vector2f mousePos) {
            emit("leftMouseDown");
            emit("leftMouseDown", mousePos.x, mousePos.y);
        });

        checkBox_->onMouseRelease([this](tgui::Vector2f mousePos) {
            emit("leftMouseUp");
            emit("leftMouseUp", mousePos.x, mousePos.y);
        });

        //Events triggered by right mouse button
        checkBox_->onRightMousePress([this](tgui::Vector2f mousePos){
            emit("rightMouseDown");
            emit("rightMouseDown", mousePos.x, mousePos.y);
        });

        checkBox_->onRightMouseRelease([this](tgui::Vector2f mousePos){
            emit("rightMouseUp");
            emit("rightMouseUp", mousePos.x, mousePos.y);
        });

        checkBox_->onRightClick([this](tgui::Vector2f mousePos){
            emit("rightClick");
            emit("rightClick", mousePos.x, mousePos.y);
        });
    }

    Vector2f CheckBox::getScale() const {
        return {checkBox_->getScale().x, checkBox_->getScale().y};
    }
}