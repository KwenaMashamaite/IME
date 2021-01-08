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

#include "IME/graphics/ui/widgets/EditBox.h"
#include "IME/core/managers/ResourceManager.h"
#include <TGUI/GuiBase.hpp>

//How long the edit box takes before its completely hidden or shown
const int fadeAnimDuration_ = 100;

namespace IME::UI {
    EditBox::EditBox()
        : editBox_{tgui::EditBox::create()},
          renderer_{std::make_shared<EditBoxRenderer>()}
    {
        renderer_->setInternalPtr(editBox_->getRenderer());
        initEvents();
    }

    void EditBox::setRenderer(std::shared_ptr<EditBoxRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        editBox_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<EditBoxRenderer> EditBox::getRenderer() {
        return renderer_;
    }

    void EditBox::setDefaultText(const std::string &text) {
        editBox_->setDefaultText(text);
    }

    std::string EditBox::getDefaultText() const {
        return editBox_->getDefaultText().toAnsiString();
    }

    void EditBox::setMaximumCharacters(unsigned int maxChars) {
        editBox_->setMaximumCharacters(maxChars);
    }

    unsigned int EditBox::getMaximumCharacters() const {
        return editBox_->getMaximumCharacters();
    }

    void EditBox::limitTextWidth(bool limitWidth) {
        editBox_->limitTextWidth(limitWidth);
    }

    bool EditBox::isTextWidthLimited() const {
        return editBox_->isTextWidthLimited();
    }

    void EditBox::setReadOnly(bool readOnly) {
        editBox_->setReadOnly(readOnly);
    }

    bool EditBox::isReadOnly() const {
        return editBox_->isReadOnly();
    }

    void EditBox::setCaretPosition(std::size_t charactersBeforeCaret) {
        editBox_->setCaretPosition(charactersBeforeCaret);
    }

    std::size_t EditBox::getCaretPosition() const {
        return editBox_->getCaretPosition();
    }

    void EditBox::setSuffix(const std::string &suffix) {
        editBox_->setSuffix(suffix);
    }

    std::string EditBox::getSuffix() const {
        return editBox_->getSuffix().toAnsiString();
    }

    void EditBox::setPosition(float x, float y) {
        editBox_->setPosition({x, y});
    }

    void EditBox::setRotation(float angle) {
        editBox_->setRotation(angle);
    }

    void EditBox::setScale(float factorX, float factorY) {
        editBox_->setScale({factorX, factorY});
    }

    void EditBox::setOrigin(float x, float y) {
        editBox_->setOrigin({x, y});
    }

    Vector2f EditBox::getPosition() const {
        return {editBox_->getPosition().x, editBox_->getPosition().y};
    }

    Vector2f EditBox::getOrigin() const {
        return {editBox_->getOrigin().x, editBox_->getOrigin().y};
    }

    float EditBox::getRotation() const {
        return editBox_->getRotation();
    }

    void EditBox::move(float xOffset, float yOffset) {
        editBox_->setPosition(getPosition().x + xOffset,
            getPosition().y + yOffset);
    }

    void EditBox::rotate(float offset) {
        editBox_->setRotation(editBox_->getRotation() + offset);
    }

    void EditBox::scale(float factorX, float factorY) {
        editBox_->setScale({editBox_->getScale().x + factorX,
            editBox_->getScale().y + factorY});
    }

    void EditBox::hide() {
        editBox_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void EditBox::show() {
        editBox_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool EditBox::isHidden() const {
        return !editBox_->isVisible();
    }

    void EditBox::setEnabled(bool isEnable) {
        editBox_->setEnabled(isEnable);
    }

    bool EditBox::isEnabled() const {
        return editBox_->isEnabled();
    }

    void EditBox::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    void EditBox::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void EditBox::setTextSize(unsigned int charSize) {
        editBox_->setTextSize(charSize);
    }

    void EditBox::setText(const std::string &content) {
        editBox_->setText(content);
    }

    void EditBox::setSize(float width, float height) {
        editBox_->setSize({width, height});
    }

    Vector2f EditBox::getSize() const {
        return {editBox_->getSize().x, editBox_->getSize().y};
    }

    std::string EditBox::getText() const {
        return editBox_->getText().toAnsiString();
    }

    unsigned int EditBox::getTextSize() const {
        return editBox_->getTextSize();
    }

    std::string EditBox::getType() const {
        return "EditBox";
    }

    void EditBox::toggleVisibility() {
        editBox_->setVisible(!editBox_->isVisible());
    }

    bool EditBox::contains(float x, float y) const {
        return editBox_->isMouseOnWidget({x, y});
    }

    void EditBox::setFocused(bool isFocused) {
        editBox_->setFocused(isFocused);
    }

    bool EditBox::isFocused() const {
        return editBox_->isFocused();
    }

    std::shared_ptr<tgui::Widget> EditBox::getInternalPtr() {
        return editBox_;
    }

    Vector2f EditBox::getAbsoluteSize() {
        return {editBox_->getFullSize().x, editBox_->getFullSize().y};
    }

    void EditBox::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void EditBox::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    void EditBox::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void EditBox::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    void EditBox::initEvents() {
        editBox_->onMouseEnter([this]{emit("mouseEnter");});
        editBox_->onMouseLeave([this]{emit("mouseLeave");});
        editBox_->onFocus([this]{emit("focus");});
        editBox_->onUnfocus([this]{emit("unfocus");});
        editBox_->onTextChange([this](const tgui::String& text) {
            emit("textEnter", text.toAnsiString());
        });

        editBox_->onReturnKeyPress([this](const tgui::String& text) {
            emit("enterKeyPress", text.toAnsiString());
        });

        editBox_->onAnimationFinish([this]{emit("animationFinish");});
        editBox_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        editBox_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });

        //Events triggered by left mouse button
        editBox_->onClick([this](tgui::Vector2f mousePos){
            emit("click");
            emit("click", mousePos.x, mousePos.y);
        });

        editBox_->onMousePress([this](tgui::Vector2f mousePos) {
            emit("leftMouseDown");
            emit("leftMouseDown", mousePos.x, mousePos.y);
        });

        editBox_->onMouseRelease([this](tgui::Vector2f mousePos) {
            emit("leftMouseUp");
            emit("leftMouseUp", mousePos.x, mousePos.y);
        });

        //Events triggered by right mouse button
        editBox_->onRightMousePress([this](tgui::Vector2f mousePos){
            emit("rightMouseDown");
            emit("rightMouseDown", mousePos.x, mousePos.y);
        });

        editBox_->onRightMouseRelease([this](tgui::Vector2f mousePos){
            emit("rightMouseUp");
            emit("rightMouseUp", mousePos.x, mousePos.y);
        });

        editBox_->onRightClick([this](tgui::Vector2f mousePos){
            emit("rightClick");
            emit("rightClick", mousePos.x, mousePos.y);
        });
    }

    Vector2f EditBox::getScale() const {
        return {editBox_->getScale().x, editBox_->getScale().y};
    }
}
