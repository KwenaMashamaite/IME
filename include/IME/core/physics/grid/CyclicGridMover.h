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

#ifndef IME_CYCLICGRIDMOVER_H
#define IME_CYCLICGRIDMOVER_H

#include "IME/Config.h"
#include "IME/core/physics/grid/GridMover.h"

namespace ime {
    /**
     * @brief Moves a game object in the grid along a cyclic path
     *
     * When there is a an obstacle game object (see ime::GridObject::setObstacle)
     * or a collidable tile in the targets direction of cycle, this grid mover
     * basically behaves like a wall follower (when the cycle direction is set
     * to clockwise, it behaves like a right wall follower and when the cycle
     * direction is set to anti-clockwise, it behaves like a left wall follower).
     * In the absence of a collidable tile or an obstacle game object, the target
     * will switch between four adjacent tiles in the chosen cycle direction.
     *
     * Note that this grid mover cannot get the target out of a dead-end. If
     * the Grid2D contains dead-ends and you intend for the target to never
     * get stuck at any point in the grid, then you should consider removing
     * them or using a different GridMover.
     */
    class IME_API CyclicGridMover : public GridMover {
    public:
        using Ptr = std::unique_ptr<CyclicGridMover>; //!< Unique grid mover pointer

        /**
         * @brief The targets direction of movement
         */
        enum class CycleDirection {
            Clockwise,    //!< The target moves in a clockwise direction resembling a right wall follower
            AntiClockwise //!< The target moves in an anti-clockwise direction resembling a left wall follower
        };

        /**
         * @brief Constructor
         * @param grid The grid to move the target in
         * @param target The target to be moved in the grid
         *
         * @warning If @a target is left as @a nullptr, then setTarget()
         * must be called before the grid mover is used. If the @a target
         * is given, it must be in the grid prior to constructor call and it
         * must not have a RigidBody attached to it, otherwise undefined
         * behavior
         *
         * @see setTarget
         */
        explicit CyclicGridMover(Grid2D& grid, GridObject* target = nullptr);

        /**
         * @brief Create a CyclicGridMover
         * @param grid The grid to move the target in
         * @param target The target to be moved in the grid
         * @return The created grid mover
         *
         * @warning If @a target is left as @a nullptr, then setTarget()
         * must be called before the grid mover is used. If the @a target
         * is given, it must be in the grid prior to constructor call and it
         * must not have a RigidBody attached to it, otherwise undefined
         * behavior
         *
         * @see setTarget
         */
        static CyclicGridMover::Ptr create(Grid2D &grid, GridObject* target = nullptr);

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Start the cycle movement
         *
         * @see stopMovement
         */
        void startMovement();

        /**
         * @brief Stop the targets movement
         *
         * Since a child in the grid can never be in between tiles, the
         * targets movement will be stopped after it completes its current
         * move.
         *
         * By default the targets movement is stopped
         *
         * @see startMovement
         */
        void stopMovement();

        /**
         * @brief Set the direction of movement
         * @param direction The new direction
         *
         * By default, the direction is CycleDirection::Clockwise
         *
         * @see getCycleDirection
         */
        void setCycleDirection(CycleDirection direction);

        /**
         * @brief Get the direction of movement
         * @return The direction of movement
         *
         * @see setCycleDirection
         */
        CycleDirection getCycleDirection() const;

    private:
        /**
         * @brief Move the target
         * @param curDir The targets current direction
         * @param nextDir The targets next desired direction
         */
        void moveTarget(const Vector2i& curDir, const Vector2i& newDir);

    private:
        CycleDirection direction_; //!< The targets direction of cycle
        bool isMovementStarted_;   //!< A flag indicating whether or not the movement has started
    };
}

#endif //IME_CYCLICGRIDMOVER_H
