////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

#include "IME/graphics/ui/renderers/ChildWindowRenderer.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"

namespace IME::UI {
    void ChildWindowRenderer::setBorders(const Borders &borders) {
        windowRenderer_->setBorders({borders.left, borders.top, borders.right, borders.bottom});
    }

    Borders ChildWindowRenderer::getBorders() const {
        return {windowRenderer_->getBorders().getLeft(),
                windowRenderer_->getBorders().getTop(),
                windowRenderer_->getBorders().getRight(),
                windowRenderer_->getBorders().getBottom()};
    }

    void ChildWindowRenderer::setTitleBarHeight(float height) {
        windowRenderer_->setTitleBarHeight(height);
    }

    float ChildWindowRenderer::getTitleBarHeight() const {
        return windowRenderer_->getTitleBarHeight();
    }

    void ChildWindowRenderer::setTitleBarColour(Colour colour) {
        windowRenderer_->setTitleBarColor(Utility::convertToTGUIColour(colour));
    }

    Colour ChildWindowRenderer::getTitleBarColour() const {
        return Utility::convertFrom3rdPartyColour(
            windowRenderer_->getTitleBarColor());
    }

    void ChildWindowRenderer::setTitleColour(Colour colour) {
        windowRenderer_->setTitleColor(Utility::convertToTGUIColour(colour));
    }

    Colour ChildWindowRenderer::getTitleColour() const {
        return Utility::convertFrom3rdPartyColour(
            windowRenderer_->getTitleColor());
    }

    void ChildWindowRenderer::setBackgroundColour(Colour colour) {
        windowRenderer_->setBackgroundColor(Utility::convertToTGUIColour(colour));
    }

    Colour ChildWindowRenderer::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            windowRenderer_->getBackgroundColor());
    }

    void ChildWindowRenderer::setBorderColour(Colour colour) {
        windowRenderer_->setBorderColor(Utility::convertToTGUIColour(colour));
    }

    Colour ChildWindowRenderer::getBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            windowRenderer_->getBorderColor());
    }

    void ChildWindowRenderer::setFocusedBorderColour(Colour colour) {
        windowRenderer_->setBorderColorFocused(Utility::convertToTGUIColour(colour));
    }

    Colour ChildWindowRenderer::getBorderColourFocused() const {
        return Utility::convertFrom3rdPartyColour(
            windowRenderer_->getBorderColorFocused());
    }

    void ChildWindowRenderer::setBorderBelowTitleBar(float border) {
        windowRenderer_->setBorderBelowTitleBar(border);
    }

    float ChildWindowRenderer::getBorderBelowTitleBar() const {
        return windowRenderer_->getBorderBelowTitleBar();
    }

    void ChildWindowRenderer::setDistanceToSide(float distanceToSide) {
        windowRenderer_->setDistanceToSide(distanceToSide);
    }

    float ChildWindowRenderer::getDistanceToSide() const {
        return windowRenderer_->getDistanceToSide();
    }

    void ChildWindowRenderer::setPaddingBetweenButtons(float padding) {
        windowRenderer_->setPaddingBetweenButtons(padding);
    }

    float ChildWindowRenderer::getPaddingBetweenButtons() const {
        return windowRenderer_->getPaddingBetweenButtons();
    }

    void ChildWindowRenderer::setMinimumResizableBorderWidth(float minimumBorderWidth) {
        windowRenderer_->setMinimumResizableBorderWidth(minimumBorderWidth);
    }

    float ChildWindowRenderer::getMinimumResizableBorderWidth() const {
        return windowRenderer_->getMinimumResizableBorderWidth();
    }

    void ChildWindowRenderer::setShowTextOnTitleButtons(bool showText) {
        windowRenderer_->setShowTextOnTitleButtons(showText);
    }

    bool ChildWindowRenderer::isTextShownOnTitleButtons() const {
        return windowRenderer_->getShowTextOnTitleButtons();
    }

    void ChildWindowRenderer::setTextureTitleBar(const std::string &filename) {
        windowRenderer_->setTextureTitleBar(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void ChildWindowRenderer::setTextureBackground(const std::string &filename) {
        windowRenderer_->setTextureBackground(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void ChildWindowRenderer::setOpacity(float opacity) {
        windowRenderer_->setOpacity(opacity);
    }

    float ChildWindowRenderer::getOpacity() const {
        return windowRenderer_->getOpacity();
    }

    void ChildWindowRenderer::setOpacityDisabled(float opacity) {
        windowRenderer_->setOpacityDisabled(opacity);
    }

    float ChildWindowRenderer::getOpacityDisabled() const {
        return windowRenderer_->getOpacity();
    }

    void ChildWindowRenderer::setFont(const std::string &filename) {
        windowRenderer_->setFont(Utility::get_TGUI_Font(filename));
    }

    void ChildWindowRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        windowRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool ChildWindowRenderer::isTransparentTextureIgnored() const {
        return windowRenderer_->getTransparentTexture();
    }

    int ChildWindowRenderer::onPropertyChange(const std::string &,
        Callback<const std::string &>)
    {
        return 0;
    }

    void ChildWindowRenderer::unsubscribe(int) {

    }

    void ChildWindowRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        windowRenderer_ = dynamic_cast<tgui::ChildWindowRenderer*>(renderer);
    }

    tgui::WidgetRenderer *ChildWindowRenderer::getInternalPtr() {
        return windowRenderer_;
    }

    ChildWindowRenderer::~ChildWindowRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        windowRenderer_ = nullptr;
    }
}