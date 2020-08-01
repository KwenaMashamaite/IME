#include "IME/core/IEntity.h"

namespace IME {
    bool IEntity::isCollideWith(IEntity &other) const {
        return getPosition().x + getBoundingRect().width >= other.getPosition().x
            && getPosition().x <= other.getPosition().x + other.getBoundingRect().width
            && getPosition().y + getBoundingRect().height >= other.getPosition().y
            && getPosition().y <= other.getPosition().y + other.getBoundingRect().height;
    }
}
