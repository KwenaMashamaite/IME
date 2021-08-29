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

#ifndef IME_JOYSTICK_H
#define IME_JOYSTICK_H

#include "IME/Config.h"
#include "IME/core/event/EventEmitter.h"

namespace ime {
    class Event;

    namespace input {
        /**
         * @brief Joystick events
         */
        enum class JoystickEvent {
            Connect,        //!< Fired when a joystick is connected
            Disconnect,     //!< Fired when a joystick is disconnected
            ButtonPress,    //!< Fired when a joystick button is pressed
            ButtonRelease,  //!< Fired when a joystick button is released
            AxisMove        //!< Fired when the axis of a joystick is moved
        };

        /**
         * @brief Give access to the state of the joysticks
         *
         * This class is not meant to be instantiated directly, use
         * ime::Scene::input or ime::Engine::getInputManager
         */
        class IME_API Joystick {
        public:
            /**
             * @brief Joystick related constants
             */
            enum {
                Count       = 8,  //!< Maximum number of supported joysticks
                ButtonCount = 32, //!< Maximum number of supported buttons
                AxisCount   = 8   //!< Maximum number of supported axes
            };

            /**
             * @brief Axes supported by IME joysticks
             */
            enum class Axis {
                X,    //!< The X axis
                Y,    //!< The Y axis
                Z,    //!< The Z axis
                R,    //!< The R axis
                U,    //!< The U axis
                V,    //!< The V axis
                PovX, //!< The X axis of the point-of-view hat
                PovY  //!< The Y axis of the point-of-view hat
            };

            /**
             * @brief Stores a joystick's identification
             */
            struct Identification {
                /**
                 * @brief Default constructor
                 *
                 * By default:
                 *  name       = "No Joystick"
                 *  vendorId   = 0
                 *  productId  = 0
                 */
                Identification();

                std::string       name; //!< Name of the joystick
                unsigned int vendorId;  //!< Manufacturer identifier
                unsigned int productId; //!< Product identifier
            };

            /**
             * @brief Check if a joystick is connected
             * @param joystick Index of the joystick to check
             * @return True if the joystick is connected, otherwise false
             *
             * This function checks the state of a key in real time, unlike
             * all the other function which are event-based
             */
            static bool isConnected(unsigned int joystick);

            /**
             * @brief Get the number of buttons supported by a joystick
             * @param joystick Index of the joystick
             * @return The number of buttons supported by the joystick
             *
             * If the joystick is not connected, this function returns 0.
             */
            static unsigned int getButtonCount(unsigned int joystick);

            /**
             * @brief Check if a joystick supports a given axis
             * @param joystick Index of the joystick
             * @param axis The axis to be checked
             * @return True if the joystick supports the axis, otherwise false
             *
             * If the joystick is not connected, this function returns false
             */
            static bool hasAxis(unsigned int joystick, Axis axis);

            /**
             * @brief Check if a joystick button is pressed
             * @param joystick Index of the joystick
             * @param button Button to be checked
             * @return True if the button is pressed, otherwise false
             *
             * If the joystick is not connected, this function returns false
             *
             * This function checks the state of a key in real time, unlike
             * all the other function which are event-based
             */
            static bool isButtonPressed(unsigned int joystick, unsigned int button);

            /**
             * @brief Get the current position of a joystick axis
             * @param joystick Index of the joystick
             * @param axis The axis to be checked
             * @return The current position of the axis, in range [-100 .. 100]
             *
             * If the joystick is not connected, this function returns 0
             *
             * This function checks the state of a key in real time, unlike
             * all the other function which are event-based
             */
            static float getAxisPosition(unsigned int joystick, Axis axis);

            /**
             * @brief Get the joystick's identification information
             * @param joystick Index of the joystick
             * @return A joystick's identification information
             */
            static Identification getIdentification(unsigned int joystick);

            /**
             * @brief Add an event listener to a connection event
             * @param callback Function to be executed when a joystick is
             *                 connected
             * @return The event listeners identification number
             *
             * The callback is passed the index of the joystick on invocation
             */
            int onConnect(const Callback<unsigned int>& callback);

            /**
             * @brief Add an event listener to a disconnection event
             * @param callback Function to be executed when a joystick is
             *                 disconnected
             * @return The event listeners identification number
             *
             * The callback is passed the index of the joystick on invocation
             */
            int onDisconnect(const Callback<unsigned int>& callback);

            /**
             * @brief Add an event listener to a button press event
             * @param callback The function to be executed when a button is pressed
             * @return The event listeners identification number
             *
             * A button press event does not fire while the button is held down
             *
             * The callback is passed the index of the joystick and the button
             * that was pressed respectively
             */
            int onButtonPress(const Callback<unsigned int, unsigned int>& callback);

            /**
             * @brief Add an event listener to button release event
             * @param callback The function to be executed when a button is released
             * @return The event listeners identification number
             *
             * The callback is passed the index of the joystick and the button
             * that was released respectively
             */
            int onButtonRelease(const Callback<unsigned int, unsigned int>& callback);

            /**
             * @brief Add an event listener to an axis move event
             * @param callback The function to be executed when an axis is moved
             * @return The event listeners identification number
             *
             * The callback is passed the index of the joystick, the axis that
             * was moved and its new position respectively
             */
            int onAxisMove(const Callback<unsigned int, Axis, float>& callback);

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
             * @brief Handle a system event
             * @param event Event to be handled
             *
             * @warning This function is intended for internal use only and
             * should never be called outside of IME
             */
            void handleEvent(Event event);

        private:
            EventEmitter emitter_; //!<
        };
    }
}

#endif //IME_JOYSTICK_H
