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
 * @brief Class for managing keyboard and mouse inputs
 */

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "IME/core/input/Keyboard.h"
#include "IME/core/input/Mouse.h"

namespace IME {
    namespace Input {
        class InputManager {
        public:
            /**
             * @brief Check if a key is currently pressed or not
             * @param key Key to check
             * @return True if key is pressed, otherwise false
             */
            bool isKeyPressed(Keyboard::Key key) const;

            /**
             * @brief Add a key listener to a key event
             * @param event Name of the event to add key listener to
             * @param key Key to listen for
             * @param callback Function to execute when the key event is raised
             * @return The event listeners identification number or -1 if the
             *         specified key event is invalid
             */
            int addKeyListener(Keyboard::Event event, Keyboard::Key key, Callback<> callback);

            /**
             * @brief Add a key listener to any key pressed event
             * @param callback Function to execute when any key is pressed
             * @return The event listeners identification number
             *
             * This event only fires after a depressed key is released
             */
            int addAnyKeyUpListener(Callback<Keyboard::Key> callback);

            /**
             * @brief Add a key listener to any key pressed event
             * @param callback Function to execute when any key is pressed
             * @return The event listeners identification number
             *
             * This event will continue to fire will a key is depressed
             */
            int addAnyKeyDownListener(Callback<Keyboard::Key> callback);

            /**
             * @brief Remove a key event listener from a specific key event
             * @param event Event to remove listener from
             * @param key The key the event listener was listening for
             * @param id The identification number of the event listener
             * @return True if the key listener was removed or false if the
              *        specified event does not have a key listener with the
              *        specified id
             */
            bool removeKeyListener(Keyboard::Event event, Keyboard::Key key, int id);

            /**
             * @brief Remove an event listener from a key down or key up event
             * @param event Event to remove event listener from
             * @param callbackId Identification number of the listener to be removed
             * @return True if a listener was removed from an event, false if the
              *        specified event does not have a listener with the specified id
             */
            bool removeKeyListener(Keyboard::Event event, int id);

            /**
             * @brief Check if a mouse button is currently pressed or not
             * @param button Mouse button to check
             * @return True if mouse button is pressed, otherwise false
             */
            bool isMouseDown(Mouse::Button button) const;

            /**
             * @brief Add a mouse listener to a mouse event
             * @param event Name of the event to add mouse listener to
             * @param button Mouse button to listen for
             * @param callback Function to execute when the mouse event is raised
             * @return The event listeners identification number or -1 if the
             *         specified mouse event is invalid
             *
             * The callback will be passed the coordinates of where the mouse
             * event took place. That is, the coordinates of where the mouse was
             * depressed or released
             */
            int addMouseButtonListener(Mouse::Event event, Mouse::Button button,
                Callback<int, int> callback);

            /**
             * @brief Add an event listener to a mouse moved event
             * @param callback Function to execute when the mouse is moved
             * @return The event listeners identification number
             *
             * The callback will be invoked and passed the coordinates of the
             * mouse cursor everytime the mouse moves
             */
            int addMouseMovedListener(Callback<int, int> callback);

            /**
             * @brief Remove a mouse event listener from a mouse event
             * @param event Event to remove listener from
             * @param button Button the event listener was listening for
             * @param id Identification number of the event listener
             * @return True if a listener was removed from an event, false if the
              *        specified event does not have a listener with the specified id
             */
            bool removeMouseListener(Mouse::Event event, Mouse::Button button, int id);

            /**
             * @brief Remove an event listener from a mouse moved event listener
             * @param id Identification number of the mouse move event listener
             * @return True if a listener was removed from an event or false if
              *        the mouse move event does not have a listener with the
              *        specified id
             */
            bool removeMouseMovedListener(int id);

            /**
             * @brief Update the event manager
             * @param event Event
             *
             * @warning This function is crucial to the proper functioning of
             * the input manager, It must be called when handling input so
             * that event listeners are notified. Failure to call this function
             * will result in key event listeners not being called
             */
            void handleEvent(sf::Event event);

        private:
            //Managed keyboard
            Keyboard keyboard_;
            //Managed Mouse
            Mouse mouse_;
        };
    }
} // namespace IME

#endif
