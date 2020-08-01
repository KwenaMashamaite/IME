#include "Entity.h"

namespace SI {
    Entity::Entity(IME::EntityType entityType,const IME::Position &position, Direction direction,
        const IME::Dimensions &boundRect, const std::string &texture,
        unsigned int numOfLives)
        : entityType_(entityType),
          position_(position),
          boundingRect_(boundRect),
          texture_(texture),
          numOfLives_(numOfLives),
          direction_(direction)
          {}

    void Entity::setPosition(float xPos, float yPos) {
        position_.x = xPos;
        position_.y = yPos;
    }

    void Entity::setDirection(Direction dir) {
        direction_ = dir;
    }

    void Entity::setTexture(const std::string &texture) {
        texture_ = texture;
    }

    const std::string &Entity::getTexture() const {
        return texture_;
    }

    IME::Dimensions Entity::getBoundingRect() const {
        return boundingRect_;
    }

    void Entity::takeDamage(unsigned int amountOfDamage) {
        if (isAlive())
            numOfLives_ -= amountOfDamage;
    }

    bool Entity::isAlive() const {
        return numOfLives_ <= 0u;
    }

    IEntity::Direction Entity::getDirection() const {
        return direction_;
    }

    IME::Position Entity::getPosition() const {
        return position_;
    }

    unsigned int Entity::getRemainingLives() const {
        return numOfLives_;
    }

    IME::EntityType Entity::getEntityType() {
        return entityType_;
    }

    Entity::~Entity() = default;
}
