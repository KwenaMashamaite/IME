#include "IME/graphics/ui/widgets/CheckBox.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>

namespace IME::Graphics::UI {
    CheckBox::CheckBox(const std::string &text)
        : checkBox_{tgui::CheckBox::create(text)}
    {}

    void CheckBox::setTextClickable(bool acceptTextClick) {
        checkBox_->setTextClickable(acceptTextClick);
    }

    bool CheckBox::isTextClickable() const {
        return checkBox_->isTextClickable();
    }

    void CheckBox::setChecked(bool isChecked) {
        checkBox_->setChecked(isChecked);
    }

    bool CheckBox::isChecked() const {
        return checkBox_->isChecked();
    }

    void CheckBox::setPosition(float x, float y) {
        checkBox_->setPosition({x, y});
    }

    void CheckBox::setRotation(float angle) {
        checkBox_->setRotation(angle);
    }

    void CheckBox::setScale(float factorX, float factorY) {
        checkBox_->setScale({factorX, factorY});
    }

    void CheckBox::setOrigin(float x, float y) {
        checkBox_->setOrigin({x, y});
    }

    Position CheckBox::getPosition() const {
        return {checkBox_->getPosition().x, checkBox_->getPosition().y};
    }

    Position CheckBox::getOrigin() const {
        return {checkBox_->getOrigin().x, checkBox_->getOrigin().y};
    }

    float CheckBox::getRotation() const {
        return checkBox_->getRotation();
    }

    void CheckBox::move(float xOffset, float yOffset) {
        checkBox_->setPosition(getPosition().x + xOffset,
                             getPosition().y + yOffset);
    }

    void CheckBox::rotate(float offset) {
        checkBox_->setRotation(checkBox_->getRotation() + offset);
    }

    void CheckBox::scale(float factorX, float factorY) {
        checkBox_->setScale({checkBox_->getScale().x + factorX,
                           checkBox_->getScale().y + factorY});
    }

    void CheckBox::draw(Window &renderTarget) {
        // Currently, widgets cannot be used as standalone, they must be
        // inside a container and that container renders them
        // @see IME::Graphics::Gui
    }

    void CheckBox::hide() {
        checkBox_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void CheckBox::show() {
        checkBox_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool CheckBox::isHidden() const {
        return !checkBox_->isVisible();
    }

    void CheckBox::setEnabled(bool isEnable) {
        checkBox_->setEnabled(isEnable);
    }

    bool CheckBox::isEnabled() const {
        return checkBox_->isEnabled();
    }

    void CheckBox::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    bool CheckBox::isMouseOverElement() const {
        //@todo
        return false;
    }

    void CheckBox::setPadding(float padding) {
        //@todo
    }

    void CheckBox::setPadding(const Padding &padding) {
        //@todo
    }

    void CheckBox::setMargin(float margin) {
        //@todo
    }

    void CheckBox::setMargin(const Margin &margin) {
        //@todo
    }

    void CheckBox::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void CheckBox::setTextFont(const std::string &textFont) {
        checkBox_->getRenderer()->setFont(textFont.c_str());
    }

    void CheckBox::setTextSize(unsigned int charSize) {
        checkBox_->setTextSize(charSize);
    }

    void CheckBox::setText(const std::string &content) {
        checkBox_->setText(content);
    }

    void CheckBox::setOutlineThickness(float outlineThickness) {
        checkBox_->getRenderer()->setBorders(
                {outlineThickness, outlineThickness, outlineThickness,
                 outlineThickness});
    }

    void CheckBox::setBackgroundColour(Colour backgroundColour) {
        checkBox_->getRenderer()->setBackgroundColor(
                Utility::convertToTGUIColour(backgroundColour));
    }

    void CheckBox::setTextColour(Colour textColour) {
        checkBox_->getRenderer()->setTextColor(
                Utility::convertToTGUIColour(textColour));
    }

    void CheckBox::setOutlineColour(Colour outlineColour) {
        checkBox_->getRenderer()->setBorderColor(
                Utility::convertToTGUIColour(outlineColour));
    }

    void CheckBox::setTextAlignment(TextAlignment textAlignment) {
        //@TODO
    }

    Padding CheckBox::getPadding() const {
        return {checkBox_->getRenderer()->getBorders().getLeft(),
                checkBox_->getRenderer()->getBorders().getRight(),
                checkBox_->getRenderer()->getBorders().getTop(),
                checkBox_->getRenderer()->getBorders().getBottom()};
    }

    Margin CheckBox::getMargin() const {
        //@todo
        return Margin();
    }

    void CheckBox::setSize(float width, float height) {
        checkBox_->setSize({width, height});
    }

    Dimensions CheckBox::getSize() const {
        return {checkBox_->getSize().x, checkBox_->getSize().y};
    }

    Colour CheckBox::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
                checkBox_->getRenderer()->getBackgroundColor());
    }

    Colour CheckBox::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(
                checkBox_->getRenderer()->getTextColor());
    }

    Colour CheckBox::getOutlineColour() const {
        return Utility::convertFrom3rdPartyColour(
                checkBox_->getRenderer()->getBorderColor());
    }

    std::string CheckBox::getText() const {
        return checkBox_->getText().toAnsiString();
    }

    unsigned int CheckBox::getOutlineThickness() const {
        //@todo
        return 0;
    }

    unsigned int CheckBox::getTextSize() const {
        return checkBox_->getTextSize();
    }

    TextAlignment CheckBox::getTextAlignment() const {
        //@TODO - FIX
        return TextAlignment::Left;
    }

    std::string CheckBox::getFontName() const {
        return checkBox_->getRenderer()->getFont().getId().toAnsiString();
    }

    std::string CheckBox::getType() const {
        return "CheckBox";
    }

    void CheckBox::toggleVisibility() {
        checkBox_->setVisible(!checkBox_->isVisible());
    }

    bool CheckBox::contains(float x, float y) const {
        return checkBox_->isMouseOnWidget({x, y});
    }

    void CheckBox::handleEvent(sf::Event event) {
        auto tguiEvent = Utility::convert_SFML_event_to_TGUI_event(event);
        checkBox_->getParentGui()->handleEvent(tguiEvent);
    }

    void CheckBox::setHoverTextColour(Colour textColour) {
        checkBox_->getRenderer()->setTextColorHover(
                Utility::convertToTGUIColour(textColour));
    }

    void CheckBox::setHoverBackgroundColour(Colour backgroundColour) {
        checkBox_->getRenderer()->setBackgroundColorHover(
                Utility::convertToTGUIColour(backgroundColour));
    }

    void CheckBox::setHoverOutlineColour(Colour outlineColour) {
        checkBox_->getRenderer()->setBorderColorHover(
                Utility::convertToTGUIColour(outlineColour));
    }

    void CheckBox::setFocused(bool isFocused) {
        checkBox_->setFocused(isFocused);
    }

    bool CheckBox::isFocused() const {
        return checkBox_->isFocused();
    }

    void CheckBox::setTexture(const std::string &filename) {

    }

    std::shared_ptr<tgui::Widget> CheckBox::getInternalPtr() {
        return checkBox_;
    }

    Dimensions CheckBox::getAbsoluteSize() {
        return {checkBox_->getFullSize().x, checkBox_->getFullSize().y};
    }

    void CheckBox::setOnFocusedImage(const std::string &filename) {

    }

    void CheckBox::setOnDisabledImage(const std::string &filename) {

    }

    void CheckBox::setOnMouseDownImage(const std::string &filename) {

    }

    void CheckBox::setOnHoverImage(const std::string &filename) {

    }
}