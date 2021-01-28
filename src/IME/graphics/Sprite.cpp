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

#include "IME/graphics/Sprite.h"
#include "IME/graphics/Window.h"
#include "IME/utility/Helpers.h"
#include "IME/core/managers/ResourceManager.h"

namespace ime {
    Sprite::Sprite() :
        isVisible_{true},
        animator_{*this}
    {}

    Sprite::Sprite(const Sprite & other) : animator_{*this} {
        sprite_ = other.sprite_;
        textureFileName_ = other.textureFileName_;
        isVisible_ = other.isVisible_;
        prevSpriteColour = other.prevSpriteColour;
    }

    Sprite &Sprite::operator=(const Sprite & other) {
        if (this != &other) {
            auto temp(other);
            std::swap(*this, temp);
        }

        return *this;
    }

    void Sprite::setPosition(float x, float y) {
        sprite_.setPosition(x, y);
    }

    void Sprite::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void Sprite::setRotation(float angle) {
        sprite_.setRotation(angle);
    }

    void Sprite::setScale(float factorX, float factorY) {
        sprite_.setScale(factorX, factorY);
    }

    void Sprite::setScale(Vector2f scale) {
        sprite_.setScale({scale.x, scale.y});
    }

    void Sprite::setOrigin(Vector2f origin) {
        sprite_.setOrigin({origin.x, origin.y});
    }

    float Sprite::getRotation() const {
        return sprite_.getRotation();
    }

    void Sprite::move(Vector2f offset) {
        sprite_.move({offset.x, offset.y});
    }

    void Sprite::scale(Vector2f offset) {
        sprite_.scale({offset.x, offset.y});
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

    FloatRect Sprite::getLocalBounds() const {
        return {sprite_.getLocalBounds().left, sprite_.getLocalBounds().top,
                sprite_.getLocalBounds().width, sprite_.getLocalBounds().height};
    }

    FloatRect Sprite::getGlobalBounds() const {
        return {sprite_.getGlobalBounds().left, sprite_.getGlobalBounds().top,
                sprite_.getGlobalBounds().width, sprite_.getGlobalBounds().height};
    }

    void Sprite::setTextureRect(int left, int top, int width, int height) {
        sprite_.setTextureRect({left, top, width, height});
    }

    void Sprite::setTextureRect(IntRect rect) {
        setTextureRect(rect.left, rect.top, rect.width, rect.height);
    }

    void Sprite::draw(Window &renderTarget) const {
        renderTarget.draw(sprite_);
    }

    void Sprite::rotate(float angle) {
        sprite_.rotate(angle);
    }

    void Sprite::setColour(Colour colour) {
        sprite_.setColor(utility::convertToSFMLColour(colour));
    }

    Colour Sprite::getColour() const {
        return utility::convertFrom3rdPartyColour(sprite_.getColor());
    }

    void Sprite::setVisible(bool visible) {
        if (isVisible_ == visible)
            return;

        if (visible) {
            isVisible_ = true;
            setColour(prevSpriteColour);
        } else {
            isVisible_ = false;
            prevSpriteColour = getColour();
            sprite_.setColor(sf::Color::Transparent);
        }
    }

    bool Sprite::isVisible() const {
        return isVisible_;
    }

    void Sprite::toggleVisibility() {
        setVisible(!isVisible());
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

    Vector2f Sprite::getScale() const {
        return {sprite_.getScale().x, sprite_.getScale().y};
    }

    IntRect Sprite::getTextureRect() const {
        return {sprite_.getTextureRect().left, sprite_.getTextureRect().top,
                sprite_.getTextureRect().width, sprite_.getTextureRect().height};
    }

    Animator &Sprite::getAnimator() {
        return animator_;
    }

    void Sprite::updateAnimation(Time deltaTime) {
        animator_.update(deltaTime);
    }
}
