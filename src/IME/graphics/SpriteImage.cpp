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

#include "IME/graphics/SpriteImage.h"
#include "IME/core/resources/ResourceManager.h"

namespace ime {
    SpriteImage::SpriteImage() = default;

    SpriteImage::SpriteImage(const std::string &sourceTexture, UIntRect area) {
        create(sourceTexture, area);
    }

    void SpriteImage::create(const std::string &sourceTexture, UIntRect area) {
        relativePos_ = {area.left, area.top};
        texture_ = std::make_shared<Texture>(sourceTexture, area);
    }

    Vector2u SpriteImage::getSize() const {
        return texture_->getSize();
    }

    unsigned int SpriteImage::getWidth() const {
        return texture_->getSize().x;
    }

    unsigned int SpriteImage::getHeight() const {
        return texture_->getSize().y;
    }

    std::string SpriteImage::getClassType() const {
        return "SpriteImage";
    }

    const Texture &SpriteImage::getTexture() const {
        return *texture_;
    }

    Vector2u SpriteImage::getRelativePosition() const {
        return relativePos_;
    }

    bool SpriteImage::contains(Vector2u point) const {
        return (point.x <= texture_->getSize().x && point.y <= texture_->getSize().y);
    }

    SpriteImage::~SpriteImage() = default;
}
