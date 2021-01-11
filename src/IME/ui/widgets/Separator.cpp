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

#include "IME/ui/widgets/Separator.h"
#include <cassert>

namespace ime::ui {
    Separator::Separator() :
        separator_{tgui::SeparatorLine::create()},
        renderer_{std::make_shared<SeparatorRenderer>()}
    {
        renderer_->setInternalPtr(separator_->getRenderer());
        initEvents();
    }

    Separator::sharedPtr Separator::create() {
        return std::make_shared<Separator>();
    }

    void Separator::setRenderer(std::shared_ptr<SeparatorRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        separator_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<SeparatorRenderer> Separator::getRenderer() {
        return renderer_;
    }

    void Separator::setTextSize(unsigned int charSize) {
        separator_->setTextSize(charSize);
    }

    unsigned int Separator::getTextSize() const {
        return separator_->getTextSize();
    }

    void Separator::setSize(float width, float height) {
        separator_->setSize({width, height});
    }

    void Separator::setSize(const std::string &width, const std::string &height) {
        separator_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f Separator::getSize() const {
        return {separator_->getSize().x, separator_->getSize().y};
    }

    Vector2f Separator::getAbsoluteSize() {
        return {separator_->getFullSize().x, separator_->getFullSize().y};
    }

    void Separator::setWidth(float width) {
        separator_->setWidth(width);
    }

    void Separator::setWidth(const std::string &width) {
        separator_->setWidth(width.c_str());
    }

    void Separator::setHeight(float height) {
        separator_->setHeight(height);
    }

    void Separator::setHeight(const std::string &height) {
        separator_->setHeight(height.c_str());
    }

    std::string Separator::getWidgetType() const {
        return "Separator";
    }

    void Separator::showWithEffect(ShowAnimationType type, int duration) {
        separator_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void Separator::hideWithEffect(ShowAnimationType type, int duration) {
        separator_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool Separator::isAnimationPlaying() const {
        return separator_->isAnimationPlaying();
    }

    void Separator::setVisible(bool visible) {
        separator_->setVisible(visible);
    }

    bool Separator::isVisible() const {
        return separator_->isVisible();
    }

    void Separator::toggleVisibility() {
        separator_->setVisible(!separator_->isVisible());
    }

    bool Separator::contains(float x, float y) const {
        return separator_->isMouseOnWidget({x, y});
    }

    void Separator::setPosition(float x, float y) {
        separator_->setPosition({x, y});
    }

    void Separator::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void Separator::setPosition(const std::string &x, const std::string &y) {
        separator_->setPosition({x.c_str(), y.c_str()});
    }

    Vector2f Separator::getPosition() const {
        return {separator_->getPosition().x, separator_->getPosition().y};
    }

    Vector2f Separator::getAbsolutePosition() const {
        return {separator_->getAbsolutePosition().x, separator_->getAbsolutePosition().y};
    }

    void Separator::setRotation(float angle) {
        separator_->setRotation(angle);
    }

    void Separator::rotate(float angle) {
        separator_->setRotation(separator_->getRotation() + angle);
    }

    float Separator::getRotation() const {
        return separator_->getRotation();
    }

    void Separator::setScale(float factorX, float factorY) {
        separator_->setScale({factorX, factorY});
    }

    void Separator::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void Separator::scale(float factorX, float factorY) {
        separator_->setScale({separator_->getScale().x + factorX,
                           separator_->getScale().y + factorY});
    }

    void Separator::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f Separator::getScale() const {
        return {separator_->getScale().x, separator_->getScale().y};
    }

    void Separator::setOrigin(float x, float y) {
        separator_->setOrigin({x, y});
    }

    void Separator::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f Separator::getOrigin() const {
        return {separator_->getOrigin().x, separator_->getOrigin().y};
    }

    void Separator::move(float offsetX, float offsetY) {
        separator_->setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    }

    void Separator::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void Separator::setEnabled(bool isEnable) {
        separator_->setEnabled(isEnable);
    }

    bool Separator::isEnabled() const {
        return separator_->isEnabled();
    }

    void Separator::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    void Separator::setFocused(bool isFocused) {
        separator_->setFocused(isFocused);
    }

    bool Separator::isFocused() const {
        return separator_->isFocused();
    }

    std::shared_ptr<tgui::Widget> Separator::getInternalPtr() {
        return separator_;
    }

    void Separator::initEvents() {
        separator_->onMouseEnter([this]{emit("mouseEnter");});
        separator_->onMouseLeave([this]{emit("mouseLeave");});
        separator_->onFocus([this]{emit("focus");});
        separator_->onUnfocus([this]{emit("unfocus");});
        separator_->onAnimationFinish([this]{emit("animationFinish");});
        separator_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        separator_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });

        //Events triggered by left mouse button
        separator_->onClick([this](tgui::Vector2f mousePos){
            emit("click");
            emit("click", mousePos.x, mousePos.y);
        });

        separator_->onMousePress([this](tgui::Vector2f mousePos) {
            emit("leftMouseDown");
            emit("leftMouseDown", mousePos.x, mousePos.y);
        });

        separator_->onMouseRelease([this](tgui::Vector2f mousePos) {
            emit("leftMouseUp");
            emit("leftMouseUp", mousePos.x, mousePos.y);
        });

        //Events triggered by right mouse button
        separator_->onRightMousePress([this](tgui::Vector2f mousePos){
            emit("rightMouseDown");
            emit("rightMouseDown", mousePos.x, mousePos.y);
        });

        separator_->onRightMouseRelease([this](tgui::Vector2f mousePos){
            emit("rightMouseUp");
            emit("rightMouseUp", mousePos.x, mousePos.y);
        });

        separator_->onRightClick([this](tgui::Vector2f mousePos){
            emit("rightClick");
            emit("rightClick", mousePos.x, mousePos.y);
        });
    }
}