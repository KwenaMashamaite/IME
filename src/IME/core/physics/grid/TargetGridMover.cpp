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

#include "IME/core/physics/grid/TargetGridMover.h"
#include "IME/core/physics/grid/path/BFS.h"
#include "IME/graphics/shapes/RectangleShape.h"
#include "IME/graphics/RenderTarget.h"
#include "IME/utility/Utils.h"

namespace ime {
    TargetGridMover::TargetGridMover(TileMap &tileMap, GameObject* target) :
        GridMover(Type::Target, tileMap, target),
        pathFinder_(std::make_unique<BFS>(tileMap.getSizeInTiles())),
        targetTileIndex_{-1, -1},
        pathColour_{utility::generateRandomColour()},
        renderPath_{false},
        movementStarted_{false},
        targetTileChangedWhileMoving_{false},
        isAdaptiveMoveEnabled_{false},
        isPendingMove_{false}
    {
        IME_ASSERT((tileMap.getSizeInTiles() != Vector2u{0u, 0u}), "A target grid mover must be instantiated with a fully constructed tilemap")

        // Invoke internal event handlers first before raising event externally
        setHandlerIntakeAsInternal(true);

        if (getTarget())
            targetTileIndex_ = getGrid().getTileOccupiedByChild(getTarget()).getIndex();

        setAdaptiveMoveEnable(false);

        onTargetTileReset([this](Index index) {
            targetTileIndex_ = index;
            clearPath();
        });

        onPropertyChange("target", [this](const Property& property) {
            if (property.getValue<GameObject*>() && movementStarted_) {
                generatePath();
                moveTarget();
            }
        });

        // Automatically keep target moving until it reaches its destination
        onAdjacentMoveEnd([this](ime::Index) {
            if (isPendingMove_)
                isPendingMove_ = false;
            else if (isAdaptiveMoveEnabled_)
                generatePath();
            else {
                if (targetTileChangedWhileMoving_) {
                    targetTileChangedWhileMoving_ = false;
                    generatePath();
                }
            }

            moveTarget();
        });

        onTileCollision([this](Index) {
            if (getTarget()) {
                generatePath();
                moveTarget();
            }
        });

        onGameObjectCollision([this](GameObject*, GameObject* other) {
            if (other->isObstacle()) {
                generatePath();
                moveTarget();
            }
        });

        // Register subsequent event handlers as external
        setHandlerIntakeAsInternal(false);
    }

    TargetGridMover::Ptr TargetGridMover::create(TileMap &tileMap, GameObject *target) {
        return std::make_unique<TargetGridMover>(tileMap, target);
    }

    std::string TargetGridMover::getClassName() const {
        return "TargetGridMover";
    }

    void TargetGridMover::setDestination(const Index& index) {
        if (index != targetTileIndex_) {
            targetTileIndex_ = index;
            if (getTarget()) {
                if (isTargetMoving()) {
                    targetTileChangedWhileMoving_ = true;
                } else {
                    generatePath();
                    moveTarget();
                }
            }
        }
    }

    Index TargetGridMover::getDestination() const {
        return targetTileIndex_;
    }

    void TargetGridMover::resetDestination() {
        targetTileIndex_ = Index{-1, -1};
        clearPath();
    }

    const std::stack<Index> &TargetGridMover::getPath() const {
        return pathToTargetTile_;
    }

    void TargetGridMover::clearPath() {
        while (!pathToTargetTile_.empty())
            pathToTargetTile_.pop();
    }

    bool TargetGridMover::isDestinationReachable(const Index& index) const {
        IME_ASSERT(getTarget(), "Cannot check destination reachability without a target")
        return !(pathFinder_->findPath(getGrid(),
            getGrid().getTileOccupiedByChild(getTarget()).getIndex(),
            index).empty());
    }

    bool TargetGridMover::isDestinationReachable(const Vector2f &position) const {
        return isDestinationReachable(getGrid().getTile(position).getIndex());
    }

    void TargetGridMover::setPathFinder(std::unique_ptr<IPathFinderStrategy> pathFinder) {
        if (pathFinder) {
            if (pathFinder_ && pathFinder_->getType() == pathFinder->getType())
                return;

            pathFinder_ = std::move(pathFinder);
            if (isTargetMoving())
                targetTileChangedWhileMoving_ = true; // Generate path using new path finder when target stops
            else {
                generatePath();
                moveTarget();
            }
        }
    }

    std::string TargetGridMover::getPathFinderType() const {
        return pathFinder_->getType();
    }

    void TargetGridMover::setDestination(const Vector2f& position) {
        setDestination(getGrid().getTile(position).getIndex());
    }

    void TargetGridMover::startMovement() {
        IME_ASSERT(getTarget(), "A grid mover target is required before starting movement")

        if (!movementStarted_) {
            movementStarted_ = true;
            moveTarget();
        }
    }

    void TargetGridMover::stopMovement() {
        movementStarted_ = false;
    }

    bool TargetGridMover::generateNewDirOfMotion(Index nextPos) {
        Direction newDirection = Unknown;
        Index currentPosIndex = getCurrentTileIndex();

        if (currentPosIndex == nextPos)
            return true;

        if (Index{currentPosIndex.row, currentPosIndex.colm + 1} == nextPos)
            newDirection = Right;
        else if (Index{currentPosIndex.row, currentPosIndex.colm - 1} == nextPos)
            newDirection = Left;
        else if (Index{currentPosIndex.row - 1, currentPosIndex.colm} == nextPos)
            newDirection = Up;
        else if (Index{currentPosIndex.row + 1, currentPosIndex.colm} == nextPos)
            newDirection = Down;
        else if (Index{currentPosIndex.row - 1, currentPosIndex.colm - 1} == nextPos)
            newDirection = UpLeft;
        else if (Index{currentPosIndex.row - 1, currentPosIndex.colm + 1} == nextPos)
            newDirection = UpRight;
        else if (Index{currentPosIndex.row + 1, currentPosIndex.colm - 1} == nextPos)
            newDirection = DownLeft;
        else if (Index{currentPosIndex.row + 1, currentPosIndex.colm + 1} == nextPos)
            newDirection = DownRight;
        else {
            IME_ASSERT(false, "Failed to determine direction from position {"
                << currentPosIndex.row << ", " << currentPosIndex.colm << "} to position {"
                << nextPos.row << ", " << nextPos.colm << "}")
        }

        return requestDirectionChange(newDirection);
    }

    void TargetGridMover::generatePath() {
        if (getTarget()) {
            pathToTargetTile_ = pathFinder_->findPath(getGrid(), getCurrentTileIndex(), targetTileIndex_);

            if (onPathGen_)
                onPathGen_(pathToTargetTile_);
        }
    }

    void TargetGridMover::moveTarget() {
        if (!pathToTargetTile_.empty() && getTarget()) {
            if (isTargetMoving()) {
                isPendingMove_ = true;
                return;
            }

            if (movementStarted_ && generateNewDirOfMotion(pathToTargetTile_.top()))
                pathToTargetTile_.pop();
        }
    }

    void TargetGridMover::setAdaptiveMoveEnable(bool enable) {
        if (isAdaptiveMoveEnabled_ == enable)
            return;

        isAdaptiveMoveEnabled_ = enable;
        emitChange(Property{"adaptiveMoveEnable", isAdaptiveMoveEnabled_});
    }

    bool TargetGridMover::isAdaptiveMoveEnabled() const {
        return isAdaptiveMoveEnabled_;
    }

    int TargetGridMover::onDestinationReached(Callback<Index> callback) {
        // Make handler be invoked first before external handlers for the same event
        setHandlerIntakeAsInternal(true);

        int id = onAdjacentMoveEnd([this, callback = std::move(callback)](Index index) {
            if (targetTileIndex_ == index)
                callback(index);
        });

        // Register subsequent event handlers as external
        setHandlerIntakeAsInternal(false);

        return id;
    }

    void TargetGridMover::setPathViewEnable(bool showPath) {
        renderPath_ = showPath;
    }

    bool TargetGridMover::isPathViewEnabled() const {
        return renderPath_;
    }

    void TargetGridMover::onPathGenFinish(const Callback<const std::stack<Index>&>& callback) {
        onPathGen_ = callback;
    }

    void TargetGridMover::renderPath(priv::RenderTarget &window) const {
        if (renderPath_) {
            auto path = pathToTargetTile_;
            path.push(getCurrentTileIndex());
            while (!path.empty()) {
                auto index = path.top();
                path.pop();
                auto gridTileSize = getGrid().getTileSize();
                static auto shape = RectangleShape();
                shape.setSize({static_cast<float>(gridTileSize.x), static_cast<float>(gridTileSize.y)});
                shape.setPosition(getGrid().getTile(index).getPosition());
                if (!path.empty())
                    shape.setFillColour(pathColour_);
                else
                    shape.setFillColour(Colour::Green);

                window.draw(shape);
            }
        }
    }

    TargetGridMover::~TargetGridMover() {
        emit("destruction");
    }
}
