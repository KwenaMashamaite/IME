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
#include "IME/utility/Helpers.h"
#include <string_view>

using namespace std::string_literals;

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
        targetDestructionId_{-1},
        isInternalHandler_{false}
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
            IME_ASSERT(!target->hasRigidBody(), "Game objects controlled by a grid mover must not have a rigid body attached to them")
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

            if (moveRestrict_ == MoveRestriction::None || moveRestrict_ == MoveRestriction::Diagonal) {
                IME_ASSERT(maxSpeed_.x == maxSpeed_.y, "Cannot have different x and y linear speeds if target can move diagonally")
            }

            prevTile_ = targetTile_ = &tileMap_.getTile(target->getTransform().getPosition());
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

    void GridMover::setMaxLinearSpeed(const Vector2f& speed) {
        if (maxSpeed_.x == std::abs(speed.x) && maxSpeed_.y == std::abs(speed.y))
            return;

        if (moveRestrict_ == MoveRestriction::None || moveRestrict_ == MoveRestriction::Diagonal) {
            IME_ASSERT(maxSpeed_.x == maxSpeed_.y, "Cannot have different x and y linear speeds if target can move diagonally")
        }

        maxSpeed_ = {std::abs(speed.x), std::abs(speed.y)};
        emitChange(Property{"maxLinearSpeed", speed});
    }

    const Vector2f& GridMover::getMaxLinearSpeed() const {
        return maxSpeed_;
    }

    void GridMover::setMovementRestriction(GridMover::MoveRestriction moveRestriction) {
        if (moveRestrict_ == moveRestriction)
            return;

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

            emitChange(Property{"movementFreeze", isMoveFrozen_});
        }
    }

    bool GridMover::isMovementFrozen() const {
        return isMoveFrozen_;
    }

    Index GridMover::getTargetTileIndex() const {
        return targetTile_->getIndex();
    }

    Index GridMover::getCurrentTileIndex() const {
        return targetTile_->getIndex();
    }

    Index GridMover::getPrevTileIndex() const {
        return prevTile_->getIndex();
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

    Direction GridMover::getPrevDirection() const {
        return prevDirection_;
    }

    std::pair<bool, GameObject*> GridMover::isBlockedInDirection(const Direction &dir) const {
        IME_ASSERT(dir.x >= -1 && dir.x <= 1, "Invalid x direction, value must be -1, 0, or 1")
        IME_ASSERT(dir.y >= -1 && dir.y <= 1, "Invalid y Direction, value must be -1, 0, or 1")
        IME_ASSERT(!(dir.x == 0 && dir.y == 0), "Invalid direction, at least one value must be -1 or 1")

        auto [row, colm] = targetTile_->getIndex();
        if (tileMap_.isIndexValid(Index{row + dir.y, colm + dir.x})) {
            const Tile& adjacentTile = tileMap_.getTile(Index{row + dir.y, colm + dir.x});
            if (!adjacentTile.isCollidable()) {
                GameObject* obstacle = getObstacleInTile(adjacentTile);

                if (obstacle && canCollide(obstacle))
                    return {true, obstacle};
                else
                    return {false, nullptr};
            }
        }

        return {true, nullptr};
    }

    void GridMover::update(Time deltaTime) {
        if (target_ && !isMoveFrozen_) {
            IME_ASSERT(tileMap_.hasChild(target_), "Target removed from the grid while still controlled by a grid mover")
            IME_ASSERT(!target_->hasRigidBody(), "Game objects controlled by a grid mover must not have a rigid body attached to them")

            if (!isMoving_ && targetDirection_ != Unknown && maxSpeed_ != Vector2f{0.0f, 0.0f}) {
                setTargetTile();

                if (handleGridBorderCollision() || handleSolidTileCollision() || handleObstacleCollision())
                    return;

                prevDirection_ = currentDirection_;
                currentDirection_ = targetDirection_;
                isMoving_ = true;

                // Move target to target tile ahead of time
                tileMap_.removeChildFromTile(*prevTile_, target_);
                auto currentPosition = target_->getTransform().getPosition();
                tileMap_.addChild(target_, targetTile_->getIndex());

                // TileMap::addChild modifies the position of the target such that it's at
                // the centre of the tile, however we don't want it to teleport, we want it
                // to smoothly move there
                target_->getTransform().setPosition(currentPosition);

                internalEmitter_.emit("adjacentMoveBegin", targetTile_->getIndex());
                externalEmitter_.emit("adjacentMoveBegin", targetTile_->getIndex());
            } else if (isMoving_) {
                if (isTargetTileReached(deltaTime)) {
                    snapTargetToTargetTile();
                    onDestinationReached();
                } else {
                    target_->getTransform().move({(maxSpeed_.x * targetDirection_.x) * deltaTime.asSeconds(), (maxSpeed_.y * targetDirection_.y) * deltaTime.asSeconds()});
                }
            }
        }
    }

    void GridMover::teleportTargetToDestination() {
        snapTargetToTargetTile();
    }

    void GridMover::snapTargetToTargetTile() {
        isMoving_ = false;
        targetDirection_ = Unknown;
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

    bool GridMover::canCollide(GameObject* other) const {
        // Prevent Self collision
        if (other == target_)
            return false;

        // Inactive objects do not collide (collision filtering by inactivity)
        if (!(target_->isActive() && other->isActive()))
            return false;

        // Objects in excluded collision group do not collide (Collision filtering by group)
        if ((target_->getCollisionExcludeList().contains(other->getCollisionGroup())) ||
            (other->getCollisionExcludeList().contains(target_->getCollisionGroup())))
        {
            return false;
        }

        // Objects with different collision id's do not collide (collision filtering by id)
        if (target_->getCollisionId() != other->getCollisionId())
            return false;

        // Satisfies collision requirement
        return true;
    }

    bool GridMover::removeEventListener(const std::string &name, int id) {
        if (externalEmitter_.removeEventListener(name, id))
            return true;
        else
            return internalEmitter_.removeEventListener(name, id);
    }

    bool GridMover::handleSolidTileCollision() {
        if (target_->isActive() && targetTile_->isCollidable()) {
            auto hitTile = targetTile_;
            targetTile_ = prevTile_;
            targetDirection_ = Unknown;
            internalEmitter_.emit("solidTileCollision", hitTile->getIndex());
            externalEmitter_.emit("solidTileCollision", hitTile->getIndex());
            return true;
        }
        return false;
    }

    bool GridMover::handleObstacleCollision() {
        GameObject* obstacle = getObstacleInTile(*targetTile_);

        if (obstacle && canCollide(obstacle)) {
            targetTile_ = prevTile_;
            targetDirection_ = Unknown;
            internalEmitter_.emit("gameObjectCollision", target_, obstacle);
            externalEmitter_.emit("gameObjectCollision", target_, obstacle);

            target_->emitCollisionEvent(obstacle);
            obstacle->emitCollisionEvent(target_);

            return true;
        }

        return false;
    }

    GameObject* GridMover::getObstacleInTile(const Tile& tile) const {
        GameObject* obstacle = nullptr;
        tileMap_.forEachChildInTile(tile, [&obstacle, this](GameObject* child) {
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
            internalEmitter_.emit("gridBorderCollision");
            externalEmitter_.emit("gridBorderCollision");
            return true;
        }
        return false;
    }

    bool GridMover::isTargetTileReached(Time deltaTime) {
        auto distanceToTile = target_->getTransform().getPosition().distanceTo(targetTile_->getWorldCentre());
        auto distanceMoved = maxSpeed_ * deltaTime.asSeconds();

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
            if (!canCollide(gameObject))
                return;

            internalEmitter_.emit("gameObjectCollision", target_, gameObject);
            externalEmitter_.emit("gameObjectCollision", target_, gameObject);

            target_->emitCollisionEvent(gameObject);
            gameObject->emitCollisionEvent(target_);
        });

        internalEmitter_.emit("adjacentMoveEnd", targetTile_->getIndex());
        externalEmitter_.emit("adjacentMoveEnd", targetTile_->getIndex());
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

    int GridMover::onTileCollision(const Callback<Index>& callback, bool oneTime) {
        return utility::addEventListener(isInternalHandler_ ? internalEmitter_ : externalEmitter_, "solidTileCollision", callback, oneTime);
    }

    int GridMover::onGameObjectCollision(const GridMover::CollisionCallback &callback, bool oneTime) {
        return utility::addEventListener(isInternalHandler_ ? internalEmitter_ : externalEmitter_, "gameObjectCollision", callback, oneTime);
    }

    int GridMover::onGridBorderCollision(const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(isInternalHandler_ ? internalEmitter_ : externalEmitter_, "gridBorderCollision", callback, oneTime);
    }

    int GridMover::onAdjacentMoveBegin(const Callback<Index>& callback, bool oneTime) {
        return utility::addEventListener(isInternalHandler_ ? internalEmitter_ : externalEmitter_, "adjacentMoveBegin", callback, oneTime);
    }

    int GridMover::onAdjacentMoveEnd(const Callback<Index>& callback, bool oneTime) {
        return utility::addEventListener(isInternalHandler_ ? internalEmitter_ : externalEmitter_, "adjacentMoveEnd", callback, oneTime);
    }

    bool GridMover::unsubscribe(int handlerId) {
        if (removeEventListener("gameObjectCollision", handlerId) ||
            (removeEventListener("adjacentMoveBegin", handlerId)) ||
            (removeEventListener("adjacentMoveEnd", handlerId)) ||
            (removeEventListener("targetTileReset", handlerId)) ||
            (removeEventListener("solidTileCollision", handlerId)) ||
            (removeEventListener("gridBorderCollision", handlerId)))
        {
            return true;
        }

        return false;
    }

    void GridMover::removeAllEventListeners() {
        externalEmitter_.removeAllEventListeners("gameObjectCollision");
        externalEmitter_.removeAllEventListeners("adjacentMoveBegin");
        externalEmitter_.removeAllEventListeners("adjacentMoveEnd");
        externalEmitter_.removeAllEventListeners("targetTileReset");
        externalEmitter_.removeAllEventListeners("solidTileCollision");
        externalEmitter_.removeAllEventListeners("gridBorderCollision");
    }

    void GridMover::copyExternEventListeners(const GridMover &other) {
        externalEmitter_ = other.externalEmitter_;
    }

    void GridMover::resetTargetTile() {
        if (target_ && !isTargetMoving() && targetTile_->getIndex()
            != tileMap_.getTileOccupiedByChild(target_).getIndex())
        {
            targetTile_ = &tileMap_.getTileOccupiedByChild(target_);
            internalEmitter_.emit("targetTileReset", targetTile_);
            externalEmitter_.emit("targetTileReset", targetTile_);
        }
    }

    int GridMover::onTargetTileReset(const Callback<Index>& callback, bool oneTime) {
        return utility::addEventListener(isInternalHandler_ ? internalEmitter_ : externalEmitter_, "targetTileReset", callback, oneTime);
    }

    void GridMover::setHandlerIntakeAsInternal(bool internal) {
        isInternalHandler_ = internal;
    }

    GridMover::~GridMover() {
        if (targetDestructionId_ != -1 && target_)
            target_->removeDestructionListener(targetDestructionId_);

        target_ = nullptr;
        prevTile_ = nullptr;
        targetTile_ = nullptr;
    }
}
