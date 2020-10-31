#include <IME/core/managers/ResourceManager.h>
#include "IME/graphics/ui/renderers/LabelRenderer.h"
#include "IME/utility/Helpers.h"

namespace IME::Graphics::UI {
    void LabelRenderer::setBorders(const Borders &borders) {
        labelRenderer_->setBorders({borders.left, borders.top, borders.right, borders.bottom});
    }

    Borders LabelRenderer::getBorders() const {
        return {labelRenderer_->getBorders().getLeft(),
                labelRenderer_->getBorders().getTop(),
        labelRenderer_->getBorders().getRight(),
        labelRenderer_->getBorders().getBottom()};
    }

    void LabelRenderer::setPadding(const Padding &padding) {
        labelRenderer_->setPadding({padding.left, padding.top, padding.right,
                                    padding.bottom});
    }

    Padding LabelRenderer::getPadding() const {
        return {labelRenderer_->getPadding().getLeft(),
                labelRenderer_->getPadding().getTop(),
                labelRenderer_->getPadding().getRight(),
                labelRenderer_->getPadding().getBottom()};
    }

    void LabelRenderer::setTextColour(Colour colour) {
        labelRenderer_->setTextColor(Utility::convertToTGUIColour(colour));
    }

    Colour LabelRenderer::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(labelRenderer_->getTextColor());
    }

    void LabelRenderer::setBackgroundColour(Colour colour) {
        labelRenderer_->setBackgroundColor(Utility::convertToTGUIColour(colour));
    }

    Colour LabelRenderer::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(labelRenderer_->getBorderColor());
    }

    void LabelRenderer::setBorderColour(Colour colour) {
        labelRenderer_->setBorderColor(Utility::convertToTGUIColour(colour));
    }

    Colour LabelRenderer::getBorderColour() const {
        return Utility::convertFrom3rdPartyColour(labelRenderer_->getBorderColor());
    }

    void LabelRenderer::setTextStyle(TextStyle style) {
        labelRenderer_->setTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle LabelRenderer::getTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(labelRenderer_->getTextStyle()));
    }

    void LabelRenderer::setTextOutlineColour(Colour outlineColor) {
        labelRenderer_->setTextOutlineColor(Utility::convertToTGUIColour(outlineColor));
    }

    Colour LabelRenderer::getTextOutlineColour() const {
        return Utility::convertFrom3rdPartyColour(
            labelRenderer_->getTextOutlineColor());
    }

    void LabelRenderer::setTextOutlineThickness(float outlineThickness) {
        labelRenderer_->setTextOutlineThickness(outlineThickness);
    }

    float LabelRenderer::getTextOutlineThickness() const {
        return labelRenderer_->getTextOutlineThickness();
    }

    void LabelRenderer::setBackgroundTexture(const std::string &filename) {
        labelRenderer_->setTextureBackground(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void LabelRenderer::setScrollbarWidth(float scrollbarWidth) {
        labelRenderer_->setScrollbarWidth(scrollbarWidth);
    }

    float LabelRenderer::getScrollbarWidth() const {
        return labelRenderer_->getScrollbarWidth();
    }

    void LabelRenderer::setOpacity(float opacity) {
        labelRenderer_->setOpacity(opacity);
    }

    float LabelRenderer::getOpacity() const {
        return labelRenderer_->getOpacity();
    }

    void LabelRenderer::setOpacityDisabled(float opacity) {
        labelRenderer_->setOpacityDisabled(opacity);
    }

    float LabelRenderer::getOpacityDisabled() const {
        return labelRenderer_->getOpacityDisabled();
    }

    void LabelRenderer::setFont(const std::string &filename) {
        labelRenderer_->setFont(Utility::get_TGUI_Font(filename));
    }

    void LabelRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        labelRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool LabelRenderer::isTransparentTextureIgnored() const {
        return labelRenderer_->getTransparentTexture();
    }

    int LabelRenderer::onPropertyChange(const std::string &property,
        Callback<const std::string &> callback) {
        return -1;
    }

    void LabelRenderer::unsubscribe(int id) {

    }

    void LabelRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        labelRenderer_ = dynamic_cast<tgui::LabelRenderer *>(renderer);
    }

    tgui::WidgetRenderer *LabelRenderer::getInternalPtr() {
        return labelRenderer_;
    }

    LabelRenderer::~LabelRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        labelRenderer_ = nullptr;
    }
}
