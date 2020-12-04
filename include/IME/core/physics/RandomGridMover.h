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

#ifndef IME_RANDOMGRIDMOVER_H
#define IME_RANDOMGRIDMOVER_H

#include "GridMover.h"

namespace IME {
    /**
     * @brief Class for moving an entity randomly in a grid
     */
    class IME_API RandomGridMover : public GridMover {
    public:
        /**
         * @brief Create a random grid mover object
         * @param tileMap Grid to move target in
         * @param target Entity to be moved in the grid
         */
        explicit RandomGridMover(TileMap &tileMap, EntityPtr target = nullptr);

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

    private:
        /**
         * @brief Generate the targets new direction of motion
         */
        void generateNewDirection();

        /**
         * @brief Restore previous direction and generate a new direction
         *        of motion based on previous direction
         *
         * This function is intended to be used only when the target has
         * collided with an obstacle. The target is not allowed to go in the
         * direction opposite its current direction (180 degree turns). This
         * prevents it from going back and forth between the same tiles instead
         * of moving. Reverting the direction allows the target to know its
         * correct opposite  direction
         */
        void revertAndGenerateDirection();

    private:
        Direction prevDirection_; //!< Keeps track of the targets previous direction
        bool movementStarted_;    //!< Tracks whether the target movement has been initiated or not
        int obstacleHandlerId_;   //!< Obstacle collision handler id
        int solidTileHandlerId_;  //!< Solid tile collision handler id
    };
}

#endif // IME_RANDOMGRIDMOVER_H
