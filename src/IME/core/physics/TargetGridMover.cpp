#include "IME/core/physics/TargetGridMover.h"
#include "IME/core/path/BFS.h"

namespace IME {
    TargetGridMover::TargetGridMover(TileMap &tileMap, TargetGridMover::EntityPtr target)
        : gridMover_(tileMap, target),
          pathFinder_(std::make_unique<BFSPathFinder>(tileMap.getSizeInTiles())),
          targetTile_{-1, -1}, targetStopped_{false},
          targetTileChangedWhileMoving_{false}
    {
        if (gridMover_.getTarget())
            targetTile_ = gridMover_.getGrid().getTile(
                gridMover_.getTarget()->getPosition()).getIndex();

        gridMover_.onTargetChanged([this](EntityPtr target) {
            if (target) {
                generatePath();
                moveTarget();
            }
        });

        gridMover_.onDestinationReached([this](float, float ) {
            if (targetTileChangedWhileMoving_) {
                generatePath();
                targetTileChangedWhileMoving_ = false;
            }
            moveTarget();
        });
    }

    void TargetGridMover::setTarget(TargetGridMover::EntityPtr target) {
        gridMover_.setTarget(target);
    }

    TargetGridMover::EntityPtr TargetGridMover::getTarget() const {
        return gridMover_.getTarget();
    }

    void TargetGridMover::setDestination(Index index) {
        if (index != targetTile_ && gridMover_.getGrid().isIndexValid(index)) {
            targetTile_ = index;
            if (gridMover_.getTarget()) {
                if (gridMover_.isTargetMoving())
                    targetTileChangedWhileMoving_ = true;
                generatePath();
                moveTarget();
            }
        }
    }

    Index TargetGridMover::getDestination() const {
        return targetTile_;
    }

    void TargetGridMover::setPathFinder(std::unique_ptr<IGridPathFinder> pathFinder) {
        if (pathFinder) {
            pathFinder_ = std::move(pathFinder);
            generatePath();
            moveTarget();
        }
    }

    void TargetGridMover::setDestination(Position position) {
        setDestination(gridMover_.getGrid().getTile(position).getIndex());
    }

    void TargetGridMover::resumeMovement() {
        targetStopped_ = false;
        moveTarget();
    }

    void TargetGridMover::pauseMovement() {
        targetStopped_ = true;
    }

    void TargetGridMover::update(float deltaTime) {
        gridMover_.update(deltaTime);
    }

    void TargetGridMover::generateNewDirOfMotion(Index nextPos) {
        if (!gridMover_.getTarget())
            return;

        auto newDirection = Direction::None;
        auto currentPosIndex = gridMover_.getGrid().getTile(
                gridMover_.getTarget()->getPosition()).getIndex();
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
        gridMover_.requestDirectionChange(newDirection);
    }

    void TargetGridMover::generatePath() {
        if (gridMover_.getTarget()) {
            auto sourceTilePos = gridMover_.getGrid().getTile(gridMover_.getTarget()->getPosition()).getIndex();
            pathToTargetTile_ = pathFinder_->findPath(gridMover_.getGrid(), sourceTilePos, targetTile_);
        }
    }

    void TargetGridMover::moveTarget() {
        if (!pathToTargetTile_.empty() && !targetStopped_) {
            generateNewDirOfMotion(pathToTargetTile_.top());
            pathToTargetTile_.pop();
        }
    }

    int TargetGridMover::onAdjacentTileReached(Callback<float, float> callback) {
        return gridMover_.onDestinationReached(std::move(callback));
    }

    int TargetGridMover::onDestinationReached(Callback<float, float> callback) {
        return gridMover_.onDestinationReached(
            [this, callback = std::move(callback)](float x, float y) {
                if (gridMover_.getGrid().getTile(targetTile_).getPosition() == Position{x, y})
                    callback(x, y);
            });
    }

    int TargetGridMover::onCollectableCollision(Callback<TargetGridMover::EntityPtr,
        TargetGridMover::EntityPtr> callback) {
            return gridMover_.onCollectableCollision(std::move(callback));
    }

    int TargetGridMover::onEnemyCollision(Callback<TargetGridMover::EntityPtr,
        TargetGridMover::EntityPtr> callback)
    {
        return gridMover_.onEnemyCollision(std::move(callback));
    }

    int TargetGridMover::onPlayerCollision(Callback<TargetGridMover::EntityPtr,
        TargetGridMover::EntityPtr> callback)
    {
        return gridMover_.onPlayerCollision(std::move(callback));
    }
}