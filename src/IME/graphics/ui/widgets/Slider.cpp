#include "IME/graphics/ui/widgets/Slider.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <cassert>
#include <TGUI/GuiBase.hpp>

namespace IME::Graphics::UI {
    Slider::Slider(float minValue, float maxValue) 
        : slider_{tgui::Slider::create(minValue, maxValue)},
          renderer_{std::make_shared<SliderRenderer>()}
    {
        renderer_->setInternalPtr(slider_->getRenderer());
    }

    void Slider::setRenderer(std::shared_ptr<SliderRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
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

    void Slider::setPosition(Position position) {
        setPosition(position.x, position.y);
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

    Position Slider::getPosition() const {
        return {slider_->getPosition().x, slider_->getPosition().y};
    }

    Position Slider::getOrigin() const {
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

    void Slider::hide() {
        slider_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void Slider::show() {
        slider_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool Slider::isHidden() const {
        return !slider_->isVisible();
    }

    void Slider::setText(const std::string &content) {

    }

    void Slider::setSize(float width, float height) {
        slider_->setSize({width, height});
    }

    Dimensions Slider::getSize() const {
        return {slider_->getSize().x, slider_->getSize().y};
    }

    Dimensions Slider::getAbsoluteSize() {
        return {slider_->getFullSize().x, slider_->getFullSize().y};;
    }

    std::string Slider::getText() const {

    }

    unsigned int Slider::getTextSize() const {
        return slider_->getTextSize();
    }

    void Slider::toggleVisibility() {
        slider_->setVisible(!slider_->isVisible());
    }

    std::string Slider::getType() const {
        return "Slider";
    }

    bool Slider::contains(float x, float y) const {
        return slider_->isMouseOnWidget({x, y});;
    }

    std::shared_ptr<tgui::Widget> Slider::getInternalPtr() {
        return slider_;
    }
}
