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
            ButtonHeld,     //!< Fired when a joystick button is held
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
             * @internal
             * @brief Constructor
             * @param index The index of the joystick
             */
            explicit Joystick(unsigned int index);

            /**
             * @brief Check if the joystick is connected or not
             * @return True if the joystick is connected, otherwise false
             *
             * This function checks the state of the joystick in real time,
             * unlike all the other function which are event-based
             */
            bool isConnected() const;

            /**
             * @brief Enable or disable the joystick
             * @param enable True to enabled or false to disable
             *
             * When disabled, the joystick will no longer generate button press,
             * button release and axis move events. Connect and disconnect events
             * are dispatched regardless of the 'enable' state of the joystick
             *
             * By default the joystick is enabled
             *
             * @see isEnabled
             */
            void setEnable(bool enable);

            /**
             * @brief Check if the joystick is enabled or not
             * @return True if enabled, otherwise false
             *
             * @see setEnabled
             */
            bool isEnabled() const;

            /**
             * @brief Get the id of the joystick
             * @return The id of the joystick
             */
            unsigned int getIndex() const;

            /**
             * @brief Get the number of buttons supported by the joystick
             * @return The number of buttons supported by the joystick
             *
             * If the joystick is not connected, this function returns 0.
             */
            unsigned int getButtonCount() const;

            /**
             * @brief Check if a joystick supports a given axis
             * @param axis The axis to be checked
             * @return True if the joystick supports the axis, otherwise false
             *
             * If the joystick is not connected, this function returns false
             */
            bool hasAxis(Axis axis) const;

            /**
             * @brief Check if a button is pressed or not
             * @param button Button to be checked
             * @return True if the button is pressed, otherwise false
             *
             * If the joystick is not connected, this function returns false
             *
             * This function checks the state of a button in real time, unlike
             * all the other function which are event-based
             */
            bool isButtonPressed(unsigned int button) const;

            /**
             * @brief Get the current position of an axis
             * @param axis The axis to get the position of
             * @return The current position of the axis, in range [-100 .. 100]
             *
             * If the joystick is not connected, this function returns 0
             *
             * This function checks the position in real time, unlike
             * all the other function which are event-based
             */
            float getAxisPosition(Axis axis) const;

            /**
             * @brief Get the joystick's identification information
             * @param joystick Index of the joystick
             * @return A joystick's identification information
             */
            Identification getIdentification() const;

            /**
             * @brief Add an event listener to a connection event
             * @param callback Function to be executed when the joystick
             *                 is connected
             * @return The event listeners identification number
             *
             * @note If the joystick is already connected by the time the Engine
             * starts running, then this event will not be dispatched
             *
             * @see ime::Engine::run
             */
            int onConnect(const Callback<>& callback);

            /**
             * @brief Add an event listener to a disconnection event
             * @param callback Function to be executed when a joystick is
             *                 disconnected
             * @return The event listeners identification number
             */
            int onDisconnect(const Callback<>& callback);

            /**
             * @brief Add an event listener to a button press event
             * @param callback The function to be executed when a button is pressed
             * @return The event listeners identification number
             *
             * A button press event does not fire while the button is held down
             *
             * The callback is passed the button that was pressed
             *
             * @see onButtonRelease, onButtonHeld
             */
            int onButtonPress(const Callback<unsigned int>& callback);

            /**
             * @brief Add an event listener to button release event
             * @param callback The function to be executed when a button is released
             * @return The event listeners identification number
             *
             * The callback is passed the button that was released
             *
             * @see onButtonPress, onButtonHeld
             */
            int onButtonRelease(const Callback<unsigned int>& callback);

            /**
             * @brief Add an event listener to button held event
             * @param callback The function to be executed when a button is held
             * @return The event listeners identification number
             *
             * The callback is passed the button that is held
             *
             * @warning This function is experimental
             *
             * @see onButtonPress, onButtonRelease
             */
            int onButtonHeld(const Callback<unsigned int>& callback);

            /**
             * @brief Add an event listener to an axis move event
             * @param callback The function to be executed when an axis is moved
             * @return The event listeners identification number
             *
             * The callback is passed the axis that was moved and its new position
             * respectively
             */
            int onAxisMove(const Callback<Axis, float>& callback);

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

            /**
             * @internal
             * @brief Update
             *
             * @warning This function is intended for internal use only and
             * should never be called outside of IME
             */
            void update();

        private:
            bool isEnabled_;                                 //!< A flag indicating whether or not the joystick is enabled
            unsigned int index_;                             //!< Joystick identifier
            EventEmitter emitter_;                           //!< Emits events
            std::unordered_map<unsigned int, bool> wasDown_; //!< The state of a button in the previous frame
        };
    }
}

#endif //IME_JOYSTICK_H
