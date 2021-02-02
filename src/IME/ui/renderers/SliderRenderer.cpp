////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "IME/ui/renderers/SliderRenderer.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/utility/Helpers.h"

namespace ime::ui {
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

    void SliderRenderer::setTrackColour(Colour colour) {
        sliderRenderer_->setTrackColor(utility::convertToTGUIColour(colour));
    }

    Colour SliderRenderer::getTrackColour() const {
        return utility::convertFrom3rdPartyColour(
            sliderRenderer_->getTrackColor());
    }

    void SliderRenderer::setTrackHoverColour(Colour colour) {
        sliderRenderer_->setTrackColorHover(utility::convertToTGUIColour(colour));
    }

    Colour SliderRenderer::getTrackHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            sliderRenderer_->getTrackColorHover());
    }

    void SliderRenderer::setThumbColour(Colour colour) {
        sliderRenderer_->setThumbColor(utility::convertToTGUIColour(colour));
    }

    Colour SliderRenderer::getThumbColour() const {
        return utility::convertFrom3rdPartyColour(
                sliderRenderer_->getThumbColor());
    }

    void SliderRenderer::setThumbHoverColour(Colour colour) {
        sliderRenderer_->setThumbColorHover(utility::convertToTGUIColour(colour));
    }

    Colour SliderRenderer::getThumbHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            sliderRenderer_->getThumbColorHover());
    }

    void SliderRenderer::setBorderColour(Colour colour) {
        sliderRenderer_->setBorderColor(utility::convertToTGUIColour(colour));
    }

    Colour SliderRenderer::getBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            sliderRenderer_->getBorderColor());
    }

    void SliderRenderer::setBorderHoverColour(Colour colour) {
        sliderRenderer_->setBorderColorHover(utility::convertToTGUIColour(colour));
    }

    Colour SliderRenderer::getBorderHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            sliderRenderer_->getBorderColorHover());
    }

    void SliderRenderer::setTrackTexture(const std::string &filename) {
        sliderRenderer_->setTextureTrack(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void SliderRenderer::setTrackHoverTexture(const std::string &filename) {
        sliderRenderer_->setTextureTrackHover(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void SliderRenderer::setThumbTexture(const std::string &filename) {
        sliderRenderer_->setTextureThumb(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void SliderRenderer::setThumbHoverTexture(const std::string &filename) {
        sliderRenderer_->setTextureThumbHover(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
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

    void SliderRenderer::setFont(const std::string &filename) {
        sliderRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void SliderRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        sliderRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool SliderRenderer::isTransparentTextureIgnored() const {
        return sliderRenderer_->getTransparentTexture();
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

