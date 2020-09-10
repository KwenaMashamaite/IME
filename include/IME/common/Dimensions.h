/**
 * @brief
 */

#ifndef DIMENSION_H
#define DIMENSION_H

namespace IME {
    struct Dimensions {
        /**
        * @brief Check if an object is the same as this object or not
        * @param other The object to check against for equality
        * @return True if the two objects are the same, otherwise false
        */
        bool operator==(const Dimensions& other);

        /**
         * @brief Check if object is not the same as this object
         * @param other The object to check against for inequality
         * @return True if the two objects are not the same otherwise false
         */
        bool operator!=(const Dimensions& other);

        float width;
        float height;
    };
}

#endif
