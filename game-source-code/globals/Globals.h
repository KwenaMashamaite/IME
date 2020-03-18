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

    /**
     * @brief Stores all game entity types
     *
     * Any Entity object that exists in the game must also be added
     * here
     */
    enum class EntityType{
        Player //An example
    };
};

#endif