#include "IME/core/entity/IEntity.h"
#include <assert.h>

namespace IME {
    void IEntity::setPosition(float x, float y) {
        if (position_.x == x && position_.y == y)
            return;
        position_.x = x;
        position_.y = y;
        publishEvent("positionChanged", position_.x, position_.y);
    }

    void IEntity::setDirection(IEntity::Direction dir) {
        if (direction_ != dir) {
            direction_ = dir;
            publishEvent("directionChanged", direction_);
        }
    }

    Dimensions IEntity::getBoundingRect() const {
        return boundingRect_;
    }

    void IEntity::setAlive(bool isAlive) {
        if (isAlive_ == isAlive)
            return;
        isAlive_ = isAlive;

        if (!isAlive_)
            publishEvent("dead");
        else
            publishEvent("revived"); //By default entity is alive
    }

    bool IEntity::isAlive() const {
        return isAlive_;
    }

    IEntity::Direction IEntity::getDirection() const {
        return direction_;
    }

    Position IEntity::getPosition() const {
        return position_;
    }

    void IEntity::update() {
        assert(!states_.empty() && "No state to update");
        states_.top()->update();
    }

    void IEntity::pushState(std::shared_ptr<IEntityState> state) {
        assert(state && "A state cannot be null");
        states_.push(std::move(state));
    }

    void IEntity::popState() {
        assert(!states_.empty() && "No state to pop");
        states_.pop();
    }

    void IEntity::reset() {
        assert(!states_.empty() && "No state to reset");
        states_.top()->reset();
    }

    bool IEntity::removeEventListener(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }
}
