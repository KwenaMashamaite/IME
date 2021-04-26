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

#include "IME/core/physics/tilemap/TargetGridMover.h"
#include "IME/core/path/BFS.h"

namespace ime {
    TargetGridMover::TargetGridMover(TileMap &tileMap, GameObject::Ptr target) :
        GridMover(Type::Target, tileMap, std::move(target)),
        pathFinder_(std::make_unique<BFS>(tileMap.getSizeInTiles())),
        targetTileIndex_{-1, -1},
        movementStarted_{false},
        targetTileChangedWhileMoving_{false}
    {
        IME_ASSERT((tileMap.getSizeInTiles() != Vector2u{0u, 0u}), "A target grid mover must be instantiated with a fully constructed tilemap")

        if (getTarget())
            targetTileIndex_ = getGrid().getTileOccupiedByChild(getTarget()).getIndex();

        enableAdaptiveMovement(false);

        onTargetTileReset([this](Index index) {
            targetTileIndex_ = index;
        });

        onTargetChanged([this](GameObject::Ptr newTarget) {
            if (newTarget && movementStarted_) {
                generatePath();
                moveTarget();
            }
        });

        onAdjacentTileReached([this](Index) {
            if (adjacentTileHandler_)
                adjacentTileHandler_();
        });

        onTileCollision([this](Index) {
            if (getTarget()) {
                generatePath();
                moveTarget();
            }
        });

        onObstacleCollision([this](GameObject::Ptr , GameObject::Ptr) {
            if (getTarget()) {
                generatePath();
                moveTarget();
            }
        });
    }

    std::string TargetGridMover::getClassName() const {
        return "TargetGridMover";
    }

    void TargetGridMover::setDestination(Index index) {
        if (index != targetTileIndex_ && getGrid().isIndexValid(index)) {
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

    const std::stack<Index> &TargetGridMover::getPath() const {
        return pathToTargetTile_;
    }

    bool TargetGridMover::isDestinationReachable(Index index) {
        IME_ASSERT(getTarget(), "Cannot check destination reachability without a target")
        return !(pathFinder_->findPath(getGrid(),
            getGrid().getTileOccupiedByChild(getTarget()).getIndex(),
            index).empty());
    }

    void TargetGridMover::setPathFinder(std::unique_ptr<IPathFinderStrategy> pathFinder) {
        if (pathFinder) {
            pathFinder_ = std::move(pathFinder);
            generatePath();
            moveTarget();
        }
    }

    void TargetGridMover::setDestination(Vector2f position) {
        setDestination(getGrid().getTile(position).getIndex());
    }

    void TargetGridMover::startMovement() {
        if (!movementStarted_) {
            movementStarted_ = true;
            moveTarget();
        }
    }

    void TargetGridMover::stopMovement() {
        movementStarted_ = false;
    }

    void TargetGridMover::generateNewDirOfMotion(Index nextPos) {
        if (!getTarget())
            return;

        auto newDirection = Unknown;
        auto currentPosIndex = getGrid().getTileOccupiedByChild(getTarget()).getIndex();
        if (Index{currentPosIndex.row, currentPosIndex.colm + 1} == nextPos)
            newDirection = Right;
        else if (Index{currentPosIndex.row, currentPosIndex.colm - 1} == nextPos)
            newDirection = Left;
        else if (Index{currentPosIndex.row - 1, currentPosIndex.colm} == nextPos)
            newDirection = Up;
        else if (Index{currentPosIndex.row + 1, currentPosIndex.colm} == nextPos)
            newDirection = Down;
        else
            newDirection = Unknown;
        requestDirectionChange(newDirection);
    }

    void TargetGridMover::generatePath() {
        if (getTarget() && getMovementRestriction() != GridMover::MoveRestriction::All) {
            auto sourceTilePos = getGrid().getTileOccupiedByChild(getTarget()).getIndex();
            pathToTargetTile_ = pathFinder_->findPath(getGrid(), sourceTilePos, targetTileIndex_);
        }
    }

    void TargetGridMover::moveTarget() {
        if (!pathToTargetTile_.empty() && movementStarted_) {
            generateNewDirOfMotion(pathToTargetTile_.top());
            pathToTargetTile_.pop();
        }
    }

    void TargetGridMover::enableAdaptiveMovement(bool isAdaptive) {
        if (isAdaptive) {
            adjacentTileHandler_ = [this]{
                generatePath();
                moveTarget();
            };
        } else {
            adjacentTileHandler_ = [this] {
                if (targetTileChangedWhileMoving_) {
                    targetTileChangedWhileMoving_ = false;
                    generatePath();
                }
                moveTarget();
            };
        }
    }

    int TargetGridMover::onDestinationReached(Callback<Index> callback) {
        return onAdjacentTileReached(
            [this, callback = std::move(callback)](Index index) {
                if (targetTileIndex_ == index)
                    callback(index);
            }
        );
    }

    TargetGridMover::~TargetGridMover() {
        emit("destruction");
    }
}
