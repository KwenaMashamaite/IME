/**
 * @brief Defines a point in a 2D space
 */

#ifndef POSITION_H
#define POSITION_H

namespace IME {
    struct Position {
        /**
         * @brief Check if a position is the same as this position or not
         * @param other The position to check against for equality
         * @return True if the two positions are the same, otherwise false
         */
        bool operator==(const Position& other);

        /**
         * @brief Check if a position is not the same as this position
         * @param other The position to check against for inequality
         * @return True if the two positions are not the same otherwise false
         */
        bool operator!=(const Position& other);

        //Horizontal coordinate
        float x;
        //Vertical coordinate
        float y;
    };
}

#endif
