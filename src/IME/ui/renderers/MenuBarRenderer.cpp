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

#include "IME/ui/renderers/MenuBarRenderer.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/Renderers/MenuBarRenderer.hpp>

namespace ime::ui {
    void MenuBarRenderer::setBackgroundColour(Colour colour) {
        menuBarRenderer_->setBackgroundColor(utility::convertToTGUIColour(colour));
    }

    Colour MenuBarRenderer::getBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(menuBarRenderer_->getBackgroundColor());
    }

    void MenuBarRenderer::setSelectedBackgroundColour(Colour backgroundColour) {
        menuBarRenderer_->setSelectedBackgroundColor(utility::convertToTGUIColour(backgroundColour));
    }

    Colour MenuBarRenderer::getSelectedBackgroundColour() const {
        return utility::convertFrom3rdPartyColour(menuBarRenderer_->getSelectedBackgroundColor());
    }

    void MenuBarRenderer::setTextColour(Colour textColour) {
        menuBarRenderer_->setTextColor(utility::convertToTGUIColour(textColour));
    }

    Colour MenuBarRenderer::getTextColour() const {
        return utility::convertFrom3rdPartyColour(menuBarRenderer_->getTextColor());
    }

    void MenuBarRenderer::setSelectedTextColour(Colour textColour) {
        menuBarRenderer_->setSelectedTextColor(utility::convertToTGUIColour(textColour));
    }

    Colour MenuBarRenderer::getSelectedTextColour() const {
        return utility::convertFrom3rdPartyColour(menuBarRenderer_->getSelectedTextColor());
    }

    void MenuBarRenderer::setDisabledTextColour(Colour textColour) {
        menuBarRenderer_->setTextColorDisabled(utility::convertToTGUIColour(textColour));
    }

    Colour MenuBarRenderer::getDisabledTextColour() const {
        return utility::convertFrom3rdPartyColour(menuBarRenderer_->getTextColorDisabled());
    }

    void MenuBarRenderer::setBackgroundTexture(const std::string &filename) {
        menuBarRenderer_->setTextureBackground(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void MenuBarRenderer::setItemBackgroundTexture(const std::string &filename) {
        menuBarRenderer_->setTextureItemBackground(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void MenuBarRenderer::setSelectedItemBackgroundTexture(const std::string &filename) {
        menuBarRenderer_->setTextureSelectedItemBackground(
            ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void MenuBarRenderer::setDistanceToSide(float distanceToSide) {
        menuBarRenderer_->setDistanceToSide(distanceToSide);
    }

    float MenuBarRenderer::getDistanceToSide() const {
        return menuBarRenderer_->getDistanceToSide();
    }

    void MenuBarRenderer::setOpacity(float opacity) {
        menuBarRenderer_->setOpacity(opacity);
    }

    float MenuBarRenderer::getOpacity() const {
        return menuBarRenderer_->getOpacity();
    }

    void MenuBarRenderer::setOpacityDisabled(float opacity) {
        menuBarRenderer_->setOpacityDisabled(opacity);
    }

    float MenuBarRenderer::getOpacityDisabled() const {
        return menuBarRenderer_->getOpacityDisabled();
    }

    void MenuBarRenderer::setFont(const std::string &filename) {
        menuBarRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void MenuBarRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        menuBarRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool MenuBarRenderer::isTransparentTextureIgnored() const {
        return menuBarRenderer_->getTransparentTexture();
    }

    IWidgetRenderer::Ptr MenuBarRenderer::clone() const {
        return std::make_unique<MenuBarRenderer>(*this);
    }

    void MenuBarRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        menuBarRenderer_ = dynamic_cast<tgui::MenuBarRenderer*>(renderer);
    }

    tgui::WidgetRenderer *MenuBarRenderer::getInternalPtr() {
        return menuBarRenderer_;
    }

    MenuBarRenderer::~MenuBarRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        menuBarRenderer_ = nullptr;
    }
}
