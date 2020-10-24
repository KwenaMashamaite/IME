#include "IME/graphics/ui/widgets/ProgressBar.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>

namespace IME::Graphics::UI {
    ProgressBar::ProgressBar()
        : progressBar_{tgui::ProgressBar::create()}
    {}

    void ProgressBar::setMinimumValue(unsigned int minValue) {
        progressBar_->setMinimum(minValue);
    }

    unsigned int ProgressBar::getMinimumValue() const {
        return progressBar_->getMinimum();
    }

    void ProgressBar::setMaximumValue(unsigned int maxValue) {
        progressBar_->setMaximum(maxValue);
    }

    unsigned int ProgressBar::getMaximumValue() const {
        return progressBar_->getMaximum();
    }

    void ProgressBar::setValue(unsigned int value) {
        progressBar_->setValue(value);
    }

    unsigned int ProgressBar::getValue() const {
        return progressBar_->getValue();
    }

    unsigned int ProgressBar::incrementValue() {
        return progressBar_->incrementValue();
    }

    void ProgressBar::setFillDirection(ProgressBar::FillDirection direction) {
        progressBar_->setFillDirection(
            static_cast<tgui::ProgressBar::FillDirection>(direction));
    }

    ProgressBar::FillDirection ProgressBar::getFillDirection() const {
        return static_cast<FillDirection>(progressBar_->getFillDirection());
    }

    void ProgressBar::setPosition(float x, float y) {
        progressBar_->setPosition({x, y});
    }

    void ProgressBar::setRotation(float angle) {
        progressBar_->setRotation(angle);
    }

    void ProgressBar::setScale(float factorX, float factorY) {
        progressBar_->setScale({factorX, factorY});
    }

    void ProgressBar::setOrigin(float x, float y) {
        progressBar_->setOrigin({x, y});
    }

    Position ProgressBar::getPosition() const {
        return {progressBar_->getPosition().x, progressBar_->getPosition().y};
    }

    Position ProgressBar::getOrigin() const {
        return {progressBar_->getOrigin().x, progressBar_->getOrigin().y};
    }

    float ProgressBar::getRotation() const {
        return progressBar_->getRotation();
    }

    void ProgressBar::move(float xOffset, float yOffset) {
        progressBar_->setPosition(getPosition().x + xOffset,
                             getPosition().y + yOffset);
    }

    void ProgressBar::rotate(float offset) {
        progressBar_->setRotation(progressBar_->getRotation() + offset);
    }

    void ProgressBar::scale(float factorX, float factorY) {
        progressBar_->setScale({progressBar_->getScale().x + factorX,
                           progressBar_->getScale().y + factorY});
    }

    void ProgressBar::draw(Window &renderTarget) {
        // Currently, widgets cannot be used as standalone, they must be
        // inside a container and that container renders them
        // @see IME::Graphics::Gui
    }

    void ProgressBar::hide() {
        progressBar_->hideWithEffect(tgui::ShowAnimationType::Fade,
                                fadeAnimDuration_);
    }

    void ProgressBar::show() {
        progressBar_->showWithEffect(tgui::ShowAnimationType::Fade,
                                fadeAnimDuration_);
    }

    bool ProgressBar::isHidden() const {
        return !progressBar_->isVisible();
    }

    void ProgressBar::setEnabled(bool isEnable) {
        progressBar_->setEnabled(isEnable);
    }

    bool ProgressBar::isEnabled() const {
        return progressBar_->isEnabled();
    }

    void ProgressBar::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    bool ProgressBar::isMouseOverElement() const {
        //@todo
        return false;
    }

    void ProgressBar::setPadding(float padding) {
        //@todo
    }

    void ProgressBar::setPadding(const Padding &padding) {
        //@todo
    }

    void ProgressBar::setMargin(float margin) {
        //@todo
    }

    void ProgressBar::setMargin(const Margin &margin) {
        //@todo
    }

    void ProgressBar::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void ProgressBar::setTextFont(const std::string &textFont) {
        progressBar_->getRenderer()->setFont(textFont.c_str());
    }

    void ProgressBar::setTextSize(unsigned int charSize) {
        progressBar_->setTextSize(charSize);
    }

    void ProgressBar::setText(const std::string &content) {
        progressBar_->setText(content);
    }

    void ProgressBar::setOutlineThickness(float outlineThickness) {
        progressBar_->getRenderer()->setBorders(
                {outlineThickness, outlineThickness, outlineThickness,
                 outlineThickness});
    }

    void ProgressBar::setBackgroundColour(Colour backgroundColour) {
        progressBar_->getRenderer()->setBackgroundColor(
                Utility::convertToTGUIColour(backgroundColour));
    }

    void ProgressBar::setTextColour(Colour textColour) {
        progressBar_->getRenderer()->setTextColor(
                Utility::convertToTGUIColour(textColour));
    }

    void ProgressBar::setOutlineColour(Colour outlineColour) {
        progressBar_->getRenderer()->setBorderColor(
                Utility::convertToTGUIColour(outlineColour));
    }

    void ProgressBar::setTextAlignment(TextAlignment textAlignment) {
        //@TODO
    }

    Padding ProgressBar::getPadding() const {
        return {progressBar_->getRenderer()->getBorders().getLeft(),
                progressBar_->getRenderer()->getBorders().getRight(),
                progressBar_->getRenderer()->getBorders().getTop(),
                progressBar_->getRenderer()->getBorders().getBottom()};
    }

    Margin ProgressBar::getMargin() const {
        //@todo
        return Margin();
    }

    void ProgressBar::setSize(float width, float height) {
        progressBar_->setSize({width, height});
    }

    Dimensions ProgressBar::getSize() const {
        return {progressBar_->getSize().x, progressBar_->getSize().y};
    }

    Colour ProgressBar::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
                progressBar_->getRenderer()->getBackgroundColor());
    }

    Colour ProgressBar::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(
                progressBar_->getRenderer()->getTextColor());
    }

    Colour ProgressBar::getOutlineColour() const {
        return Utility::convertFrom3rdPartyColour(
                progressBar_->getRenderer()->getBorderColor());
    }

    std::string ProgressBar::getText() const {
        return progressBar_->getText().toAnsiString();
    }

    unsigned int ProgressBar::getOutlineThickness() const {
        //@todo
        return 0;
    }

    unsigned int ProgressBar::getTextSize() const {
        return progressBar_->getTextSize();
    }

    TextAlignment ProgressBar::getTextAlignment() const {
        //@TODO - FIX
        return TextAlignment::Left;
    }

    std::string ProgressBar::getFontName() const {
        return progressBar_->getRenderer()->getFont().getId().toAnsiString();
    }

    std::string ProgressBar::getType() const {
        return "ProgressBar";
    }

    void ProgressBar::toggleVisibility() {
        progressBar_->setVisible(!progressBar_->isVisible());
    }

    bool ProgressBar::contains(float x, float y) const {
        return progressBar_->isMouseOnWidget({x, y});
    }

    void ProgressBar::handleEvent(sf::Event event) {
        auto tguiEvent = Utility::convert_SFML_event_to_TGUI_event(event);
        progressBar_->getParentGui()->handleEvent(tguiEvent);
    }

    void ProgressBar::setHoverTextColour(Colour textColour) {

    }

    void ProgressBar::setHoverBackgroundColour(Colour backgroundColour) {

    }

    void ProgressBar::setHoverOutlineColour(Colour outlineColour) {

    }

    void ProgressBar::setFocused(bool isFocused) {
        progressBar_->setFocused(isFocused);
    }

    bool ProgressBar::isFocused() const {
        return progressBar_->isFocused();
    }

    void ProgressBar::setTexture(const std::string &filename) {

    }

    std::shared_ptr<tgui::Widget> ProgressBar::getInternalPtr() {
        return progressBar_;
    }

    Dimensions ProgressBar::getAbsoluteSize() {
        return {progressBar_->getFullSize().x, progressBar_->getFullSize().y};
    }

    void ProgressBar::setOnFocusedImage(const std::string &filename) {

    }

    void ProgressBar::setOnDisabledImage(const std::string &filename) {

    }

    void ProgressBar::setOnMouseDownImage(const std::string &filename) {

    }

    void ProgressBar::setOnHoverImage(const std::string &filename) {

    }
}