/**
 * @brief Stores shared/common definitions and/or declarations (structs, constants, events etc)
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include "event/Event.h"
#include "input/InputManager.h"

namespace Globals{
    /**
	 * @brief List of global events that can be subscribed to
	 */
    struct Events{
        /**
         * @brief Request to close window event. Passes no arguments on notify
         */
        inline static Event<> windowClose;

        /**
         * @brief Key was pressed event. Passes the key that was pressed on notify
         */
        inline static Event<InputManager::Key> keyPressed;

        /**
         * @brief Key was released event. passes the key that was released as an argument on notify
         */
        inline static Event<InputManager::Key> keyReleased;

        /**
         * @brief Mouse was moved event. Passes the new position of the mouse as arguments on notify
         */
        inline static Event<int, int> mouseMoved;

        /**
         * @brief Mouse button was pressed event. Passes the mouse button that was pressed and the
         *        position of the mouse as arguments on notify
         */
        inline static Event<InputManager::MouseButton, int, int> mouseButtonPressed;

        /**
         * @brief Mouse button was released event. Passes the mouse button that was released and the
         *        position of the mouse as arguments on notify
         */
        inline static Event<InputManager::MouseButton, int, int> mouseButtonReleased;
    };

    /**
     * @brief Dimensions
     */
    struct Dimensions{
        unsigned int width;
        unsigned int height;
    };

    /**
     * @brief Position
     */
    struct Position{
        float x;
        float y;
    };
};

#endif