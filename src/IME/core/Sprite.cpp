#include "IME/core/Sprite.h"
#include "IME/gui/window/Window.h"
#include "IME/utility/Helpers.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME {
    Sprite::Sprite() : isHidden_(false)
    {}

    void Sprite::setPosition(float x, float y) {
        sprite_.setPosition(x, y);
    }

    void Sprite::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void Sprite::setTexture(const std::string &filename) {
        sprite_.setTexture(ResourceManager::getInstance()->getTexture(filename));
    }

    Position Sprite::getPosition() const {
        return {sprite_.getPosition().x, sprite_.getPosition().y};
    }

    Dimensions Sprite::getSize() const {
        return {sprite_.getGlobalBounds().width, sprite_.getGlobalBounds().height};
    }

    void Sprite::setTextureRect(int left, int top, int width, int height) {
        sprite_.setTextureRect({left, top, width, height});
    }

    void Sprite::draw(Gui::Window &renderTarget) {
        renderTarget.draw(sprite_);
    }

    void Sprite::hide() {
        if (!isHidden_) {
            isHidden_ = true;
            spriteColour_ = getColour();
            sprite_.setColor(sf::Color::Transparent);
        }
    }

    void Sprite::show() {
        if (isHidden_) {
            isHidden_ = false;
            setColour(spriteColour_);
        }
    }

    bool Sprite::isHidden() const {
        return isHidden_;
    }

    void Sprite::rotate(float angle) {
        sprite_.rotate(angle);
    }

    void Sprite::setColour(Gui::Colour colour) {
        sprite_.setColor(Utility::convertTo3rdPartyColour(colour));
    }

    Gui::Colour Sprite::getColour() const {
        return Utility::convertFrom3rdPartyColour(sprite_.getColor());
    }

    void Sprite::setOrigin(float x, float y) {
        sprite_.setOrigin(x, y);
    }

    void Sprite::scale(float xFactor, float yFactor) {
        sprite_.scale(xFactor, yFactor);
    }

    void Sprite::move(float xOffset, float yOffset) {
        sprite_.move(xOffset, yOffset);
    }
}
