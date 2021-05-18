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

#include "IME/ui/renderers/MessageBoxRenderer.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/Renderers/MessageBoxRenderer.hpp>

namespace ime::ui {
    void MessageBoxRenderer::setTextColour(Colour textColour) {
        messageBoxRenderer_->setTextColor(utility::convertToTGUIColour(textColour));
    }

    Colour MessageBoxRenderer::getTextColour() const {
        return utility::convertFrom3rdPartyColour(
            messageBoxRenderer_->getTextColor());
    }

    void MessageBoxRenderer::setBorders(const Borders &borders) {
        messageBoxRenderer_->setBorders({borders.left, borders.top, borders.right, borders.bottom});
    }

    Borders MessageBoxRenderer::getBorders() const {
        return {messageBoxRenderer_->getBorders().getLeft(),
                messageBoxRenderer_->getBorders().getTop(),
                messageBoxRenderer_->getBorders().getRight(),
                messageBoxRenderer_->getBorders().getBottom()};
    }

    void MessageBoxRenderer::setTitleBarHeight(float height) {
        messageBoxRenderer_->setTitleBarHeight(height);
    }

    float MessageBoxRenderer::getTitleBarHeight() const {
        return messageBoxRenderer_->getTitleBarHeight();
    }

    void MessageBoxRenderer::setTitleBarColour(Colour colour) {
        messageBoxRenderer_->setTitleBarColor(utility::convertToTGUIColour(colour));
    }

    Colour MessageBoxRenderer::getTitleBarColour() const {
        return utility::convertFrom3rdPartyColour(
            messageBoxRenderer_->getTitleBarColor());
    }

    void MessageBoxRenderer::setTitleColour(Colour colour) {
        messageBoxRenderer_->setTitleColor(utility::convertToTGUIColour(colour));
    }

    Colour MessageBoxRenderer::getTitleColour() const {
        return utility::convertFrom3rdPartyColour(
            messageBoxRenderer_->getTitleColor());
    }

    void MessageBoxRenderer::setBackgroundColour(Colour colour) {
        messageBoxRenderer_->setBackgroundColor(utility::convertToTGUIColour(colour));
    }

    Colour MessageBoxRenderer::getBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            messageBoxRenderer_->getBackgroundColor());
    }

    void MessageBoxRenderer::setBorderColour(Colour colour) {
        messageBoxRenderer_->setBorderColor(utility::convertToTGUIColour(colour));
    }

    Colour MessageBoxRenderer::getBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            messageBoxRenderer_->getBorderColor());
    }

    void MessageBoxRenderer::setFocusedBorderColour(Colour colour) {
        messageBoxRenderer_->setBorderColorFocused(utility::convertToTGUIColour(colour));
    }

    Colour MessageBoxRenderer::getBorderColourFocused() const {
        return utility::convertFrom3rdPartyColour(
            messageBoxRenderer_->getBorderColorFocused());
    }

    void MessageBoxRenderer::setBorderBelowTitleBar(float border) {
        messageBoxRenderer_->setBorderBelowTitleBar(border);
    }

    float MessageBoxRenderer::getBorderBelowTitleBar() const {
        return messageBoxRenderer_->getBorderBelowTitleBar();
    }

    void MessageBoxRenderer::setDistanceToSide(float distanceToSide) {
        messageBoxRenderer_->setDistanceToSide(distanceToSide);
    }

    float MessageBoxRenderer::getDistanceToSide() const {
        return messageBoxRenderer_->getDistanceToSide();
    }

    void MessageBoxRenderer::setPaddingBetweenButtons(float padding) {
        messageBoxRenderer_->setPaddingBetweenButtons(padding);
    }

    float MessageBoxRenderer::getPaddingBetweenButtons() const {
        return messageBoxRenderer_->getPaddingBetweenButtons();
    }

    void MessageBoxRenderer::setMinimumResizableBorderWidth(float minimumBorderWidth) {
        messageBoxRenderer_->setMinimumResizableBorderWidth(minimumBorderWidth);
    }

    float MessageBoxRenderer::getMinimumResizableBorderWidth() const {
        return messageBoxRenderer_->getMinimumResizableBorderWidth();
    }

    void MessageBoxRenderer::setShowTextOnTitleButtons(bool showText) {
        messageBoxRenderer_->setShowTextOnTitleButtons(showText);
    }

    bool MessageBoxRenderer::isTextShownOnTitleButtons() const {
        return messageBoxRenderer_->getShowTextOnTitleButtons();
    }

    void MessageBoxRenderer::setTextureTitleBar(const std::string &filename) {
        messageBoxRenderer_->setTextureTitleBar(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void MessageBoxRenderer::setTextureBackground(const std::string &filename) {
        messageBoxRenderer_->setTextureBackground(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void MessageBoxRenderer::setOpacity(float opacity) {
        messageBoxRenderer_->setOpacity(opacity);
    }

    float MessageBoxRenderer::getOpacity() const {
        return messageBoxRenderer_->getOpacity();
    }

    void MessageBoxRenderer::setOpacityDisabled(float opacity) {
        messageBoxRenderer_->setOpacityDisabled(opacity);
    }

    float MessageBoxRenderer::getOpacityDisabled() const {
        return messageBoxRenderer_->getOpacity();
    }

    void MessageBoxRenderer::setFont(const std::string &filename) {
        messageBoxRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void MessageBoxRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        messageBoxRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool MessageBoxRenderer::isTransparentTextureIgnored() const {
        return messageBoxRenderer_->getTransparentTexture();
    }

    IWidgetRenderer::Ptr MessageBoxRenderer::clone() const {
        return std::make_unique<MessageBoxRenderer>(*this);
    }

    void MessageBoxRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        messageBoxRenderer_ = dynamic_cast<tgui::MessageBoxRenderer*>(renderer);
    }

    tgui::WidgetRenderer *MessageBoxRenderer::getInternalPtr() {
        return messageBoxRenderer_;
    }

    MessageBoxRenderer::~MessageBoxRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        messageBoxRenderer_ = nullptr;
    }
}
