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

#include "IME/graphics/ui/renderers/RadioButtonRenderer.h"
#include "IME/core/managers/ResourceManager.h"
#include <IME/utility/Helpers.h>

namespace IME::UI {
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
        buttonRenderer_->setTextColor(Utility::convertToTGUIColour(textColour));
    }

    Colour RadioButtonRenderer::getTextColour() const {
        return Utility::convertFrom3rdPartyColour(buttonRenderer_->getTextColor());
    }

    void RadioButtonRenderer::setTextHoverColour(Colour colour) {
        buttonRenderer_->setTextColorHover(Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getTextHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorHover());
    }

    void RadioButtonRenderer::setDisabledTextColour(Colour textColour) {
        buttonRenderer_->setTextColorDisabled(
            Utility::convertToTGUIColour(textColour));
    }

    Colour RadioButtonRenderer::getDisabledTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorDisabled());
    }

    void RadioButtonRenderer::setCheckedTextColour(Colour colour) {
        buttonRenderer_->setTextColorChecked(Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getTextColourChecked() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorChecked());
    }

    void RadioButtonRenderer::setCheckedTextHoverColour(Colour colour) {
        buttonRenderer_->setTextColorCheckedHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedTextHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorCheckedHover());
    }

    void RadioButtonRenderer::setCheckedDisabledTextColour(Colour colour) {
        buttonRenderer_->setTextColorCheckedDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedDisabledTextColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getTextColorCheckedDisabled());
    }

    void RadioButtonRenderer::setBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColor(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColor());
    }

    void RadioButtonRenderer::setBackgroundHoverColour(Colour colour) {
        buttonRenderer_->setBackgroundColorHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getBackgroundHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorHover());
    }

    void RadioButtonRenderer::setDisabledBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getDisabledBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorDisabled());
    }

    void RadioButtonRenderer::setCheckedBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorChecked(Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(buttonRenderer_->getBackgroundColorChecked());
    }

    void RadioButtonRenderer::setCheckedHoverBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorCheckedHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedHoverBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorCheckedHover());
    }

    void RadioButtonRenderer::setCheckedDisabledBackgroundColour(Colour colour) {
        buttonRenderer_->setBackgroundColorCheckedDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedDisabledBackgroundColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBackgroundColorCheckedDisabled());
    }

    void RadioButtonRenderer::setBorderColour(Colour colour) {
        buttonRenderer_->setBorderColor(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColor());
    }

    void RadioButtonRenderer::setBorderHoverColour(Colour colour) {
        buttonRenderer_->setBorderColorHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getBorderHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorHover());
    }

    void RadioButtonRenderer::setDisabledBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getDisabledBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorDisabled());
    }

    void RadioButtonRenderer::setFocusedBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorFocused(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getFocusedBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorFocused());
    }

    void RadioButtonRenderer::setCheckedBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorChecked(
             Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorChecked());
    }

    void RadioButtonRenderer::setCheckedHoverBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorCheckedHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedHoverBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorCheckedHover());
    }

    void RadioButtonRenderer::setCheckedDisabledBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorCheckedDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedDisabledBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorCheckedDisabled());
    }

    void RadioButtonRenderer::setCheckedFocusedBorderColour(Colour colour) {
        buttonRenderer_->setBorderColorCheckedFocused(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckedFocusedBorderColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getBorderColorCheckedFocused());
    }

    void RadioButtonRenderer::setCheckColour(Colour colour) {
        buttonRenderer_->setCheckColor(Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getCheckColor());
    }

    void RadioButtonRenderer::setCheckHoverColour(Colour colour) {
        buttonRenderer_->setCheckColorHover(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getCheckHoverColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getCheckColorHover());
    }

    void RadioButtonRenderer::setDisabledCheckedColour(Colour colour) {
        buttonRenderer_->setCheckColorDisabled(
            Utility::convertToTGUIColour(colour));
    }

    Colour RadioButtonRenderer::getDisabledCheckColour() const {
        return Utility::convertFrom3rdPartyColour(
            buttonRenderer_->getCheckColorDisabled());
    }

    void RadioButtonRenderer::setUncheckedTexture(const std::string &filename) {
        buttonRenderer_->setTextureUnchecked(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void RadioButtonRenderer::setCheckedTexture(const std::string &filename) {
        buttonRenderer_->setTextureChecked(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void RadioButtonRenderer::setUncheckedHoverTexture(const std::string &filename) {
        buttonRenderer_->setTextureUncheckedHover(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void RadioButtonRenderer::setCheckedHoverTexture(const std::string &filename) {
        buttonRenderer_->setTextureCheckedHover(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void RadioButtonRenderer::setUncheckedDisabledTexture(const std::string &filename) {
        buttonRenderer_->setTextureUncheckedDisabled(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void RadioButtonRenderer::setCheckedDisabledTexture(const std::string &filename) {
        buttonRenderer_->setTextureCheckedDisabled(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void RadioButtonRenderer::setUncheckedFocusedTexture(const std::string &filename) {
        buttonRenderer_->setTextureUncheckedFocused(
            IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void RadioButtonRenderer::setCheckedFocusedTexture(const std::string &filename) {
        buttonRenderer_->setTextureCheckedFocused(
            IME::ResourceManager::getInstance()->getTexture(filename));
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
        buttonRenderer_->setFont(Utility::get_TGUI_Font(filename));
    }

    void RadioButtonRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        buttonRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool RadioButtonRenderer::isTransparentTextureIgnored() const {
        return buttonRenderer_->getTransparentTexture();
    }

    int RadioButtonRenderer::onPropertyChange(const std::string&,
        Callback<const std::string &>)
    {
        return 0;
    }

    void RadioButtonRenderer::unsubscribe(int) {

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