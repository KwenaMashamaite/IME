#include "IME/core/tile/Tile.h"
#include "IME/gui/window/Window.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME {
    Tile::Tile(const Dimensions &size, const Position &position)
    {
        isCollideable_ = false;
        tileBoarder_.setSize(sf::Vector2f{size.width, size.height});
        tileBoarder_.setOutlineColor(sf::Color::White);
        tileBoarder_.setOutlineThickness(-1.0f);
        tileBoarder_.setFillColor(sf::Color::Transparent);
        setPosition(position);
        setTextureRect({0, 0}, size);
    }

    Dimensions Tile::getSize() const {
        return {tileBoarder_.getGlobalBounds().width, tileBoarder_.getGlobalBounds().height};
    }

    Position Tile::getPosition() const {
        return {tileBoarder_.getPosition().x, tileBoarder_.getPosition().y};
    }

    void Tile::setPosition(const Position &position) {
        tileBoarder_.setPosition(position.x, position.y);
        sprite_.setPosition(getPosition().x + getSize().width / 2.0f,
            getPosition().y + getSize().height / 2.0f);
    }

    void Tile::setToken(const char &token) {
        token_ = token;
    }

    const char &Tile::getToken() const {
        return token_;
    }

    void Tile::draw(Gui::Window &renderTarget) {
        renderTarget.draw(tileBoarder_);
        renderTarget.draw(sprite_);
    }

    void Tile::hide() {
        sprite_.hide();
    }

    void Tile::show() {
        sprite_.show();
    }

    bool Tile::isHidden() const {
        return sprite_.isHidden();
    }

    void Tile::setTextureRect(Position position, Dimensions size) {
        if (size.width > getSize().width)
            size.width = getSize().width;

        if (size.height > getSize().height)
            size.height = getSize().height;

        sprite_.setTextureRect(position.x, position.y, size.width, size.height);
        sprite_.setOrigin(sprite_.getSize().width / 2.0f, sprite_.getSize().height / 2.0f);
    }

    void Tile::setTexture(const std::string &filename) {
        sprite_.setTexture(filename);
    }

    bool Tile::isCollideable() const {
        return isCollideable_;
    }

    void Tile::setCollideable(bool isCollideable) {
        isCollideable_ = isCollideable;
    }
}
