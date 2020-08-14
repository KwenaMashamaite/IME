/**
 * @brief Class for capturing keyboard inputs
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "IME/event/EventEmitter.h"

namespace IME {
    namespace Input {
        class Keyboard {
        public:
            /**
             * @brief keyboard keys
             */
            enum class Key {
                A, B, C,
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
             * @brief Constructor
             */
            Keyboard();

            /**
             * @brief Check if key is pressed or not
             * @param key Key to check
             * @return true if key is pressed, false if it not pressed
             *
             * This function checks the state of a key in real time
             */
            static bool isKeyPressed(Key key);

            /**
              * @brief Add an event listener to a key down event
              * @param key Key to listen for
              * @param callback Function to execute when the key is down
              * @return Event listener's identification number
              *
              * A key down event fires when a key is pressed on the keyboard and
              * continues to fire while that key is held down
              */
            static int onKeyDown(Key key, Callback<> callback);

            /**
              * @brief Add an event listener to a key up event
              * @param key Key to listen for
              * @param callback Function to execute when the key is released
              * @return Event listener's identification number
              *
              * A key up event fires when a key is released on the keyboard. This event
              * always fires after a key down event @see onKeyDown(Key, Callback)
              */
            static int onKeyUp(Key key, Callback<> callback);

            /**
              * @brief  Remove an event listener from an event
              * @param  event Event to remove listener from
              * @param  key Key to remove event listener from
              * @param  listenerId Identification number of the listener to be removed
              * @return True if a listener was removed from an event, false if the
              *         specified event does not have a listener with the specified id
              */
            static bool
            removeEventListener(const std::string &event, Key key, int callbackId);

        private:
            /**
             * @brief Initialize the event emitter for event publishing
             */
            static void initEventEmitter();

        private:
            //Event Emitter/publisher
            inline static EventEmitter eventEmitter_{};
            //State of the event emitter (Since class can be used without instance)
            inline static auto isEventEmitterInitialized_{false};
        };
    } // namespace Gui
} // namespace IME

#endif
