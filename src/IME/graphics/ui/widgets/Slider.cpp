#include "IME/graphics/ui/widgets/Slider.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>

namespace IME::Graphics::UI {
    Slider::Slider(float minValue, float maxValue) 
        : slider_{tgui::Slider::create(minValue, maxValue)}
    {}

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

    void Slider::rotate(float offset) {
        slider_->setRotation(slider_->getRotation() + offset);
    }

    void Slider::scale(float factorX, float factorY) {
        slider_->setScale({slider_->getScale().x + factorX,
            slider_->getScale().y + factorY});
    }

    void Slider::draw(Window &renderTarget) {
        // Currently, widgets cannot be used as standalone, they must be
        // inside a container and that container renders them
        // @see IME::Graphics::Gui
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

    void Slider::setPadding(float padding) {

    }

    void Slider::setPadding(const Padding &padding) {

    }

    void Slider::setMargin(float margin) {

    }

    void Slider::setMargin(const Margin &margin) {

    }

    void Slider::setTextFont(const std::string &textFont) {
        slider_->getRenderer()->setFont(textFont.c_str());
    }

    void Slider::setTextSize(unsigned int charSize) {
        slider_->setTextSize(charSize);
    }

    void Slider::setText(const std::string &content) {

    }

    void Slider::setOutlineThickness(float outlineThickness) {
        slider_->getRenderer()->setBorders(
                {outlineThickness, outlineThickness, outlineThickness,
                 outlineThickness});
    }

    void Slider::setBackgroundColour(Colour backgroundColour) {

    }

    void Slider::setTextColour(Colour textColour) {

    }

    void Slider::setOutlineColour(Colour outlineColour) {
        slider_->getRenderer()->setBorderColor(
                Utility::convertToTGUIColour(outlineColour));
    }

    void Slider::setTextAlignment(TextAlignment textAlignment) {

    }

    Padding Slider::getPadding() const {
        return Padding();
    }

    Margin Slider::getMargin() const {
        return Margin();
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

    Colour Slider::getBackgroundColour() const {

    }

    Colour Slider::getTextColour() const {

    }

    Colour Slider::getOutlineColour() const {
        return Utility::convertFrom3rdPartyColour(
                slider_->getRenderer()->getBorderColor());
    }

    std::string Slider::getText() const {

    }

    unsigned int Slider::getOutlineThickness() const {
        return 0;
    }

    unsigned int Slider::getTextSize() const {
        return slider_->getTextSize();
    }

    TextAlignment Slider::getTextAlignment() const {
        return TextAlignment::Center;
    }

    std::string Slider::getFontName() const {
        return slider_->getRenderer()->getFont().getId().toAnsiString();
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

    void Slider::handleEvent(sf::Event event) {
        auto tguiEvent = Utility::convert_SFML_event_to_TGUI_event(event);
        slider_->getParentGui()->handleEvent(tguiEvent);
    }
}
