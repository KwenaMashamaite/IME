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

#include "IME/ui/renderers/SeparatorRenderer.h"
#include "IME/utility/Helpers.h"

namespace ime::ui {
    void SeparatorRenderer::setColour(Colour colour) {
        separatorRenderer_->setColor(utility::convertToTGUIColour(colour));
    }

    Colour SeparatorRenderer::getColour() const {
        return utility::convertFrom3rdPartyColour(separatorRenderer_->getColor());
    }

    void SeparatorRenderer::setOpacity(float opacity) {
        separatorRenderer_->setOpacity(opacity);
    }

    float SeparatorRenderer::getOpacity() const {
        return separatorRenderer_->getOpacity();
    }

    void SeparatorRenderer::setOpacityDisabled(float opacity) {
        separatorRenderer_->setOpacityDisabled(opacity);
    }

    float SeparatorRenderer::getOpacityDisabled() const {
        return separatorRenderer_->getOpacityDisabled();
    }

    void SeparatorRenderer::setFont(const std::string &filename) {
        separatorRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void SeparatorRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        separatorRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool SeparatorRenderer::isTransparentTextureIgnored() const {
        return separatorRenderer_->getTransparentTexture();
    }

    void SeparatorRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        separatorRenderer_ = dynamic_cast<tgui::SeparatorLineRenderer*>(renderer);
    }

    tgui::WidgetRenderer *SeparatorRenderer::getInternalPtr() {
        return separatorRenderer_;
    }

    SeparatorRenderer::~SeparatorRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        separatorRenderer_ = nullptr;
    }
}