/**
 * @brief Stores shared/common definitions and/or declarations (structs, constants, events etc)
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include "event/Event.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"

namespace Globals{
    /**
	 * @brief List of global events that can be subscribed to
	 */
    struct Events{
        /**
         * @brief Request to close window event. Passes no arguments on notify
         */
        inline static Event<> windowClose;
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