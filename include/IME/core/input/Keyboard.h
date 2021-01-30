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

#ifndef IME_KEYBOARD_H
#define IME_KEYBOARD_H

#include "IME/Config.h"
#include "IME/core/event/EventEmitter.h"

namespace ime {
    class Event; //!< Event class forward declaration

    /**
     * @brief Keyboard events
     */
    enum class KeyboardEvent {
        KeyDown, //!< Fired when key is depressed
        KeyUp    //!< Fired when depressed key is released
    };

    namespace input {
        /**
         * @brief Captures keyboard inputs from the user
         *
         * You usually don't instantiate this class directly, you either use
         * the input manager that is local to a Scene or the global input
         * manager that from the Engine class
         */
        class IME_API Keyboard {
        public:
            /**
             * @brief keyboard keys
             */
            enum class Key {
                Unknown = -1, //!< Unhandled key
                A = 0, B, C,
                D, E, F, G,
                H, I, J, K,
                L, M, N, O,
                P, Q, R, S,
                T, U, V, W,
                X, Y, Z, Num0,
                Num1, Num2, Num3, Num4,
                Num5, Num6, Num7, Num8,
                Num9, Escape, LControl, LShift,
                LAlt, LSystem, RControl, RShift,
                RAlt, RSystem, Menu, LBracket,
                RBracket, Semicolon, Comma, Period,
                Quote, Slash, Backslash, Tilde,
                Equal, Hyphen, Space, Enter,
                Backspace, Tab, PageUp, PageDown,
                End, Home, Insert, Delete,
                Add, Subtract, Multiply, Divide,
                Left, Right, Up, Down,
                Numpad0, Numpad1, Numpad2, Numpad3,
                Numpad4, Numpad5, Numpad6, Numpad7,
                Numpad8, Numpad9, F1, F2,
                F3, F4, F5, F6,
                F7, F8, F9, F10,
                F11, F12, F13, F14,
                F15, Pause
            };

            /**
             * @brief Check if a key is pressed or not
             * @param key Key to be checked
             * @return True if the key is pressed or false if it not pressed
             *
             * This function checks the state of a key in real time, unlike
             * all the other function which are event-based
             */
            static bool isKeyPressed(Key key);

            /**
             * @brief Add an event listener to a key up event
             * @param callback Function to be executed when a key is released
             * @return The event listeners identification number
             *
             * This event is triggered only when a depressed key is released.
             * The callback is passed the key that was released
             *
             * @see onKeyDown
             */
            int onKeyUp(Callback<Key> callback);

            /**
             * @brief Add an event listener to a key down event
             * @param callback Function to be executed when the key is down
             * @return The event listeners identification number
             *
             * This event will continue to fire while a key is held down
             *
             * @see onKeyUp
             */
            int onKeyDown(Callback<Key> callback);

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
             * @brief Handle a system event
             * @param event Event to be handled
             */
            void handleEvent(Event event);

        private:
            EventEmitter eventEmitter_; //!< Event publisher
        };
    }
}

#endif // IME_KEYBOARD_H
