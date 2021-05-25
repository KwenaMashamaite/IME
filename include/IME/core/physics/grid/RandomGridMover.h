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

#include "IME/core/physics/grid/GridMover.h"
#include "IME/core/physics/grid/TargetGridMover.h"

namespace ime {
    /**
     * @brief Class for moving a game object randomly in a grid
     */
    class IME_API RandomGridMover : public GridMover {
    public:
        using Ptr = std::unique_ptr<RandomGridMover>; //!< Unique grid mover pointer

        /**
         * @brief Create a random grid mover object
         * @param tileMap Grid to move target in
         * @param target Game object to be moved in the grid
         */
        explicit RandomGridMover(TileMap &tileMap, GameObject* target = nullptr);

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
         * @brief Get the index of the tile the target is trying to reach
         * @return The index of the tile the target is trying to reach
         *
         * If the target it not moving towards any tiles, this function
         * will return the index of the tile currently occupied by the
         * target
         */
        Index getTargetTileIndex() const override;

        /**
         * @brief Enable or disable smart random movement
         * @param enable True to enable or false to disable
         *
         * In smart mode, the target can get itself out of a dead end. As a
         * result the no reversing direction rule is overridden. Note for
         * large grids or grids that have a lot of accessible tiles, smart
         * mode may have an impact on performance
         *
         * @note In smart mode, the target cannot move diagonally
         *
         * By default smart mode is disabled
         */
        void setSmartMoveEnable(bool enable);

        /**
         * @brief Check if smart mode is enabled or not
         * @return True if enabled, otherwise false
         *
         * @see setSmartMoveEnable
         */
        bool isSmartMoveEnabled() const;

        /**
         * @internal
         * @brief Update the game object movement in the grid
         * @param deltaTime Time passed since movement was last updated
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void update(Time deltaTime) override;

        /**
         * @brief Destructor
         */
        ~RandomGridMover() override;

    private:
        /**
         * @brief Generate the targets new direction of motion
         */
        void generateNewDirection();

        /**
         * @brief Set a random position to go to in the grid
         *
         * This function is only valid when in smart mode
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
        Direction currDirection_;    //!< Keeps track of the targets previous direction
        Direction prevDirection_;    //!< Keeps track of the targets previous direction
        bool movementStarted_;       //!< A flag indicating whether or not movement has been started
        bool isSmartMoveEnabled_;    //!< A flag indicating whether or not smart mode is enabled
        bool switchToSmartMove_;     //!< A flag indicating whether or not to switch to smart movement
        bool switchToNormal_;        //!< A flag indicating whether or not to switch to default movement
        TargetGridMover smartMover_; //!< Handles grid movement in smart mode
    };
}

#endif // IME_RANDOMGRIDMOVER_H
