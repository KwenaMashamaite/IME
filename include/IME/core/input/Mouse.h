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

#ifndef IME_MOUSE_H
#define IME_MOUSE_H

#include "IME/Config.h"
#include "IME/core/event/EventEmitter.h"
#include <SFML/Window/Event.hpp>

namespace ime {
    namespace input {
        /**
         * @brief Class for capturing mouse inputs
         */
        class IME_API Mouse {
        public:
            /**
             * @brief Mouse events
             */
            enum class Event {
                MouseDown, //!< Fired when mouse is depressed
                MouseUp    //!< Fired when depressed mouse is released
            };

            /**
             * @brief Mouse buttons
             */
            enum class Button {
                Left,  //!< Left mouse button
                Right, //!< Right mouse button
                Middle //!< Middle mouse button
            };

            /**
            * @brief Check if a mouse button is pressed or not
            * @param button Mouse button to check
            * @return True if mouse button is pressed, false if not pressed
             *
             * This function checks the state of a mouse button in real time,
             * unlike all the other function which are event-based
            */
            static bool isButtonPressed(Button button);

            /**
             * @brief Add an event listener to a mouse button up event
             * @param button Mouse button to listen for
             * @param callback Function to execute when the mouse button is
             *                 released
             * @return The event listeners identification number
             *
             * This event is fired when the a depressed mouse button is
             * released. The callback is optionally passed the coordinates
             * of where the mouse button was released
             */
            int onButtonUp(Button button, Callback<int, int> callback);
            int onButtonUp(Button button, Callback<> callback);

            /**
             * @brief Add an event listener to mouse button down event
             * @param button Mouse button to listen for
             * @param callback Function to execute when mouse button is down
             * @return Event listeners identification number
             *
             * This event is fired when a mouse button is depressed. The
             * callback is optionally passed the coordinates of where the
             * mouse button was depressed
             *
             * @note This event does not fire repetitively while the mouse
             * button remains depressed
             */
            int onButtonDown(Button button, Callback<int, int> callback);
            int onButtonDown(Button button, Callback<> callback);

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
            * @brief Handle event
            * @param event Event to handle
            *
            * This function must be called at least once per frame in
            * order to determine the current frame state of a the mouse
            * (pressed, released, moved or no input)
            */
            void handleEvent(sf::Event event);

            /**
              * @brief  Remove an event listener from an event
              * @param  event Event to remove event listener from
              * @param  button Mouse button to remove event listener from
              * @param  id Identification number of the listener to be removed
              * @return True if the event listener was removed from the event,
              *         or false if the specified event does not have an event
              *         listener with the specified id
              */
            bool removeEventListener(Event event, Button button, int id);

            /**
             * @brief Remove a mouse moved event listener
             * @param id Identification number of the event listener
             * @return True if the event listener was removed from the event,
              *         or false if the specified event does not have an event
              *         listener with the specified id
             */
            bool removeMouseMovedListener(int id);

        private:
            EventEmitter eventEmitter_; //!< Event publisher
        };
    }
}

#endif // IME_MOUSE_H
