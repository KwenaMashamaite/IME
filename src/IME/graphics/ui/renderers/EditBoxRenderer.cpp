#include "IME/graphics/ui/renderers/EditBoxRenderer.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"

namespace IME::Graphics::UI {
    void EditBoxRenderer::setTextStyle(TextStyle style) {
        editBoxRenderer_->setTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle EditBoxRenderer::getTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(editBoxRenderer_->getTextStyle()));
    }

    void EditBoxRenderer::setDefaultTextStyle(TextStyle style) {
        editBoxRenderer_->setDefaultTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle EditBoxRenderer::getDefaultTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(editBoxRenderer_->getDefaultTextStyle()));
    }

    void EditBoxRenderer::setBorders(const Borders &borders) {
        editBoxRenderer_->setBorders({borders.left, borders.top, borders.right, borders.bottom});
    }

    Borders EditBoxRenderer::getBorders() const {
        return {editBoxRenderer_->getBorders().getLeft(),
                editBoxRenderer_->getBorders().getTop(),
                editBoxRenderer_->getBorders().getRight(),
                editBoxRenderer_->getBorders().getBottom()};
    }

    void EditBoxRenderer::setPadding(const Padding &padding) {
        editBoxRenderer_->setPadding({padding.left, padding.top, padding.right,
            padding.bottom});
    }

    Padding EditBoxRenderer::getPadding() const {
        return {editBoxRenderer_->getPadding().getLeft(),
                editBoxRenderer_->getPadding().getTop(),
                editBoxRenderer_->getPadding().getRight(),
                editBoxRenderer_->getPadding().getBottom()};
    }

    void EditBoxRenderer::setCaretWidth(float width) {
        editBoxRenderer_->setCaretWidth(width);
    }

    float EditBoxRenderer::getCaretWidth() const {
        return editBoxRenderer_->getCaretWidth();
    }

    void EditBoxRenderer::setTextColour(Colour textColour) {
        editBoxRenderer_->setTextColor(Utility::convertToTGUIColour(textColour));
    }

    Colour EditBoxRenderer::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getTextColor());
    }

    void EditBoxRenderer::setDisabledTextColour(Colour textColour) {
        editBoxRenderer_->setTextColorDisabled(Utility::convertToTGUIColour(textColour));
    }

    Colour EditBoxRenderer::getDisabledTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getTextColorDisabled());
    }

    void EditBoxRenderer::setFocusedTextColour(Colour textColour) {
        editBoxRenderer_->setTextColorFocused(
            Utility::convertToTGUIColour(textColour));
    }

    Colour EditBoxRenderer::getFocusedTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getTextColorFocused());
    }

    void EditBoxRenderer::setSelectedTextColour(Colour colour) {
        editBoxRenderer_->setSelectedTextColor(
            Utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getSelectedTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getSelectedTextColor());
    }

    void
    EditBoxRenderer::setSelectedTextBackgroundColour(Colour backgroundColour) {
        editBoxRenderer_->setSelectedTextBackgroundColor(
            Utility::convertToTGUIColour(backgroundColour));
    }

    Colour EditBoxRenderer::getSelectedTextBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getSelectedTextBackgroundColor());
    }

    void EditBoxRenderer::setDefaultTextColour(Colour defaultTextColour) {
        editBoxRenderer_->setDefaultTextColor(
            Utility::convertToTGUIColour(defaultTextColour));
    }

    Colour EditBoxRenderer::getDefaultTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getDefaultTextColor());
    }

    void EditBoxRenderer::setBackgroundColour(Colour colour) {
        editBoxRenderer_->setBackgroundColor(
            Utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBackgroundColor());
    }

    void EditBoxRenderer::setBackgroundHoverColour(Colour colour) {
        editBoxRenderer_->setBackgroundColor(
            Utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getBackgroundColorHover() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBackgroundColorHover());
    }

    void EditBoxRenderer::setDisabledBackgroundColour(Colour colour) {
        editBoxRenderer_->setBorderColorDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getDisabledBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBackgroundColorDisabled());
    }

    void EditBoxRenderer::setFocusedBackgroundColour(Colour colour) {
        editBoxRenderer_->setBackgroundColorFocused(
            Utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getFocusedBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBackgroundColorFocused());
    }

    void EditBoxRenderer::setCaretColour(Colour caretColour) {
        editBoxRenderer_->setCaretColor(
            Utility::convertToTGUIColour(caretColour));
    }

    Colour EditBoxRenderer::getCaretColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getCaretColor());
    }

    void EditBoxRenderer::setCaretHoverColour(Colour caretColour) {
        editBoxRenderer_->setCaretColorHover(
            Utility::convertToTGUIColour(caretColour));
    }

    Colour EditBoxRenderer::getCaretHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getCaretColorHover());
    }

    void EditBoxRenderer::setCaretColorFocused(Colour caretColour) {
        editBoxRenderer_->setCaretColorFocused(
            Utility::convertToTGUIColour(caretColour));
    }

    Colour EditBoxRenderer::getFocusedCaretColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getCaretColorFocused());
    }

    void EditBoxRenderer::setBorderColour(Colour colour) {
        editBoxRenderer_->setBorderColor(
            Utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
                editBoxRenderer_->getBorderColor());
    }

    void EditBoxRenderer::setBorderHoverColour(Colour colour) {
        editBoxRenderer_->setBorderColorHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getBorderHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
                editBoxRenderer_->getBorderColorHover());
    }

    void EditBoxRenderer::setDisabledBorderColour(Colour colour) {
        editBoxRenderer_->setBorderColorDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getDisabledBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBorderColorDisabled());
    }

    void EditBoxRenderer::setFocusedBorderColour(Colour colour) {
        editBoxRenderer_->setBorderColorFocused(
            Utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getFocusedBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBorderColorFocused());
    }

    void EditBoxRenderer::setTexture(const std::string &filename) {
        editBoxRenderer_->setTexture(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void EditBoxRenderer::setHoverTexture(const std::string &filename) {
        editBoxRenderer_->setTextureHover(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void EditBoxRenderer::setDisabledTexture(const std::string &filename) {
        editBoxRenderer_->setTextureDisabled(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void EditBoxRenderer::setFocusedTexture(const std::string &filename) {
        editBoxRenderer_->setTextureFocused(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void EditBoxRenderer::setOpacity(float opacity) {
        editBoxRenderer_->setOpacity(opacity);
    }

    float EditBoxRenderer::getOpacity() const {
        return editBoxRenderer_->getOpacity();
    }

    void EditBoxRenderer::setOpacityDisabled(float opacity) {
        editBoxRenderer_->setOpacityDisabled(opacity);
    }

    float EditBoxRenderer::getOpacityDisabled() const {
        return editBoxRenderer_->getOpacity();
    }

    void EditBoxRenderer::setFont(const std::string &filename) {
        editBoxRenderer_->setFont(Utility::get_TGUI_Font(filename));
    }

    void EditBoxRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        editBoxRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool EditBoxRenderer::isTransparentTextureIgnored() const {
        return editBoxRenderer_->getTransparentTexture();
    }

    int EditBoxRenderer::onPropertyChange(const std::string &property,
        Callback<const std::string &> callback)
    {
        return 0;
    }

    void EditBoxRenderer::unsubscribe(int id) {

    }

    void EditBoxRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        editBoxRenderer_ = dynamic_cast<tgui::EditBoxRenderer*>(renderer);
    }

    tgui::WidgetRenderer *EditBoxRenderer::getInternalPtr() {
        return editBoxRenderer_;
    }

    EditBoxRenderer::~EditBoxRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        editBoxRenderer_ = nullptr;
    }
}