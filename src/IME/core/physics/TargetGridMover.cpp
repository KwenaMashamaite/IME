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

#include "IME/core/physics/TargetGridMover.h"
#include "IME/core/path/BFS.h"

namespace IME {
    TargetGridMover::TargetGridMover(TileMap &tileMap, TargetGridMover::EntityPtr target) :
        GridMover(tileMap, target),
        pathFinder_(std::make_unique<BFSPathFinder>(tileMap.getSizeInTiles())),
        targetTileIndex_{-1, -1}, targetStopped_{false},
        targetTileChangedWhileMoving_{false}
    {
        if (getTarget())
            targetTileIndex_ = getGrid().getTileOccupiedByChild(getTarget()).getIndex();

        onTargetChanged([this](EntityPtr target) {
            if (target) {
                generatePath();
                moveTarget();
            }
        });

        onAdjacentTileReached([this](Graphics::Tile) {
            if (targetTileChangedWhileMoving_) {
                generatePath();
                targetTileChangedWhileMoving_ = false;
            }
            moveTarget();
        });
    }

    void TargetGridMover::setDestination(Index index) {
        if (index != targetTileIndex_ && getGrid().isIndexValid(index)) {
            targetTileIndex_ = index;
            if (getTarget()) {
                if (isTargetMoving())
                    targetTileChangedWhileMoving_ = true;
                generatePath();
                moveTarget();
            }
        }
    }

    Index TargetGridMover::getDestination() const {
        return targetTileIndex_;
    }

    void TargetGridMover::setPathFinder(std::unique_ptr<IGridPathFinder> pathFinder) {
        if (pathFinder) {
            pathFinder_ = std::move(pathFinder);
            generatePath();
            moveTarget();
        }
    }

    void TargetGridMover::setDestination(Vector2f position) {
        setDestination(getGrid().getTile(position).getIndex());
    }

    void TargetGridMover::resumeMovement() {
        if (targetStopped_) {
            targetStopped_ = false;
            moveTarget();
        }
    }

    void TargetGridMover::pauseMovement() {
        targetStopped_ = true;
    }

    void TargetGridMover::generateNewDirOfMotion(Index nextPos) {
        if (!getTarget())
            return;

        auto newDirection = Direction::None;
        auto currentPosIndex = getGrid().getTile(
                getTarget()->getPosition()).getIndex();
        if (Index{currentPosIndex.row, currentPosIndex.colm + 1} == nextPos)
            newDirection = Direction::Right;
        else if (Index{currentPosIndex.row, currentPosIndex.colm - 1} == nextPos)
            newDirection = Direction::Left;
        else if (Index{currentPosIndex.row - 1, currentPosIndex.colm} == nextPos)
            newDirection = Direction::Up;
        else if (Index{currentPosIndex.row + 1, currentPosIndex.colm} == nextPos)
            newDirection = Direction::Down;
        else
            newDirection = Direction::None;
        requestDirectionChange(newDirection);
    }

    void TargetGridMover::generatePath() {
        if (getTarget()) {
            auto sourceTilePos = getGrid().getTileOccupiedByChild(getTarget()).getIndex();
            pathToTargetTile_ = pathFinder_->findPath(getGrid(), sourceTilePos, targetTileIndex_);
        }
    }

    void TargetGridMover::moveTarget() {
        if (!pathToTargetTile_.empty() && !targetStopped_) {
            generateNewDirOfMotion(pathToTargetTile_.top());
            pathToTargetTile_.pop();
        }
    }

    int TargetGridMover::onDestinationReached(Callback<Graphics::Tile> callback) {
        return onAdjacentTileReached(
            [this, callback = std::move(callback)](Graphics::Tile tile) {
                if (targetTileIndex_ == tile.getIndex())
                    callback(tile);
            }
        );
    }
}