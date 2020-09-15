#include "IME/core/IEntity.h"
#include <assert.h>

namespace IME {
    bool IEntity::isCollideWith(IEntity &other) const {
        return getPosition().x + getBoundingRect().width >= other.getPosition().x
            && getPosition().x <= other.getPosition().x + other.getBoundingRect().width
            && getPosition().y + getBoundingRect().height >= other.getPosition().y
            && getPosition().y <= other.getPosition().y + other.getBoundingRect().height;
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
}
