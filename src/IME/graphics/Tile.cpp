////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
#include "IME/graphics/RenderTarget.h"
#include "IME/core/physics/rigid_body/colliders/BoxCollider.h"
#include "IME/core/physics/rigid_body/PhysicsEngine.h"

namespace ime {
    Tile::Tile(Vector2u size, Vector2f position) :
        id_{'\0'},
        index_{-1, -1},
        tile_({static_cast<float>(size.x), static_cast<float>(size.y)}),
        isCollidable_{false}
    {
        tile_.setFillColour(Colour::White);
        prevFillColour_ = tile_.getFillColour();
        tile_.setPosition(position);
    }

    Tile::Tile(const Tile& other) :
        Drawable(other),
        id_{other.id_},
        index_{other.index_},
        tile_{other.tile_},
        prevFillColour_{other.prevFillColour_},
        isCollidable_{other.isCollidable_}
    {}

    Tile& Tile::operator=(Tile other) {
        swap(other);
        return *this;
    }

    void Tile::swap(Tile &other) {
        using std::swap;

        swap(id_, other.id_);
        swap(index_, other.index_);
        swap(tile_, other.tile_);
        swap(prevFillColour_, other.prevFillColour_);
        swap(isCollidable_, other.isCollidable_);
    }

    void Tile::attachCollider(BoxCollider::Ptr collider) {
        IME_ASSERT(collider, "Collider must not be a nullptr")
        IME_ASSERT(tile_.hasRigidBody(), "The tile must have a RigidBody before attaching a collider")

        if (collider->getSize() < tile_.getSize() || collider->getSize() > tile_.getSize())
            collider->setSize(tile_.getSize());

        tile_.getRigidBody()->attachCollider(std::move(collider));
    }

    void Tile::removeCollider() {
        tile_.removeRigidBody();
    }

    bool Tile::hasCollider() const {
        return tile_.hasRigidBody() ? tile_.getRigidBody()->getColliderCount() != 0: false;
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

        if (tile_.hasRigidBody())
            tile_.getRigidBody()->setPosition(getWorldCentre());

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

        if (hasCollider()) {
            tile_.getRigidBody()->forEachCollider([this, width, height](Collider* collider) {
                static_cast<BoxCollider*>(collider)->setSize(static_cast<float>(width), static_cast<float>(height));
                collider->getBody()->setPosition(getWorldCentre());
            });
        }

        emitChange(Property{"size", getSize()});
    }

    void Tile::setSize(Vector2u size) {
        setSize(size.x, size.y);
    }

    void Tile::setCollidable(bool collidable) {
        if (isCollidable_ == collidable)
            return;

        isCollidable_ = collidable;

        if (tile_.hasRigidBody())
            tile_.getRigidBody()->setEnabled(collidable);

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

    void Tile::draw(priv::RenderTarget &renderTarget) const {
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

    void Tile::setBody(RigidBody::Ptr body) {
        IME_ASSERT(body, "The physWorld body must not be a nullptr")
        IME_ASSERT(body->getType() == RigidBody::Type::Static, "The physWorld body of a tile must be of type ime::RigidBody::Type::Static")
        tile_.attachRigidBody(std::move(body));
        tile_.setOrigin(0, 0);
        tile_.getRigidBody()->setPosition(getWorldCentre());
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
