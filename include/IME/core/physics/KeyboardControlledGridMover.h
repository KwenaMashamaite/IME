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

#ifndef IME_KEYBOARDCONTROLLED_H
#define IME_KEYBOARDCONTROLLED_H

#include "IME/core/input/Keyboard.h"
#include "GridMover.h"

namespace IME {
    /**
     * @brief Defines how the movement is triggered based on the state of a key
     */
    enum class MovementTrigger {
        None,      //!< Does not trigger any movement
        OnKeyDown, //!< Continues to trigger movement while key is held down
        OnKeyUp    //!< Only triggers movement when a key is released
    };

    /**
     * @brief Class that performs grid based movement on an entity using the
     *        keyboard as a movement trigger
     */
    class IME_API KeyboardControlledGridMover : public GridMover {
    public:
        /**
         * @brief Constructor
         * @param tileMap Grid to move target in
         * @param target Target to be moved in the grid
         */
        explicit KeyboardControlledGridMover(TileMap &tileMap, std::shared_ptr<Entity> target = nullptr);

        /**
         * @brief Set the key event that triggers the targets movement
         * @param trigger The targets movement trigger
         *
         * The actual keys that trigger the movements must be set, in order to
         * determine the direction of motion
         *
         * @see setKeys
         */
        void setMovementTrigger(MovementTrigger trigger);

        /**
         * @brief Get the current movement trigger
         * @return Current movement trigger
         */
        MovementTrigger getMovementTrigger() const;

        /**
         * @brief Set the keys to move the target in all four directions
         * @param leftKey Key to move target left on trigger
         * @param rightKey Key to move target right on trigger
         * @param upKey Key to move target up on trigger
         * @param downKey Key to move target down on trigger
         *
         * In addition to setting the keys, the movement trigger must be set.
         * There are no set keys by default
         *
         * @see setMovementTrigger
         */
        void setKeys(Input::Keyboard::Key leftKey, Input::Keyboard::Key rightKey,
             Input::Keyboard::Key upKey, Input::Keyboard::Key downKey);

        /**
         * @brief Handle an event
         * @param event Event to handle
         */
        void handleEvent(sf::Event event);

    private:
        /**
         * @brief Move target in the grid
         * @param key pressed key (Helps Determine which direction to go)
         */
        void moveTarget(Input::Keyboard::Key key);

        /**
         * @brief Attach input event listeners to the set trigger
         */
        void attachInputEventListeners();

    private:
        MovementTrigger trigger_;                                         //!< Key event that triggers target movement
        int onTriggerHandlerId_;                                          //!< Movement trigger Handler id
        Input::Keyboard keyboard_;                                        //!< Input detector
        std::pair<bool, Direction> newDir_;                               //!< Flags if direction was changed during target movement
        Input::Keyboard::Key goLeftKey_ = Input::Keyboard::Key::Unknown;  //!< A Key when triggered moves target left
        Input::Keyboard::Key goRightKey_ = Input::Keyboard::Key::Unknown; //!< A Key when triggered moves target right
        Input::Keyboard::Key goUpKey_ = Input::Keyboard::Key::Unknown;    //!< A Key when triggered moves target up
        Input::Keyboard::Key goDownKey_ = Input::Keyboard::Key::Unknown;  //!< A Key when triggered moves target down
    };
}

#endif
