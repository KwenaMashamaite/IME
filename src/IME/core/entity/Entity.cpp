#include "IME/core/entity/Entity.h"
#include <assert.h>

namespace IME {
    Entity::Entity(const Dimensions &boundingRect)
        : boundingRect_(boundingRect), isAlive_(true),
          direction_(Direction::None), position_({0, 0})
    {}

    void Entity::setPosition(float x, float y) {
        if (position_.x == x && position_.y == y)
            return;
        position_.x = x;
        position_.y = y;
        publishEvent("positionChanged", position_.x, position_.y);
    }

    void Entity::setDirection(Entity::Direction dir) {
        if (direction_ != dir) {
            direction_ = dir;
            publishEvent("directionChanged", direction_);
        }
    }

    Dimensions Entity::getBoundingRect() const {
        return boundingRect_;
    }

    void Entity::setAlive(bool isAlive) {
        if (isAlive_ == isAlive)
            return;
        isAlive_ = isAlive;

        if (!isAlive_)
            publishEvent("dead");
        else
            publishEvent("revived"); //By default entity is alive
    }

    bool Entity::isAlive() const {
        return isAlive_;
    }

    Entity::Direction Entity::getDirection() const {
        return direction_;
    }

    Position Entity::getPosition() const {
        return position_;
    }

    void Entity::update() {
        assert(!states_.empty() && "No state to update");
        states_.top()->update();
    }

    void Entity::pushState(std::shared_ptr<IEntityState> state) {
        assert(state && "A state cannot be null");
        states_.push(std::move(state));
    }

    void Entity::popState() {
        assert(!states_.empty() && "No state to pop");
        states_.pop();
    }

    void Entity::reset() {
        assert(!states_.empty() && "No state to reset");
        states_.top()->reset();
    }

    bool Entity::removeEventListener(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }
}
