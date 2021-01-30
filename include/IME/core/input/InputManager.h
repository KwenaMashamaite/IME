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

#ifndef IME_INPUTMANAGER_H
#define IME_INPUTMANAGER_H

#include "IME/Config.h"
#include "IME/core/input/Keyboard.h"
#include "IME/core/input/Mouse.h"
#include "IME/core/event/Event.h"

namespace ime {
    namespace input {
        /**
         * @brief Manages keyboard and mouse inputs
         *
         * You usually don't instantiate this class directly, you either use
         * the input manager that is local to a Scene or the global input
         * manager that from the Engine class
         */
        class IME_API InputManager {
        public:
            /**
             * @brief Check if a key is currently pressed or not
             * @param key Key to be checked
             * @return True if the key is pressed, otherwise false
             *
             * This function checks the state of the key in real time
             */
            bool isKeyPressed(Keyboard::Key key) const;

            /**
             * @brief Add an event listener to a key up event
             * @param callback Function to be executed when the key is released
             * @return The event listeners identification number
             *
             * This event is triggered only when a depressed key is
             * released. The callback is passed the key that was released
             *
             * @see onKeyDown
             */
            int onKeyUp(Callback<Keyboard::Key> callback);

            /**
             * @brief Add an event listener to a key down event
             * @param callback Function to be executed when a key is down
             * @return The event listeners identification number
             *
             * @note This event will continue to fire while the key is
             * held down
             *
             * @see onKeyUp
             */
            int onKeyDown(Callback<Keyboard::Key> callback);

            /**
             * @brief Remove an event listener from a key down or key up event
             * @param event Event to remove event listener from
             * @param id Identification number of the listener to be removed
             * @return True if the event listener was removed from the event,
              *        or false if the specified event does not have an event
              *        listener with the specified id
             */
            bool unsubscribe(KeyboardEvent event, int id);

            /**
             * @brief Check if a mouse button is currently pressed or not
             * @param button Mouse button to check
             * @return True if the mouse button is pressed, otherwise false
             *
             * This function checks the state of a mouse button in real time
             */
            bool isMouseDown(Mouse::Button button) const;

            /**
             * @brief Add an event listener to a mouse button up event
             * @param callback The function to be executed when the mouse
             *                 button is released
             * @return The event listeners identification number
             *
             * The mouse button up event is fired when a depressed mouse
             * button is released. The callback is passed the button that
             * was released and the coordinates of the mouse cursor when
             * the button was released. The mouse cursor coordinates are
             * relative to the game window
             */
            int onMouseUp(Callback<Mouse::Button, int, int> callback);

            /**
             * @brief Add an event listener to a mouse button up event
             * @param callback The function to be executed when the mouse
             *                 button is released
             * @return The event listeners identification number
             *
             * The mouse button up event is fired when a depressed mouse
             * button is released. The callback is passed the button that
             * was released
             */
            int onMouseUp(Callback<Mouse::Button> callback);

            /**
             * @brief Add an event listener to a mouse button up event
             * @param callback The function to be executed when the event a
             *                 mouse button is released
             * @return The event listeners identification number
             *
             * The mouse button down event is fired when a mouse button
             * is depressed. The callback is passed the button that was
             * depressed and the coordinates of the mouse cursor when
             * the button was depressed. The mouse cursor coordinates
             * are relative to the game window
             *
             * @note This event does NOT fire repetitively while the
             * mouse button is depressed
             */
            int onMouseDown(Callback<Mouse::Button, int, int> callback);

            /**
             * @brief Add an event listener to a mouse button down event
             * @param callback The function to be executed when the mouse
             *                 button is depressed
             * @return The event listeners identification number
             *
             * The callback is passed the button that was depressed
             *
             * @note This event does NOT fire repetitively while the
             * mouse button is depressed
             */
            int onMouseDown(Callback<Mouse::Button> callback);

            /**
             * @brief Add an event listener to a mouse move event
             * @param callback Function to execute when the mouse moves
             * @return The event listeners identification number
             *
             * The callback function will be passed the new position of
             * the mouse cursor
             */
            int onMouseMove(Callback<int, int> callback);

            /**
             * @brief Add an event listener to a mouse wheel scroll event
             * @param callback Function to be executed when the mouse wheel
             *                 is scrolled
             * @return The event listeners identification number
             *
             * The callback is passed the scrolled wheel and the wheel
             * offset (positive is up/left, negative is down/right), and
             * the mouse coordinates relative to the game window
             */
            int onMouseWheelScroll(Callback<Mouse::Wheel, float, int, int> callback);

            /**
             * @brief Remove an event listener from a mouse event
             * @param event The event to remove the event listener from
             * @param id The id of the event listener
             * @return True if the event listener was removed or false if
             *         the given event does not have the specified event
             *         listener
             */
            bool unsubscribe(MouseEvent event, int id);

            /**
             * @brief Update the event manager
             * @param event Event to be handled
             */
            void handleEvent(Event event);

        private:
            Keyboard keyboard_; //!< Managed keyboard
            Mouse mouse_;       //!< Managed Mouse
        };
    }
}

#endif // IME_INPUTMANAGER_H
