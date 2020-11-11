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
#include <assert.h>

namespace IME {
    Entity::Entity(const Dimensions &boundingRect)
        : boundingRect_(boundingRect), isVulnerable_(true), isAlive_(true), isCollidable_(false),
          direction_(Direction::None), position_({0, 0})
    {
        static std::size_t prevEntityId = 0;
        id_ = prevEntityId++;
    }

    void Entity::setPosition(float x, float y) {
        if (position_.x == x && position_.y == y)
            return;
        position_.x = x;
        position_.y = y;
        publishEvent("positionChanged", position_.x, position_.y);
    }

    void Entity::setDirection(Direction dir) {
        if (direction_ != dir) {
            direction_ = dir;
            publishEvent("directionChanged", direction_);
        }
    }

    Dimensions Entity::getSize() const {
        return boundingRect_;
    }

    void Entity::setAlive(bool isAlive) {
        if (isAlive_ == isAlive || (isAlive_ && !isVulnerable_))
            return;
        isAlive_ = isAlive;

        if (!isAlive_)
            publishEvent("killed");
        else
            publishEvent("revived"); //By default entity is alive (Will be killed first)
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
                publishEvent("collisionEnabled");
            else
                publishEvent("collisionDisabled");
        }
    }

    bool Entity::isAlive() const {
        return isAlive_;
    }

    bool Entity::isCollidable() const {
        return isCollidable_;
    }

    bool Entity::isVulnerable() const {
        return isVulnerable_;
    }

    std::size_t Entity::getId() const {
        return id_;
    }

    Direction Entity::getDirection() const {
        return direction_;
    }

    Position Entity::getPosition() const {
        return position_;
    }

    bool Entity::removeEventListener(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }

    bool Entity::operator==(const Entity &rhs) {
        return id_ == rhs.id_;
    }

    bool Entity::operator!=(const Entity &rhs) {
        return !(*this == rhs);
    }
}
