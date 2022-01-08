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

#ifndef IME_KEYBOARD_H
#define IME_KEYBOARD_H

#include "IME/Config.h"
#include "IME/core/event/EventEmitter.h"
#include <unordered_map>

namespace ime {
    class Event;

    /**
     * @brief Keyboard events
     */
    enum class KeyboardEvent {
        KeyUp,   //!< Fired when depressed/held key is released
        KeyDown, //!< Fired when key is depressed for the first time
        KeyHeld  //!< Fired when a depressed key remains held
    };

    namespace input {
        /**
         * @brief Captures keyboard inputs from the user
         *
         * This class is not meant to be instantiated directly, use
         * ime::Scene::input or ime::Engine::getInputManager
         */
        class IME_API Keyboard {
        public:
            /**
             * @brief keyboard key codes
             */
            enum class Key {
                Unknown = -1, ///< Unhandled key
                A = 0,        ///< The A key
                B,            ///< The B key
                C,            ///< The C key
                D,            ///< The D key
                E,            ///< The E key
                F,            ///< The F key
                G,            ///< The G key
                H,            ///< The H key
                I,            ///< The I key
                J,            ///< The J key
                K,            ///< The K key
                L,            ///< The L key
                M,            ///< The M key
                N,            ///< The N key
                O,            ///< The O key
                P,            ///< The P key
                Q,            ///< The Q key
                R,            ///< The R key
                S,            ///< The S key
                T,            ///< The T key
                U,            ///< The U key
                V,            ///< The V key
                W,            ///< The W key
                X,            ///< The X key
                Y,            ///< The Y key
                Z,            ///< The Z key
                Num0,         ///< The 0 key
                Num1,         ///< The 1 key
                Num2,         ///< The 2 key
                Num3,         ///< The 3 key
                Num4,         ///< The 4 key
                Num5,         ///< The 5 key
                Num6,         ///< The 6 key
                Num7,         ///< The 7 key
                Num8,         ///< The 8 key
                Num9,         ///< The 9 key
                Escape,       ///< The Escape key
                LControl,     ///< The left Control key
                LShift,       ///< The left Shift key
                LAlt,         ///< The left Alt key
                LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
                RControl,     ///< The right Control key
                RShift,       ///< The right Shift key
                RAlt,         ///< The right Alt key
                RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
                Menu,         ///< The Menu key
                LBracket,     ///< The [ key
                RBracket,     ///< The ] key
                Semicolon,    ///< The ; key
                Comma,        ///< The , key
                Period,       ///< The . key
                Quote,        ///< The ' key
                Slash,        ///< The / key
                Backslash,    ///< The \ key
                Tilde,        ///< The ~ key
                Equal,        ///< The = key
                Hyphen,       ///< The - key (hyphen)
                Space,        ///< The Space key
                Enter,        ///< The Enter/Return keys
                Backspace,    ///< The Backspace key
                Tab,          ///< The Tabulation key
                PageUp,       ///< The Page up key
                PageDown,     ///< The Page down key
                End,          ///< The End key
                Home,         ///< The Home key
                Insert,       ///< The Insert key
                Delete,       ///< The Delete key
                Add,          ///< The + key
                Subtract,     ///< The - key (minus, usually from numpad)
                Multiply,     ///< The * key
                Divide,       ///< The / key
                Left,         ///< Left arrow
                Right,        ///< Right arrow
                Up,           ///< Up arrow
                Down,         ///< Down arrow
                Numpad0,      ///< The numpad 0 key
                Numpad1,      ///< The numpad 1 key
                Numpad2,      ///< The numpad 2 key
                Numpad3,      ///< The numpad 3 key
                Numpad4,      ///< The numpad 4 key
                Numpad5,      ///< The numpad 5 key
                Numpad6,      ///< The numpad 6 key
                Numpad7,      ///< The numpad 7 key
                Numpad8,      ///< The numpad 8 key
                Numpad9,      ///< The numpad 9 key
                F1,           ///< The F1 key
                F2,           ///< The F2 key
                F3,           ///< The F3 key
                F4,           ///< The F4 key
                F5,           ///< The F5 key
                F6,           ///< The F6 key
                F7,           ///< The F7 key
                F8,           ///< The F8 key
                F9,           ///< The F9 key
                F10,          ///< The F10 key
                F11,          ///< The F11 key
                F12,          ///< The F12 key
                F13,          ///< The F13 key
                F14,          ///< The F14 key
                F15,          ///< The F15 key
                Pause,        ///< The Pause key

                KeyCount,     ///< Keep last -- the total number of keyboard keys
            };

            /**
             * @brief Default constructor
             */
            Keyboard();

            /**
             * @brief Convert an enum Key value to its string representation
             * @param key The key to be converted
             * @return The given key as a string
             *
             * The returned string is the same as the enum value, that is, if
             * @a key is Key::Space then the function will return "Space"
             */
            static std::string keyToString(Key key);

            /**
             * @brief Convert a string representation of a key to its enum value
             * @param key The key to be converted
             * @return The given key as an enum key value
             *
             * The returned enum key value is the same as the string value,
             * that is, if @a key is "Space" then the function will return
             * Key::Space
             *
             * @warning If the given string is not convertible to an enum key
             * value, them the program will exit with an error
             */
            static Key stringToKey(const std::string& key);

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
             * This event is triggered only when a depressed/held key is
             * released. The callback is passed the key that was released
             *
             * @see onKeyDown and onKeyHeld
             */
            int onKeyUp(Callback<Key> callback);

            /**
             * @brief Add an event listener to a key down event
             * @param callback Function to be executed when the key is down
             * @return The event listeners identification number
             *
             * The key down event fires once when a key is depressed. If the
             * key remains depressed a key held event fires. In other words,
             * if you press and hold a key on the keyboard, the key down event
             * will fire once and wil not fire again until the key is released
             * and pressed again
             *
             * @see onKeyUp and onKeyHeld
             */
            int onKeyDown(Callback<Key> callback);

            /**
             * @brief Add an event listener to a key held event
             * @param callback Function to be executed when a key is held
             * @return The event listeners identification number
             *
             * The key held event will continue to fire while a key is held
             * down. The event always fires after a key down event. The
             * callback is passed the key that is held down
             *
             * @see onKeyDown
             */
            int onKeyHeld(Callback<Key> callback);

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
             * @internal
             * @brief Handle a system event
             * @param event Event to be handled
             *
             * @warning This function is intended for internal use only and
             * should never be called outside of IME
             */
            void handleEvent(Event event);

        private:
            EventEmitter eventEmitter_;             //!< Event publisher
            std::unordered_map<int, bool> wasDown_; //!< The state of a key in the previous frame
            inline static std::unordered_map<std::string, Key> stringKeyPairs_{};
        };
    }

    using Keyboard = ime::input::Keyboard; //!< ime::input::Keyboard alias
    using Key = ime::input::Keyboard::Key; //!< ime::input::Keyboard::Key alias
}

#endif // IME_KEYBOARD_H
