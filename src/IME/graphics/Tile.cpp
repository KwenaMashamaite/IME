////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

namespace ime {
    Tile::Tile(Vector2u size, Vector2f position) :
        isSolid_{false},
        id_{'\0'},
        index_{-1, -1}
    {
        setSize(size.x, size.y);
        tile_.setOutlineColour(Colour::White);
        tile_.setFillColour({36, 37, 38, 255});
        prevFillColour_ = tile_.getFillColour();
        setPosition(position);
    }

    Vector2u Tile::getSize() const {
        return {static_cast<unsigned int>(tile_.getGlobalBounds().width),
                static_cast<unsigned int>(tile_.getGlobalBounds().height)};
    }

    void Tile::setPosition(float x, float y) {
        tile_.setPosition(x, y);
        sprite_.setPosition(getPosition().x, getPosition().y);
    }

    void Tile::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    Vector2f Tile::getPosition() const {
        return {tile_.getPosition().x, tile_.getPosition().y};
    }

    Vector2f Tile::getWorldCentre() const {
        return {tile_.getPosition().x + tile_.getSize().x / 2.0f,
                tile_.getPosition().y + tile_.getSize().y / 2.0f};
    }

    Vector2f Tile::getLocalCentre() const {
        return tile_.getSize() / 2.0f;
    }

    void Tile::setSize(unsigned int width, unsigned int height) {
        tile_.setSize({static_cast<float>(width), static_cast<float>(height)});
    }

    void Tile::setSize(Vector2u size) {
        setSize(size.x, size.y);
    }

    void Tile::setSolid(bool isSolid) {
        isSolid_ = isSolid;
    }

    bool Tile::isSolid() const {
        return isSolid_;
    }

    void Tile::setId(char id) {
        id_ = id;
    }

    char Tile::getId() const {
        return id_;
    }

    void Tile::draw(Window &renderTarget) const {
        renderTarget.draw(tile_);
        renderTarget.draw(sprite_);
    }

    void Tile::setVisible(bool visible) {
        if (isVisible() == visible)
            return;

        if (visible) {
            sprite_.setVisible(true);
            tile_.setFillColour(prevFillColour_);
            tile_.setOutlineColour(Colour::White);
        } else {
            sprite_.setVisible(false);
            tile_.setOutlineColour(Colour::Transparent);
            prevFillColour_ = tile_.getFillColour();
            tile_.setFillColour(Colour::Transparent);
        }
    }

    bool Tile::isVisible() const {
        return sprite_.isVisible();
    }

    void Tile::toggleVisibility() {
        sprite_.toggleVisibility();
    }

    void Tile::addSprite(Sprite sprite) {
        sprite.setPosition(sprite_.getPosition());
        sprite_ = sprite;
    }

    bool Tile::isCollidable() const {
        return isSolid_;
    }

    bool Tile::contains(float x, float y) const {
        return ((x >= getPosition().x && x <= getPosition().x + getSize().x)
                && (y >= getPosition().y && y <= getPosition().y + getSize().y));
    }

    Sprite &Tile::getSprite() {
        return sprite_;
    }

    void Tile::setIndex(Index index) {
        index_ = index;
    }

    Index Tile::getIndex() const {
        return index_;
    }

    void Tile::setFillColour(const Colour &colour) {
        tile_.setFillColour(colour);
    }

    Colour Tile::getFillColour() const {
        return tile_.getFillColour();
    }
}
