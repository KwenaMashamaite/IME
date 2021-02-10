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

#include "IME/ui/widgets/SpinControl.h"
#include <TGUI/Widgets/SpinControl.hpp>

namespace ime::ui {
    SpinControl::SpinControl(float minValue, float maxValue, float initialValue,
        unsigned int decimal, float step) :
            spinControl_{tgui::SpinControl::create(minValue, maxValue, initialValue, decimal, step)},
            spinButtonRenderer_{std::make_shared<SpinButtonRenderer>()}
    {
        spinButtonRenderer_->setInternalPtr(spinControl_->getSpinButtonRenderer());
        initEvents();
    }

    SpinControl::sharedPtr SpinControl::create(float minValue, float maxValue, 
        float initialValue, unsigned int decimal, float step) 
    {
        return std::make_shared<SpinControl>(minValue, maxValue, initialValue, decimal, step);
    }

    SpinControl::sharedPtr SpinControl::copy(SpinControl::constSharedPtr other, bool shareRenderer) {
        auto widget = create();
        widget->spinControl_ = widget->spinControl_->copy(other->spinControl_);

        if (!shareRenderer)
            widget->spinControl_->setRenderer(other->spinControl_->getRenderer()->clone());
        widget->spinButtonRenderer_->setInternalPtr(other->spinControl_->getRenderer());

        return widget;
    }

    void SpinControl::setSpinButtonRenderer(SpinButtonRenderer::sharedPtr renderer) {
        IME_ASSERT(renderer, "Cannot set nullptr as renderer");
        spinButtonRenderer_ = renderer;
        spinControl_->setRenderer(renderer->getInternalPtr()->getData());
    }

    SpinButtonRenderer::sharedPtr SpinControl::getSpinButtonRenderer() {
        return spinButtonRenderer_;
    }

    void SpinControl::setMinimumValue(float minValue) {
        spinControl_->setMinimum(minValue);
    }

    float SpinControl::getMinimumValue() const {
        return spinControl_->getMinimum();
    }

    void SpinControl::setMaximumValue(float maxValue) {
        spinControl_->setMaximum(maxValue);
    }

    float SpinControl::getMaximumValue() const {
        return spinControl_->getMaximum();
    }

    void SpinControl::setValue(float value) {
        spinControl_->setValue(value);
    }

    float SpinControl::getValue() const {
        return spinControl_->getValue();
    }

    void SpinControl::setStep(float step) {
        spinControl_->setStep(step);
    }

    float SpinControl::getStep() const {
        return spinControl_->getStep();
    }

    void SpinControl::setDecimalPlaces(unsigned int decimalPlaces) {
        spinControl_->setDecimalPlaces(decimalPlaces);
    }

    unsigned int SpinControl::getDecimalPlaces() const {
        return spinControl_->getDecimalPlaces();
    }

    void SpinControl::setTextSize(unsigned int charSize) {
        spinControl_->setTextSize(charSize);
    }

    unsigned int SpinControl::getTextSize() const {
        return spinControl_->getTextSize();
    }

    void SpinControl::setSize(float width, float height) {
        spinControl_->setSize({width, height});
    }

    void SpinControl::setSize(const std::string &width, const std::string &height) {
        spinControl_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f SpinControl::getSize() const {
        return {spinControl_->getSize().x, spinControl_->getSize().y};
    }

    Vector2f SpinControl::getAbsoluteSize() {
        return {spinControl_->getFullSize().x, spinControl_->getFullSize().y};
    }

    void SpinControl::setWidth(float width) {
        spinControl_->setWidth(width);
    }

    void SpinControl::setWidth(const std::string &width) {
        spinControl_->setWidth(width.c_str());
    }

    void SpinControl::setHeight(float height) {
        spinControl_->setHeight(height);
    }

    void SpinControl::setHeight(const std::string &height) {
        spinControl_->setHeight(height.c_str());
    }

    void SpinControl::setMouseCursor(CursorType cursor) {
        spinControl_->setMouseCursor(static_cast<tgui::Cursor::Type>(cursor));
    }

    CursorType SpinControl::getMouseCursor() const {
        return static_cast<CursorType>(spinControl_->getMouseCursor());
    }

    std::string SpinControl::getWidgetType() const {
        return "SpinControl";
    }

    void SpinControl::showWithEffect(ShowAnimationType type, int duration) {
        spinControl_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void SpinControl::hideWithEffect(ShowAnimationType type, int duration) {
        spinControl_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool SpinControl::isAnimationPlaying() const {
        return spinControl_->isAnimationPlaying();
    }

    void SpinControl::setVisible(bool visible) {
        spinControl_->setVisible(visible);
    }

    bool SpinControl::isVisible() const {
        return spinControl_->isVisible();
    }

    void SpinControl::toggleVisibility() {
        spinControl_->setVisible(!spinControl_->isVisible());
    }

    bool SpinControl::contains(float x, float y) const {
        return spinControl_->isMouseOnWidget({x, y});
    }

    void SpinControl::setPosition(float x, float y) {
        spinControl_->setPosition({x, y});
    }

    void SpinControl::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void SpinControl::setPosition(const std::string &x, const std::string &y) {
        spinControl_->setPosition({x.c_str(), y.c_str()});
    }

    Vector2f SpinControl::getPosition() const {
        return {spinControl_->getPosition().x, spinControl_->getPosition().y};
    }

    Vector2f SpinControl::getAbsolutePosition() const {
        return {spinControl_->getAbsolutePosition().x, spinControl_->getAbsolutePosition().y};
    }

    void SpinControl::setRotation(float angle) {
        spinControl_->setRotation(angle);
    }

    void SpinControl::rotate(float angle) {
        spinControl_->setRotation(spinControl_->getRotation() + angle);
    }

    float SpinControl::getRotation() const {
        return spinControl_->getRotation();
    }

    void SpinControl::setScale(float factorX, float factorY) {
        spinControl_->setScale({factorX, factorY});
    }

    void SpinControl::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void SpinControl::scale(float factorX, float factorY) {
        spinControl_->setScale({spinControl_->getScale().x + factorX,
                           spinControl_->getScale().y + factorY});
    }

    void SpinControl::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f SpinControl::getScale() const {
        return {spinControl_->getScale().x, spinControl_->getScale().y};
    }

    void SpinControl::setOrigin(float x, float y) {
        spinControl_->setOrigin({x, y});
    }

    void SpinControl::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f SpinControl::getOrigin() const {
        return {spinControl_->getOrigin().x, spinControl_->getOrigin().y};
    }

    void SpinControl::move(float offsetX, float offsetY) {
        spinControl_->setPosition(getPosition().x + offsetX,
                             getPosition().y + offsetY);
    }

    void SpinControl::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void SpinControl::setEnabled(bool isEnable) {
        spinControl_->setEnabled(isEnable);
    }

    bool SpinControl::isEnabled() const {
        return spinControl_->isEnabled();
    }

    void SpinControl::toggleEnabled() {
        spinControl_->setEnabled(!spinControl_->isEnabled());
    }

    void SpinControl::setFocused(bool isFocused) {
        spinControl_->setFocused(isFocused);
    }

    bool SpinControl::isFocused() const {
        return spinControl_->isFocused();
    }

    std::shared_ptr<tgui::Widget> SpinControl::getInternalPtr() {
        return spinControl_;
    }

    void SpinControl::initEvents() {
        spinControl_->onMouseEnter([this]{emit("mouseEnter");});
        spinControl_->onMouseLeave([this]{emit("mouseLeave");});
        spinControl_->onFocus([this]{emit("focus");});
        spinControl_->onUnfocus([this]{emit("unfocus");});
        spinControl_->onAnimationFinish([this]{emit("animationFinish");});
        spinControl_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        spinControl_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });
        
        spinControl_->onValueChange([this](float value) {
            emit("valueChange", value);
        });
    }
}
