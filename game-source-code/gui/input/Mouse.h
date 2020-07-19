/**
 * @brief Class for capturing mouse inputs
 */

#ifndef MOUSE_H
#define MOUSE_H

#include "event/EventEmitter.h"

namespace IME {
    namespace Input {
        class Mouse {
        public:
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
             * @brief Add an event listener to a mouse button up event
             * @param button Mouse button to listen for
             * @param callback Function to execute when the mouse button is released
             * @return Event listeners identification number
             *
             * A button up event fires when a mouse button is released. This event always
             * fires after a mouse button down event @see onButtonDown(Button, Callback)
             */
            static int onButtonUp(Button button, Callback<> callback);

            /**
             * @brief Add an event listener to mouse button down event
             * @param button Mouse button to listen for
             * @param callback Function to execute when mouse button is down
             * @return Event listeners identification number
             *
             * A button down event fires when you depress a mouse button. @note This
             * event does not fire repetitively while the mouse button remains depressed
             */
            static int onButtonDown(Button button, Callback<> callback);

            /**
             * @brief Add an event listener to a mouse move event
             * @param callback Function to execute when the mouse moves
             * @return Event listeners identification number
             *
             * The callback function will be invoked with the new position (int, int)
             * of the mouse cursor
             */
            static int onMouseMove(Callback<int, int> callback);

            /**
              * @brief  Remove an event listener from an event
              * @param  event Event to remove listener from
              * @param  button Mouse button to remove event listener from
              * @param  listenerId Identification number of the listener to be removed
              * @return True if a listener was removed from an event, false if the
              *         specified event does not have a listener with the specified id
              */
            static bool removeEventListener(const std::string &event, Button button,
                int listenerId);

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
    }
}

#endif
