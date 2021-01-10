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

#include "IME/ui/renderers/ButtonRenderer.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"

namespace ime::ui {
    void ButtonRenderer::setBorders(const Borders &borders) {
        buttonRenderer_->setBorders({borders.left, borders.top, borders.right, borders.bottom});
    }

    Borders ButtonRenderer::getBorders() const {
        return {buttonRenderer_->getBorders().getLeft(),
                buttonRenderer_->getBorders().getTop(),
                buttonRenderer_->getBorders().getRight(),
                buttonRenderer_->getBorders().getBottom()};
    }

    void ButtonRenderer::setTextColour(Colour colour) {
        buttonRenderer_->setTextColor(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getTextColour() const {
        return utility::convertFrom3rdPartyColour(buttonRenderer_->getTextColor());
    }

    void ButtonRenderer::setTextHoverColour(Colour colour) {
        buttonRenderer_->setTextColorHover(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getTextHoverColour() const {
        return utility::convertFrom3rdPartyColour(
                buttonRenderer_->getTextColorHover());
    }

    void ButtonRenderer::setTextColourOnMouseDown(Colour colour) {
        buttonRenderer_->setTextColorDown(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getTextColourOnMouseDown() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorDown());
    }

    void ButtonRenderer::setDisabledTextColour(Colour colour) {
        buttonRenderer_->setTextColorDisabled(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getDisabledTextColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorDisabled());
    }

    void ButtonRenderer::setFocusedTextColour(Colour colour) {
        buttonRenderer_->setTextColorFocused(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getTextColourFocused() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorFocused());
    }

    void ButtonRenderer::setBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColor(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(buttonRenderer_->getBackgroundColor());
    }

    void ButtonRenderer::setBackgroundHoverColour(Colour colour) {
        buttonRenderer_->setBackgroundColorHover(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getBackgroundColourHover() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorHover());
    }

    void ButtonRenderer::setBackgroundColourDown(Colour colour) {
        buttonRenderer_->setBackgroundColorDown(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getBackgroundColourDown() const {
        return utility::convertFrom3rdPartyColour(
                buttonRenderer_->getBackgroundColorDown());
    }

    void ButtonRenderer::setDisabledBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorDisabled(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getDisabledBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorDisabled());
    }

    void ButtonRenderer::setFocusedBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorFocused(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getFocusedBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorFocused());
    }

    void ButtonRenderer::setBorderColour(Colour colour) {
        buttonRenderer_->setBorderColor(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColor());
    }

    void ButtonRenderer::setBorderHoverColour(Colour colour) {
        buttonRenderer_->setBorderColorHover(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getBorderHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorHover());
    }

    void ButtonRenderer::setBorderColourOnMouseDown(Colour colour) {
        buttonRenderer_->setBorderColorDown(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getBorderColourOnMouseDown() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorDown());
    }

    void ButtonRenderer::setDisabledBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorDisabled(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getDisabledBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorDisabled());
    }

    void ButtonRenderer::setFocusedBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorFocused(utility::convertToTGUIColour(colour));
    }

    Colour ButtonRenderer::getBorderColourFocused() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorFocused());
    }

    void ButtonRenderer::setTexture(const std::string &texture) {
        buttonRenderer_->setTexture(
            ime::ResourceManager::getInstance()->getTexture(texture));
    }

    void ButtonRenderer::setTextureHover(const std::string &texture) {
        buttonRenderer_->setTextureHover(
            ime::ResourceManager::getInstance()->getTexture(texture));
    }

    void ButtonRenderer::setMouseDownTexture(const std::string &texture) {
        buttonRenderer_->setTextureDown(
            ime::ResourceManager::getInstance()->getTexture(texture));
    }

    void ButtonRenderer::setDisabledTexture(const std::string &texture) {
        buttonRenderer_->setTextureDisabled(
            ime::ResourceManager::getInstance()->getTexture(texture));
    }

    void ButtonRenderer::setFocusedTextureFocused(const std::string& texture) {
        buttonRenderer_->setTextureDisabled(
            ime::ResourceManager::getInstance()->getTexture(texture));
    }

    void ButtonRenderer::setTextStyle(TextStyle style) {
        buttonRenderer_->setTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle ButtonRenderer::getTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(buttonRenderer_->getTextStyle()));
    }

    void ButtonRenderer::setHoverTextStyle(TextStyle style) {
        buttonRenderer_->setTextStyleHover(static_cast<tgui::TextStyle>(style));
    }

    TextStyle ButtonRenderer::getHoverTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(buttonRenderer_->getTextStyleHover()));
    }

    void ButtonRenderer::setTextStyleOnMouseDown(TextStyle style) {
        buttonRenderer_->setTextStyleDown(static_cast<tgui::TextStyle>(style));
    }

    TextStyle ButtonRenderer::getTextStyleOnMouseDown() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(buttonRenderer_->getTextStyleDown()));
    }

    void ButtonRenderer::setTextStyleDisabled(TextStyle style) {
        buttonRenderer_->setTextStyleDisabled(static_cast<tgui::TextStyle>(style));
    }

    TextStyle ButtonRenderer::getTextStyleDisabled() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(buttonRenderer_->getTextStyleDisabled()));
    }

    void ButtonRenderer::setTextStyleFocused(TextStyle style) {
        buttonRenderer_->setTextStyleFocused(static_cast<tgui::TextStyle>(style));
    }

    TextStyle ButtonRenderer::getTextStyleFocused() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(buttonRenderer_->getTextStyleFocused()));
    }

    void ButtonRenderer::setTextOutlineColour(Colour outlineColour) {
        buttonRenderer_->setTextOutlineColor(utility::convertToTGUIColour(outlineColour));
    }

    Colour ButtonRenderer::getTextOutlineColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextOutlineColor());
    }

    void ButtonRenderer::setTextOutlineThickness(float outlineThickness) {
        buttonRenderer_->setTextOutlineThickness(outlineThickness);
    }

    float ButtonRenderer::getTextOutlineThickness() const {
        return 0;
    }

    void ButtonRenderer::setOpacity(float opacity) {
        buttonRenderer_->setOpacity(opacity);
    }

    float ButtonRenderer::getOpacity() const {
        return buttonRenderer_->getOpacity();
    }

    void ButtonRenderer::setOpacityDisabled(float opacity) {
        buttonRenderer_->setOpacityDisabled(opacity);
    }

    float ButtonRenderer::getOpacityDisabled() const {
        return buttonRenderer_->getOpacity();
    }

    void ButtonRenderer::setFont(const std::string &filename) {
        buttonRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void ButtonRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        buttonRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool ButtonRenderer::isTransparentTextureIgnored() const {
        return buttonRenderer_->getTransparentTexture();
    }

    void ButtonRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        buttonRenderer_ = dynamic_cast<tgui::ButtonRenderer*>(renderer);
    }

    tgui::WidgetRenderer *ButtonRenderer::getInternalPtr() {
        return buttonRenderer_;
    }

    ButtonRenderer::~ButtonRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        buttonRenderer_ = nullptr;
    }
}