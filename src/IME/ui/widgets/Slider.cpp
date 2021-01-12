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

#include "IME/ui/widgets/Slider.h"

namespace ime::ui {
    Slider::Slider(float minValue, float maxValue) :
        slider_{tgui::Slider::create(minValue, maxValue)},
        renderer_{std::make_shared<SliderRenderer>()}
    {
        renderer_->setInternalPtr(slider_->getRenderer());
        initEvents();
    }

    Slider::sharedPtr Slider::create(float minimum, float maximum) {
        return std::make_shared<Slider>(minimum, maximum);
    }

    void Slider::setRenderer(std::shared_ptr<SliderRenderer> renderer) {
        IME_ASSERT(renderer, "Cannot set nullptr as renderer");
        renderer_ = renderer;
        slider_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<SliderRenderer> Slider::getRenderer() {
        return renderer_;
    }

    void Slider::setMinimumValue(float minValue) {
        slider_->setMinimum(minValue);
    }

    float Slider::getMinimumValue() const {
        return slider_->getMinimum();
    }

    void Slider::setMaximumValue(float maxValue) {
        slider_->setMaximum(maxValue);
    }

    float Slider::getMaximumValue() const {
        return slider_->getMaximum();
    }

    void Slider::setValue(float value) {
        slider_->setValue(value);
    }

    float Slider::getValue() const {
        return slider_->getValue();
    }

    void Slider::setStep(float step) {
        slider_->setStep(step);
    }

    float Slider::getStep() const {
        return slider_->getStep();
    }

    void Slider::setVerticalScroll(bool isVertical) {
        slider_->setVerticalScroll(isVertical);
    }

    bool Slider::isVerticalScroll() const {
        return slider_->getVerticalScroll();
    }

    void Slider::invert(bool isInverted) {
        slider_->setInvertedDirection(isInverted);
    }

    bool Slider::isInverted() const {
        return slider_->getInvertedDirection();
    }

    void Slider::setChangeValueOnScroll(bool changeValueOnScroll) {
        slider_->setChangeValueOnScroll(changeValueOnScroll);
    }

    bool Slider::isValueChangedOnScroll() const {
        return slider_->getChangeValueOnScroll();
    }

    void Slider::setPosition(float x, float y) {
        slider_->setPosition({x, y});
    }

    void Slider::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void Slider::setPosition(const std::string &x, const std::string &y) {
        slider_->setPosition({x.c_str(), y.c_str()});
    }

    void Slider::setRotation(float angle) {
        slider_->setRotation(angle);
    }

    void Slider::setScale(float factorX, float factorY) {
        slider_->setScale({factorX, factorY});
    }

    void Slider::setOrigin(float x, float y) {
        slider_->setOrigin({x, y});
    }

    Vector2f Slider::getPosition() const {
        return {slider_->getPosition().x, slider_->getPosition().y};
    }

    Vector2f Slider::getAbsolutePosition() const {
        return {slider_->getAbsolutePosition().x, slider_->getAbsolutePosition().y};
    }

    Vector2f Slider::getOrigin() const {
        return {slider_->getOrigin().x, slider_->getOrigin().y};
    }

    float Slider::getRotation() const {
        return slider_->getRotation();
    }

    void Slider::move(float xOffset, float yOffset) {
        slider_->setPosition(getPosition().x + xOffset,
            getPosition().y + yOffset);
    }

    void Slider::setTextSize(unsigned int charSize) {
        slider_->setTextSize(charSize);
    }

    void Slider::rotate(float offset) {
        slider_->setRotation(slider_->getRotation() + offset);
    }

    void Slider::scale(float factorX, float factorY) {
        slider_->setScale({slider_->getScale().x + factorX,
            slider_->getScale().y + factorY});
    }

    void Slider::setSize(float width, float height) {
        slider_->setSize({width, height});
    }

    void Slider::setSize(const std::string &width, const std::string &height) {
        slider_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f Slider::getSize() const {
        return {slider_->getSize().x, slider_->getSize().y};
    }

    Vector2f Slider::getAbsoluteSize() {
        return {slider_->getFullSize().x, slider_->getFullSize().y};;
    }

    void Slider::setWidth(float width) {
        slider_->setWidth(width);
    }

    void Slider::setWidth(const std::string &width) {
        slider_->setWidth(width.c_str());
    }

    void Slider::setHeight(float height) {
        slider_->setHeight(height);
    }

    void Slider::setHeight(const std::string &height) {
        slider_->setHeight(height.c_str());
    }

    unsigned int Slider::getTextSize() const {
        return slider_->getTextSize();
    }

    void Slider::toggleVisibility() {
        slider_->setVisible(!slider_->isVisible());
    }

    std::string Slider::getWidgetType() const {
        return "Slider";
    }

    void Slider::showWithEffect(ShowAnimationType type, int duration) {
        slider_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void Slider::hideWithEffect(ShowAnimationType type, int duration) {
        slider_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool Slider::isAnimationPlaying() const {
        return slider_->isAnimationPlaying();
    }

    void Slider::setVisible(bool visible) {
        slider_->setVisible(visible);
    }

    bool Slider::isVisible() const {
        return slider_->isVisible();
    }

    bool Slider::contains(float x, float y) const {
        return slider_->isMouseOnWidget({x, y});;
    }

    std::shared_ptr<tgui::Widget> Slider::getInternalPtr() {
        return slider_;
    }

    void Slider::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void Slider::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    void Slider::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void Slider::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    void Slider::initEvents() {
        slider_->onMouseEnter([this]{emit("mouseEnter");});
        slider_->onMouseLeave([this]{emit("mouseLeave");});
        slider_->onFocus([this]{emit("focus");});
        slider_->onUnfocus([this]{emit("unfocus");});
        slider_->onAnimationFinish([this]{emit("animationFinish");});
        slider_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        slider_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });

        slider_->onValueChange([this](float newValue) {
            emit("valueChange", newValue);
        });
    }

    Vector2f Slider::getScale() const {
        return {slider_->getScale().x, slider_->getScale().y};
    }
}