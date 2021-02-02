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

#include "IME/utility/Helpers.h"
#include "IME/ui/renderers/PictureRenderer.h"
#include "IME/core/resources/ResourceManager.h"

namespace ime::ui {
    void PictureRenderer::setTexture(const std::string &filename) {
        pictureRenderer_->setTexture(ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
    }

    void PictureRenderer::setOpacity(float opacity) {
        pictureRenderer_->setOpacity(opacity);
    }

    float PictureRenderer::getOpacity() const {
        return pictureRenderer_->getOpacity();
    }

    void PictureRenderer::setOpacityDisabled(float opacity) {
        pictureRenderer_->setOpacityDisabled(opacity);
    }

    float PictureRenderer::getOpacityDisabled() const {
        return pictureRenderer_->getOpacityDisabled();
    }

    void PictureRenderer::setFont(const std::string &filename) {
        pictureRenderer_->setFont(utility::get_TGUI_Font(filename));
    }

    void PictureRenderer::ignoreTransparentTexture(bool ignoreTransparentParts) {
        pictureRenderer_->setTransparentTexture(ignoreTransparentParts);
    }

    bool PictureRenderer::isTransparentTextureIgnored() const {
        return pictureRenderer_->getTransparentTexture();
    }

    void PictureRenderer::setInternalPtr(tgui::WidgetRenderer *renderer) {
        pictureRenderer_ = dynamic_cast<tgui::PictureRenderer*>(renderer);
    }

    tgui::WidgetRenderer *PictureRenderer::getInternalPtr() {
        return pictureRenderer_;
    }

    PictureRenderer::~PictureRenderer() {
        // We don't delete the pointee because its lifetime is managed by the
        // third party library
        pictureRenderer_ = nullptr;
    }
}
