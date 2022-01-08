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

#ifndef IME_MOUSE_H
#define IME_MOUSE_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/core/event/EventEmitter.h"

namespace ime {
    class Event;

    /**
     * @brief Mouse events
     */
    enum class MouseEvent {
        MouseDown,       //!< Fired when mouse is depressed
        MouseUp,         //!< Fired when depressed mouse is released
        MouseMove,       //!< Fired when the mouse is moved
        MouseWheelScroll //!< Fired when the mouse wheel is scrolled
    };

    namespace input {
        /**
         * @brief Captures mouse inputs from the user
         *
         * This class is not meant to be instantiated directly, use
         * ime::Scene::input or ime::Engine::getInputManager
         */
        class IME_API Mouse {
        public:
            /**
             * @brief Mouse buttons
             */
            enum class Button {
                Left,      //!< The left mouse button
                Right,     //!< The right mouse button
                Middle,    //!< The middle (wheel) mouse button
                XButton1,  //!< The first extra mouse button
                XButton2,  //!< The second extra mouse button
            };

            /**
             * @brief Mouse wheels
             */
            enum class Wheel {
                VerticalWheel,  //!< The vertical mouse wheel
                HorizontalWheel //!< The horizontal mouse wheel
            };

            /**
             * @brief Convert an enum Button value to its string representation
             * @param button The button to be converted
             * @return The given button as a string
             *
             * The returned string is the same as the enum value, that is, if
             * @a button is Button::Left then the function will return "Left"
             */
            static std::string buttonToString(Button button);

            /**
             * @brief Convert a string representation of a button to enum value
             * @param button The button to be converted
             * @return The given key as an enum key value
             *
             * The returned enum button value is the same as the string value,
             * that is, if @a button is "Left" then the function will return
             * Button::Left
             *
             * @warning If the given string is not convertible to an enum button
             * value, them the program will exit with an error
             */
            static Button stringToButton(const std::string& button);

            /**
            * @brief Check if a mouse button is pressed or not
            * @param button Mouse button to be checked
            * @return True if a mouse button is pressed, otherwise false
             *
             * This function checks the state of a mouse button in real
             * time, unlike all the other function which are event-based
            */
            static bool isButtonPressed(Button button);

            /**
             * @brief Set the current position of the mouse in desktop coordinates
             * @param position New position of the mouse
             *
             * This function sets the global position of the mouse cursor on
             * the desktop. To set the position of the mouse cursor relative
             * to the game window, use ime::Window::setRelativeMousePosition
             *
             * @see getPosition
             */
            static void setPosition(const Vector2i& position);

            /**
             * @brief Get the current position of the mouse in desktop coordinates
             * @return The current position of the mouse
             *
             * This function returns the global position of the mouse cursor
             * on the desktop. To get the position of the mouse cursor relative
             * to the game window, use ime::Window::getRelativeMousePosition
             *
             * @see setPosition
             */
            static Vector2i getPosition();

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
            int onButtonUp(Callback<Button, int, int> callback);

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
            int onButtonUp(Callback<Button> callback);

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
             * @note This event does Not fire repetitively while the
             * mouse button is depressed
             */
            int onButtonDown(Callback<Button, int, int> callback);

            /**
             * @brief Add an event listener to a mouse button down event
             * @param callback The function to be executed when the mouse
             *                 button is depressed
             * @return The event listeners identification number
             *
             * The callback is passed the button that was depressed
             *
             * @note This event does Not fire repetitively while the
             * mouse button is depressed
             */
            int onButtonDown(Callback<Button> callback);

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
            int onWheelScroll(Callback<Wheel, float, int, int> callback);

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
             * @internal
            * @brief Handle a system event
            * @param event Event to be handled
             *
             * @warning This function is intended for internal use only and
             * should never be called outside of IME
            */
            void handleEvent(Event event);

        private:
            EventEmitter eventEmitter_; //!< Event publisher
        };
    }

    using Mouse = ime::input::Mouse; //!< ime::input::Mouse alias
}

#endif // IME_MOUSE_H
