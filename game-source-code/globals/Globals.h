/**
 * @brief Stores shared/common definitions and/or declarations (structs, constants, events etc)
 */

#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals{
    /**
     * @brief Dimensions
     */
    struct Dimensions{
        float width;
        float height;
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