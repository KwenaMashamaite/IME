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
 * @brief Class for capturing mouse inputs
 */

#ifndef IME_MOUSE_H
#define IME_MOUSE_H

#include "IME/core/event/EventEmitter.h"
#include <SFML/Window/Event.hpp>

namespace IME {
    namespace Input {
        class Mouse {
        public:
            enum class Event {
                MouseDown,
                MouseUp
            };

            /**
             * @brief Mouse Buttons
             */
            enum class Button {
                Left,
                Right,
                Middle
            };

            /**
            * @brief Check if a mouse button is pressed or not
            * @param button Mouse button to check
            * @return true if mouse button is pressed, false if not pressed
             *
             * This function checks the state of a mouse button in real time
            */
            static bool isButtonPressed(Button button);

            /**
            * @brief Handle event
            * @param event Event to handle
            *
            * This function must be called once per frame in order for the object
            * to determine if a mouse was pressed, released or moved
            */
            void handleEvent(sf::Event event);

            /**
             * @brief Add an event listener to a mouse button up event
             * @param button Mouse button to listen for
             * @param callback Function to execute when the mouse button is released
             * @return Event listeners identification number
             *
             * A button up event fires when a mouse button is released. This event always
             * fires after a mouse button down event @see onButtonDown(Button, Callback).
             * The callback will be passes the coordinates of where the button was released
             */
            int onButtonUp(Button button, Callback<int, int> callback);

            /**
             * @brief Add an event listener to mouse button down event
             * @param button Mouse button to listen for
             * @param callback Function to execute when mouse button is down
             * @return Event listeners identification number
             *
             * A button down event fires when you depress a mouse button. @note This
             * event does not fire repetitively while the mouse button remains depressed.
             * The callback will be passes the coordinates of where the button was
             * depressed
             */
            int onButtonDown(Button button, Callback<int, int> callback);

            /**
             * @brief Add an event listener to a mouse move event
             * @param callback Function to execute when the mouse moves
             * @return Event listeners identification number
             *
             * The callback function will be invoked with the new position (int, int)
             * of the mouse cursor
             */
            int onMouseMove(Callback<int, int> callback);

            /**
              * @brief  Remove an event listener from an event
              * @param  event Event to remove listener from
              * @param  button Mouse button to remove event listener from
              * @param  listenerId Identification number of the listener to be removed
              * @return True if a listener was removed from an event, false if the
              *         specified event does not have a listener with the specified id
              */
            bool removeEventListener(Event event, Button button,
                int listenerId);

            /**
             * @brief Remove a mouse moved event listener
             * @param id Identification number of the event listener
             * @return True if the event listener was removed or false if the
             *         event listener does not exist
             */
            bool removeMouseMovedListener(int id);

        private:
            //Event Emitter/publisher
            EventEmitter eventEmitter_{};
        };
    }
} // namespace IME

#endif
