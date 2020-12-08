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

#include "IME/core/physics/GridMover.h"
#include "IME/core/entity/IMovable.h"
#include <cassert>

namespace IME {
    GridMover::GridMover(TileMap &tileMap, std::shared_ptr<Entity> target) :
        tileMap_(tileMap),
        target_(target),
        targetDirection_(Direction::None),
        targetTile_{tileMap.getTileSize(), {0, 0}},
        prevTile_({tileMap.getTileSize(), {}}),
        reachedTarget_(false)
    {
        if (target) {
            assert(std::dynamic_pointer_cast<IMovable>(target) && "Provided entity is not movable (derived from IMovable)");
            assert(tileMap_.hasChild(target) && "Target must already be in the grid before instantiating a grid mover");
            targetTile_ = tileMap.getTile(target->getPosition());
        }

        obstacleCollisionHandler_ = [this] {
            targetTile_ = prevTile_;
            targetDirection_ = Direction::None;
        };

        solidTileCollisionHandler_ = [this] {
            auto hitTile = targetTile_;
            targetTile_ = prevTile_;
            targetDirection_ = Direction::None;
            eventEmitter_.emit("solidTileCollision", hitTile);
        };
    }

    void GridMover::setTarget(GridMover::EntityPtr target) {
        if (target_ == target)
            return;
        else if (target) {
            assert(std::dynamic_pointer_cast<IMovable>(target) && "Provided entity is not movable (derived from IMovable)");
            assert(tileMap_.hasChild(target) && "Target must already be in the grid before calling setTarget()");
            if (target_)
                teleportTargetToDestination();
            targetTile_ = tileMap_.getTile(target->getPosition());
            target_ = std::move(target);
        }
    }

    GridMover::EntityPtr GridMover::getTarget() const {
        return target_;
    }

    TileMap &GridMover::getGrid() {
        return tileMap_;
    }

    bool GridMover::isTargetMoving() const {
        auto target = std::dynamic_pointer_cast<IMovable>(target_);
        if (target)
            return target->isMoving();
        return false;
    }

    bool GridMover::requestDirectionChange(Direction newDir) {
        auto movableObj = std::dynamic_pointer_cast<IMovable>(target_);
        if (movableObj && !movableObj->isMoving()) {
            switch (newDir) {
                case Direction::None:
                    target_->setDirection(Direction::None);
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

    void GridMover::update(float deltaTime) {
        if (target_) {
            assert(tileMap_.hasChild(target_) && "Target removed from the grid while still controlled by a grid mover");
            auto movable = std::dynamic_pointer_cast<IMovable>(target_);
            if (!movable->isMoving() && targetDirection_ != Direction::None) {
                setTargetTile();

                // Stop further execution if a collision will occur if we move
                if (handleGridBorderCollision())
                    return;
                else if (handleSolidTileCollision())
                    return;
                else if (auto [found, obstacle] = targetTileHasObstacle(); found) {
                    if (obstacleCollisionHandler_) {
                        obstacleCollisionHandler_();
                        eventEmitter_.emit("obstacleCollision", target_, obstacle);
                        return;
                    }
                    eventEmitter_.emit("obstacleCollision", target_, obstacle);
                }

                movable->move();
            } else if (movable->isMoving()) {
                if (targetDirection_ == Direction::Left || targetDirection_ == Direction::Right) {
                    auto horizontalDistToTarget = std::abs(targetTile_.getPosition().x - target_->getPosition().x);
                    if (movable->getSpeed() * deltaTime >= horizontalDistToTarget)
                        snapTargetToTargetTile();
                }

                if (targetDirection_ == Direction::Up || targetDirection_ == Direction::Down) {
                    auto verticalDistToTarget = std::abs(targetTile_.getPosition().y - target_->getPosition().y);
                    if (movable->getSpeed() * deltaTime >= verticalDistToTarget)
                        snapTargetToTargetTile();
                }

                if (reachedTarget_) {
                    reachedTarget_ = false;
                    onDestinationReached();
                }
            }
        }
    }

    void GridMover::teleportTargetToDestination() {
        snapTargetToTargetTile();
    }

    void GridMover::snapTargetToTargetTile() {
        if (target_ && target_->getPosition() != targetTile_.getPosition()) {
            std::dynamic_pointer_cast<IMovable>(target_)->stop();
            tileMap_.removeChildFromTile(prevTile_, target_);
            tileMap_.addChild(target_, targetTile_.getIndex());
            targetDirection_ = Direction::None;
            reachedTarget_ = true;
        }
    }

    bool GridMover::handleSolidTileCollision() {
        if (targetTile_.isSolid() && target_->isCollidable()) {
            if (solidTileCollisionHandler_) {
                solidTileCollisionHandler_();
                return true;
            }
            eventEmitter_.emit("solidTileCollision", targetTile_);
        }
        return false;
    }

    std::pair<bool, std::shared_ptr<Entity>> GridMover::targetTileHasObstacle() {
        EntityPtr obstacle;
        tileMap_.forEachChildInTile(targetTile_, [&](EntityPtr child) {
            if (child->getType() == Entity::Type::Obstacle && child->isCollidable()) {
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
            targetDirection_ = Direction::None;
            eventEmitter_.emit("gridBorderCollision");
            return true;
        }
        return false;
    }

    void GridMover::onDestinationReached() {
        tileMap_.forEachChildInTile(targetTile_, [this](EntityPtr entity) {
            if (target_->isCollidable() && entity->isCollidable()) {
                switch (entity->getType()) {
                    case Entity::Type::Unknown:
                        break;
                    case Entity::Type::Player:
                        eventEmitter_.emit("playerCollision", target_, entity);
                        break;
                    case Entity::Type::Enemy:
                        eventEmitter_.emit("enemyCollision", target_, entity);
                        break;
                    case Entity::Type::Collectable:
                        eventEmitter_.emit("collectableCollision", target_, entity);
                        break;
                    case Entity::Type::Obstacle:
                        break;
                }
            }
        });
        eventEmitter_.emit("adjacentTileReached", targetTile_);
    }

    void GridMover::setTargetTile() {
        prevTile_ = tileMap_.getTile(target_->getPosition());
        switch (targetDirection_) {
            case Direction::Left:
                targetTile_ = tileMap_.getTileLeftOf(prevTile_);
                break;
            case Direction::Right:
                targetTile_ = tileMap_.getTileRightOf(prevTile_);
                break;
            case Direction::Up:
                targetTile_ = tileMap_.getTileAbove(prevTile_);
                break;
            case Direction::Down:
                targetTile_ = tileMap_.getTileBelow(prevTile_);
                break;
            case Direction::None:
                return;
        }
    }

    int GridMover::onTargetChanged(Callback<GridMover::EntityPtr> callback) {
        return eventEmitter_.addEventListener("targetChange", std::move(callback));
    }

    int GridMover::onSolidTileCollision(Callback<Graphics::Tile> callback) {
        return eventEmitter_.addEventListener("solidTileCollision", std::move(callback));
    }

    int GridMover::onGridBorderCollision(Callback<> callback) {
        return eventEmitter_.addEventListener("gridBorderCollision", std::move(callback));
    }

    int GridMover::onAdjacentTileReached(Callback<Graphics::Tile> callback) {
        return eventEmitter_.addEventListener("adjacentTileReached", std::move(callback));
    }

    int GridMover::onObstacleCollision(Callback<EntityPtr, EntityPtr> callback) {
        return eventEmitter_.addEventListener("obstacleCollision", std::move(callback));
    }

    int GridMover::onCollectableCollision(Callback<EntityPtr, EntityPtr> callback) {
        return eventEmitter_.addEventListener("collectableCollision", std::move(callback));
    }

    int GridMover::onEnemyCollision(Callback<EntityPtr, EntityPtr> callback) {
        return eventEmitter_.addEventListener("enemyCollision", std::move(callback));
    }

    int GridMover::onPlayerCollision(Callback<GridMover::EntityPtr, GridMover::EntityPtr> callback) {
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

    bool GridMover::removeEventListener(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }

    bool GridMover::removeInternalCollisionHandlerFor(const std::string &handler) {
        if (handler == "solidTiles") {
            solidTileCollisionHandler_ = nullptr;
            eventEmitter_.emit("handlerRemoved", handler);
            return true;
        } else if (handler == "obstacles") {
            obstacleCollisionHandler_ = nullptr;
            eventEmitter_.emit("handlerRemoved", handler);
            return true;
        }
        return false;
    }

    bool GridMover::isInternalHandlerRemoved(const std::string &handler) {
        if (handler == "solidTiles") {
            return solidTileCollisionHandler_ == nullptr;
        } else if (handler == "obstacles") {
            return obstacleCollisionHandler_ == nullptr;
        }
        return true;
    }

    void GridMover::onInternalHandlerRemove(Callback<std::string> callback) {
        eventEmitter_.addEventListener("handlerRemoved", std::move(callback));
    }
}
