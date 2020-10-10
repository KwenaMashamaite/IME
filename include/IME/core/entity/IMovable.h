/**
 * @brief Interface for movable entities
 */

#ifndef IMOVABLE_H
#define IMOVABLE_H

namespace IME {
    class IMovable {
    public:
        /**
         * @brief Move the object in the current direction at the current speed
         */
        virtual void move() = 0;

        /**
         * @brief Set the speed of the object
         * @param speed The new speed of the object
         *
         * The default speed is 0
         */
        virtual void setSpeed(float speed) = 0;

        /**
         * @brief Get the speed of the object
         * @return The speed of the object
         */
        virtual float getSpeed() const = 0;

        /**
         * @brief Check if object is moving or not
         * @return True if object is moving, otherwise false
         */
        virtual bool isMoving() const = 0;

        /**
         * @brief Stop a moving object
         *
         * This function does nothing if the object is not moving
         */
        virtual void stop() = 0;
    };
}

#endif
