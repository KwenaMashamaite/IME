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

/**
 * @brief Class for capturing keyboard inputs
 */

#ifndef IME_KEYBOARD_H
#define IME_KEYBOARD_H

#include "IME/Config.h"
#include "IME/core/event/EventEmitter.h"
#include <SFML/Window/Event.hpp>

namespace IME {
    namespace Input {
        class IME_API Keyboard {
        public:
            enum class Event {
                KeyDown,
                KeyUp
            };

            /**
             * @brief keyboard keys
             */
            enum class Key {
                Unknown = -1, ///< Unhandled key
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
             * @brief Handle event
             * @param event Event to handle
             *
             * This function must be called at least once per frame in order for
             * the object to determine if a key was pressed or released or neither
             */
            void handleEvent(sf::Event event);

            /**
             * @brief Check if key is pressed or not
             * @param key Key to check
             * @return true if key is pressed, false if it not pressed
             *
             * This function checks the state of a key in real time
             */
            static bool isKeyPressed(Key key);

            /**
             * @brief Add an event listener to any key up event
             * @param callback Function to execute when the key is pressed
             * @return The event listeners identification number
             *
             * @note This event will only be triggered when the key is depressed
             * and released
             */
            int onKeyUp(Callback<Key> callback);

            /**
             * @brief Add an event listener to any key down event
             * @param callback Function to execute when the key is down
             * @return The event listeners identification number
             *
             * This event will continue to fire while any key is held down
             */
            int onKeyDown(Callback<Key> callback);

            /**
              * @brief Add an event listener to a specific key down event
              * @param key Key to listen for
              * @param callback Function to execute when the key is down
              * @return Event listener's identification number
              *
              * A key down event fires when a key is pressed on the keyboard and
              * continues to fire while that key is held down
              */
            int onKeyDown(Key key, Callback<> callback);

            /**
              * @brief Add an event listener to a specific key up event
              * @param key Key to listen for
              * @param callback Function to execute when the key is released
              * @return Event listener's identification number
              *
              * A key up event fires when a key is released on the keyboard. This event
              * always fires after a key down event @see onKeyDown(Key, Callback)
              */
            int onKeyUp(Key key, Callback<> callback);

            /**
              * @brief  Remove an event listener from an event
              * @param  event Event to remove listener from
              * @param  key Key to remove event listener from
              * @param  listenerId Identification number of the listener to be removed
              * @return True if a listener was removed from an event, false if the
              *         specified event does not have a listener with the specified id
              */
            bool removeEventListener(Event event, Key key, int callbackId);

            /**
             * @brief Remove an event listener from a key down or key up event
             * @param event Event to remove event listener from
             * @param callbackId Identification number of the listener to be removed
             * @return True if a listener was removed from an event, false if the
              *        specified event does not have a listener with the specified id
             */
            bool removeEventListener(Event event, int callbackId);

        private:
            //Event Emitter/publisher
            EventEmitter eventEmitter_;
        };
    }
} // namespace IME

#endif
