#include "IME/graphics/Tile.h"
#include "IME/graphics/Window.h"
#include "IME/utility/Helpers.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::Graphics {
    Tile::Tile(const Dimensions &size, const Position &position) {
        isCollidable_ = false;
        id_ = '\0';
        index_ = {-1, -1}; //Invalid index
        setSize(size.width, size.height);
        tileBoarder_.setOutlineColor(sf::Color::White);
        tileBoarder_.setOutlineThickness(-1.0f);
        tileBoarder_.setFillColor(sf::Color::Transparent);
        setPosition(position);
        setTextureRect({0, 0}, size);
        tileType_ = TileType::Empty;
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

    void Tile::setSize(float width, float height) {
        tileBoarder_.setSize(sf::Vector2f{width, height});
    }

    void Tile::setSize(Dimensions size) {
        setSize(size.width, size.height);
    }

    void Tile::setId(const char &id) {
        id_ = id;
    }

    const char &Tile::getId() const {
        return id_;
    }

    void Tile::draw(Window &renderTarget) {
        renderTarget.draw(tileBoarder_);
        renderTarget.draw(sprite_);
    }

    void Tile::hide() {
        sprite_.hide();
        tileBoarder_.setOutlineColor(sf::Color::Transparent);
    }

    void Tile::show() {
        sprite_.show();
        tileBoarder_.setOutlineColor(sf::Color::White);
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

    bool Tile::isCollidable() const {
        return isCollidable_;
    }

    void Tile::setCollidable(bool isCollidable) {
        isCollidable_ = isCollidable;
    }

    bool Tile::contains(float x, float y) const {
        return ((x >= getPosition().x && x <= getPosition().x + getSize().width)
                && (y >= getPosition().y && y <= getPosition().y + getSize().height));
    }

    Sprite &Tile::getSprite() {
        return sprite_;
    }

    int Tile::onCollision(Callback<Tile&> callback) {
        return eventEmitter_.addEventListener("hit", std::move(callback));
    }

    void Tile::hit() {
        eventEmitter_.emit("hit", *this);
    }

    void Tile::setBorderVisible(bool isVisible) {
        if (isVisible)
            tileBoarder_.setOutlineColor(sf::Color::White);
        else
            tileBoarder_.setOutlineColor(sf::Color::Transparent);
    }

    void Tile::setIndex(Index index) {
        index_ = index;
    }

    Index Tile::getIndex() const {
        return index_;
    }

    void Tile::setFillColour(const Colour &colour) {
        tileBoarder_.setFillColor(Utility::convertTo3rdPartyColour(colour));
    }

    Colour Tile::getFillColour() const {
        return Utility::convertFrom3rdPartyColour(tileBoarder_.getFillColor());
    }

    void Tile::setType(const TileType &tileType) {
        tileType_ = tileType;
    }

    TileType Tile::getType() const {
        return tileType_;
    }
}
