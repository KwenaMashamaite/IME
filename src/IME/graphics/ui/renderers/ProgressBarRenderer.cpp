#include "IME/graphics/ui/renderers/ProgressBarRenderer.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"

namespace IME::Graphics::UI {
    void ProgressBarRenderer::setBorders(const Borders &borders) {
        progressBarRenderer_->setBorders({borders.left, borders.top,
            borders.right, borders.bottom});
    }

    Borders ProgressBarRenderer::getBorders() const {
        return {progressBarRenderer_->getBorders().getLeft(),
                progressBarRenderer_->getBorders().getTop(),
                progressBarRenderer_->getBorders().getRight(),
                progressBarRenderer_->getBorders().getBottom()};
    }

    void ProgressBarRenderer::setTextColour(Colour color) {
        progressBarRenderer_->setTextColor(Utility::convertToTGUIColour(color));
    }

    Colour ProgressBarRenderer::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(progressBarRenderer_->getTextColor());
    }

    void ProgressBarRenderer::setTextColourFilled(Colour color) {
        progressBarRenderer_->setTextColorFilled(Utility::convertToTGUIColour(color));
    }

    Colour ProgressBarRenderer::getTextColourFilled() const {
        return Utility::convertFrom3rdPartyColour(progressBarRenderer_->getTextColorFilled());
    }

    void ProgressBarRenderer::setBackgroundColour(Colour color) {
        progressBarRenderer_->setBackgroundColor(Utility::convertToTGUIColour(color));
    }

    Colour ProgressBarRenderer::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(progressBarRenderer_->getBackgroundColor());
    }

    void ProgressBarRenderer::setFillColour(Colour color) {
        progressBarRenderer_->setFillColor(Utility::convertToTGUIColour(color));
    }

    Colour ProgressBarRenderer::getFillColour() const {
        return Utility::convertFrom3rdPartyColour(progressBarRenderer_->getFillColor());
    }

    void ProgressBarRenderer::setBorderColour(Colour color) {
        progressBarRenderer_->setBorderColor(Utility::convertToTGUIColour(color));
    }

    Colour ProgressBarRenderer::getBorderColour() const {
        return Utility::convertFrom3rdPartyColour(progressBarRenderer_->getBorderColor());
    }

    void ProgressBarRenderer::setBackgroundTexture(const std::string &texture) {
        progressBarRenderer_->setTextureBackground(
            IME::ResourceManager::getInstance()->getTexture(texture));
    }

    void ProgressBarRenderer::setFillTexture(const std::string &texture) {
        progressBarRenderer_->setTextureFill(
            IME::ResourceManager::getInstance()->getTexture(texture));
    }

    void ProgressBarRenderer::setTextStyle(TextStyle style) {
        progressBarRenderer_->setTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle ProgressBarRenderer::getTextStyle() const {
        return static_cast<TextStyle>(static_cast<unsigned int>(
                progressBarRenderer_->getTextStyle()));
    }

    void ProgressBarRenderer::setOpacity(float opacity) {
        progressBarRenderer_->setOpacity(opacity);
    }

    float ProgressBarRenderer::getOpacity() const {
        return progressBarRenderer_->getOpacity();
    }

    void ProgressBarRenderer::setOpacityDisabled(float opacity) {
        progressBarRenderer_->setOpacityDisabled(opacity);
    }

    float ProgressBarRenderer::getOpacityDisabled() const {
        return progressBarRenderer_->getOpacity();
    }

    void ProgressBarRenderer::setFont(const std::string &font) {
        progressBarRenderer_->setFont(font.c_str());
    }

    void ProgressBarRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        progressBarRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool ProgressBarRenderer::isTransparentTextureIgnored() const {
        return progressBarRenderer_->getTransparentTexture();
    }

    void ProgressBarRenderer::unsubscribe(int id) {

    }

    void ProgressBarRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        progressBarRenderer_ = dynamic_cast<tgui::ProgressBarRenderer*>(renderer);
    }

    tgui::WidgetRenderer *ProgressBarRenderer::getInternalPtr() {
        return progressBarRenderer_;
    }

    int ProgressBarRenderer::onPropertyChange(const std::string &property,
        Callback<const std::string &> callback) {
        return 0;
    }
}
