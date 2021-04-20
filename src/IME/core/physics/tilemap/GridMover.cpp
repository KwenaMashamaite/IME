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
    namespace {
        bool isSupportedDirection(const Direction& dir) {
            return dir == Left || dir == UpLeft || dir == Up || dir == UpRight
                || dir == Right ||dir == DownRight || dir == Down || dir == DownLeft;
        }
    }

    GridMover::GridMover(Type type, TileMap &tileMap, GameObject::Ptr target) :
        type_{type},
        tileMap_(tileMap),
        maxSpeed_{Vector2f {0, 0}},
        targetDirection_{Unknown},
        targetTile_{tileMap.getTileSize(), Vector2f{0, 0}},
        prevTile_{tileMap.getTileSize(), Vector2f{0, 0}},
        isMoving_{false},
        moveRestrict_{MoveRestriction::None}
    {
        setTarget(std::move(target));
    }

    GridMover::GridMover(TileMap& tilemap, GameObject::Ptr gameObject) :
        GridMover(Type::Manual, tilemap, std::move(gameObject))
    {}

    std::string GridMover::getClassType() const {
        return "GridMover";
    }

    void GridMover::setTarget(GameObject::Ptr target) {
        if (target_ == target)
            return;
        else if (target) {
            IME_ASSERT(target->hasRigidBody(), "Game objects controlled by a grid mover must have a rigid body attached to them")
            IME_ASSERT(target->getRigidBody()->getType() == Body::Type::Kinematic, "A grid mover can only control game objects with a Body::Type::Kinematic rigid body")
            IME_ASSERT(tileMap_.hasChild(target), "The game object must already be in the grid/tilemap before adding it to a grid mover")

            if (target_)
                teleportTargetToDestination();

            auto velocity = target->getRigidBody()->getLinearVelocity();
            maxSpeed_ = {std::abs(velocity.x), std::abs(velocity.y)};
            target->getRigidBody()->setLinearVelocity({0, 0});
            targetTile_ = tileMap_.getTile(target->getTransform().getPosition());
            target_ = std::move(target);
        } else
            target_ = target;

        emitChange(Property{"target", target_});
        eventEmitter_.emit("targetChange", target_);
    }

    GridMover::Type GridMover::getType() const {
        return type_;
    }

    GameObject::Ptr GridMover::getTarget() const {
        return target_;
    }

    void GridMover::setMaxLinearSpeed(Vector2f speed) {
        maxSpeed_ = {std::abs(speed.x), std::abs(speed.y)};
        emitChange(Property{"maxLinearSpeed", speed});
    }

    Vector2f GridMover::getMaxLinearSpeed() const {
        return maxSpeed_;
    }

    void GridMover::setMovementRestriction(GridMover::MoveRestriction moveRestriction) {
        if (type_ == Type::Target && !(moveRestriction == MoveRestriction::All || moveRestriction == MoveRestriction::None)) {
            IME_PRINT_WARNING("Cannot set movement restriction for a TargetGridMover, movement depends on path finder algorithm")
            return;
        }

        moveRestrict_ = moveRestriction;
        emitChange(Property{"movementRestriction", moveRestrict_});
    }

    GridMover::MoveRestriction GridMover::getMovementRestriction() const {
        return moveRestrict_;
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

    bool GridMover::requestDirectionChange(const Direction& newDir) {
        IME_ASSERT(target_, "requestDirectionChange called on a grid mover without a target, call setTarget first")

        if (!isMoveValid(newDir))
            return false;

        if (!isTargetMoving() && targetDirection_ == Unknown) {
            targetDirection_ = newDir;
            emitChange(Property{"direction", targetDirection_});
            return true;
        }

        return false;
    }

    Direction GridMover::getDirection() const {
        return currentDirection_;
    }

    void GridMover::update(Time deltaTime) {
        if (target_) {
            IME_ASSERT(tileMap_.hasChild(target_), "Target removed from the grid while still controlled by a grid mover")
            IME_ASSERT(target_->hasRigidBody(), "The targets rigid body was removed while it was still controlled by a grid mover")
            IME_ASSERT(target_->getRigidBody()->getType() == Body::Type::Kinematic, "The targets rigid body was changed from Body::Type::Kinematic, a grid mover can only move game objects with a Kinematic rigid body")

            if (!isTargetMoving() && targetDirection_ != Unknown) {
                setTargetTile();

                if (handleGridBorderCollision() || (target_->isCollidable() && (handleSolidTileCollision() || handleObstacleCollision())))
                    return;

                currentDirection_ = targetDirection_;
                isMoving_ = true;
                auto velocity = Vector2f{maxSpeed_.x * targetDirection_.x,maxSpeed_.y * targetDirection_.y};
                target_->getRigidBody()->setLinearVelocity(velocity);
                eventEmitter_.emit("moveBegin", targetTile_);
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
        targetDirection_ = Unknown;
        tileMap_.removeChildFromTile(prevTile_, target_);
        tileMap_.addChild(target_, targetTile_.getIndex());
        target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
        target_->getRigidBody()->setPosition(targetTile_.getWorldCentre());
    }

    bool GridMover::isMoveValid(Direction targetDir) const {
        if (!isSupportedDirection(targetDir)) {
            IME_PRINT_WARNING("Direction change ignored: Target can only move in these directions: W, NW, N, NE, E, SE, S, SW")
            return false;
        } else {
            switch (moveRestrict_) {
                case MoveRestriction::None:
                    return true;
                case MoveRestriction::All:
                    IME_PRINT_WARNING("Direction change ignored: All movement restricted")
                    return false;
                case MoveRestriction::Vertical:
                    if (targetDir != Up && targetDir != Down) {
                        IME_PRINT_WARNING("Direction change ignored - Target restricted to \"vertical\" movement only")
                        return false;
                    }
                    break;
                case MoveRestriction::Horizontal:
                    if (targetDir != Left && targetDir != Right) {
                        IME_PRINT_WARNING("Direction change ignored - Target restricted to \"horizontal\" movement only")
                        return false;
                    }
                    break;
                case MoveRestriction::Diagonal:
                    if (abs(targetDir.x) != 1 || abs(targetDir.y) != 1) {
                        IME_PRINT_WARNING("Direction change ignored - Target restricted to \"diagonal\" movement only")
                        return false;
                    }
                    break;
                case MoveRestriction::NonDiagonal:
                    if (abs(targetDir.x) == 1 && abs(targetDir.y) == 1) {
                        IME_PRINT_WARNING("Direction change ignored - Target restricted to \"non-diagonal\" movement only")
                        return false;
                    }
                    break;
                default:
                    return false;
            }
        }

        return true;
    }

    bool GridMover::handleSolidTileCollision() {
        if (targetTile_.isCollidable()) {
            auto hitTile = targetTile_;
            targetTile_ = prevTile_;
            targetDirection_ = Unknown;
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
            eventEmitter_.emit("solidTileCollision", hitTile);
            return true;
        }
        return false;
    }

    bool GridMover::handleObstacleCollision() {
        if (auto [found, obstacle] = targetTileHasObstacle(); found) {
            targetTile_ = prevTile_;
            targetDirection_ = Unknown;
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
            eventEmitter_.emit("obstacleCollision", target_, obstacle);
            return true;
        }
        return false;
    }

    std::pair<bool, GameObject::Ptr> GridMover::targetTileHasObstacle() {
        GameObject::Ptr obstacle;
        tileMap_.forEachChildInTile(targetTile_, [&obstacle, this](const GameObject::Ptr& child) {
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
            targetDirection_ = Unknown;
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
            eventEmitter_.emit("gridBorderCollision");
            return true;
        }
        return false;
    }

    bool GridMover::isTargetTileReached(Time deltaTime) {
        auto distanceToTile = target_->getTransform().getPosition().distanceTo(targetTile_.getWorldCentre());
        auto distanceMoved = target_->getRigidBody()->getLinearVelocity() * deltaTime.asSeconds();

        // Horizontally movement
        if (targetDirection_.x != 0 && std::fabs(distanceMoved.x) >= distanceToTile) {
            return true;
        }

        // Vertical movement
        if (targetDirection_.y != 0 && std::fabs(distanceMoved.y) >= distanceToTile)
            return true;

        return false;
    }

    void GridMover::onDestinationReached() {
        tileMap_.forEachChildInTile(targetTile_, [this](const GameObject::Ptr& gameObject) {
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
        if (targetDirection_ == Left)
            targetTile_ = tileMap_.getTileLeftOf(targetTile_);
        else if (targetDirection_ == UpLeft)
            targetTile_ = tileMap_.getTileAbove(tileMap_.getTileLeftOf(targetTile_));
        else if (targetDirection_ == Up)
            targetTile_ = tileMap_.getTileAbove(targetTile_);
        else if (targetDirection_ == UpRight)
            targetTile_ = tileMap_.getTileAbove(tileMap_.getTileRightOf(targetTile_));
        else if (targetDirection_ == Right)
            targetTile_ = tileMap_.getTileRightOf(targetTile_);
        else if (targetDirection_ == DownRight)
            targetTile_ = tileMap_.getTileBelow(tileMap_.getTileRightOf(targetTile_));
        else if (targetDirection_ == Down)
            targetTile_ = tileMap_.getTileBelow(targetTile_);
        else if (targetDirection_ == DownLeft)
            targetTile_ = tileMap_.getTileBelow(tileMap_.getTileLeftOf(targetTile_));
    }

    int GridMover::onTargetChanged(Callback<GameObject::Ptr> callback) {
        return eventEmitter_.addEventListener("targetChange", std::move(callback));
    }

    int GridMover::onSolidTileCollision(Callback<Tile> callback) {
        return eventEmitter_.addEventListener("solidTileCollision", std::move(callback));
    }

    int GridMover::onGridBorderCollision(Callback<> callback) {
        return eventEmitter_.addEventListener("gridBorderCollision", std::move(callback));
    }

    int GridMover::onMoveBegin(Callback<Tile> callback) {
        return eventEmitter_.addEventListener("moveBegin", std::move(callback));
    }

    int GridMover::onAdjacentTileReached(Callback<Tile> callback) {
        return eventEmitter_.addEventListener("adjacentTileReached", std::move(callback));
    }

    int GridMover::onObstacleCollision(Callback<GameObject::Ptr, GameObject::Ptr> callback) {
        return eventEmitter_.addEventListener("obstacleCollision", std::move(callback));
    }

    int GridMover::onCollectableCollision(Callback<GameObject::Ptr, GameObject::Ptr> callback) {
        return eventEmitter_.addEventListener("collectableCollision", std::move(callback));
    }

    int GridMover::onEnemyCollision(Callback<GameObject::Ptr, GameObject::Ptr> callback) {
        return eventEmitter_.addEventListener("enemyCollision", std::move(callback));
    }

    int GridMover::onPlayerCollision(Callback<GameObject::Ptr, GameObject::Ptr> callback) {
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
        eventEmitter_.addEventListener("targetTileReset", std::move(callback));
    }

    bool GridMover::removeEventListener(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }
}
