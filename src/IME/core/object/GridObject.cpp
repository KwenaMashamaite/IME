////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/core/object/GridObject.h"
#include "IME/core/physics/grid/GridMover.h"
#include "IME/core/scene/Scene.h"
#include "IME/utility/Helpers.h"

namespace ime {
    GridObject::GridObject(Scene &scene) :
        GameObject(scene),
        grid_{nullptr},
        isObstacle_{false},
        direction_{0, 0},
        collisionId_{0},
        gridMover_{nullptr}
    {}

    GridObject::GridObject(const GridObject& other) :
        GameObject(other),
        grid_{other.grid_},
        isObstacle_{other.isObstacle_},
        direction_{other.direction_},
        collisionGroup_{other.collisionGroup_},
        collisionId_{other.collisionId_},
        gridMover_{nullptr}
    {}

    GridObject &GridObject::operator=(const GridObject& rhs) {
        if (this != &rhs) {
            GridObject temp{rhs};
            GameObject::operator=(temp);
            swap(temp);
            gridMover_ = nullptr;
        }

        return *this;
    }

    void GridObject::swap(GridObject &other) {
        std::swap(grid_, other.grid_);
        std::swap(isObstacle_, other.isObstacle_);
        std::swap(direction_, other.direction_);
        std::swap(excludeList_, other.excludeList_);
        std::swap(obstacleColFilter_, other.obstacleColFilter_);
        std::swap(collisionGroup_, other.collisionGroup_);
        std::swap(collisionId_, other.collisionId_);
        std::swap(gridMover_, other.gridMover_);
    }

    std::string GridObject::getClassName() const {
        return "GridObject";
    }

    GridObject::Ptr GridObject::create(Scene &scene) {
        return std::make_unique<GridObject>(scene);
    }

    GridObject::Ptr GridObject::copy() const {
        return std::make_unique<GridObject>(*this);
    }

    void GridObject::setDirection(const Vector2i &dir) {
        if (direction_ != dir) {
            direction_ = dir;
            emitChange(Property{"direction", dir});
        }
    }

    const Vector2i &GridObject::getDirection() const {
        return direction_;
    }

    void GridObject::setObstacle(bool isObstacle) {
        if (isObstacle_ != isObstacle) {
            isObstacle_ = isObstacle;
            emitChange(Property{"obstacle", isObstacle_});
        }
    }

    bool GridObject::isObstacle() const {
        return isObstacle_;
    }

    void GridObject::setCollisionId(int id) {
        if (collisionId_ != id) {
            collisionId_ = id;
            emitChange(Property{"collisionId", collisionId_});
        }
    }

    int GridObject::getCollisionId() const {
        return collisionId_;
    }

    void GridObject::setCollisionGroup(const std::string &name) {
        if (collisionGroup_ != name) {
            collisionGroup_ = name;
            emitChange(Property{"collisionGroup", collisionGroup_});
        }
    }

    const std::string &GridObject::getCollisionGroup() const {
        return collisionGroup_;
    }

    void GridObject::setSpeed(const Vector2f &speed) {
        if (speed_ != speed) {
            speed_ = speed;
            emitChange(Property{"speed", speed});
        }
    }

    const Vector2f &GridObject::getSpeed() const {
        return speed_;
    }

    bool GridObject::isMoving() const {
        if (gridMover_)
            return gridMover_->isTargetMoving();
        else
            return false;
    }

    Index GridObject::getGridIndex() const {
        if (grid_)
            return grid_->getTileOccupiedByChild(this).getIndex();
        else
            return {-1, -1};
    }

    Grid2D *GridObject::getGrid() {
        return grid_;
    }

    const Grid2D *GridObject::getGrid() const {
        return grid_;
    }

    ExcludeList &GridObject::getCollisionExcludeList() {
        return excludeList_;
    }

    const ExcludeList &GridObject::getCollisionExcludeList() const {
        return excludeList_;
    }

    ExcludeList &GridObject::getObstacleCollisionFilter() {
        return obstacleColFilter_;
    }

    const ExcludeList &GridObject::getObstacleCollisionFilter() const {
        return  obstacleColFilter_;
    }

    GridMover *GridObject::getGridMover() {
        return gridMover_;
    }

    const GridMover *GridObject::getGridMover() const {
        return gridMover_;
    }

    int GridObject::onGridEnter(const Callback<GridObject*> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GridObject_gridEnter", callback, oneTime);
    }

    int GridObject::onGridExit(const Callback<GridObject*> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GridObject_gridExit", callback, oneTime);
    }

    int GridObject::onGridMoveBegin(const Callback<GridObject*>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GridObject_moveBegin", callback, oneTime);
    }

    int GridObject::onGridPreMove(const Callback<GridObject *> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GridObject_preMove", callback, oneTime);
    }

    int GridObject::onGridPostMove(const Callback<GridObject *> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GridObject_postMove", callback, oneTime);
    }

    int GridObject::onGridMoveEnd(const Callback<GridObject*>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GridObject_moveEnd", callback, oneTime);
    }

    int GridObject::onGridObjectCollision(const Callback<GridObject*, GridObject*> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GridObject_objectCollision", callback, oneTime);
    }

    int GridObject::onGridBorderCollision(const Callback<GridObject*> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GridObject_borderCollision", callback, oneTime);
    }

    int GridObject::onGridTileCollision(const Callback<GridObject*, Index> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GridObject_tileCollision", callback, oneTime);
    }

    void GridObject::setGridMover(GridMover *gridMover) {
        gridMover_ = gridMover;
    }

    void GridObject::setGrid(Grid2D *grid) {
        if (grid_ != grid) {
            if (grid) {
                if (grid_)
                    setGrid(nullptr);

                grid_ = grid;
                eventEmitter_.emit("GridObject_gridEnter", this);
            } else if (grid_) {
                grid_ = nullptr;
                eventEmitter_.emit("GridObject_gridExit", this);
            }
        }
    }

    void GridObject::emitGridEvent(const Property& property) {
        if ((property.getName() == "borderCollision") ||
            (property.getName() == "moveBegin") ||
            (property.getName() == "moveEnd") ||
            (property.getName() == "preMove") ||
            (property.getName() == "postMove"))
        {
            eventEmitter_.emit("GridObject_" + property.getName(), this);
        }
        else {
            IME_ASSERT(property.hasValue(), "Internal error: Raising grid event without arguments")

            if (property.getName() == "tileCollision")
                eventEmitter_.emit("GridObject_" + property.getName(), this, property.getValue<Index>());
            else if (property.getName() == "objectCollision")
                eventEmitter_.emit("GridObject_" + property.getName(), this, property.getValue<GridObject*>());
        }
    }

    GridObject::~GridObject() {
        emitDestruction();
    }
}
