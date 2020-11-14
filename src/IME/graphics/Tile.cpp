////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

#include "IME/graphics/Tile.h"
#include "IME/graphics/Window.h"
#include "IME/utility/Helpers.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::Graphics {
    Tile::Tile(const Vector2u &size, const Vector2f &position) {
        isCollidable_ = false;
        id_ = '\0';
        index_ = {-1, -1}; //Invalid index
        setSize(size.x, size.y);
        tile_.setOutlineColor(sf::Color::White);
        tile_.setOutlineThickness(-1.0f);
        tile_.setFillColor(sf::Color::Transparent);
        prevFillColour_ = sf::Color::Transparent;
        setPosition(position);
        tileType_ = TileType::Empty;
    }

    Vector2u Tile::getSize() const {
        return {static_cast<unsigned int>(tile_.getGlobalBounds().width),
                static_cast<unsigned int>(tile_.getGlobalBounds().height)};
    }

    Vector2f Tile::getPosition() const {
        return {tile_.getPosition().x, tile_.getPosition().y};
    }

    void Tile::setPosition(float x, float y) {
        tile_.setPosition(x, y);
        sprite_.setPosition(getPosition().x, getPosition().y);
    }

    void Tile::setPosition(const Vector2f &position) {
        setPosition(position.x, position.y);
    }

    void Tile::setSize(unsigned int width, unsigned int height) {
        tile_.setSize(sf::Vector2f{static_cast<float>(width),
            static_cast<float>(height)});
    }

    void Tile::setSize(Vector2u size) {
        setSize(size.x, size.y);
    }

    void Tile::setId(char id) {
        id_ = id;
    }

    char Tile::getId() const {
        return id_;
    }

    void Tile::draw(Window &renderTarget) {
        renderTarget.draw(tile_);
        renderTarget.draw(sprite_);
    }

    void Tile::hide() {
        sprite_.hide();
        tile_.setOutlineColor(sf::Color::Transparent);
        prevFillColour_ = tile_.getFillColor();
        tile_.setFillColor(sf::Color::Transparent);
    }

    void Tile::show() {
        sprite_.show();
        tile_.setFillColor(prevFillColour_);
        tile_.setOutlineColor(sf::Color::White);
    }

    bool Tile::isHidden() const {
        return sprite_.isHidden();
    }

    void Tile::addSprite(Sprite sprite) {
        sprite.setPosition(sprite_.getPosition());
        sprite_ = sprite;
    }

    bool Tile::isCollidable() const {
        return isCollidable_;
    }

    void Tile::setCollidable(bool isCollidable) {
        isCollidable_ = isCollidable;
    }

    bool Tile::contains(float x, float y) const {
        return ((x >= getPosition().x && x <= getPosition().x + getSize().x)
                && (y >= getPosition().y && y <= getPosition().y + getSize().y));
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
            tile_.setOutlineColor(sf::Color::White);
        else
            tile_.setOutlineColor(sf::Color::Transparent);
    }

    void Tile::setIndex(Index index) {
        index_ = index;
    }

    Index Tile::getIndex() const {
        return index_;
    }

    void Tile::setFillColour(const Colour &colour) {
        tile_.setFillColor(Utility::convertToSFMLColour(colour));
    }

    Colour Tile::getFillColour() const {
        return Utility::convertFrom3rdPartyColour(tile_.getFillColor());
    }

    void Tile::setType(TileType tileType) {
        tileType_ = tileType;
    }

    TileType Tile::getType() const {
        return tileType_;
    }

    void Tile::setSpritePosition(float x, float y) {
        if (contains(x, y))
            sprite_.setPosition(x, y);
    }
}
