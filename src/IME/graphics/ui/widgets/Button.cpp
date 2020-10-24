#include "IME/graphics/ui/widgets/Button.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>
#include "IME/core/managers/ResourceManager.h"

namespace IME::Graphics::UI {
    Button::Button() : Button("") {}

    Button::Button(const std::string &buttonText)
        : button_{tgui::Button::create(buttonText)}
    {}

    void Button::setPosition(float x, float y) {
        button_->setPosition({x, y});
    }

    void Button::setRotation(float angle) {
        button_->setRotation(angle);
    }

    void Button::setScale(float factorX, float factorY) {
        button_->setScale({factorX, factorY});
    }

    void Button::setOrigin(float x, float y) {
        button_->setOrigin({x, y});
    }

    Position Button::getPosition() const {
        return {button_->getPosition().x, button_->getPosition().y};
    }

    Position Button::getOrigin() const {
        return {button_->getOrigin().x, button_->getOrigin().y};
    }

    float Button::getRotation() const {
        return button_->getRotation();
    }

    void Button::move(float xOffset, float yOffset) {
        button_->setPosition(getPosition().x + xOffset,
                             getPosition().y + yOffset);
    }

    void Button::rotate(float offset) {
        button_->setRotation(button_->getRotation() + offset);
    }

    void Button::scale(float factorX, float factorY) {
        button_->setScale({button_->getScale().x + factorX,
            button_->getScale().y + factorY});
    }

    void Button::draw(Window &renderTarget) {
        // Currently, widgets cannot be used as standalone, they must be
        // inside a container and that container renders them
        // @see IME::Graphics::Gui
    }

    void Button::hide() {
        button_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void Button::show() {
        button_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool Button::isHidden() const {
        return !button_->isVisible();
    }

    void Button::setEnabled(bool isEnable) {
        button_->setEnabled(isEnable);
    }

    bool Button::isEnabled() const {
        return button_->isEnabled();
    }

    void Button::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    bool Button::isMouseOverElement() const {
        //@todo
        return false;
    }

    void Button::setPadding(float padding) {
        //@todo
    }

    void Button::setPadding(const Padding &padding) {
        //@todo
    }

    void Button::setMargin(float margin) {
        //@todo
    }

    void Button::setMargin(const Margin &margin) {
        //@todo
    }

    void Button::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void Button::setTextFont(const std::string &textFont) {
        button_->getRenderer()->setFont(textFont.c_str());
    }

    void Button::setTextSize(unsigned int charSize) {
        button_->setTextSize(charSize);
    }

    void Button::setText(const std::string &content) {
        button_->setText(content);
    }

    void Button::setOutlineThickness(float outlineThickness) {
        button_->getRenderer()->setBorders(
            {outlineThickness, outlineThickness, outlineThickness,
             outlineThickness});
    }

    void Button::setBackgroundColour(Colour backgroundColour) {
        button_->getRenderer()->setBackgroundColor(
            Utility::convertToTGUIColour(backgroundColour));
    }

    void Button::setTextColour(Colour textColour) {
        button_->getRenderer()->setTextColor(
            Utility::convertToTGUIColour(textColour));
    }

    void Button::setOutlineColour(Colour outlineColour) {
        button_->getRenderer()->setBorderColor(
            Utility::convertToTGUIColour(outlineColour));
    }

    void Button::setTextAlignment(TextAlignment textAlignment) {
        //@TODO
    }

    Padding Button::getPadding() const {
        return {button_->getRenderer()->getBorders().getLeft(),
                button_->getRenderer()->getBorders().getRight(),
                button_->getRenderer()->getBorders().getTop(),
                button_->getRenderer()->getBorders().getBottom()};
    }

    Margin Button::getMargin() const {
        //@todo
        return Margin();
    }

    void Button::setSize(float width, float height) {
        button_->setSize({width, height});
    }

    Dimensions Button::getSize() const {
        return {button_->getSize().x, button_->getSize().y};
    }

    Colour Button::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            button_->getRenderer()->getBackgroundColor());
    }

    Colour Button::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            button_->getRenderer()->getTextColor());
    }

    Colour Button::getOutlineColour() const {
        return Utility::convertFrom3rdPartyColour(
            button_->getRenderer()->getBorderColor());
    }

    std::string Button::getText() const {
        return button_->getText().toAnsiString();
    }

    unsigned int Button::getOutlineThickness() const {
        //@todo
        return 0;
    }

    unsigned int Button::getTextSize() const {
        return button_->getTextSize();
    }

    TextAlignment Button::getTextAlignment() const {
        //@TODO - FIX
        return TextAlignment::Left;
    }

    std::string Button::getFontName() const {
        return button_->getRenderer()->getFont().getId().toAnsiString();
    }

    std::string Button::getType() const {
        return "Button";
    }

    void Button::toggleVisibility() {
        button_->setVisible(!button_->isVisible());
    }

    bool Button::contains(float x, float y) const {
        return button_->isMouseOnWidget({x, y});
    }

    void Button::handleEvent(sf::Event event) {
        auto tguiEvent = Utility::convert_SFML_event_to_TGUI_event(event);
        button_->getParentGui()->handleEvent(tguiEvent);
    }

    void Button::setHoverTextColour(Colour textColour) {
        button_->getRenderer()->setTextColorHover(
            Utility::convertToTGUIColour(textColour));
    }

    void Button::setHoverBackgroundColour(Colour backgroundColour) {
        button_->getRenderer()->setBackgroundColorHover(
            Utility::convertToTGUIColour(backgroundColour));
    }

    void Button::setHoverOutlineColour(Colour outlineColour) {
        button_->getRenderer()->setBorderColorHover(
            Utility::convertToTGUIColour(outlineColour));
    }

    void Button::setFocused(bool isFocused) {
        button_->setFocused(isFocused);
    }

    bool Button::isFocused() const {
        return button_->isFocused();
    }

    void Button::setTexture(const std::string &filename) {
        button_->getRenderer()->setTexture(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    std::shared_ptr<tgui::Widget> Button::getInternalPtr() {
        return button_;
    }

    Dimensions Button::getAbsoluteSize() {
        return {button_->getFullSize().x, button_->getFullSize().y};
    }

    void Button::setOnFocusedImage(const std::string &filename) {
        button_->getRenderer()->setTextureFocused(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void Button::setOnDisabledImage(const std::string &filename) {
        button_->getRenderer()->setTextureDisabled(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void Button::setOnMouseDownImage(const std::string &filename) {
        button_->getRenderer()->setTextureDown(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void Button::setOnHoverImage(const std::string &filename) {
        button_->getRenderer()->setTextureHover(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }
}
