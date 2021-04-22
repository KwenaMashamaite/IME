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
#include "IME/core/physics/rigid_body/colliders/BoxCollider.h"
#include "IME/core/physics/World.h"

namespace ime {
    Tile::Tile(Vector2u size, Vector2f position) :
        isCollidable_{false},
        id_{'\0'},
        index_{-1, -1},
        tile_({static_cast<float>(size.x), static_cast<float>(size.y)})
    {
        tile_.setFillColour({36, 37, 38, 255});
        prevFillColour_ = tile_.getFillColour();
        tile_.setPosition(position);
    }

    Tile::Tile(const Tile& other) :
        Drawable(other),
        isCollidable_{other.isCollidable_},
        id_{other.id_},
        index_{other.index_},
        tile_{other.tile_},
        prevFillColour_{other.prevFillColour_}
    {
        if (other.collider_) {
            collider_ = other.collider_->copy();
        }
    }

    Tile& Tile::operator=(Tile other) {
        swap(other);
        return *this;
    }

    void Tile::swap(Tile &other) {
        using std::swap;

        swap(isCollidable_, other.isCollidable_);
        swap(id_, other.id_);
        swap(index_, other.index_);
        swap(tile_, other.tile_);
        swap(prevFillColour_, other.prevFillColour_);
        swap(collider_, other.collider_);
    }

    Tile::Tile(Tile&&) noexcept = default;
    Tile &Tile::operator=(Tile&&) noexcept = default;

    void Tile::attachCollider(std::shared_ptr<BoxCollider> collider) {
        IME_ASSERT(!collider_, "Cannot add a collider to a tile that already has one, use the removeCollider function to remove it first")
        IME_ASSERT(collider->getBody(), "A tile collider must have a rigid body attached to it")
        IME_ASSERT(collider->getBody()->getType() == Body::Type::Static, "The rigid body a tile collider is attached to must be of type Body::Type::Static")
        IME_ASSERT(collider->getType() == Collider::Type::Box, "A tile collider must be of ime::Collider::Type::Box")

        collider_ = std::move(collider);
        if (collider_->getSize() < tile_.getSize() || collider_->getSize() > tile_.getSize())
            collider_->setSize(tile_.getSize());

        collider_->getBody()->setPosition(getWorldCentre());
    }

    void Tile::removeCollider() {
        setCollidable(false);
        auto body = collider_->getBody();
        body->removeColliderWithId(collider_->getObjectId());
        body->getWorld()->removeBodyById(body->getObjectId());
        collider_.reset();
    }

    bool Tile::hasCollider() const {
        return collider_ != nullptr;
    }

    std::string Tile::getClassName() const {
        return "Tile";
    }

    Vector2u Tile::getSize() const {
        return {static_cast<unsigned int>(tile_.getGlobalBounds().width),
                static_cast<unsigned int>(tile_.getGlobalBounds().height)};
    }

    void Tile::setPosition(float x, float y) {
        if (getPosition() == Vector2f{x, y})
            return;

        tile_.setPosition(x, y);

        if (collider_)
            collider_->getBody()->setPosition(getWorldCentre());

        emitChange(Property{Property{"position", getPosition()}});
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
        if (getSize() == Vector2u{width, height})
            return;

        tile_.setSize({static_cast<float>(width), static_cast<float>(height)});

        if (collider_) {
            collider_->setSize(static_cast<float>(width), static_cast<float>(height));
            collider_->getBody()->setPosition(getWorldCentre());
        }

        emitChange(Property{"size", getSize()});
    }

    void Tile::setSize(Vector2u size) {
        setSize(size.x, size.y);
    }

    void Tile::setCollidable(bool collidable) {
        if (isCollidable_ == collidable)
            return;

        if (collidable) {
            IME_ASSERT(collider_, "Cannot set Tile as collidable without a collider, use the setCollidable function to add one")
        }

        isCollidable_ = collidable;

        if (collider_)
            collider_->setEnable(collidable);

        emitChange(Property{"collidable", isCollidable_});
    }

    void Tile::setId(char id) {
        if (id_ != id) {
            id_ = id;
            emitChange(Property{"id", id_});
        }
    }

    char Tile::getId() const {
        return id_;
    }

    void Tile::draw(Window &renderTarget) const {
        renderTarget.draw(tile_);
    }

    void Tile::setVisible(bool visible) {
        if (isVisible() == visible)
            return;

        if (visible)
            tile_.setFillColour(prevFillColour_);
        else {
            prevFillColour_ = tile_.getFillColour();
            tile_.setFillColour(Colour::Transparent);
        }

        emitChange(Property{"visible", isVisible()});
    }

    bool Tile::isVisible() const {
        return tile_.getFillColour() != Colour::Transparent;
    }

    void Tile::toggleVisibility() {
        setVisible(!isVisible());
    }

    bool Tile::isCollidable() const {
        return isCollidable_;
    }

    bool Tile::contains(Vector2f point) const {
        return ((point.x >= getPosition().x && point.x <= getPosition().x + getSize().x)
                && (point.y >= getPosition().y && point.y <= getPosition().y + getSize().y));
    }

    void Tile::setIndex(Index index) {
        if (index_ != index) {
            index_ = index;
            emitChange(Property{"index", index_});
        }
    }

    Index Tile::getIndex() const {
        return index_;
    }

    void Tile::setFillColour(const Colour &colour) {
        if (tile_.getFillColour() != colour) {
            tile_.setFillColour(colour);
            emitChange(Property{"fillColour", tile_.getFillColour()});
        }
    }

    Colour Tile::getFillColour() const {
        return tile_.getFillColour();
    }

    Tile::~Tile() {
        emit("destruction");
    }
}
