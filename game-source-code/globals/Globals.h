/**
 * @brief Stores shared/common definitions and/or declarations (structs, constants etc)
 */

#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals{
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