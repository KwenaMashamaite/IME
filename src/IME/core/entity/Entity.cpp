#include "IME/core/entity/Entity.h"
#include <assert.h>

namespace IME {
    Entity::Entity(const Dimensions &boundingRect)
        : boundingRect_(boundingRect), isInvincible_(false), isAlive_(true), isCollidable_(false),
          direction_(Direction::None), position_({0, 0})
    {}

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
        if (isAlive_ == isAlive || (isAlive_ && isInvincible_))
            return;
        isAlive_ = isAlive;

        if (!isAlive_)
            publishEvent("killed");
        else
            publishEvent("revived"); //By default entity is alive
    }

    void Entity::setInvincible(bool isInvincible) {
        if (isInvincible_ != isInvincible) {
            isInvincible_ = isInvincible;
            if (isInvincible_)
                publishEvent("godModeEnabled");
            else
                publishEvent("godModeDisabled");
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

    bool Entity::isInvincible() const {
        return isInvincible_;
    }

    Direction Entity::getDirection() const {
        return direction_;
    }

    Position Entity::getPosition() const {
        return position_;
    }

    void Entity::update() {
        if (!states_.empty())
            states_.top()->update();
    }

    void Entity::pushState(std::shared_ptr<IEntityState> state) {
        assert(state && "A state cannot be null");
        states_.top()->onPause();
        state->onEnter();
        states_.push(std::move(state));
    }

    void Entity::popState() {
        if (!states_.empty()) {
            states_.top()->onExit();
            states_.pop();
            if (!states_.empty())
                states_.top()->onResume();
        }
    }

    void Entity::reset() {
        if (!states_.empty())
            states_.top()->reset();
    }

    bool Entity::removeEventListener(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }
}
