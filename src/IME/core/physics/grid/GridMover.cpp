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

#include "IME/core/physics/grid/GridMover.h"

namespace ime {
    namespace {
        bool isSupportedDirection(const Direction& dir) {
            return dir == Left || dir == UpLeft || dir == Up || dir == UpRight
                || dir == Right ||dir == DownRight || dir == Down || dir == DownLeft;
        }
    }

    GridMover::GridMover(Type type, TileMap &tileMap, GameObject* target) :
        type_{type},
        tileMap_(tileMap),
        target_{nullptr},
        maxSpeed_{Vector2f {0, 0}},
        targetDirection_{Unknown},
        targetTile_{nullptr},
        prevTile_{nullptr},
        isMoving_{false},
        isMoveFrozen_{false},
        moveRestrict_{MoveRestriction::None},
        targetDestructionId_{-1}
    {
        setTarget(target);
    }

    GridMover::GridMover(TileMap& tilemap, GameObject* gameObject) :
        GridMover(Type::Manual, tilemap, gameObject)
    {}

    std::string GridMover::getClassType() const {
        return "GridMover";
    }

    std::string GridMover::getClassName() const {
        return "GridMover";
    }

    void GridMover::setTarget(GameObject* target) {
        if (target_ == target)
            return;
        else if (target) {
            IME_ASSERT(target->hasRigidBody(), "Game objects controlled by a grid mover must have a rigid body attached to them")
            IME_ASSERT(target->getRigidBody()->getType() == RigidBody::Type::Kinematic, "A grid mover can only control game objects with a ime::RigidBody::Type::Kinematic rigid body")
            IME_ASSERT(tileMap_.hasChild(target), "The game object must already be in the grid/tilemap before adding it to a grid mover")

            if (target_) {
                target_->removeDestructionListener(targetDestructionId_);
                targetDestructionId_ = -1;
                teleportTargetToDestination();
            }

            targetDestructionId_ = target->onDestruction([this] {
                setTarget(nullptr);
                targetDestructionId_ = -1;
            });

            auto velocity = target->getRigidBody()->getLinearVelocity();
            maxSpeed_ = {std::abs(velocity.x), std::abs(velocity.y)};

            if (moveRestrict_ == MoveRestriction::None || moveRestrict_ == MoveRestriction::Diagonal) {
                IME_ASSERT(maxSpeed_.x == maxSpeed_.y, "Cannot have different x and y linear speeds if target can move diagonally")
            }

            target->getRigidBody()->setLinearVelocity({0, 0});
            targetTile_ = &tileMap_.getTile(target->getTransform().getPosition());
            target_ = target;
        } else
            target_ = target;

        emitChange(Property{"target", target_});
    }

    GridMover::Type GridMover::getType() const {
        return type_;
    }

    GameObject* GridMover::getTarget() const {
        return target_;
    }

    void GridMover::setMaxLinearSpeed(Vector2f speed) {
        if (moveRestrict_ == MoveRestriction::None || moveRestrict_ == MoveRestriction::Diagonal) {
            IME_ASSERT(maxSpeed_.x == maxSpeed_.y, "Cannot have different x and y linear speeds if target can move diagonally")
        }

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

        if (moveRestriction == MoveRestriction::None || moveRestriction == MoveRestriction::Diagonal) {
            IME_ASSERT(maxSpeed_.x == maxSpeed_.y, "Cannot have different x and y linear speeds if target can move diagonally")
        }

        moveRestrict_ = moveRestriction;
        emitChange(Property{"movementRestriction", moveRestrict_});
    }

    GridMover::MoveRestriction GridMover::getMovementRestriction() const {
        return moveRestrict_;
    }

    void GridMover::setMovementFreeze(bool freeze) {
        if (isMoveFrozen_ != freeze) {
            isMoveFrozen_ = freeze;
            if (!isMoveFrozen_ && isMoving_)
                target_->getRigidBody()->setLinearVelocity({maxSpeed_.x * targetDirection_.x, maxSpeed_.y * targetDirection_.y});
            else
                target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});

            emitChange(Property{"movementFreeze", isMoveFrozen_});
        }
    }

    bool GridMover::isMovementFrozen() const {
        return isMoveFrozen_;
    }

    Index GridMover::getTargetTileIndex() const {
        return targetTile_->getIndex();
    }

    TileMap &GridMover::getGrid() {
        return tileMap_;
    }

    const TileMap &GridMover::getGrid() const {
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
        if (target_ && !isMoveFrozen_) {
            IME_ASSERT(tileMap_.hasChild(target_), "Target removed from the grid while still controlled by a grid mover")
            IME_ASSERT(target_->hasRigidBody(), "The targets rigid body was removed while it was still controlled by a grid mover")
            IME_ASSERT(target_->getRigidBody()->getType() == RigidBody::Type::Kinematic, "The targets rigid body was changed from ime::RigidBody::Type::Kinematic, a grid mover can only move game objects with a Kinematic rigid body")

            if (!isTargetMoving() && targetDirection_ != Unknown) {
                setTargetTile();

                if (handleGridBorderCollision() || (target_->isActive() && (handleSolidTileCollision() || handleObstacleCollision())))
                    return;

                currentDirection_ = targetDirection_;
                isMoving_ = true;
                target_->getRigidBody()->setLinearVelocity({maxSpeed_.x * targetDirection_.x, maxSpeed_.y * targetDirection_.y});

                // Move target to target tile ahead of time
                tileMap_.removeChildFromTile(*prevTile_, target_);
                auto currentPosition = target_->getTransform().getPosition();
                tileMap_.addChild(target_, targetTile_->getIndex());

                // TileMap::addChild modifies the position of the target such that it's at
                // the centre of the tile, however we don't want it to teleport, we want it
                // to smoothly move there
                target_->getTransform().setPosition(currentPosition);

                eventEmitter_.emit("adjacentMoveBegin", targetTile_->getIndex());
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
        target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
        target_->getTransform().setPosition(targetTile_->getWorldCentre());
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
                    return false;
                case MoveRestriction::Vertical:
                    if (targetDir != Up && targetDir != Down)
                        return false;
                    break;
                case MoveRestriction::Horizontal:
                    if (targetDir != Left && targetDir != Right)
                        return false;
                    break;
                case MoveRestriction::Diagonal:
                    if (abs(targetDir.x) != 1 || abs(targetDir.y) != 1)
                        return false;
                    break;
                case MoveRestriction::NonDiagonal:
                    if (abs(targetDir.x) == 1 && abs(targetDir.y) == 1)
                        return false;
                    break;
                default:
                    return false;
            }
        }

        return true;
    }

    bool GridMover::handleSolidTileCollision() {
        if (targetTile_->isCollidable()) {
            auto hitTile = targetTile_;
            targetTile_ = prevTile_;
            targetDirection_ = Unknown;
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
            eventEmitter_.emit("solidTileCollision", hitTile->getIndex());
            return true;
        }
        return false;
    }

    bool GridMover::handleObstacleCollision() {
        if (GameObject* obstacle = getObstacleInTargetTile(); obstacle) {
            targetTile_ = prevTile_;
            targetDirection_ = Unknown;
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
            eventEmitter_.emit("gameObjectCollision", target_, obstacle);
            return true;
        }
        return false;
    }

    GameObject* GridMover::getObstacleInTargetTile() {
        GameObject* obstacle = nullptr;
        tileMap_.forEachChildInTile(*targetTile_, [&obstacle, this](GameObject* child) {
            if (child->isObstacle() && child->isActive() && child != target_) {
                obstacle = child;
                return;
            }
        });
        return obstacle;
    }

    bool GridMover::handleGridBorderCollision() {
        //A tile outside the grid bounds has the index {-1, -1}
        if (targetTile_->getIndex().row < 0 || targetTile_->getIndex().colm < 0) {
            targetTile_ = prevTile_;
            targetDirection_ = Unknown;
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});
            eventEmitter_.emit("gridBorderCollision");
            return true;
        }
        return false;
    }

    bool GridMover::isTargetTileReached(Time deltaTime) {
        auto distanceToTile = target_->getTransform().getPosition().distanceTo(targetTile_->getWorldCentre());
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
        // Collide target with occupants of target tile
        tileMap_.forEachChildInTile(*targetTile_, [this](GameObject* gameObject) {
            // Prevent Self collision
            if (gameObject == target_)
                return;

            // Inactive objects do not collide (collision filtering by inactivity)
            if (!(target_->isActive() && gameObject->isActive()))
                return;

            // Objects in excluded collision group do not collide (Collision filtering by group)
            if ((target_->getCollisionExcludeList().contains(gameObject->getCollisionGroup())) ||
                (gameObject->getCollisionExcludeList().contains(target_->getCollisionGroup())))
            {
                return;
            }

            // Objects with different collision id's do not collide (collision filtering by id)
            if (!(target_->getCollisionId() == gameObject->getCollisionId()))
                return;

            // Satisfied collision criteria, invoke collision handler
            eventEmitter_.emit("gameObjectCollision", target_, gameObject);
        });

        eventEmitter_.emit("adjacentMoveEnd", targetTile_->getIndex());
    }

    void GridMover::setTargetTile() {
        prevTile_ = targetTile_;
        if (targetDirection_ == Left)
            targetTile_ = &tileMap_.getTileLeftOf(*targetTile_);
        else if (targetDirection_ == UpLeft)
            targetTile_ = &tileMap_.getTileAbove(tileMap_.getTileLeftOf(*targetTile_));
        else if (targetDirection_ == Up)
            targetTile_ = &tileMap_.getTileAbove(*targetTile_);
        else if (targetDirection_ == UpRight)
            targetTile_ = &tileMap_.getTileAbove(tileMap_.getTileRightOf(*targetTile_));
        else if (targetDirection_ == Right)
            targetTile_ = &tileMap_.getTileRightOf(*targetTile_);
        else if (targetDirection_ == DownRight)
            targetTile_ = &tileMap_.getTileBelow(tileMap_.getTileRightOf(*targetTile_));
        else if (targetDirection_ == Down)
            targetTile_ = &tileMap_.getTileBelow(*targetTile_);
        else if (targetDirection_ == DownLeft)
            targetTile_ = &tileMap_.getTileBelow(tileMap_.getTileLeftOf(*targetTile_));
    }

    int GridMover::onTileCollision(const Callback<Index>& callback) {
        return eventEmitter_.addEventListener("solidTileCollision", callback);
    }

    int GridMover::onGameObjectCollision(const GridMover::CollisionCallback &callback) {
        return eventEmitter_.addEventListener("gameObjectCollision", callback);
    }

    int GridMover::onGridBorderCollision(const Callback<>& callback) {
        return eventEmitter_.addEventListener("gridBorderCollision", callback);
    }

    int GridMover::onAdjacentMoveBegin(const Callback<Index>& callback) {
        return eventEmitter_.addEventListener("adjacentMoveBegin", callback);
    }

    int GridMover::onAdjacentMoveEnd(const Callback<Index>& callback) {
        return eventEmitter_.addEventListener("adjacentMoveEnd", callback);
    }

    bool GridMover::unsubscribe(int handlerId) {
        if (eventEmitter_.removeEventListener("gameObjectCollision", handlerId)
            || eventEmitter_.removeEventListener("adjacentMoveBegin", handlerId)
            || eventEmitter_.removeEventListener("adjacentMoveEnd", handlerId)
            || eventEmitter_.removeEventListener("targetTileReset", handlerId)
            || eventEmitter_.removeEventListener("solidTileCollision", handlerId)
            || eventEmitter_.removeEventListener("gridBorderCollision", handlerId))
        {
            return true;
        }
        return false;
    }

    void GridMover::resetTargetTile() {
        if (target_ && !isTargetMoving() && targetTile_->getIndex()
            != tileMap_.getTileOccupiedByChild(target_).getIndex())
        {
            targetTile_ = &tileMap_.getTileOccupiedByChild(target_);
            eventEmitter_.emit("targetTileReset", targetTile_);
        }
    }

    int GridMover::onTargetTileReset(const Callback<Index>& callback) {
        return eventEmitter_.addEventListener("targetTileReset", callback);
    }

    GridMover::~GridMover() {
        if (targetDestructionId_ != -1 && target_)
            target_->removeDestructionListener(targetDestructionId_);

        if (target_ && target_->getRigidBody())
            target_->getRigidBody()->setLinearVelocity({0.0f, 0.0f});

        target_ = nullptr;
        prevTile_ = nullptr;
        targetTile_ = nullptr;
    }
}
