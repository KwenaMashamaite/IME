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

#include "IME/ui/renderers/EditBoxRenderer.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/Renderers/EditBoxRenderer.hpp>

namespace ime::ui {
    void EditBoxRenderer::setTextStyle(TextStyle style) {
        editBoxRenderer_->setTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle EditBoxRenderer::getTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(editBoxRenderer_->getTextStyle()));
    }

    void EditBoxRenderer::setDefaultTextStyle(TextStyle style) {
        editBoxRenderer_->setDefaultTextStyle(static_cast<tgui::TextStyle>(style));
    }

    TextStyle EditBoxRenderer::getDefaultTextStyle() const {
        return static_cast<TextStyle>(
            static_cast<unsigned int>(editBoxRenderer_->getDefaultTextStyle()));
    }

    void EditBoxRenderer::setBorders(const Borders &borders) {
        editBoxRenderer_->setBorders({borders.left, borders.top, borders.right, borders.bottom});
    }

    Borders EditBoxRenderer::getBorders() const {
        return {editBoxRenderer_->getBorders().getLeft(),
                editBoxRenderer_->getBorders().getTop(),
                editBoxRenderer_->getBorders().getRight(),
                editBoxRenderer_->getBorders().getBottom()};
    }

    void EditBoxRenderer::setPadding(const Padding &padding) {
        editBoxRenderer_->setPadding({padding.left, padding.top, padding.right,
            padding.bottom});
    }

    Padding EditBoxRenderer::getPadding() const {
        return {editBoxRenderer_->getPadding().getLeft(),
                editBoxRenderer_->getPadding().getTop(),
                editBoxRenderer_->getPadding().getRight(),
                editBoxRenderer_->getPadding().getBottom()};
    }

    void EditBoxRenderer::setCaretWidth(float width) {
        editBoxRenderer_->setCaretWidth(width);
    }

    float EditBoxRenderer::getCaretWidth() const {
        return editBoxRenderer_->getCaretWidth();
    }

    void EditBoxRenderer::setTextColour(Colour textColour) {
        editBoxRenderer_->setTextColor(utility::convertToTGUIColour(textColour));
    }

    Colour EditBoxRenderer::getTextColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getTextColor());
    }

    void EditBoxRenderer::setDisabledTextColour(Colour textColour) {
        editBoxRenderer_->setTextColorDisabled(utility::convertToTGUIColour(textColour));
    }

    Colour EditBoxRenderer::getDisabledTextColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getTextColorDisabled());
    }

    void EditBoxRenderer::setFocusedTextColour(Colour textColour) {
        editBoxRenderer_->setTextColorFocused(
            utility::convertToTGUIColour(textColour));
    }

    Colour EditBoxRenderer::getFocusedTextColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getTextColorFocused());
    }

    void EditBoxRenderer::setSelectedTextColour(Colour colour) {
        editBoxRenderer_->setSelectedTextColor(
            utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getSelectedTextColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getSelectedTextColor());
    }

    void
    EditBoxRenderer::setSelectedTextBackgroundColour(Colour backgroundColour) {
        editBoxRenderer_->setSelectedTextBackgroundColor(
            utility::convertToTGUIColour(backgroundColour));
    }

    Colour EditBoxRenderer::getSelectedTextBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getSelectedTextBackgroundColor());
    }

    void EditBoxRenderer::setDefaultTextColour(Colour defaultTextColour) {
        editBoxRenderer_->setDefaultTextColor(
            utility::convertToTGUIColour(defaultTextColour));
    }

    Colour EditBoxRenderer::getDefaultTextColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getDefaultTextColor());
    }

    void EditBoxRenderer::setBackgroundColour(Colour colour) {
        editBoxRenderer_->setBackgroundColor(
            utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBackgroundColor());
    }

    void EditBoxRenderer::setBackgroundHoverColour(Colour colour) {
        editBoxRenderer_->setBackgroundColor(
            utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getBackgroundColourHover() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBackgroundColorHover());
    }

    void EditBoxRenderer::setDisabledBackgroundColour(Colour colour) {
        editBoxRenderer_->setBorderColorDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getDisabledBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBackgroundColorDisabled());
    }

    void EditBoxRenderer::setFocusedBackgroundColour(Colour colour) {
        editBoxRenderer_->setBackgroundColorFocused(
            utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getFocusedBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBackgroundColorFocused());
    }

    void EditBoxRenderer::setCaretColour(Colour caretColour) {
        editBoxRenderer_->setCaretColor(
            utility::convertToTGUIColour(caretColour));
    }

    Colour EditBoxRenderer::getCaretColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getCaretColor());
    }

    void EditBoxRenderer::setCaretHoverColour(Colour caretColour) {
        editBoxRenderer_->setCaretColorHover(
            utility::convertToTGUIColour(caretColour));
    }

    Colour EditBoxRenderer::getCaretHoverColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getCaretColorHover());
    }

    void EditBoxRenderer::setCaretColourFocused(Colour caretColour) {
        editBoxRenderer_->setCaretColorFocused(
            utility::convertToTGUIColour(caretColour));
    }

    Colour EditBoxRenderer::getFocusedCaretColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getCaretColorFocused());
    }

    void EditBoxRenderer::setBorderColour(Colour colour) {
        editBoxRenderer_->setBorderColor(
            utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getBorderColour() const {
        return utility::convertFrom3rdPartyColour(
                editBoxRenderer_->getBorderColor());
    }

    void EditBoxRenderer::setBorderHoverColour(Colour colour) {
        editBoxRenderer_->setBorderColorHover(
            utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getBorderHoverColour() const {
        return utility::convertFrom3rdPartyColour(
                editBoxRenderer_->getBorderColorHover());
    }

    void EditBoxRenderer::setDisabledBorderColour(Colour colour) {
        editBoxRenderer_->setBorderColorDisabled(
            utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getDisabledBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBorderColorDisabled());
    }

    void EditBoxRenderer::setFocusedBorderColour(Colour colour) {
        editBoxRenderer_->setBorderColorFocused(
            utility::convertToTGUIColour(colour));
    }

    Colour EditBoxRenderer::getFocusedBorderColour() const {
        return utility::convertFrom3rdPartyColour(
            editBoxRenderer_->getBorderColorFocused());
    }

    void EditBoxRenderer::setTexture(const std::string &filename) {
        editBoxRenderer_->setTexture(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void EditBoxRenderer::setHoverTexture(const std::string &filename) {
        editBoxRenderer_->setTextureHover(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void EditBoxRenderer::setDisabledTexture(const std::string &filename) {
        editBoxRenderer_->setTextureDisabled(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void EditBoxRenderer::setFocusedTexture(const std::string &filename) {
        editBoxRenderer_->setTextureFocused(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void EditBoxRenderer::setOpacity(float opacity) {
        editBoxRenderer_->setOpacity(opacity);
    }

    float EditBoxRenderer::getOpacity() const {
        return editBoxRenderer_->getOpacity();
    }

    void EditBoxRenderer::setOpacityDisabled(float opacity) {
        editBoxRenderer_->setOpacityDisabled(opacity);
    }

    float EditBoxRenderer::getOpacityDisabled() const {
        return editBoxRenderer_->getOpacity();
    }

    void EditBoxRenderer::setFont(const std::string &filename) {
        editBoxRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void EditBoxRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        editBoxRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool EditBoxRenderer::isTransparentTextureIgnored() const {
        return editBoxRenderer_->getTransparentTexture();
    }

    IWidgetRenderer::Ptr EditBoxRenderer::clone() const {
        return std::make_unique<EditBoxRenderer>(*this);
    }

    void EditBoxRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        editBoxRenderer_ = dynamic_cast<tgui::EditBoxRenderer*>(renderer);
    }

    tgui::WidgetRenderer *EditBoxRenderer::getInternalPtr() {
        return editBoxRenderer_;
    }

    EditBoxRenderer::~EditBoxRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        editBoxRenderer_ = nullptr;
    }
}