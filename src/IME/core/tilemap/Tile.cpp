#include "IME/core/tilemap/Tile.h"
#include "IME/gui/window/Window.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME {
    Tile::Tile(const Dimensions &size, const Position &position)
    {
        isCollideable_ = false;
        id_ = '\0';
        tileBoarder_.setSize(sf::Vector2f{size.width, size.height});
        tileBoarder_.setOutlineColor(sf::Color::White);
        tileBoarder_.setOutlineThickness(-1.0f);
        tileBoarder_.setFillColor(sf::Color::Transparent);
        setPosition(position);
        setTextureRect({0, 0}, size);
        borderCollisionFlags_.insert({Border::Left, false});

        //Flag all four sides of the tile as not collideable
        for (auto i = 0u; i < 4u; i++)
            borderCollisionFlags_.insert({static_cast<Border>(i), false});
    }

    Dimensions Tile::getSize() const {
        return {tileBoarder_.getGlobalBounds().width, tileBoarder_.getGlobalBounds().height};
    }

    Position Tile::getPosition() const {
        return {tileBoarder_.getPosition().x, tileBoarder_.getPosition().y};
    }

    void Tile::setPosition(float x, float y) {
        tileBoarder_.setPosition(x, y);
        sprite_.setPosition(getPosition().x, getPosition().y);
    }

    void Tile::setPosition(const Position &position) {
        setPosition(position.x, position.y);
    }

    void Tile::setId(const char &id) {
        id_ = id;
    }

    const char &Tile::getId() const {
        return id_;
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
    }

    void Tile::setTexture(const std::string &filename) {
        sprite_.setTexture(filename);
    }

    bool Tile::isCollideable(const Border &border) const {
        return borderCollisionFlags_.at(border);
    }

    bool Tile::isCollideable() const {
        return isCollideable(Border::Left)
            && isCollideable(Border::Right)
            && isCollideable(Border::Top)
            && isCollideable(Border::Bottom);
    }

    void Tile::setCollideable(bool isCollideable) {
        for (auto& border : borderCollisionFlags_)
            border.second = isCollideable;
    }

    void Tile::setCollideable(const Border &border, bool isCollideable) {
        borderCollisionFlags_.at(border) = isCollideable;
    }

    bool Tile::contains(float x, float y) const {
        return ((x >= getPosition().x && x <= getPosition().x + getSize().width)
            && (y >= getPosition().y && y <= getPosition().y + getSize().height));
    }

    Sprite &Tile::getSprite() {
        return sprite_;
    }

    int Tile::onCollision(Callback<Tile&, Border> callback) {
        return eventEmitter_.addEventListener("hit", std::move(callback));
    }

    void Tile::hit(const Border& border) {
        eventEmitter_.emit("borderHit", *this, border);
    }
}
