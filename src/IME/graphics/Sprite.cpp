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
#include "../utility/Helpers.h"
#include "WindowImpl.h"
#include "IME/core/resources/ResourceManager.h"
#include <SFML/Graphics/Sprite.hpp>

namespace ime {
    //////////////////////////////////////////////////////////////////////////
    // Sprite class implementation
    //////////////////////////////////////////////////////////////////////////
    struct Sprite::SpriteImpl {
        SpriteImpl(Sprite& sprite) :
            isVisible_{true},
            animator_{sprite},
            texture_{nullptr}
        {}

        void swap(SpriteImpl &other) {
            std::swap(sprite_, other.sprite_);
            std::swap(isVisible_, other.isVisible_);
            std::swap(prevSpriteColour_, other.prevSpriteColour_);
            std::swap(animator_, other.animator_);
            std::swap(texture_, other.texture_);
        }

        void setTexture(const Texture &texture) {
            texture_ = &texture;
            sprite_.setTexture(texture_->getInternalTexture(), true);
        }

        void setTexture(const std::string &filename) {
            texture_ = &ResourceManager::getInstance()->getTexture(filename);
            sprite_.setTexture(texture_->getInternalTexture(), true);
        }

        void setTextureRect(const UIntRect& rect) {
            setTextureRect(rect.left, rect.top, rect.width, rect.height);
        }

        void setTextureRect(unsigned int left, unsigned int top,
            unsigned int width,unsigned int height)
        {
            sprite_.setTextureRect({static_cast<int>(left),
                static_cast<int>(top), static_cast<int>(width), static_cast<int>(height)});
        }

        UIntRect getTextureRect() const {
            return {static_cast<unsigned int>(sprite_.getTextureRect().left),
                    static_cast<unsigned int>(sprite_.getTextureRect().top),
                    static_cast<unsigned int>(sprite_.getTextureRect().width),
                    static_cast<unsigned int>(sprite_.getTextureRect().height)};
        }

        void setPosition(float x, float y) {
            sprite_.setPosition(x, y);
        }

        void setPosition(Vector2f position) {
            setPosition(position.x, position.y);
        }

        void setRotation(float angle) {
            sprite_.setRotation(angle);
        }

        void setScale(float factorX, float factorY) {
            sprite_.setScale(factorX, factorY);
        }

        void setScale(Vector2f scale) {
            sprite_.setScale({scale.x, scale.y});
        }

        void setOrigin(Vector2f origin) {
            sprite_.setOrigin({origin.x, origin.y});
        }

        float getRotation() const {
            return sprite_.getRotation();
        }

        void move(Vector2f offset) {
            sprite_.move({offset.x, offset.y});
        }

        void scale(Vector2f offset) {
            sprite_.scale({offset.x, offset.y});
        }

        Vector2f getPosition() const {
            return {sprite_.getPosition().x, sprite_.getPosition().y};
        }

        const Texture &getTexture() const {
            return *texture_;
        }

        FloatRect getLocalBounds() const {
            return {sprite_.getLocalBounds().left, sprite_.getLocalBounds().top,
                    sprite_.getLocalBounds().width, sprite_.getLocalBounds().height};
        }

        FloatRect getGlobalBounds() const {
            return {sprite_.getGlobalBounds().left, sprite_.getGlobalBounds().top,
                    sprite_.getGlobalBounds().width, sprite_.getGlobalBounds().height};
        }

        void draw(Window &renderTarget) const {
            renderTarget.getImpl()->getSFMLWindow().draw(sprite_);
        }

        void rotate(float angle) {
            sprite_.rotate(angle);
        }

        void setColour(Colour colour) {
            sprite_.setColor(utility::convertToSFMLColour(colour));
        }

        Colour getColour() const {
            return utility::convertFrom3rdPartyColour(sprite_.getColor());
        }

        void setVisible(bool visible) {
            if (isVisible_ == visible)
                return;

            if (visible) {
                isVisible_ = true;
                setColour(prevSpriteColour_);
            } else {
                isVisible_ = false;
                prevSpriteColour_ = getColour();
                sprite_.setColor(sf::Color::Transparent);
            }
        }

        bool isVisible() const {
            return isVisible_;
        }

        void toggleVisibility() {
            setVisible(!isVisible());
        }

        void setOrigin(float x, float y) {
            sprite_.setOrigin(x, y);
        }

        Vector2f getOrigin() const {
            return {sprite_.getOrigin().x, sprite_.getOrigin().y};
        }

        void scale(float xFactor, float yFactor) {
            sprite_.scale(xFactor, yFactor);
        }

        void move(float xOffset, float yOffset) {
            sprite_.move(xOffset, yOffset);
        }

        Vector2f getScale() const {
            return {sprite_.getScale().x, sprite_.getScale().y};
        }

        Animator &getAnimator() {
            return animator_;
        }

        void updateAnimation(Time deltaTime) {
            animator_.update(deltaTime);
        }

        void setAnimationTarget(Sprite& target) {
            animator_.setTarget(target);
        }

        ~SpriteImpl() {
            // We don't call delete because the memory will be deallocated by
            // the resource manager
            texture_ = nullptr;
        }

    private:
        sf::Sprite sprite_;           //!< Third party sprite
        bool isVisible_;              //!< Flags whether or not the sprite is visible
        Colour prevSpriteColour_;     //!< Sprite colour before it was hidden
        Animator animator_;           //!< Sprite animator
        const Texture* texture_;      //!< Sprite texture
    }; // class Impl

    //////////////////////////////////////////////////////////////////////////
    // Sprite class delegation
    //////////////////////////////////////////////////////////////////////////
    Sprite::Sprite() :
        pImpl_{std::make_unique<SpriteImpl>(*this)}
    {}

    Sprite::Sprite(const std::string &texture) : Sprite() {
        pImpl_->setTexture(texture);
    }

    Sprite::Sprite(const Texture &texture) : Sprite() {
        pImpl_->setTexture(texture);
    }

    Sprite::Sprite(const Texture &texture, const UIntRect &rectangle) : Sprite() {
        pImpl_->setTexture(texture);
        pImpl_->setTextureRect(rectangle);
    }

    Sprite::Sprite(const Sprite& other) :
        pImpl_{std::make_unique<SpriteImpl>(*other.pImpl_)}
    {
        pImpl_->setAnimationTarget(*this);
    }

    Sprite &Sprite::operator=(const Sprite& other) {
        if (this != &other) {
            pImpl_.reset(new SpriteImpl(*other.pImpl_));
            pImpl_->setAnimationTarget(*this);
        }
        return *this;
    }

    Sprite::Sprite(Sprite &&) noexcept = default;

    Sprite &Sprite::operator=(Sprite &&) noexcept = default;

    void Sprite::swap(Sprite &other) {
        pImpl_->swap(*other.pImpl_);
    }

    void Sprite::setTexture(const Texture &texture) {
        pImpl_->setTexture(texture);
    }

    void Sprite::setTexture(const std::string &filename) {
        pImpl_->setTexture(filename);
    }

    void Sprite::setTextureRect(const UIntRect& rect) {
        pImpl_->setTextureRect(rect.left, rect.top, rect.width, rect.height);
    }

    void Sprite::setTextureRect(unsigned int left, unsigned int top, unsigned int width,
        unsigned int height)
    {
        pImpl_->setTextureRect(left, top, width, height);
    }

    UIntRect Sprite::getTextureRect() const {
        return pImpl_->getTextureRect();
    }

    void Sprite::setPosition(float x, float y) {
        pImpl_->setPosition(x, y);
    }

    void Sprite::setPosition(Vector2f position) {
        pImpl_->setPosition(position);
    }

    void Sprite::setRotation(float angle) {
        pImpl_->setRotation(angle);
    }

    void Sprite::setScale(float factorX, float factorY) {
        pImpl_->setScale(factorX, factorY);
    }

    void Sprite::setScale(Vector2f scale) {
        pImpl_->setScale({scale.x, scale.y});
    }

    void Sprite::setOrigin(Vector2f origin) {
        pImpl_->setOrigin({origin.x, origin.y});
    }

    float Sprite::getRotation() const {
        return pImpl_->getRotation();
    }

    void Sprite::move(Vector2f offset) {
        pImpl_->move({offset.x, offset.y});
    }

    void Sprite::scale(Vector2f offset) {
        pImpl_->scale({offset.x, offset.y});
    }

    Vector2f Sprite::getPosition() const {
        return pImpl_->getPosition();
    }

    const Texture &Sprite::getTexture() const {
        return pImpl_->getTexture();
    }

    FloatRect Sprite::getLocalBounds() const {
        return pImpl_->getLocalBounds();
    }

    FloatRect Sprite::getGlobalBounds() const {
        return pImpl_->getGlobalBounds();
    }

    void Sprite::draw(Window &renderTarget) const {
        pImpl_->draw(renderTarget);
    }

    void Sprite::rotate(float angle) {
        pImpl_->rotate(angle);
    }

    void Sprite::setColour(Colour colour) {
        pImpl_->setColour(colour);
    }

    Colour Sprite::getColour() const {
        return pImpl_->getColour();
    }

    void Sprite::setVisible(bool visible) {
        pImpl_->setVisible(visible);
    }

    bool Sprite::isVisible() const {
        return pImpl_->isVisible();
    }

    void Sprite::toggleVisibility() {
        pImpl_->toggleVisibility();
    }

    void Sprite::setOrigin(float x, float y) {
        pImpl_->setOrigin(x, y);
    }

    Vector2f Sprite::getOrigin() const {
        return pImpl_->getOrigin();
    }

    void Sprite::scale(float xFactor, float yFactor) {
        pImpl_->scale(xFactor, yFactor);
    }

    void Sprite::move(float xOffset, float yOffset) {
        pImpl_->move(xOffset, yOffset);
    }

    Vector2f Sprite::getScale() const {
        return pImpl_->getScale();
    }

    Animator &Sprite::getAnimator() {
        return pImpl_->getAnimator();
    }

    void Sprite::updateAnimation(Time deltaTime) {
        pImpl_->updateAnimation(deltaTime);
    }

    Sprite::~Sprite() = default;
}
