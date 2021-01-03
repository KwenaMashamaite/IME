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

#include "IME/core/entity/Entity.h"
#include <cassert>

/* @TODO - Remove this if copy constructor and assignment operator
 *         implementation changes
 *
 * @warning Update copy constructor and assignment operator if a new member
 * variable is added, why? look at their respective implementations
 */

std::size_t IME::Entity::prevEntityId_{0};

namespace IME {
    Entity::Entity() : Entity({8, 8})
    {}

    Entity::Entity(const Entity &other) {
        // Assign everything but create new id (Both must have unique id's)
        // We are using manual assignment because we can't use std::swap()
        // due to a pure virtual method in the class
        type_ = other.type_;
        id_ = prevEntityId_++; //Default copy constructor assigns same Id
        boundingRect_ = other.boundingRect_;
        isVulnerable_ = other.isVulnerable_;
        isActive_ = other.isActive_;
        isCollidable_ = other.isCollidable_;
        direction_ = other.direction_;
        position_ = other.position_;
        eventEmitter_ = other.eventEmitter_;
    }

    Entity &Entity::operator=(const Entity &other) {
        // Assign everything but the id (Both must have unique id's)
        // We are using manual assignment because we can't use std::swap()
        // due to a pure virtual method in the class
        type_ = other.type_;
        boundingRect_ = other.boundingRect_;
        isVulnerable_ = other.isVulnerable_;
        isActive_ = other.isActive_;
        isCollidable_ = other.isCollidable_;
        direction_ = other.direction_;
        position_ = other.position_;
        eventEmitter_ = other.eventEmitter_;
        return *this;
    }

    Entity::Entity(const Vector2u &boundingBoxSize, Type type) :
        type_(type),
        id_{prevEntityId_++},
        boundingRect_(boundingBoxSize),
        isVulnerable_(true),
        isActive_(true),
        isCollidable_(false),
        direction_(Direction::Unknown),
        position_({0, 0})
    {}

    void Entity::setPosition(float x, float y) {
        if (position_.x == x && position_.y == y)
            return;
        position_.x = x;
        position_.y = y;
        publishEvent("positionChange", position_.x, position_.y);
        publishEvent("positionChange", position_);
    }

    void Entity::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    Vector2f Entity::getPosition() const {
        return position_;
    }

    void Entity::setDirection(Direction dir) {
        if (direction_ != dir) {
            direction_ = dir;
            publishEvent("directionChange", direction_);
        }
    }

    Direction Entity::getDirection() const {
        return direction_;
    }

    void Entity::setSize(Vector2u size) {
        if (boundingRect_ != size) {
            boundingRect_ = size;
            eventEmitter_.emit("sizeChange", boundingRect_);
        }
    }

    Vector2u Entity::getSize() const {
        return boundingRect_;
    }

    void Entity::setActive(bool isActive) {
        if (isActive_ == isActive || (isActive_ && !isVulnerable_))
            return;
        isActive_ = isActive;

        if (!isActive_)
            publishEvent("inactive");
        else
            publishEvent("active");
    }

    void Entity::setVulnerable(bool isVulnerable) {
        if (isVulnerable_ != isVulnerable) {
            isVulnerable_ = isVulnerable;
            if (isVulnerable_)
                publishEvent("vulnerable");
            else
                publishEvent("inVulnerable");
        }
    }

    void Entity::setCollidable(bool isCollidable) {
        if (isCollidable_ != isCollidable) {
            isCollidable_ = isCollidable;
            if (isCollidable_)
                publishEvent("collisionEnable");
            else
                publishEvent("collisionDisable");
        }
    }

    bool Entity::isActive() const {
        return isActive_;
    }

    bool Entity::isCollidable() const {
        return isCollidable_;
    }

    void Entity::setType(Entity::Type type) {
        type_ = type;
    }

    Entity::Type Entity::getType() const {
        return type_;
    }

    bool Entity::isVulnerable() const {
        return isVulnerable_;
    }

    std::size_t Entity::getObjectId() const {
        return id_;
    }

    bool Entity::unsubscribe(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }

    bool Entity::operator==(const Entity &rhs) {
        return id_ == rhs.id_;
    }

    bool Entity::operator!=(const Entity &rhs) {
        return !(*this == rhs);
    }
}
