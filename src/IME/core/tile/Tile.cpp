#include "IME/core/tile/Tile.h"
#include "IME/gui/window/Window.h"

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

    void Tile::setProperty(const Property &property) {
        properties_.addProperty(property);
    }

    Property Tile::getProperty(const std::string &name) {
        return properties_.getProperty(name);
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

    void Tile::setTextureRect(Position position, Dimensions size) {
        tileBoarder_.setTextureRect({
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(size.width),
            static_cast<int>(size.height)
        });
    }
}
