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

#include "IME/ui/renderers/CheckBoxRenderer.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/Renderers/CheckBoxRenderer.hpp>

namespace ime::ui {
    void CheckBoxRenderer::setBorders(const Borders &borders) {
        checkBoxRenderer_->setBorders({borders.left, borders.top, borders.right, borders.bottom});
    }

    Borders CheckBoxRenderer::getBorders() const {
        return {checkBoxRenderer_->getBorders().getLeft(),
                checkBoxRenderer_->getBorders().getTop(),
                checkBoxRenderer_->getBorders().getRight(),
                checkBoxRenderer_->getBorders().getBottom()};
    }

    void CheckBoxRenderer::setTextDistanceRatio(float ratio) {
        checkBoxRenderer_->setTextDistanceRatio(ratio);
    }

    float CheckBoxRenderer::getTextDistanceRatio() const {
        return checkBoxRenderer_->getTextDistanceRatio();
    }

    void CheckBoxRenderer::setTextColour(Colour textColour) {
        checkBoxRenderer_->setTextColor(utility::convertToTGUIColour(textColour));
    }

    Colour CheckBoxRenderer::getTextColour() const {
        return utility::convertFrom3rdPartyColour(checkBoxRenderer_->getTextColor());
    }

    void CheckBoxRenderer::setTextHoverColour(Colour colour) {
        checkBoxRenderer_->setTextColorHover(utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getTextHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorHover());
    }

    void CheckBoxRenderer::setDisabledTextColour(Colour textColour) {
        checkBoxRenderer_->setTextColorDisabled(
            utility::convertToTGUIColour(textColour));
    }

    Colour CheckBoxRenderer::getDisabledTextColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorDisabled());
    }

    void CheckBoxRenderer::setCheckedTextColour(Colour colour) {
        checkBoxRenderer_->setTextColorChecked(utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getTextColourChecked() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorChecked());
    }

    void CheckBoxRenderer::setCheckedTextHoverColour(Colour colour) {
        checkBoxRenderer_->setTextColorCheckedHover(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedTextHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorCheckedHover());
    }

    void CheckBoxRenderer::setCheckedDisabledTextColour(Colour colour) {
        checkBoxRenderer_->setTextColorCheckedDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedDisabledTextColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorCheckedDisabled());
    }

    void CheckBoxRenderer::setBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColor(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBackgroundColor());
    }

    void CheckBoxRenderer::setBackgroundHoverColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorHover(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getBackgroundHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorCheckedHover());
    }

    void CheckBoxRenderer::setDisabledBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getDisabledBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBackgroundColorDisabled());
    }

    void CheckBoxRenderer::setCheckedBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorChecked(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBackgroundColorChecked());
    }

    void CheckBoxRenderer::setCheckedHoverBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorCheckedHover(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedHoverBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getTextColorCheckedHover());
    }

    void CheckBoxRenderer::setCheckedDisabledBackgroundColour(Colour colour) {
        checkBoxRenderer_->setBackgroundColorCheckedDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedDisabledBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBackgroundColorCheckedDisabled());
    }

    void CheckBoxRenderer::setBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColor(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColor());
    }

    void CheckBoxRenderer::setBorderHoverColour(Colour colour) {
        checkBoxRenderer_->setBorderColorHover(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getBorderHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorHover());
    }

    void CheckBoxRenderer::setDisabledBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getDisabledBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorDisabled());
    }

    void CheckBoxRenderer::setFocusedBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorFocused(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getFocusedBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorFocused());
    }

    void CheckBoxRenderer::setCheckedBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorChecked(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorChecked());
    }

    void CheckBoxRenderer::setCheckedHoverBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorCheckedHover(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedHoverBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorCheckedHover());
    }

    void CheckBoxRenderer::setCheckedDisabledBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorCheckedDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedDisabledBorderColour() const {
        return utility::convertFrom3rdPartyColour(
                checkBoxRenderer_->getBorderColorCheckedDisabled());
    }

    void CheckBoxRenderer::setCheckedFocusedBorderColour(Colour colour) {
        checkBoxRenderer_->setBorderColorCheckedFocused(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckedFocusedBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getBorderColorCheckedFocused());
    }

    void CheckBoxRenderer::setCheckColour(Colour colour) {
        checkBoxRenderer_->setCheckColor(utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getCheckColor());
    }

    void CheckBoxRenderer::setCheckHoverColour(Colour colour) {
        checkBoxRenderer_->setCheckColorHover(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getCheckHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getCheckColorHover());
    }

    void CheckBoxRenderer::setDisabledCheckedColour(Colour colour) {
        checkBoxRenderer_->setCheckColorDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour CheckBoxRenderer::getDisabledCheckColour() const {
        return utility::convertFrom3rdPartyColour(
            checkBoxRenderer_->getCheckColorDisabled());
    }

    void CheckBoxRenderer::setUncheckedTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureUnchecked(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void CheckBoxRenderer::setCheckedTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureChecked(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void CheckBoxRenderer::setUncheckedHoverTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureUncheckedHover(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void CheckBoxRenderer::setCheckedHoverTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureCheckedHover(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void CheckBoxRenderer::setUncheckedDisabledTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureUncheckedDisabled(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void CheckBoxRenderer::setCheckedDisabledTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureCheckedDisabled(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void CheckBoxRenderer::setUncheckedFocusedTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureUncheckedFocused(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void CheckBoxRenderer::setCheckedFocusedTexture(const std::string &filename) {
        checkBoxRenderer_->setTextureCheckedFocused(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void CheckBoxRenderer::setTextStyle(TextStyle style) {
        checkBoxRenderer_->setTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle CheckBoxRenderer::getTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(checkBoxRenderer_->getTextStyle()));
    }

    void CheckBoxRenderer::setCheckedTextStyle(TextStyle style) {
        checkBoxRenderer_->setTextStyleChecked(static_cast<tgui::TextStyle>(style));
    }

    TextStyle CheckBoxRenderer::getCheckedTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(checkBoxRenderer_->getTextStyleChecked()));
    }

    void CheckBoxRenderer::setOpacity(float opacity) {
        checkBoxRenderer_->setOpacity(opacity);
    }

    float CheckBoxRenderer::getOpacity() const {
        return checkBoxRenderer_->getOpacity();
    }

    void CheckBoxRenderer::setOpacityDisabled(float opacity) {
        checkBoxRenderer_->setOpacityDisabled(opacity);
    }

    float CheckBoxRenderer::getOpacityDisabled() const {
        return checkBoxRenderer_->getOpacityDisabled();
    }

    void CheckBoxRenderer::setFont(const std::string &filename) {
        checkBoxRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void CheckBoxRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        checkBoxRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool CheckBoxRenderer::isTransparentTextureIgnored() const {
        return checkBoxRenderer_->getTransparentTexture();
    }

    IWidgetRenderer::Ptr CheckBoxRenderer::clone() const {
        return std::make_unique<CheckBoxRenderer>(*this);
    }

    void CheckBoxRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        checkBoxRenderer_ = dynamic_cast<tgui::CheckBoxRenderer*>(renderer);
    }

    tgui::WidgetRenderer *CheckBoxRenderer::getInternalPtr() {
        return checkBoxRenderer_;
    }

    CheckBoxRenderer::~CheckBoxRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        checkBoxRenderer_ = nullptr;
    }
}