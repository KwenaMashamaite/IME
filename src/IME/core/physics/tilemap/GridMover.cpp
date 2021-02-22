////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/core/physics/tilemap/GridMover.h"

namespace ime {
    GridMover::GridMover(Type type, TileMap &tileMap, GameObject::sharedPtr target) :
        type_{type},
        tileMap_(tileMap),
        targetVelocity_{Vector2f {0, 0}},
        targetDirection_(Direction::Unknown),
        targetTile_{tileMap.getTileSize(), Vector2f{0, 0}},
        prevTile_{tileMap.getTileSize(), Vector2f{0, 0}},
        isMoving_{false}
    {
        setTarget(target);
    }

    void GridMover::setTarget(GameObject::sharedPtr target) {
        if (target_ == target)
            return;
        else if (target) {
            IME_ASSERT(target->hasRigidBody(), "Game objects controlled by a grid mover must have a rigid body attached to them");
            IME_ASSERT(target->getRigidBody()->getType() == BodyType::Kinematic, "A grid mover can only control game objects with a BodyType::Kinematic rigid body");
            IME_ASSERT(tileMap_.hasChild(target), "The game object must already be in the grid/tilemap before adding it to a grid mover");

            if (target_)
                teleportTargetToDestination();

            auto velocity = target->getRigidBody()->getLinearVelocity();
            targetVelocity_ = {std::abs(velocity.x), std::abs(velocity.y)};
            target->getRigidBody()->setLinearVelocity({0, 0});
            targetTile_ = tileMap_.getTile(target->getTransform().getPosition());
            target_ = std::move(target);
        } else
            target_ = target;

        eventEmitter_.emit("targetChange", target_);
    }

    GridMover::Type GridMover::getType() const {
        return type_;
    }

    GameObject::sharedPtr GridMover::getTarget() const {
        return target_;
    }

    void GridMover::setHorizontalVelocity(float velocity) {
        targetVelocity_.x = std::abs(velocity);
    }

    void GridMover::setVerticalVelocity(float velocity) {
        targetVelocity_.y = std::abs(velocity);
    }

    Vector2f GridMover::getTargetVelocity() const {
        return targetVelocity_;
    }

    Index GridMover::getTargetTileIndex() const {
        return targetTile_.getIndex();
    }

    TileMap &GridMover::getGrid() {
        return tileMap_;
    }

    bool GridMover::isTargetMoving() const {
        return isMoving_;
    }

    bool GridMover::requestDirectionChange(Direction newDir) {
        if (!isTargetMoving() && targetDirection_ == Direction::Unknown) {
            switch (newDir) {
                case Direction::Unknown:
                    target_->setDirection(Direction::Unknown);
                    break;
                case Direction::Left:
                    target_->setDirection(Direction::Left);
                    break;
                case Direction::Right:
                    target_->setDirection(Direction::Right);
                    break;
                case Direction::Up:
                    target_->setDirection(Direction::Up);
                    break;
                case Direction::Down:
                    target_->setDirection(Direction::Down);
                    break;
            }
            targetDirection_ = target_->getDirection();
            return true;
        }
        return false;
    }

    void GridMover::update(Time deltaTime) {
        if (target_) {
            IME_ASSERT(tileMap_.hasChild(target_), "Target removed from the grid while still controlled by a grid mover");
            IME_ASSERT(target_->hasRigidBody(), "The targets rigid body was removed while it was still controlled by a grid mover");
            IME_ASSERT(target_->getRigidBody()->getType() == BodyType::Kinematic, "The targets rigid body was changed from BodyType::Kinematic, a grid mover can only move game objects with a Kinematic rigid body");

            if (!isTargetMoving() && targetDirection_ != Direction::Unknown) {
                setTargetTile();

                // Prevent target from moving to a tile that results in a collision
                if (handleGridBorderCollision())
                    return;
                else if (target_->isCollidable() && (handleSolidTileCollision() || handleObstacleCollision()))
                    return;

                isMoving_ = true;
                setTargetVelocity();
            } else if (isTargetMoving() && isTargetTileReached(deltaTime)) {
                snapTargetToTargetTile();
                onDestinationReached();
            }
        }
    }

    void GridMover::teleportTargetToDestination() {
        snapTargetToTargetTile();
    }

    void GridMover::snapTargetToTargetTile() {
        isMoving_ = false;
        targetDirection_ = Direction::Unknown;
        tileMap_.removeChildFromTile(prevTile_, target_);
        tileMap_.addChild(target_, targetTile_.getIndex());
        target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
        target_->getRigidBody()->setPosition(targetTile_.getWorldCentre());
    }

    void GridMover::setTargetVelocity() {
        switch (targetDirection_) {
            case Direction::Unknown:
                target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
                break;
            case Direction::Left:
                target_->getRigidBody()->setLinearVelocity({-targetVelocity_.x, 0.0f});
                break;
            case Direction::Right:
                target_->getRigidBody()->setLinearVelocity({targetVelocity_.x, 0.0f});
                break;
            case Direction::Up:
                target_->getRigidBody()->setLinearVelocity({0.0f, -targetVelocity_.y});
                break;
            case Direction::Down:
                target_->getRigidBody()->setLinearVelocity({0.0f, targetVelocity_.y});
                break;
        }
    }

    bool GridMover::handleSolidTileCollision() {
        if (targetTile_.isSolid()) {
            auto hitTile = targetTile_;
            targetTile_ = prevTile_;
            targetDirection_ = Direction::Unknown;
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
            eventEmitter_.emit("solidTileCollision", hitTile);
            return true;
        }
        return false;
    }

    bool GridMover::handleObstacleCollision() {
        if (auto [found, obstacle] = targetTileHasObstacle(); found) {
            targetTile_ = prevTile_;
            targetDirection_ = Direction::Unknown;
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
            eventEmitter_.emit("obstacleCollision", target_, obstacle);
            return true;
        }
        return false;
    }

    std::pair<bool, GameObject::sharedPtr> GridMover::targetTileHasObstacle() {
        GameObject::sharedPtr obstacle;
        tileMap_.forEachChildInTile(targetTile_, [&obstacle, this](GameObject::sharedPtr child) {
            if (child->getType() == GameObject::Type::Obstacle && child->isCollidable() && child != target_) {
                obstacle = child;
                return;
            }
        });
        return {obstacle != nullptr, std::move(obstacle)};
    }

    bool GridMover::handleGridBorderCollision() {
        //A tile outside the grid bounds has the index {-1, -1}
        if (targetTile_.getIndex().row < 0 || targetTile_.getIndex().colm < 0) {
            targetTile_ = prevTile_;
            targetDirection_ = Direction::Unknown;
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
            eventEmitter_.emit("gridBorderCollision");
            return true;
        }
        return false;
    }

    bool GridMover::isTargetTileReached(Time deltaTime) {
        if (targetDirection_ == Direction::Left || targetDirection_ == Direction::Right) {
            auto horizontalDistToTarget = std::abs(targetTile_.getWorldCentre().x - target_->getRigidBody()->getPosition().x);
            if (targetVelocity_.x * deltaTime.asSeconds() >= horizontalDistToTarget)
                return true;
        } else if (targetDirection_ == Direction::Up || targetDirection_ == Direction::Down) {
            auto verticalDistToTarget = std::abs(targetTile_.getWorldCentre().y - target_->getRigidBody()->getPosition().y);
            if (targetVelocity_.y * deltaTime.asSeconds() >= verticalDistToTarget)
                return true;
        }
        return false;
    }

    void GridMover::onDestinationReached() {
        tileMap_.forEachChildInTile(targetTile_, [this](GameObject::sharedPtr gameObject) {
            if (target_->isCollidable() && gameObject->isCollidable()) {
                switch (gameObject->getType()) {
                    case GameObject::Type::Player:
                        eventEmitter_.emit("playerCollision", target_, gameObject);
                        break;
                    case GameObject::Type::Enemy:
                        eventEmitter_.emit("enemyCollision", target_, gameObject);
                        break;
                    case GameObject::Type::Collectable:
                        eventEmitter_.emit("collectableCollision", target_, gameObject);
                        break;
                    default:
                        break;
                }
            }
        });
        eventEmitter_.emit("adjacentTileReached", targetTile_);
    }

    void GridMover::setTargetTile() {
        prevTile_ = targetTile_;
        switch (targetDirection_) {
            case Direction::Left:
                targetTile_ = tileMap_.getTileLeftOf(targetTile_);
                break;
            case Direction::Right:
                targetTile_ = tileMap_.getTileRightOf(targetTile_);
                break;
            case Direction::Up:
                targetTile_ = tileMap_.getTileAbove(targetTile_);
                break;
            case Direction::Down:
                targetTile_ = tileMap_.getTileBelow(targetTile_);
                break;
            case Direction::Unknown:
                return;
        }
    }

    int GridMover::onTargetChanged(Callback<GameObject::sharedPtr> callback) {
        return eventEmitter_.addEventListener("targetChange", std::move(callback));
    }

    int GridMover::onSolidTileCollision(Callback<Tile> callback) {
        return eventEmitter_.addEventListener("solidTileCollision", std::move(callback));
    }

    int GridMover::onGridBorderCollision(Callback<> callback) {
        return eventEmitter_.addEventListener("gridBorderCollision", std::move(callback));
    }

    int GridMover::onAdjacentTileReached(Callback<Tile> callback) {
        return eventEmitter_.addEventListener("adjacentTileReached", std::move(callback));
    }

    int GridMover::onObstacleCollision(Callback<GameObject::sharedPtr, GameObject::sharedPtr> callback) {
        return eventEmitter_.addEventListener("obstacleCollision", std::move(callback));
    }

    int GridMover::onCollectableCollision(Callback<GameObject::sharedPtr, GameObject::sharedPtr> callback) {
        return eventEmitter_.addEventListener("collectableCollision", std::move(callback));
    }

    int GridMover::onEnemyCollision(Callback<GameObject::sharedPtr, GameObject::sharedPtr> callback) {
        return eventEmitter_.addEventListener("enemyCollision", std::move(callback));
    }

    int GridMover::onPlayerCollision(Callback<GameObject::sharedPtr, GameObject::sharedPtr> callback) {
        return eventEmitter_.addEventListener("playerCollision", std::move(callback));
    }

    bool GridMover::removeCollisionHandler(int handlerId) {
        if (eventEmitter_.removeEventListener("playerCollision", handlerId)
            || eventEmitter_.removeEventListener("enemyCollision", handlerId)
            || eventEmitter_.removeEventListener("collectableCollision", handlerId)
            || eventEmitter_.removeEventListener("obstacleCollision", handlerId)
            || eventEmitter_.removeEventListener("adjacentTileReached", handlerId)
            || eventEmitter_.removeEventListener("solidTileCollision", handlerId)
            || eventEmitter_.removeEventListener("gridBorderCollision", handlerId))
        {
            return true;
        }
        return false;
    }

    void GridMover::resetTargetTile() {
        if (target_ && !isTargetMoving() && targetTile_.getIndex()
            != tileMap_.getTileOccupiedByChild(target_).getIndex())
        {
            targetTile_ = tileMap_.getTileOccupiedByChild(target_);
            eventEmitter_.emit("targetTileReset", targetTile_);
        }
    }

    void GridMover::onTargetTileReset(Callback<Tile> callback) {
        eventEmitter_.addEventListener("targetTileReset", callback);
    }

    bool GridMover::removeEventListener(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }
}
