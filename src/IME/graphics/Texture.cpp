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

#include "IME/graphics/Texture.h"
#include "IME/core/resources/ResourceManager.h"

namespace ime {
    Texture::Texture(const std::string &filename, const UIntRect &area) :
        filename_{filename},
        image_{ResourceManager::getInstance()->getImage(filename)}
    {
        auto sfArea = sf::IntRect {
            static_cast<int>(area.left), static_cast<int>(area.top),
            static_cast<int>(area.width),static_cast<int>(area.height)
        };

        texture_.loadFromImage(image_, sfArea);
    }

    Vector2u Texture::getSize() const {
        return {texture_.getSize().x, texture_.getSize().y};
    }

    void Texture::setSmooth(bool smooth) {
        texture_.setSmooth(smooth);
    }

    bool Texture::isSmooth() const {
        return texture_.isSmooth();
    }

    void Texture::setRepeated(bool repeated) {
        texture_.setRepeated(repeated);
    }

    bool Texture::isRepeated() const {
        return texture_.isRepeated();
    }

    unsigned int Texture::getMaximumSize() {
        return sf::Texture::getMaximumSize();
    }

    const std::string &Texture::getFilename() const {
        return filename_;
    }

    const sf::Texture &Texture::getInternalTexture() const {
        return texture_;
    }
}
