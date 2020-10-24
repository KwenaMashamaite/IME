#include "IME/graphics/ui/widgets/EditBox.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>

namespace IME::Graphics::UI {
    EditBox::EditBox() : editBox_{tgui::EditBox::create()}
    {}

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

    Position EditBox::getPosition() const {
        return {editBox_->getPosition().x, editBox_->getPosition().y};
    }

    Position EditBox::getOrigin() const {
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

    void EditBox::draw(Window &renderTarget) {
        // Currently, widgets cannot be used as standalone, they must be
        // inside a container and that container renders them
        // @see IME::Graphics::Gui
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

    bool EditBox::isMouseOverElement() const {
        //@todo
        return false;
    }

    void EditBox::setPadding(float padding) {
        //@todo
    }

    void EditBox::setPadding(const Padding &padding) {
        //@todo
    }

    void EditBox::setMargin(float margin) {
        //@todo
    }

    void EditBox::setMargin(const Margin &margin) {
        //@todo
    }

    void EditBox::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void EditBox::setTextFont(const std::string &textFont) {
        editBox_->getRenderer()->setFont(textFont.c_str());
    }

    void EditBox::setTextSize(unsigned int charSize) {
        editBox_->setTextSize(charSize);
    }

    void EditBox::setText(const std::string &content) {
        editBox_->setText(content);
    }

    void EditBox::setOutlineThickness(float outlineThickness) {
        editBox_->getRenderer()->setBorders(
                {outlineThickness, outlineThickness, outlineThickness,
                 outlineThickness});
    }

    void EditBox::setBackgroundColour(Colour backgroundColour) {
        editBox_->getRenderer()->setBackgroundColor(
                Utility::convertToTGUIColour(backgroundColour));
    }

    void EditBox::setTextColour(Colour textColour) {
        editBox_->getRenderer()->setTextColor(
                Utility::convertToTGUIColour(textColour));
    }

    void EditBox::setOutlineColour(Colour outlineColour) {
        editBox_->getRenderer()->setBorderColor(
                Utility::convertToTGUIColour(outlineColour));
    }

    void EditBox::setTextAlignment(TextAlignment textAlignment) {
        //@TODO
    }

    Padding EditBox::getPadding() const {
        return {editBox_->getRenderer()->getBorders().getLeft(),
                editBox_->getRenderer()->getBorders().getRight(),
                editBox_->getRenderer()->getBorders().getTop(),
                editBox_->getRenderer()->getBorders().getBottom()};
    }

    Margin EditBox::getMargin() const {
        //@todo
        return Margin();
    }

    void EditBox::setSize(float width, float height) {
        editBox_->setSize({width, height});
    }

    Dimensions EditBox::getSize() const {
        return {editBox_->getSize().x, editBox_->getSize().y};
    }

    Colour EditBox::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
                editBox_->getRenderer()->getBackgroundColor());
    }

    Colour EditBox::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(
                editBox_->getRenderer()->getTextColor());
    }

    Colour EditBox::getOutlineColour() const {
        return Utility::convertFrom3rdPartyColour(
                editBox_->getRenderer()->getBorderColor());
    }

    std::string EditBox::getText() const {
        return editBox_->getText().toAnsiString();
    }

    unsigned int EditBox::getOutlineThickness() const {
        //@todo
        return 0;
    }

    unsigned int EditBox::getTextSize() const {
        return editBox_->getTextSize();
    }

    TextAlignment EditBox::getTextAlignment() const {
        //@TODO - FIX
        return TextAlignment::Left;
    }

    std::string EditBox::getFontName() const {
        return editBox_->getRenderer()->getFont().getId().toAnsiString();
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

    void EditBox::handleEvent(sf::Event event) {
        auto tguiEvent = Utility::convert_SFML_event_to_TGUI_event(event);
        editBox_->getParentGui()->handleEvent(tguiEvent);
    }

    void EditBox::setHoverTextColour(Colour textColour) {

    }

    void EditBox::setHoverBackgroundColour(Colour backgroundColour) {
        editBox_->getRenderer()->setBackgroundColorHover(
            Utility::convertToTGUIColour(backgroundColour));
    }

    void EditBox::setHoverOutlineColour(Colour outlineColour) {
        editBox_->getRenderer()->setBorderColorHover(
            Utility::convertToTGUIColour(outlineColour));
    }

    void EditBox::setFocused(bool isFocused) {
        editBox_->setFocused(isFocused);
    }

    bool EditBox::isFocused() const {
        return editBox_->isFocused();
    }

    void EditBox::setTexture(const std::string &filename) {
        editBox_->getRenderer()->setTexture(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    std::shared_ptr<tgui::Widget> EditBox::getInternalPtr() {
        return editBox_;
    }

    Dimensions EditBox::getAbsoluteSize() {
        return {editBox_->getFullSize().x, editBox_->getFullSize().y};
    }

    void EditBox::setOnFocusedImage(const std::string &filename) {
        editBox_->getRenderer()->setTextureFocused(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void EditBox::setOnDisabledImage(const std::string &filename) {
        editBox_->getRenderer()->setTextureDisabled(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void EditBox::setOnMouseDownImage(const std::string &filename) {

    }

    void EditBox::setOnHoverImage(const std::string &filename) {
        editBox_->getRenderer()->setTextureHover(
                IME::ResourceManager::getInstance()->getTexture(filename));
    }
}
