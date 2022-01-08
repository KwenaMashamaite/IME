////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
#include "IME/graphics/RenderTarget.h"
#include "IME/utility/Helpers.h"
#include "IME/graphics/RenderTargetImpl.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

namespace ime {
    //////////////////////////////////////////////////////////////////////////
    // Sprite class implementation
    //////////////////////////////////////////////////////////////////////////
    struct Sprite::SpriteImpl {
        explicit SpriteImpl(Sprite& sprite) :
            isVisible_{true},
            prevSpriteColour_{Colour::Transparent},
            animator_{sprite},
            texture_{std::make_shared<Texture>()}
        {}

        SpriteImpl(const SpriteImpl& other) :
            sprite_{other.sprite_},
            isVisible_{other.isVisible_},
            prevSpriteColour_{other.prevSpriteColour_},
            animator_{other.animator_},
            texture_{std::make_shared<Texture>(*other.texture_)}
        {}

        SpriteImpl& operator=(const SpriteImpl& rhs) {
            if (this != &rhs) {
                auto temp{rhs};
                swap(temp);
            }

            return *this;
        }

        SpriteImpl(SpriteImpl&& other) noexcept {
            *this = std::move(other);
        }

        SpriteImpl& operator=(SpriteImpl&& rhs) noexcept {
            if (this != &rhs) {
                swap(rhs);
            }
            return *this;
        }

        void swap(SpriteImpl &other) {
            std::swap(sprite_, other.sprite_);
            std::swap(isVisible_, other.isVisible_);
            std::swap(prevSpriteColour_, other.prevSpriteColour_);
            std::swap(animator_, other.animator_);
            std::swap(texture_, other.texture_);
        }

        void setTexture(const Texture &texture) {
            if (*texture_ != texture) {
                *texture_ = *std::make_shared<Texture>(texture);
                sprite_.setTexture(texture_->getInternalTexture(), true);
            }
        }

        void setTexture(const std::string &filename) {
            texture_ = std::make_shared<Texture>(ResourceManager::getInstance()->getTexture(filename));
            sprite_.setTexture(texture_->getInternalTexture(), true);
        }

        void setTextureRect(unsigned int left, unsigned int top,
            unsigned int width,unsigned int height)
        {
            if (getTextureRect() == UIntRect{left, top, width, height})
                return;

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

        void setRotation(float angle) {
            sprite_.setRotation(angle);
        }

        void setScale(float factorX, float factorY) {
            sprite_.setScale(factorX, factorY);
        }

        float getRotation() const {
            return sprite_.getRotation();
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

        void draw(priv::RenderTarget &renderTarget) const {
            if (isVisible_)
                renderTarget.getImpl()->getSFMLWindow().draw(sprite_);
        }

        void setColour(Colour colour) {
            sprite_.setColor(utility::convertToSFMLColour(colour));
        }

        void setOpacity(unsigned int opacity) {
            const auto& [r, g, b, a] = sprite_.getColor();
            sprite_.setColor(sf::Color{r, g, b, opacity < 255 ? sf::Uint8(opacity) : sf::Uint8(255)});
        }

        unsigned int getOpacity() const {
            return sprite_.getColor().a;
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

        void setOrigin(float x, float y) {
            sprite_.setOrigin(x, y);
        }

        Vector2f getOrigin() const {
            return {sprite_.getOrigin().x, sprite_.getOrigin().y};
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

    private:
        sf::Sprite sprite_;           //!< Third party sprite
        bool isVisible_;              //!< Flags whether or not the sprite is visible
        Colour prevSpriteColour_;     //!< Sprite colour before it was hidden
        Animator animator_;           //!< Sprite animator
        std::shared_ptr<Texture> texture_; //!< Keeps sf::Texture alive for sf::Sprite
    }; // class Impl

    /*-------------------------------------------------------------------------
     # Sprite class
     =-----------------------------------------------------------------------*/

    Sprite::Sprite() :
        pImpl_{std::make_unique<SpriteImpl>(*this)}
    {}

    Sprite::Sprite(const std::string &texture) :
        Sprite()
    {
        pImpl_->setTexture(texture);
    }

    Sprite::Sprite(const Texture &texture) :
        Sprite()
    {
        pImpl_->setTexture(texture);
    }

    Sprite::Sprite(const Texture &texture, const UIntRect &rectangle) :
        Sprite()
    {
        pImpl_->setTexture(texture);
        setTextureRect(rectangle);
    }

    Sprite::Sprite(const Sprite& other) :
        Drawable(other),
        pImpl_{std::make_unique<SpriteImpl>(*other.pImpl_)}
    {
        pImpl_->setAnimationTarget(*this);
    }

    Sprite &Sprite::operator=(const Sprite& other) {
        if (this != &other) {
            auto temp{other};
            std::swap(pImpl_, temp.pImpl_);
            pImpl_->setAnimationTarget(*this);
        }
        return *this;
    }

    Sprite::Sprite(Sprite&& other) noexcept :
        Drawable(std::move(other)),
        pImpl_{std::move(other.pImpl_)}
    {
        pImpl_->setAnimationTarget(*this);
    }

    Sprite &Sprite::operator=(Sprite&& other) noexcept {
        if (this != &other) {
            Drawable::operator=(std::move(other));
            *pImpl_ = std::move(*other.pImpl_);
            pImpl_->setAnimationTarget(*this);
        }

        return *this;
    }

    std::string Sprite::getClassName() const {
        return "Sprite";
    }

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
        setTextureRect(rect.left, rect.top, rect.width, rect.height);
    }

    void Sprite::setTextureRect(unsigned int left, unsigned int top, unsigned int width,
        unsigned int height)
    {
        if (auto [l, t, w, h] = getTextureRect(); l == left && t == top && w == width && h == height)
            return;

        pImpl_->setTextureRect(left, top, width, height);
        emitChange(Property{"textureRect", getTextureRect()});
    }

    UIntRect Sprite::getTextureRect() const {
        return pImpl_->getTextureRect();
    }

    void Sprite::setPosition(float x, float y) {
        if (auto [xPos, yPos] = getPosition(); xPos == x && yPos == y)
            return;

        pImpl_->setPosition(x, y);
        emitChange(Property{"position", Vector2f{x, y}});
    }

    void Sprite::setPosition(const Vector2f& position) {
        setPosition(position.x, position.y);
    }

    void Sprite::setRotation(float angle) {
        if (getRotation() == angle)
            return;

        pImpl_->setRotation(angle);
        emitChange(Property{"rotation", angle});
    }

    void Sprite::setScale(float factorX, float factorY) {
        if (auto [x, y] = getScale(); x == factorX && y == factorY)
            return;

        pImpl_->setScale(factorX, factorY);
        emitChange(Property{"scale", Vector2f{factorX, factorY}});
    }

    void Sprite::setScale(const Vector2f& scale) {
        setScale(scale.x, scale.y);
    }

    void Sprite::setOrigin(const Vector2f& origin) {
        setOrigin(origin.x, origin.y);
    }

    float Sprite::getRotation() const {
        return pImpl_->getRotation();
    }

    void Sprite::move(const Vector2f& offset) {
        move(offset.x, offset.y);
    }

    void Sprite::scale(const Vector2f& offset) {
        setScale(offset.x, offset.y);
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

    void Sprite::draw(priv::RenderTarget &renderTarget) const {
        pImpl_->draw(renderTarget);
    }

    void Sprite::rotate(float angle) {
        setRotation(getRotation() + angle);
    }

    void Sprite::setColour(Colour colour) {
        if (getColour() == colour)
            return;

        pImpl_->setColour(colour);
        emitChange(Property{"colour", colour});
    }

    Colour Sprite::getColour() const {
        return pImpl_->getColour();
    }

    void Sprite::setOpacity(unsigned int opacity) {
        if (getOpacity() == opacity)
            return;

        pImpl_->setOpacity(opacity);
        emitChange(Property{"opacity", opacity});
    }

    unsigned int Sprite::getOpacity() const {
        return pImpl_->getOpacity();
    }

    void Sprite::setVisible(bool visible) {
        if (isVisible() == visible)
            return;

        pImpl_->setVisible(visible);
        emitChange(Property{"visible", visible});
    }

    bool Sprite::isVisible() const {
        return pImpl_->isVisible();
    }

    void Sprite::toggleVisibility() {
        setVisible(!isVisible());
    }

    void Sprite::setOrigin(float x, float y) {
        if (auto [xO, yO] = getOrigin(); xO == x && yO == y)
            return;

        pImpl_->setOrigin(x, y);
        emitChange(Property{"origin", Vector2f{x, y}});
    }

    Vector2f Sprite::getOrigin() const {
        return pImpl_->getOrigin();
    }

    void Sprite::scale(float xFactor, float yFactor) {
        setScale(getScale().x * xFactor, getScale().y * yFactor);
    }

    void Sprite::move(float xOffset, float yOffset) {
        setPosition(getPosition().x + xOffset, getPosition().y + yOffset);
    }

    Vector2f Sprite::getScale() const {
        return pImpl_->getScale();
    }

    Animator &Sprite::getAnimator() {
        return pImpl_->getAnimator();
    }

    const Animator &Sprite::getAnimator() const {
        return pImpl_->getAnimator();
    }

    void Sprite::updateAnimation(Time deltaTime) {
        pImpl_->updateAnimation(deltaTime);
    }

    Sprite::~Sprite() {
        emit("destruction");
    }
}
