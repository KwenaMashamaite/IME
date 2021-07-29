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
#include "IME/core/physics/grid/GridMover.h"

namespace ime {
    /**
     * @brief Defines how the movement is triggered based on the state of a key
     */
    enum class MovementTrigger {
        None,      //!< Does not trigger any movement
        OnKeyDown, //!< Only triggers movement when a key goes down
        OnKeyUp,   //!< Only triggers movement when a key is released
        OnKeyHeld  //!< Continues to trigger movement while key is held down
    };

    /**
     * @brief Keys that triggers the targets direction change
     */
    struct TriggerKeys {
        Keyboard::Key leftKey;  //!< A key that moves the target to the left
        Keyboard::Key rightKey; //!< A key that moves the target to the right
        Keyboard::Key upKey;    //!< A key that moves the target upwards
        Keyboard::Key downKey;  //!< A key that moves the target downwards
    };

    /**
     * @brief Moves a GameObject in the grid using the keyboard as a movement
     *        trigger
     */
    class IME_API KeyboardGridMover : public GridMover {
    public:
        using Ptr = std::unique_ptr<KeyboardGridMover>; //!< Unique grid mover pointer
        using InputCallback = std::function<bool(Keyboard::Key)>; //!< Input callback

        /**
         * @brief Constructor
         * @param tileMap Grid to move target in
         * @param target Target to be moved in the grid
         */
        explicit KeyboardGridMover(TileMap &tileMap, GameObject* target = nullptr);

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Set the key event that triggers the targets movement
         * @param trigger The targets movement trigger
         *
         * The actual keys that trigger the movements must be set, in order to
         * determine the direction of motion. The default movement trigger is
         * MovementTrigger::OnKeyDown
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
         * @deprecated Since v2.2.0. Use ime::KeyboardGridMover::setKeys(const TriggerKeys&) instead
         * @brief Set the keys to move the target in all four directions
         * @param leftKey Key to move target left on trigger
         * @param rightKey Key to move target right on trigger
         * @param upKey Key to move target up on trigger
         * @param downKey Key to move target down on trigger
         *
         * In addition to setting the keys, the movement trigger must be set.
         * The default keys are as follows:
         *
         * A = Left, W = Up, S = Down and D = Right
         *
         * @see setMovementTrigger
         */
         [[deprecated("Use 'void ime::KeyboardGridMover::setKeys(const TriggerKeys&)' instead.")]]
        void setKeys(Key leftKey, Key rightKey, Key upKey, Key downKey);

        /**
         * @brief Set the keys to move the target
         * @param triggerKeys The keys to set
         *
         * The default keys are as follows:
         *
         *  ime::Keyboard::Key::A = move target left,
         *  ime::Keyboard::Key::W = move target up,
         *  ime::Keyboard::Key::S = move target down and
         *  ime::Keyboard::Key::D = move target right
         *
         * @see setMovementTrigger
         */
        void setKeys(const TriggerKeys& triggerKeys);

        /**
         * @brief Get the keys that move the target
         * @return The keys that trigger the targets direction change
         */
        TriggerKeys& getTriggerKeys();
        const TriggerKeys& getTriggerKeys() const;

        /**
         * @brief Add an event listener to an input event
         * @param callback A function which returns true if the input should be
         *                 handled or false if the input should be ignored
         *
         * An input event is triggered when the grid mover receives a keyboard
         * input that matches any one of the keys that move the target. The
         * callback function will be passed this key when it is called. To
         * remove the callback pass nullptr. Note that when there is no callback
         * assigned to this event, the input will always be handled
         *
         * By default, there is no registered
         */
        void onInput(const InputCallback& callback);

        /**
         * @internal
         * @brief Handle an event
         * @param event Event to handle
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void handleEvent(Event event);

        /**
         * @brief Destructor
         */
        ~KeyboardGridMover() override;

    private:
        /**
         * @brief Move target in the grid
         * @param key pressed key (Helps Determine which direction to go)
         */
        void moveTarget(Key key);

        /**
         * @brief Attach input event listeners to the set trigger
         */
        void attachInputEventListeners();

        /**
         * @brief Remove input event listeners from the set trigger
         */
        void removeInputEventListeners();

    private:
        MovementTrigger trigger_;           //!< Key event that triggers target movement
        int onTriggerHandlerId_;            //!< Movement trigger Handler id
        input::Keyboard keyboard_;          //!< Detects keyboard inputs
        std::pair<bool, Direction> newDir_; //!< A flag indicating whether or not the direction was changed while target was moving
        TriggerKeys triggerKeys_;           //!< Keyboard keys that control the actors direction of motion
        InputCallback onInput_;             //!< A function called when the grid mover receives input
    };

    /**
     * @brief Overload of binary operator ==
     * @param lhs Left operand
     * @param rhs Right operand
     * @return True if @a lhs is equal to @a rhs
     */
    extern IME_API bool operator==(const TriggerKeys& lhs, const TriggerKeys& rhs);

    /**
     * @brief Overload of binary operator !=
     * @param lhs Left operand (a vector)
     * @param rhs Right operand (a vector)
     * @return True if @a lhs is @e not equal to @a rhs
     */
    extern IME_API bool operator!=(const TriggerKeys& lhs, const TriggerKeys& rhs);
}

#endif
