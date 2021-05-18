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

#include "IME/ui/renderers/SpinButtonRenderer.h"
#include "IME/utility/Helpers.h"
#include "IME/core/resources/ResourceManager.h"
#include <TGUI/Renderers/SpinButtonRenderer.hpp>

namespace ime::ui {
    void SpinButtonRenderer::setBorders(const Borders &borders) {
        renderer_->setBorders({borders.left, borders.top, borders.right, borders.bottom});
    }

    Borders SpinButtonRenderer::getBorders() const {
        return {renderer_->getBorders().getLeft(),
                renderer_->getBorders().getTop(),
                renderer_->getBorders().getRight(),
                renderer_->getBorders().getBottom()};
    }

    void SpinButtonRenderer::setSpaceBetweenArrows(float space) {
        renderer_->setBorderBetweenArrows(space);
    }

    float SpinButtonRenderer::getSpaceBetweenArrows() const {
        return renderer_->getBorderBetweenArrows();
    }

    void SpinButtonRenderer::setBackgroundColour(Colour colour) {
        renderer_->setBackgroundColor(utility::convertToTGUIColour(colour));
    }

    Colour SpinButtonRenderer::getBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(renderer_->getBackgroundColor());
    }

    void SpinButtonRenderer::setBackgroundHoverColour(Colour colour) {
        renderer_->setBackgroundColor(utility::convertToTGUIColour(colour));
    }

    Colour SpinButtonRenderer::getBackgroundHoverColour() const {
        return utility::convertFrom3rdPartyColour(renderer_->getBackgroundColorHover());
    }

    void SpinButtonRenderer::setArrowColor(Colour colour) {
        renderer_->setArrowColor(utility::convertToTGUIColour(colour));
    }

    Colour SpinButtonRenderer::getArrowColour() const {
        return utility::convertFrom3rdPartyColour(renderer_->getArrowColor());
    }

    void SpinButtonRenderer::setArrowHoverColor(Colour colour) {
        renderer_->setArrowColorHover(utility::convertToTGUIColour(colour));
    }

    Colour SpinButtonRenderer::getArrowHoverColour() const {
        return utility::convertFrom3rdPartyColour(renderer_->getArrowColorHover());
    }

    void SpinButtonRenderer::setBorderColour(Colour colour) {
        renderer_->setBorderColor(utility::convertToTGUIColour(colour));
    }

    Colour SpinButtonRenderer::getBorderColour() const {
        return utility::convertFrom3rdPartyColour(renderer_->getBorderColor());
    }

    void SpinButtonRenderer::setUpArrowTexture(const std::string &filename) {
        renderer_->setTextureArrowUp(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void SpinButtonRenderer::setUpArrowHoverTexture(const std::string &filename) {
        renderer_->setTextureArrowUpHover(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void SpinButtonRenderer::setDownArrowTexture(const std::string &filename) {
        renderer_->setTextureArrowDown(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void SpinButtonRenderer::setDownArrowHoverTexture(const std::string &filename) {
        renderer_->setTextureArrowDownHover(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void SpinButtonRenderer::setOpacity(float opacity) {
        renderer_->setOpacity(opacity);
    }

    float SpinButtonRenderer::getOpacity() const {
        return renderer_->getOpacity();
    }

    void SpinButtonRenderer::setOpacityDisabled(float opacity) {
        renderer_->setOpacityDisabled(opacity);
    }

    float SpinButtonRenderer::getOpacityDisabled() const {
        return renderer_->getOpacityDisabled();
    }

    void SpinButtonRenderer::setFont(const std::string &filename) {
        renderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void SpinButtonRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        renderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool SpinButtonRenderer::isTransparentTextureIgnored() const {
        return renderer_->getTransparentTexture();
    }

    IWidgetRenderer::Ptr SpinButtonRenderer::clone() const {
        return std::make_unique<SpinButtonRenderer>(*this);
    }

    void SpinButtonRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        renderer_ = dynamic_cast<tgui::SpinButtonRenderer*>(renderer);
    }

    tgui::WidgetRenderer *SpinButtonRenderer::getInternalPtr() {
        return renderer_;
    }

    SpinButtonRenderer::~SpinButtonRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        renderer_ = nullptr;
    }
}
