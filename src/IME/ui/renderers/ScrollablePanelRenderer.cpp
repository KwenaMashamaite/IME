////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/ui/renderers/ScrollablePanelRenderer.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/Renderers/ScrollablePanelRenderer.hpp>

namespace ime::ui {
    void ScrollablePanelRenderer::setBorders(const Borders &borders) {
        panelRenderer_->setBorders({borders.left, borders.top,
            borders.right, borders.bottom});
    }

    Borders ScrollablePanelRenderer::getBorders() const {
        return {panelRenderer_->getBorders().getLeft(),
                panelRenderer_->getBorders().getTop(),
                panelRenderer_->getBorders().getRight(),
                panelRenderer_->getBorders().getBottom()};
    }

    void ScrollablePanelRenderer::setBorderColour(Colour colour) {
        panelRenderer_->setBorderColor(utility::convertToTGUIColour(colour));
    }

    Colour ScrollablePanelRenderer::getBorderColour() const {
        return utility::convertFrom3rdPartyColour(panelRenderer_->getBorderColor());
    }

    void ScrollablePanelRenderer::setBackgroundColour(Colour colour) {
        panelRenderer_->setBackgroundColor(utility::convertToTGUIColour(colour));
    }

    Colour ScrollablePanelRenderer::getBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(panelRenderer_->getBackgroundColor());
    }

    void ScrollablePanelRenderer::setRoundedBorderRadius(float radius) {
        panelRenderer_->setRoundedBorderRadius(radius);
    }

    float ScrollablePanelRenderer::getRoundedBorderRadius() const {
        return panelRenderer_->getRoundedBorderRadius();
    }

    void ScrollablePanelRenderer::setBackgroundTexture(const std::string &texture) {
        panelRenderer_->setTextureBackground(
            ime::ResourceManager::getInstance()->getTexture(texture).getInternalTexture());
    }
    
    void ScrollablePanelRenderer::setScrollbarWidth(float scrollbarWidth) {
        panelRenderer_->setScrollbarWidth(scrollbarWidth);
    }

    float ScrollablePanelRenderer::getScrollbarWidth() const {
        return panelRenderer_->getScrollbarWidth();
    }

    void ScrollablePanelRenderer::setOpacity(float opacity) {
        panelRenderer_->setOpacity(opacity);
    }

    float ScrollablePanelRenderer::getOpacity() const {
        return panelRenderer_->getOpacity();
    }

    void ScrollablePanelRenderer::setOpacityDisabled(float opacity) {
        panelRenderer_->setOpacityDisabled(opacity);
    }

    float ScrollablePanelRenderer::getOpacityDisabled() const {
        return panelRenderer_->getOpacityDisabled();
    }

    void ScrollablePanelRenderer::setFont(const std::string &filename) {
        panelRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void ScrollablePanelRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        panelRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool ScrollablePanelRenderer::isTransparentTextureIgnored() const {
        return panelRenderer_->getTransparentTexture();
    }

    IWidgetRenderer::Ptr ScrollablePanelRenderer::clone() const {
        return std::make_unique<ScrollablePanelRenderer>(*this);
    }

    void ScrollablePanelRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        panelRenderer_ = dynamic_cast<tgui::ScrollablePanelRenderer*>(renderer);
    }

    tgui::WidgetRenderer *ScrollablePanelRenderer::getInternalPtr() {
        return panelRenderer_;
    }

    ScrollablePanelRenderer::~ScrollablePanelRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        panelRenderer_ = nullptr;
    }
}
