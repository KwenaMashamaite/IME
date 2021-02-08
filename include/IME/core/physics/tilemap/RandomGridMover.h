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

#ifndef IME_RANDOMGRIDMOVER_H
#define IME_RANDOMGRIDMOVER_H

#include "IME/core/physics/tilemap/GridMover.h"
#include "IME/core/physics/tilemap/TargetGridMover.h"

namespace ime {
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

        /**
         * @brief Update entity movement in the grid
         * @param deltaTime Time passed since movement was last updated
         */
        void update(Time deltaTime) override;

        /**
         * @brief Enable or disable advanced random movement
         * @param enable True to enable or false to disable
         *
         * In advanced mode, instead of choosing a random adjacent tile, a
         * random tile is anywhere in the grid is selected and the target
         * advances to that tile. A new random tile is generated after the
         * target reaches the current destination tile and so on. This
         * prevents the stop and go movement. However this is expensive
         * and the game may slow down depending on the size of the tilemap
         *
         * Advanced movement is disabled at by default
         *
         * @warning This function is experimental
         */
        void enableAdvancedMovement(bool enable);

    private:
        /**
         * @brief Generate the targets new direction of motion
         */
        void generateNewDirection();

        /**
         * @brief Set a random position to go to in the grid
         *
         * This function is only valid when in advance mode
         */
        void setRandomPosition();

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
        bool isAdvance_;          //!< Flags whether or not advanced random movement is enabled
        bool switchToAdvanced_;
        bool switchToNormal_;
        TargetGridMover targetGridMover_;
    };
}

#endif // IME_RANDOMGRIDMOVER_H
