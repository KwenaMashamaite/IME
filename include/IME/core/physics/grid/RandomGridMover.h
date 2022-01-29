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

#ifndef IME_RANDOMGRIDMOVER_H
#define IME_RANDOMGRIDMOVER_H

#include "IME/core/physics/grid/GridMover.h"
#include <vector>

namespace ime {
    /**
     * @brief Moves a GridObject randomly in a TileMap
     *
     * Note that the target cannot move backwards because it may be
     * stuck in a loop where it switches between the same two tiles.
     * The only time it reverses direction is when attempting to get
     * out of a ead-end.
     */
    class IME_API RandomGridMover : public GridMover {
    public:
        using Ptr = std::unique_ptr<RandomGridMover>; //!< Unique grid mover pointer

        /**
         * @brief Constructor
         * @param tileMap Grid to move target in
         * @param target Game object to be moved in the grid
         *
         * @warning If @a target is left as @a nullptr, then setTarget()
         * must be called before the grid mover is used. If the @a target
         * is given, it must be in the grid prior to constructor call and it
         * must not have a RigidBody attached to it, otherwise undefined
         * behavior
         *
         * @see setTarget
         */
        explicit RandomGridMover(TileMap &tileMap, GridObject* target = nullptr);

        /**
         * @brief Create a RandomGridMover
         * @param tileMap The grid to move the target in
         * @param target Game object to be moved in the grid
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
        static RandomGridMover::Ptr create(TileMap &tileMap, GridObject* target = nullptr);

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Start moving the target in the grid
         *
         * This function will move the target if it hasn't been moved for the
         * first time or the movement was stopped
         *
         * @see stopMovement
         */
        void startMovement();

        /**
         * @brief Stop moving the target in the grid
         *
         * Since a child in the grid can never be in between tiles, the
         * targets movement will be stopped after it completes its current
         * move. The targets movement is stopped by default
         *
         * @see startMovement
         */
        void stopMovement();

        /**
         * @brief Destructor
         */
        ~RandomGridMover() override;

    private:
        /**
         * @brief Generate the targets new direction of motion
         */
        void generateNewDirection();

    private:
        bool movementStarted_;                     //!< A flag indicating whether or not movement has been started
        std::vector<Direction> directionAttempts_; //!< Stores directions to be attempted
        std::vector<Vector2i> possibleDirections_; //!< Stores possible directions based on the current movement restriction
    };
}

#endif // IME_RANDOMGRIDMOVER_H
