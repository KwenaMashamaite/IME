#include "IME/graphics/ui/widgets/Label.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>

namespace IME::Graphics::UI {
    Label::Label(const std::string &text) : label_{tgui::Label::create(text)}
    {}

    std::string Label::getType() const {
        return "Label";
    }

    void Label::setPosition(float x, float y) {
        label_->setPosition({x, y});
    }

    void Label::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void Label::setRotation(float angle) {
        label_->setRotation(angle);
    }

    void Label::setScale(float factorX, float factorY) {
        label_->setScale({factorX, factorY});
    }

    void Label::setOrigin(float x, float y) {
        label_->setOrigin({x, y});
    }

    Position Label::getPosition() const {
        return {label_->getPosition().x, label_->getPosition().y};
    }

    Position Label::getOrigin() const {
        return {label_->getOrigin().x, label_->getOrigin().y};
    }

    float Label::getRotation() const {
        return label_->getRotation();
    }

    void Label::move(float xOffset, float yOffset) {
        label_->setPosition(getPosition().x + xOffset,
            getPosition().y + yOffset);
    }

    void Label::rotate(float offset) {
        label_->setRotation(label_->getRotation() + offset);
    }

    void Label::scale(float factorX, float factorY) {
        label_->setScale({label_->getScale().x + factorX,
            label_->getScale().y + factorY});
    }

    void Label::draw(Window &renderTarget) {
        // Currently, widgets cannot be used as standalone, they must be
        // inside a container and that container renders them
        // @see IME::Graphics::Gui
    }

    void Label::hide() {
        label_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void Label::show() {
        label_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool Label::isHidden() const {
        return !label_->isVisible();
    }

    void Label::setPadding(float padding) {

    }

    void Label::setPadding(const Padding &padding) {

    }

    void Label::setMargin(float margin) {

    }

    void Label::setMargin(const Margin &margin) {

    }

    void Label::setTextFont(const std::string &textFont) {
        label_->getRenderer()->setFont(textFont.c_str());
    }

    void Label::setTextSize(unsigned int charSize) {
        label_->setTextSize(charSize);
    }

    void Label::setText(const std::string &content) {
        label_->setText(content);
    }

    void Label::setOutlineThickness(float outlineThickness) {
        label_->getRenderer()->setBorders(
            {outlineThickness, outlineThickness, outlineThickness,
             outlineThickness});
    }

    void Label::setBackgroundColour(Colour backgroundColour) {
        label_->getRenderer()->setBackgroundColor(
            Utility::convertToTGUIColour(backgroundColour));
    }

    void Label::setTextColour(Colour textColour) {
        label_->getRenderer()->setTextColor(
            Utility::convertToTGUIColour(textColour));
    }

    void Label::setOutlineColour(Colour outlineColour) {
        label_->getRenderer()->setBorderColor(
            Utility::convertToTGUIColour(outlineColour));
    }

    void Label::setTextAlignment(TextAlignment textAlignment) {

    }

    Padding Label::getPadding() const {
        return Padding();
    }

    Margin Label::getMargin() const {
        return Margin();
    }

    void Label::setSize(float width, float height) {
        label_->setSize({width, height});
    }

    Dimensions Label::getSize() const {
        return {label_->getSize().x, label_->getSize().y};
    }

    Dimensions Label::getAbsoluteSize() {
        return {label_->getFullSize().x, label_->getFullSize().y};;
    }

    Colour Label::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
                    label_->getRenderer()->getBackgroundColor());
    }

    Colour Label::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(
                    label_->getRenderer()->getTextColor());
    }

    Colour Label::getOutlineColour() const {
        return Utility::convertFrom3rdPartyColour(
                label_->getRenderer()->getBorderColor());
    }

    std::string Label::getText() const {

    }

    unsigned int Label::getOutlineThickness() const {
        return 0;
    }

    unsigned int Label::getTextSize() const {
        return label_->getTextSize();
    }

    TextAlignment Label::getTextAlignment() const {
        return TextAlignment::Center;
    }

    std::string Label::getFontName() const {
        return label_->getRenderer()->getFont().getId().toAnsiString();
    }

    void Label::toggleVisibility() {
        label_->setVisible(!label_->isVisible());
    }

    bool Label::contains(float x, float y) const {
        return label_->isMouseOnWidget({x, y});;
    }

    std::shared_ptr<tgui::Widget> Label::getInternalPtr() {
        return label_;
    }

    void Label::handleEvent(sf::Event event) {
        auto tguiEvent = Utility::convert_SFML_event_to_TGUI_event(event);
        label_->getParentGui()->handleEvent(tguiEvent);
    }
}