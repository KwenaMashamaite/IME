#include "IME/core/tile/Tile.h"
#include "IME/gui/window/Window.h"
#include "IME/core/resources/ResourceManager.h"

namespace IME {
    Tile::Tile(const Dimensions &size, const Position &position)
    {
        tileBoarder_.setSize(sf::Vector2f{size.width, size.height});
        tileBoarder_.setOutlineColor(sf::Color::White);
        tileBoarder_.setOutlineThickness(-1.0f);
        tileBoarder_.setFillColor(sf::Color::Transparent);
        setPosition(position);
    }

    Dimensions Tile::getSize() const {
        return {tileBoarder_.getGlobalBounds().width, tileBoarder_.getGlobalBounds().height};
    }

    Position Tile::getPosition() const {
        return {tileBoarder_.getPosition().x, tileBoarder_.getPosition().y};
    }

    void Tile::setPosition(const Position &position) {
        tileBoarder_.setPosition(position.x, position.y);
    }

    void Tile::setToken(const char &token) {
        token_ = token;
    }

    const char &Tile::getToken() const {
        return token_;
    }

    void Tile::draw(Gui::Window &renderTarget) {
        renderTarget.draw(tileBoarder_);
    }

    void Tile::hide() {
        sprite_.hide();
    }

    void Tile::show() {
        sprite_.show();
    }

    bool Tile::isHidden() const {
        return false;
    }

    void Tile::setTextureRect(const std::string& filename, Position position, Dimensions size) {
        if (size.width > getSize().width)
            size.width = getSize().width;

        if (size.height > getSize().height)
            size.height = getSize().height;

        //texture_ = std::make_shared<sf::Texture>(ResourceManager::getInstance()->getTexture(filename));
        //tileBoarder_.setTexture(texture_.get());
        tileBoarder_.setTextureRect({
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(size.width),
            static_cast<int>(size.height)
        });
    }
}
