////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

#include "IME/graphics/Sprite.h"
#include "IME/graphics/Window.h"
#include "IME/utility/Helpers.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::Graphics {
    Sprite::Sprite() : isHidden_(false), textureFileName_("")
    {}

    void Sprite::setPosition(float x, float y) {
        sprite_.setPosition(x, y);
    }

    void Sprite::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void Sprite::setTexture(const std::string &filename) {
        sprite_.setTexture(ResourceManager::getInstance()->getTexture(filename));
        textureFileName_ = filename;
    }

    Vector2f Sprite::getPosition() const {
        return {sprite_.getPosition().x, sprite_.getPosition().y};
    }

    const std::string &Sprite::getTexture() const {
        return textureFileName_;
    }

    Vector2f Sprite::getSize() const {
        return {static_cast<float>(sprite_.getTextureRect().width),
                static_cast<float>(sprite_.getTextureRect().height)};
    }

    void Sprite::setTextureRect(int left, int top, int width, int height) {
        sprite_.setTextureRect({left, top, width, height});
    }

    void Sprite::draw(Window &renderTarget) {
        renderTarget.draw(sprite_);
    }

    void Sprite::hide() {
        if (!isHidden_) {
            isHidden_ = true;
            prevSpriteColour = getColour();
            sprite_.setColor(sf::Color::Transparent);
        }
    }

    void Sprite::show() {
        if (isHidden_) {
            isHidden_ = false;
            setColour(prevSpriteColour);
        }
    }

    bool Sprite::isHidden() const {
        return isHidden_;
    }

    void Sprite::rotate(float angle) {
        sprite_.rotate(angle);
    }

    void Sprite::setColour(Colour colour) {
        sprite_.setColor(Utility::convertToSFMLColour(colour));
    }

    Colour Sprite::getColour() const {
        return Utility::convertFrom3rdPartyColour(sprite_.getColor());
    }

    void Sprite::setOrigin(float x, float y) {
        sprite_.setOrigin(x, y);
    }

    Vector2f Sprite::getOrigin() const {
        return {sprite_.getOrigin().x, sprite_.getOrigin().y};
    }

    void Sprite::scale(float xFactor, float yFactor) {
        sprite_.scale(xFactor, yFactor);
    }

    void Sprite::move(float xOffset, float yOffset) {
        sprite_.move(xOffset, yOffset);
    }
}
