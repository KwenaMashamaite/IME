#include "Entity.h"

Entity::Entity(const Position &position, const Dimensions &boundRect, const std::string &texture, float life)
        : position_(position), boundingRect_(boundRect), texture_(texture), life_(life),
          direction_(Direction::Up), speed_(0.0f), angleOfRotation_(0.0f)
          {}

void Entity::setPosition(float xPos, float yPos) {
    position_.x = xPos;
    position_.y = yPos;
}

void Entity::setDirection(Direction dir) {
    direction_ = dir;
}

void Entity::setSpeed(float speed) {
    speed_ = speed;
}

void Entity::rotateBy(float angle) {
    angleOfRotation_ += angle;
}

void Entity::setTexture(const std::string &texture) {
    texture_ = texture;
}

const std::string &Entity::getTexture() const {
    return texture_;
}

Dimensions Entity::getBoundingRect() const {
    return boundingRect_;
}

void Entity::takeDamage(float amountOfDamage) {
    if (isAlive())
        life_ -= amountOfDamage;
}

bool Entity::isAlive() const {
    return life_ <= 0.0f;
}

Direction Entity::getDirection() const {
    return direction_;
}

Position Entity::getPosition() const {
    return position_;
}

float Entity::getAngleOfRotation() const {
    return angleOfRotation_;
}

float Entity::getRemainingLife() const {
    return life_;
}

void Entity::adjustSpeed(float speed) {
    speed_ += speed;
}
