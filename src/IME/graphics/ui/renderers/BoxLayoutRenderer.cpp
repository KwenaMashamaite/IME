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

#include "IME/graphics/ui/renderers/BoxLayoutRenderer.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::UI {
    void BoxLayoutRenderer::setPadding(const Padding &padding) {
        boxLayoutRenderer_->setPadding({padding.left, padding.top, 
            padding.right, padding.bottom});
    }

    Padding BoxLayoutRenderer::getPadding() const {
        return {boxLayoutRenderer_->getPadding().getLeft(),
                boxLayoutRenderer_->getPadding().getTop(),
                boxLayoutRenderer_->getPadding().getRight(),
                boxLayoutRenderer_->getPadding().getBottom()};
    }

    void BoxLayoutRenderer::setSpaceBetweenWidgets(float distance) {
        boxLayoutRenderer_->setSpaceBetweenWidgets(distance);
    }

    float BoxLayoutRenderer::getSpaceBetweenWidgets() const {
        return boxLayoutRenderer_->getSpaceBetweenWidgets();
    }

    void BoxLayoutRenderer::setOpacity(float opacity) {
        boxLayoutRenderer_->setOpacity(opacity);
    }

    float BoxLayoutRenderer::getOpacity() const {
        return boxLayoutRenderer_->getOpacity();
    }

    void BoxLayoutRenderer::setOpacityDisabled(float opacity) {
        boxLayoutRenderer_->setOpacityDisabled(opacity);
    }

    float BoxLayoutRenderer::getOpacityDisabled() const {
        return boxLayoutRenderer_->getOpacity();
    }

    void BoxLayoutRenderer::setFont(const std::string &filename) {
        boxLayoutRenderer_->setFont(Utility::get_TGUI_Font(filename));
    }

    void BoxLayoutRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        boxLayoutRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool BoxLayoutRenderer::isTransparentTextureIgnored() const {
        return boxLayoutRenderer_->getTransparentTexture();
    }

    int BoxLayoutRenderer::onPropertyChange(const std::string &,
         Callback<const std::string &>)
    {
        return 0;
    }

    void BoxLayoutRenderer::unsubscribe(int) {

    }

    void BoxLayoutRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        boxLayoutRenderer_ = dynamic_cast<tgui::BoxLayoutRenderer*>(renderer);
    }

    tgui::WidgetRenderer *BoxLayoutRenderer::getInternalPtr() {
        return boxLayoutRenderer_;
    }

    BoxLayoutRenderer::~BoxLayoutRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        boxLayoutRenderer_ = nullptr;
    }
}
