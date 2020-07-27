/**
 * @brief Interface for movable game entities
 */

#ifndef IMOVABLE_H
#define IMOVABLE_H

namespace SI {
    class IMovableEntity {
    public:
        /**
         * @brief move entity in current direction at current speed
         * @param deltaTime Amount of time passed since entity last moved
         */
        virtual void move(float deltaTime) = 0;

        /**
         * @brief Set the speed of the entity
         * @param speed New speed of the entity
         *
         * This function overrides the previous speed
         * of the entity
         */
        virtual void setSpeed(float speed) = 0;

        /**
         * @brief Increase/decrease the speed of the entity
         * @param speed Amount of speed to be added/subtracted
         *        from the current speed
         */
        virtual void adjustSpeed(float speed) = 0;
    };
}

#endif
