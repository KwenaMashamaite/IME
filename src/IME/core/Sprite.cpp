#include "IME/core/Sprite.h"
#include "IME/gui/window/Window.h"
#include "IME/utility/Helpers.h"
#include "IME/core/resources/ResourceManager.h"

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
        sprite_.setTexture(ResourceManager::getTexture(filename));
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
            spriteColour_ = Utility::convertFrom3rdPartyColour(sprite_.getColor());
            sprite_.setColor(sf::Color::Transparent);
        }
    }

    void Sprite::show() {
        if (isHidden_) {
            isHidden_ = false;
            sprite_.setColor(Utility::convertTo3rdPartyColour(spriteColour_));
        }
    }

    bool Sprite::isHidden() const {
        return isHidden_;
    }

    void Sprite::rotate(float angle) {
        sprite_.rotate(angle);
    }
}
