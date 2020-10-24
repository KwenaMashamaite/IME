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

    void Sprite::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void Sprite::setTexture(const std::string &filename) {
        sprite_.setTexture(ResourceManager::getInstance()->getTexture(filename));
        textureFileName_ = filename;
    }

    Position Sprite::getPosition() const {
        return {sprite_.getPosition().x, sprite_.getPosition().y};
    }

    const std::string &Sprite::getTexture() const {
        return textureFileName_;
    }

    Dimensions Sprite::getSize() const {
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

    Position Sprite::getOrigin() const {
        return {sprite_.getOrigin().x, sprite_.getOrigin().y};
    }

    void Sprite::scale(float xFactor, float yFactor) {
        sprite_.scale(xFactor, yFactor);
    }

    void Sprite::move(float xOffset, float yOffset) {
        sprite_.move(xOffset, yOffset);
    }
}
