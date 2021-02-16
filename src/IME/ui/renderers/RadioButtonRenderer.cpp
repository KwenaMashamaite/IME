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

#include "IME/ui/renderers/RadioButtonRenderer.h"
#include "IME/core/resources/ResourceManager.h"
#include "../../utility/Helpers.h"
#include <TGUI/Renderers/RadioButtonRenderer.hpp>

namespace ime::ui {
    void RadioButtonRenderer::setBorders(const Borders &borders) {
        buttonRenderer_->setBorders({borders.left, borders.top,
            borders.right, borders.bottom});
    }

    Borders RadioButtonRenderer::getBorders() const {
        return {buttonRenderer_->getBorders().getLeft(),
                buttonRenderer_->getBorders().getTop(),
                buttonRenderer_->getBorders().getRight(),
                buttonRenderer_->getBorders().getBottom()};
    }

    void RadioButtonRenderer::setTextDistanceRatio(float ratio) {
        buttonRenderer_->setTextDistanceRatio(ratio);
    }

    float RadioButtonRenderer::getTextDistanceRatio() const {
        return buttonRenderer_->getTextDistanceRatio();
    }

    void RadioButtonRenderer::setTextColour(Colour textColour) {
        buttonRenderer_->setTextColor(utility::convertToTGUIColour(textColour));
    }

    Colour RadioButtonRenderer::getTextColour() const {
        return utility::convertFrom3rdPartyColour(buttonRenderer_->getTextColor());
    }

    void RadioButtonRenderer::setTextHoverColour(Colour colour) {
        buttonRenderer_->setTextColorHover(utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getTextHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorHover());
    }

    void RadioButtonRenderer::setDisabledTextColour(Colour textColour) {
        buttonRenderer_->setTextColorDisabled(
            utility::convertToTGUIColour(textColour));
    }

    Colour RadioButtonRenderer::getDisabledTextColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorDisabled());
    }

    void RadioButtonRenderer::setCheckedTextColour(Colour colour) {
        buttonRenderer_->setTextColorChecked(utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getTextColourChecked() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorChecked());
    }

    void RadioButtonRenderer::setCheckedTextHoverColour(Colour colour) {
        buttonRenderer_->setTextColorCheckedHover(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedTextHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorCheckedHover());
    }

    void RadioButtonRenderer::setCheckedDisabledTextColour(Colour colour) {
        buttonRenderer_->setTextColorCheckedDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedDisabledTextColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorCheckedDisabled());
    }

    void RadioButtonRenderer::setBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColor(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColor());
    }

    void RadioButtonRenderer::setBackgroundHoverColour(Colour colour) {
        buttonRenderer_->setBackgroundColorHover(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getBackgroundHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorHover());
    }

    void RadioButtonRenderer::setDisabledBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getDisabledBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorDisabled());
    }

    void RadioButtonRenderer::setCheckedBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorChecked(utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(buttonRenderer_->getBackgroundColorChecked());
    }

    void RadioButtonRenderer::setCheckedHoverBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorCheckedHover(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedHoverBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorCheckedHover());
    }

    void RadioButtonRenderer::setCheckedDisabledBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorCheckedDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedDisabledBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorCheckedDisabled());
    }

    void RadioButtonRenderer::setBorderColour(Colour colour) {
        buttonRenderer_->setBorderColor(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColor());
    }

    void RadioButtonRenderer::setBorderHoverColour(Colour colour) {
        buttonRenderer_->setBorderColorHover(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getBorderHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorHover());
    }

    void RadioButtonRenderer::setDisabledBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getDisabledBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorDisabled());
    }

    void RadioButtonRenderer::setFocusedBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorFocused(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getFocusedBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorFocused());
    }

    void RadioButtonRenderer::setCheckedBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorChecked(
             utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorChecked());
    }

    void RadioButtonRenderer::setCheckedHoverBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorCheckedHover(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedHoverBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorCheckedHover());
    }

    void RadioButtonRenderer::setCheckedDisabledBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorCheckedDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedDisabledBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorCheckedDisabled());
    }

    void RadioButtonRenderer::setCheckedFocusedBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorCheckedFocused(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedFocusedBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorCheckedFocused());
    }

    void RadioButtonRenderer::setCheckColour(Colour colour) {
        buttonRenderer_->setCheckColor(utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getCheckColor());
    }

    void RadioButtonRenderer::setCheckHoverColour(Colour colour) {
        buttonRenderer_->setCheckColorHover(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getCheckColorHover());
    }

    void RadioButtonRenderer::setDisabledCheckedColour(Colour colour) {
        buttonRenderer_->setCheckColorDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getDisabledCheckColour() const {
        return utility::convertFrom3rdPartyColour(
            buttonRenderer_->getCheckColorDisabled());
    }

    void RadioButtonRenderer::setUncheckedTexture(const std::string &filename) {
        buttonRenderer_->setTextureUnchecked(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void RadioButtonRenderer::setCheckedTexture(const std::string &filename) {
        buttonRenderer_->setTextureChecked(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void RadioButtonRenderer::setUncheckedHoverTexture(const std::string &filename) {
        buttonRenderer_->setTextureUncheckedHover(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void RadioButtonRenderer::setCheckedHoverTexture(const std::string &filename) {
        buttonRenderer_->setTextureCheckedHover(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void RadioButtonRenderer::setUncheckedDisabledTexture(const std::string &filename) {
        buttonRenderer_->setTextureUncheckedDisabled(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void RadioButtonRenderer::setCheckedDisabledTexture(const std::string &filename) {
        buttonRenderer_->setTextureCheckedDisabled(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void RadioButtonRenderer::setUncheckedFocusedTexture(const std::string &filename) {
        buttonRenderer_->setTextureUncheckedFocused(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void RadioButtonRenderer::setCheckedFocusedTexture(const std::string &filename) {
        buttonRenderer_->setTextureCheckedFocused(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void RadioButtonRenderer::setTextStyle(TextStyle style) {
        buttonRenderer_->setTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle RadioButtonRenderer::getTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(buttonRenderer_->getTextStyle()));
    }

    void RadioButtonRenderer::setCheckedTextStyle(TextStyle style) {
        buttonRenderer_->setTextStyleChecked(static_cast<tgui::TextStyle>(style));
    }

    TextStyle RadioButtonRenderer::getCheckedTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(buttonRenderer_->getTextStyleChecked()));
    }

    void RadioButtonRenderer::setOpacity(float opacity) {
        buttonRenderer_->setOpacity(opacity);
    }

    float RadioButtonRenderer::getOpacity() const {
        return buttonRenderer_->getOpacity();
    }

    void RadioButtonRenderer::setOpacityDisabled(float opacity) {
        buttonRenderer_->setOpacityDisabled(opacity);
    }

    float RadioButtonRenderer::getOpacityDisabled() const {
        return buttonRenderer_->getOpacityDisabled();
    }

    void RadioButtonRenderer::setFont(const std::string &filename) {
        buttonRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void RadioButtonRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        buttonRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool RadioButtonRenderer::isTransparentTextureIgnored() const {
        return buttonRenderer_->getTransparentTexture();
    }

    void RadioButtonRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        buttonRenderer_ = dynamic_cast<tgui::RadioButtonRenderer*>(renderer);
    }

    tgui::WidgetRenderer *RadioButtonRenderer::getInternalPtr() {
        return buttonRenderer_;
    }

    RadioButtonRenderer::~RadioButtonRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        buttonRenderer_ = nullptr;
    }
}