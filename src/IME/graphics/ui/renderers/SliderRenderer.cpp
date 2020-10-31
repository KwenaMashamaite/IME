#include "IME/graphics/ui/renderers/SliderRenderer.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"

namespace IME::Graphics::UI {
    void SliderRenderer::setBorders(const Borders &borders) {
        sliderRenderer_->setBorders({borders.left, borders.top,
                    borders.right, borders.bottom});
    }

    Borders SliderRenderer::getBorders() const {
        return {sliderRenderer_->getBorders().getLeft(),
                sliderRenderer_->getBorders().getTop(),
                sliderRenderer_->getBorders().getRight(),
                sliderRenderer_->getBorders().getBottom()};
    }

    void SliderRenderer::setTrackColour(Colour color) {
        sliderRenderer_->setTrackColor(Utility::convertToTGUIColour(color));
    }

    Colour SliderRenderer::getTrackColour() const {
        return Utility::convertFrom3rdPartyColour(
            sliderRenderer_->getTrackColor());
    }

    void SliderRenderer::setTrackHoverColour(Colour color) {
        sliderRenderer_->setTrackColorHover(Utility::convertToTGUIColour(color));
    }

    Colour SliderRenderer::getTrackHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            sliderRenderer_->getTrackColorHover());
    }

    void SliderRenderer::setThumbColour(Colour color) {
        sliderRenderer_->setThumbColor(Utility::convertToTGUIColour(color));
    }

    Colour SliderRenderer::getThumbColour() const {
        return Utility::convertFrom3rdPartyColour(
                sliderRenderer_->getThumbColor());
    }

    void SliderRenderer::setThumbHoverColour(Colour color) {
        sliderRenderer_->setThumbColorHover(Utility::convertToTGUIColour(color));
    }

    Colour SliderRenderer::getThumbHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            sliderRenderer_->getThumbColorHover());
    }

    void SliderRenderer::setBorderColour(Colour color) {
        sliderRenderer_->setBorderColor(Utility::convertToTGUIColour(color));
    }

    Colour SliderRenderer::getBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            sliderRenderer_->getBorderColor());
    }

    void SliderRenderer::setBorderHoverColour(Colour color) {
        sliderRenderer_->setBorderColorHover(Utility::convertToTGUIColour(color));
    }

    Colour SliderRenderer::getBorderHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            sliderRenderer_->getBorderColorHover());
    }

    void SliderRenderer::setTrackTexture(const std::string &filename) {
        sliderRenderer_->setTextureTrack(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void SliderRenderer::setTrackHoverTexture(const std::string &filename) {
        sliderRenderer_->setTextureTrackHover(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void SliderRenderer::setThumbTexture(const std::string &filename) {
        sliderRenderer_->setTextureThumb(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void SliderRenderer::setThumbHoverTexture(const std::string &filename) {
        sliderRenderer_->setTextureThumbHover(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void SliderRenderer::setThumbWithinTrack(bool keepThumbInside) {
        sliderRenderer_->setThumbWithinTrack(keepThumbInside);
    }

    bool SliderRenderer::isThumbWithinTrack() const {
        return sliderRenderer_->getThumbWithinTrack();
    }

    void SliderRenderer::setOpacity(float opacity) {
        sliderRenderer_->setOpacity(opacity);
    }

    float SliderRenderer::getOpacity() const {
        return sliderRenderer_->getOpacity();
    }

    void SliderRenderer::setOpacityDisabled(float opacity) {
        sliderRenderer_->setOpacityDisabled(opacity);
    }

    float SliderRenderer::getOpacityDisabled() const {
        return sliderRenderer_->getOpacity();
    }

    void SliderRenderer::setFont(const std::string &font) {
        sliderRenderer_->setFont(font.c_str());
    }

    void SliderRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        sliderRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool SliderRenderer::isTransparentTextureIgnored() const {
        return sliderRenderer_->getTransparentTexture();
    }

    int SliderRenderer::onPropertyChange(const std::string &property,
         Callback<const std::string &> callback)
    {
        return 0;
    }

    void SliderRenderer::unsubscribe(int id) {

    }

    void SliderRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        sliderRenderer_ = dynamic_cast<tgui::SliderRenderer*>(renderer);
    }

    tgui::WidgetRenderer *SliderRenderer::getInternalPtr() {
        return sliderRenderer_;
    }

    SliderRenderer::~SliderRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        sliderRenderer_ = nullptr;
    }
}

