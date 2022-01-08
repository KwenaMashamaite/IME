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
#include "IME/core/input/Joystick.h"
#include "IME/core/event/Event.h"

namespace ime {
    namespace input {
        /**
         * @brief Action triggers for key binds
         */
        enum class KeyBindType {
            KeyUp,   //!< The action is triggered when a depressed/held key is released
            KeyDown, //!< The action is triggered when a key is depressed
            KeyHeld  //!< The action is triggered when a depressed key remains held
        };

        using KeybindAction = Callback<>; //!< An action performed when a key bind is triggered

        /**
         * @brief Manages keyboard and mouse inputs
         *
         * This class is not meant to be instantiated directly, use
         * ime::Scene::input or ime::Engine::getInputManager
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
            static bool isKeyPressed(Keyboard::Key key) ;

            /**
             * @brief Bind a key to an action
             * @param key The key to bind the action to
             * @param type The type of key bind
             * @param action The action to be performed when the key is triggered
             * @return The actions unique identifier
             *
             * @see unbindKey
             */
            int bindKey(Keyboard::Key key, KeyBindType type, const KeybindAction& action);

            /**
             * @brief Bind a two key combination to an action
             * @param keyA The first key
             * @param keyB The second key
             * @param keyBindType The type of key bind (key down or key held only)
             * @param action The action to be performed when the two keys are triggered
             * @return The actions unique identifier
             *
             * Note that if @a keyBindType is ime::input::KeyBindType::KeyUp,
             * the key bind will be ignored
             *
             * @see bindKey, unbindKey
             */
            int bindKeys(Keyboard::Key keyA, Keyboard::Key keyB, KeyBindType keyBindType,
                const KeybindAction& action);

            /**
             * @brief Unbind a key action
             * @param keyBindType The type of key action to unbind
             * @param id The id of the action
             * @return True if the action was unbounded or false if no such
             *         binding key exists
             *
             * @see bindKey
             */
            bool unbindKey(KeyBindType keyBindType, int id);

            /**
             * @brief Add an event listener to a key up event
             * @param callback Function to be executed when the key is released
             * @return The event listeners identification number
             *
             * This event is triggered only when a depressed/held key is
             * released. The callback is passed the key that was released
             *
             * @see onKeyDown and onKeyHeld
             */
            int onKeyUp(Callback<Keyboard::Key> callback);

            /**
             * @brief Add an event listener to a key down event
             * @param callback Function to be executed when a key is down
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
            int onKeyDown(Callback<Keyboard::Key> callback);

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
            int onKeyHeld(Callback<Keyboard::Key> callback);

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
            static bool isMouseDown(Mouse::Button button) ;

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
             * @brief Add an event listener to a joystick connection event
             * @param callback Function to be executed when a joystick is
             *                 connected
             * @return The event listeners identification number
             *
             * The callback is passed the index of the joystick on invocation
             */
            int onJoyConnect(const Callback<unsigned int>& callback);

            /**
             * @brief Add an event listener to a joystick disconnect event
             * @param callback Function to be executed when a joystick is
             *                 disconnected
             * @return The event listeners identification number
             *
             * The callback is passed the index of the joystick on invocation
             */
            int onJoyDisconnect(const Callback<unsigned int>& callback);

            /**
             * @brief Add an event listener to a joystick button press event
             * @param callback The function to be executed when a joystick
             *                 button is pressed
             * @return The event listeners identification number
             *
             * A button press event does not fire while the button is held down
             *
             * The callback is passed the index of the joystick and the button
             * that was pressed respectively
             */
            int onJoyButtonPress(const Callback<unsigned int, unsigned int>& callback);

            /**
             * @brief Add an event listener to joystick button release event
             * @param callback The function to be executed when a joystick
             *                 button is released
             * @return The event listeners identification number
             *
             * The callback is passed the index of the joystick and the button
             * that was released respectively
             */
            int onJoyButtonRelease(const Callback<unsigned int, unsigned int>& callback);

            /**
             * @brief Add an event listener to an joystick axis move event
             * @param callback The function to be executed when the axis of
             *                 a joystick is moved
             * @return The event listeners identification number
             *
             * The callback is passed the index of the joystick, the axis that
             * was moved and its new position respectively
             */
            int onJoyAxisMove(const Callback<unsigned int, Joystick::Axis, float>& callback);

            /**
             * @brief Remove an event listener from a joystick event
             * @param event The event to remove the event listener from
             * @param id The event listeners identification number
             * @return True if the event listener was removed or false if
             *         the given event does not have the specified event
             *         listener
             */
            bool unsubscribe(JoystickEvent event, int id);

            /**
             * @internal
             * @brief Update the event manager
             * @param event Event to be handled
             *
             * @warning This function is intended for internal use only and
             * should never be called outside of IME
             */
            void handleEvent(Event event);

        private:
            Keyboard keyboard_; //!< Managed keyboard
            Mouse mouse_;       //!< Managed Mouse
            Joystick joystick_; //!< Managed Joystick
        };
    }
}

#endif // IME_INPUTMANAGER_H
