#include "IME/graphics/ui/renderers/CheckBoxRenderer.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"

namespace IME::Graphics::UI {
    void CheckBoxRenderer::setBorders(const Borders &borders) {
        checkBoxRenderer_->setBorders({borders.left, borders.top, borders.right, borders.bottom});
    }

    Borders CheckBoxRenderer::getBorders() const {
        return {checkBoxRenderer_->getBorders().getLeft(),
                checkBoxRenderer_->getBorders().getTop(),
                checkBoxRenderer_->getBorders().getRight(),
                checkBoxRenderer_->getBorders().getBottom()};
    }

    void CheckBoxRenderer::setTextDistanceRatio(float ratio) {
        checkBoxRenderer_->setTextDistanceRatio(ratio);
    }

    float CheckBoxRenderer::getTextDistanceRatio() const {
        return checkBoxRenderer_->getTextDistanceRatio();
    }

    void CheckBoxRenderer::setTextColour(Colour textColour) {
        checkBoxRenderer_->setTextColor(Utility::convertToTGUIColour(textColour));
    }

    void CheckBoxRenderer::setTextHoverColour(Colour colour) {
        checkBoxRenderer_->setTextColorHover(Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getTextHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorHover());
    }

    void CheckBoxRenderer::setDisabledTextColour(Colour textColour) {
        checkBoxRenderer_->setTextColorDisabled(
            Utility::convertToTGUIColour(textColour));
    }

    Colour CheckBoxRenderer::getDisabledTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorDisabled());
    }

    void CheckBoxRenderer::setCheckedTextColour(Colour colour) {
        checkBoxRenderer_->setTextColorChecked(Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getTextColorChecked() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorChecked());
    }

    void CheckBoxRenderer::setCheckedTextHoverColour(Colour colour) {
        checkBoxRenderer_->setTextColorCheckedHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedTextHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorCheckedHover());
    }

    void CheckBoxRenderer::setCheckedDisabledTextColour(Colour colour) {
        checkBoxRenderer_->setTextColorCheckedDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedDisabledTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorCheckedDisabled());
    }

    void CheckBoxRenderer::setBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColor(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBackgroundColor());
    }

    void CheckBoxRenderer::setBackgroundHoverColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getBackgroundHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorCheckedHover());
    }

    void CheckBoxRenderer::setDisabledBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getDisabledBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBackgroundColorDisabled());
    }

    void CheckBoxRenderer::setCheckedBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorChecked(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBackgroundColorChecked());
    }

    void CheckBoxRenderer::setCheckedHoverBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorCheckedHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedHoverBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorCheckedHover());
    }

    void CheckBoxRenderer::setCheckedDisabledBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorCheckedDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedDisabledBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBackgroundColorCheckedDisabled());
    }

    void CheckBoxRenderer::setBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColor(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColor());
    }

    void CheckBoxRenderer::setBorderHoverColour(Colour colour) {
        checkBoxRenderer_->setBorderColorHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getBorderHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorHover());
    }

    void CheckBoxRenderer::setDisabledBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getDisabledBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorDisabled());
    }

    void CheckBoxRenderer::setFocusedBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorFocused(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getFocusedBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorFocused());
    }

    void CheckBoxRenderer::setCheckedBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorChecked(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorChecked());
    }

    void CheckBoxRenderer::setCheckedHoverBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorCheckedHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedHoverBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorCheckedHover());
    }

    void CheckBoxRenderer::setCheckedDisabledBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorCheckedDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedDisabledBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
                checkBoxRenderer_->getBorderColorCheckedDisabled());
    }

    void CheckBoxRenderer::setCheckedFocusedBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorCheckedFocused(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedFocusedBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorCheckedFocused());
    }

    void CheckBoxRenderer::setCheckColour(Colour colour) {
        checkBoxRenderer_->setCheckColor(Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getCheckColor());
    }

    void CheckBoxRenderer::setCheckHoverColour(Colour colour) {
        checkBoxRenderer_->setCheckColorHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getCheckColorHover());
    }

    void CheckBoxRenderer::setDisabledCheckedColour(Colour colour) {
        checkBoxRenderer_->setCheckColorDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getDisabledCheckColour() const {
        return Utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getCheckColorDisabled());
    }

    void CheckBoxRenderer::setUncheckedTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureUnchecked(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void CheckBoxRenderer::setCheckedTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureChecked(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void CheckBoxRenderer::setUncheckedHoverTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureUncheckedHover(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void CheckBoxRenderer::setCheckedHoverTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureCheckedHover(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void CheckBoxRenderer::setUncheckedDisabledTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureUncheckedDisabled(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void CheckBoxRenderer::setCheckedDisabledTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureCheckedDisabled(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void CheckBoxRenderer::setUncheckedFocusedTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureUncheckedFocused(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void CheckBoxRenderer::setCheckedFocusedTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureCheckedFocused(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void CheckBoxRenderer::setTextStyle(TextStyle style) {
        checkBoxRenderer_->setTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle CheckBoxRenderer::getTextStyle() const {
        return static_cast<TextStyle>(
                static_cast<unsigned int>(checkBoxRenderer_->getTextStyle()));
    }

    void CheckBoxRenderer::setCheckedTextStyle(TextStyle style) {
        checkBoxRenderer_->setTextStyleChecked(static_cast<tgui::TextStyle>(style));
    }

    TextStyle CheckBoxRenderer::getCheckedTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(checkBoxRenderer_->getTextStyleChecked()));
    }

    void CheckBoxRenderer::setOpacity(float opacity) {
        checkBoxRenderer_->setOpacity(opacity);
    }

    float CheckBoxRenderer::getOpacity() const {
        return checkBoxRenderer_->getOpacity();
    }

    void CheckBoxRenderer::setOpacityDisabled(float opacity) {
        checkBoxRenderer_->setOpacityDisabled(opacity);
    }

    float CheckBoxRenderer::getOpacityDisabled() const {
        return checkBoxRenderer_->getOpacityDisabled();
    }

    void CheckBoxRenderer::setFont(const std::string &font) {
        checkBoxRenderer_->setFont(font.c_str());
    }

    void CheckBoxRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        checkBoxRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool CheckBoxRenderer::isTransparentTextureIgnored() const {
        return checkBoxRenderer_->getTransparentTexture();
    }

    int CheckBoxRenderer::onPropertyChange(const std::string &property,
           Callback<const std::string &> callback)
    {
        return 0;
    }

    void CheckBoxRenderer::unsubscribe(int id) {

    }

    void CheckBoxRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        checkBoxRenderer_ = dynamic_cast<tgui::CheckBoxRenderer*>(renderer);
    }

    tgui::WidgetRenderer *CheckBoxRenderer::getInternalPtr() {
        return checkBoxRenderer_;
    }

    CheckBoxRenderer::~CheckBoxRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        checkBoxRenderer_ = nullptr;
    }
}