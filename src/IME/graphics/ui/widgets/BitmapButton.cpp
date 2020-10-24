#include "IME/graphics/ui/widgets/BitmapButton.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>
#include "IME/core/managers/ResourceManager.h"

namespace IME::Graphics::UI {
    BitmapButton::BitmapButton() : BitmapButton("") 
    {}

    BitmapButton::BitmapButton(const std::string &buttonText)
        : button_{tgui::BitmapButton::create(buttonText)}
    {}
    
    void BitmapButton::setImage(const std::string &filename) {
        button_->setImage(IME::ResourceManager::getInstance()->getTexture(filename));
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

    void BitmapButton::setOrigin(float x, float y) {
        button_->setOrigin({x, y});
    }

    Position BitmapButton::getPosition() const {
        return {button_->getPosition().x, button_->getPosition().y};
    }

    Position BitmapButton::getOrigin() const {
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

    void BitmapButton::draw(Window &renderTarget) {
        // Currently, widgets cannot be used as standalone, they must be
        // inside a container and that container renders them
        // @see IME::Graphics::Gui
    }

    void BitmapButton::hide() {
        button_->hideWithEffect(tgui::ShowAnimationType::Fade,
                                fadeAnimDuration_);
    }

    void BitmapButton::show() {
        button_->showWithEffect(tgui::ShowAnimationType::Fade,
                                fadeAnimDuration_);
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

    bool BitmapButton::isMouseOverElement() const {
        //@todo
        return false;
    }

    void BitmapButton::setPadding(float padding) {
        //@todo
    }

    void BitmapButton::setPadding(const Padding &padding) {
        //@todo
    }

    void BitmapButton::setMargin(float margin) {
        //@todo
    }

    void BitmapButton::setMargin(const Margin &margin) {
        //@todo
    }

    void BitmapButton::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void BitmapButton::setTextFont(const std::string &textFont) {
        button_->getRenderer()->setFont(textFont.c_str());
    }

    void BitmapButton::setTextSize(unsigned int charSize) {
        button_->setTextSize(charSize);
    }

    void BitmapButton::setText(const std::string &content) {
        button_->setText(content);
    }

    void BitmapButton::setOutlineThickness(float outlineThickness) {
        button_->getRenderer()->setBorders(
                {outlineThickness, outlineThickness, outlineThickness,
                 outlineThickness});
    }

    void BitmapButton::setBackgroundColour(Colour backgroundColour) {
        button_->getRenderer()->setBackgroundColor(
                Utility::convertToTGUIColour(backgroundColour));
    }

    void BitmapButton::setTextColour(Colour textColour) {
        button_->getRenderer()->setTextColor(
                Utility::convertToTGUIColour(textColour));
    }

    void BitmapButton::setOutlineColour(Colour outlineColour) {
        button_->getRenderer()->setBorderColor(
                Utility::convertToTGUIColour(outlineColour));
    }

    void BitmapButton::setTextAlignment(TextAlignment textAlignment) {
        //@TODO
    }

    Padding BitmapButton::getPadding() const {
        return {button_->getRenderer()->getBorders().getLeft(),
                button_->getRenderer()->getBorders().getRight(),
                button_->getRenderer()->getBorders().getTop(),
                button_->getRenderer()->getBorders().getBottom()};
    }

    Margin BitmapButton::getMargin() const {
        //@todo
        return Margin();
    }

    void BitmapButton::setSize(float width, float height) {
        button_->setSize({width, height});
    }

    Dimensions BitmapButton::getSize() const {
        return {button_->getSize().x, button_->getSize().y};
    }

    Colour BitmapButton::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
                button_->getRenderer()->getBackgroundColor());
    }

    Colour BitmapButton::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(
                button_->getRenderer()->getTextColor());
    }

    Colour BitmapButton::getOutlineColour() const {
        return Utility::convertFrom3rdPartyColour(
                button_->getRenderer()->getBorderColor());
    }

    std::string BitmapButton::getText() const {
        return button_->getText().toAnsiString();
    }

    unsigned int BitmapButton::getOutlineThickness() const {
        //@todo
        return 0;
    }

    unsigned int BitmapButton::getTextSize() const {
        return button_->getTextSize();
    }

    TextAlignment BitmapButton::getTextAlignment() const {
        //@TODO - FIX
        return TextAlignment::Left;
    }

    std::string BitmapButton::getFontName() const {
        return button_->getRenderer()->getFont().getId().toAnsiString();
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

    void BitmapButton::handleEvent(sf::Event event) {
        auto tguiEvent = Utility::convert_SFML_event_to_TGUI_event(event);
        button_->getParentGui()->handleEvent(tguiEvent);
    }

    void BitmapButton::setHoverTextColour(Colour textColour) {
        button_->getRenderer()->setTextColorHover(
                Utility::convertToTGUIColour(textColour));
    }

    void BitmapButton::setHoverBackgroundColour(Colour backgroundColour) {
        button_->getRenderer()->setBackgroundColorHover(
                Utility::convertToTGUIColour(backgroundColour));
    }

    void BitmapButton::setHoverOutlineColour(Colour outlineColour) {
        button_->getRenderer()->setBorderColorHover(
                Utility::convertToTGUIColour(outlineColour));
    }

    void BitmapButton::setFocused(bool isFocused) {
        button_->setFocused(isFocused);
    }

    bool BitmapButton::isFocused() const {
        return button_->isFocused();
    }

    void BitmapButton::setTexture(const std::string &filename) {
        button_->getRenderer()->setTexture(
                IME::ResourceManager::getInstance()->getTexture(filename));
    }

    std::shared_ptr<tgui::Widget> BitmapButton::getInternalPtr() {
        return button_;
    }

    Dimensions BitmapButton::getAbsoluteSize() {
        return {button_->getFullSize().x, button_->getFullSize().y};
    }

    void BitmapButton::setOnFocusedImage(const std::string &filename) {
        button_->getRenderer()->setTextureFocused(
                IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void BitmapButton::setOnDisabledImage(const std::string &filename) {
        button_->getRenderer()->setTextureDisabled(
                IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void BitmapButton::setOnMouseDownImage(const std::string &filename) {
        button_->getRenderer()->setTextureDown(
                IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void BitmapButton::setOnHoverImage(const std::string &filename) {
        button_->getRenderer()->setTextureHover(
                IME::ResourceManager::getInstance()->getTexture(filename));
    }
}
