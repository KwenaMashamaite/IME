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

#include "IME/ui/widgets/BitmapButton.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>
#include "IME/core/managers/ResourceManager.h"
#include <cassert>

//How long the button takes before its completely hidden or shown
const int fadeAnimDuration_ = 100;

namespace ime::ui {
    BitmapButton::BitmapButton(const std::string &buttonText) :
        button_{tgui::BitmapButton::create(buttonText)},
        renderer_{std::make_shared<ButtonRenderer>()}
    {
        renderer_->setInternalPtr(button_->getRenderer());
        initEvents();
    }

    std::shared_ptr<BitmapButton> BitmapButton::create(const std::string &text) {
        return std::make_shared<BitmapButton>(text);
    }

    void BitmapButton::setRenderer(std::shared_ptr<ButtonRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        button_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<ButtonRenderer> BitmapButton::getRenderer() {
        return renderer_;
    }
    
    void BitmapButton::setImage(const std::string &filename) {
        button_->setImage(ime::ResourceManager::getInstance()->getTexture(filename));
    }

    void BitmapButton::setImageScaling(float relativeHeight) {
        button_->setImageScaling(relativeHeight);
    }

    float BitmapButton::getImageScaling() const {
        return button_->getImageScaling();
    }

    void BitmapButton::setPosition(float x, float y) {
        button_->setPosition({x, y});
    }

    void BitmapButton::setRotation(float angle) {
        button_->setRotation(angle);
    }

    void BitmapButton::setScale(float factorX, float factorY) {
        button_->setScale({factorX, factorY});
    }

    void BitmapButton::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void BitmapButton::setOrigin(float x, float y) {
        button_->setOrigin({x, y});
    }

    Vector2f BitmapButton::getPosition() const {
        return {button_->getPosition().x, button_->getPosition().y};
    }

    Vector2f BitmapButton::getOrigin() const {
        return {button_->getOrigin().x, button_->getOrigin().y};
    }

    float BitmapButton::getRotation() const {
        return button_->getRotation();
    }

    void BitmapButton::move(float xOffset, float yOffset) {
        button_->setPosition(getPosition().x + xOffset,
            getPosition().y + yOffset);
    }

    void BitmapButton::rotate(float offset) {
        button_->setRotation(button_->getRotation() + offset);
    }

    void BitmapButton::scale(float factorX, float factorY) {
        button_->setScale({button_->getScale().x + factorX,
    button_->getScale().y + factorY});
    }

    void BitmapButton::hide() {
        button_->hideWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    void BitmapButton::show() {
        button_->showWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    bool BitmapButton::isHidden() const {
        return !button_->isVisible();
    }

    void BitmapButton::setEnabled(bool isEnable) {
        button_->setEnabled(isEnable);
    }

    bool BitmapButton::isEnabled() const {
        return button_->isEnabled();
    }

    void BitmapButton::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    void BitmapButton::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void BitmapButton::setPosition(const std::string &x, const std::string &y) {
        button_->setPosition({x.c_str(), y.c_str()});
    }

    void BitmapButton::setTextSize(unsigned int charSize) {
        button_->setTextSize(charSize);
    }

    void BitmapButton::setText(const std::string &content) {
        button_->setText(content);
    }

    void BitmapButton::setSize(float width, float height) {
        button_->setSize({width, height});
    }

    void BitmapButton::setSize(const std::string &width, const std::string &height) {
        button_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f BitmapButton::getSize() const {
        return {button_->getSize().x, button_->getSize().y};
    }

    std::string BitmapButton::getText() const {
        return button_->getText().toAnsiString();
    }

    unsigned int BitmapButton::getTextSize() const {
        return button_->getTextSize();
    }

    std::string BitmapButton::getType() const {
        return "BitmapButton";
    }

    void BitmapButton::toggleVisibility() {
        button_->setVisible(!button_->isVisible());
    }

    bool BitmapButton::contains(float x, float y) const {
        return button_->isMouseOnWidget({x, y});
    }

    void BitmapButton::setFocused(bool isFocused) {
        button_->setFocused(isFocused);
    }

    bool BitmapButton::isFocused() const {
        return button_->isFocused();
    }

    std::shared_ptr<tgui::Widget> BitmapButton::getInternalPtr() {
        return button_;
    }

    Vector2f BitmapButton::getAbsoluteSize() {
        return {button_->getFullSize().x, button_->getFullSize().y};
    }

    void BitmapButton::setWidth(float width) {
        button_->setWidth(width);
    }

    void BitmapButton::setWidth(const std::string &width) {
        button_->setWidth(width.c_str());
    }

    void BitmapButton::setHeight(float height) {
        button_->setHeight(height);
    }

    void BitmapButton::setHeight(const std::string &height) {
        button_->setHeight(height.c_str());
    }

    void BitmapButton::initEvents() {
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

    void BitmapButton::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    void BitmapButton::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void BitmapButton::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f BitmapButton::getScale() const {
        return {button_->getScale().x, button_->getScale().y};
    }
}
