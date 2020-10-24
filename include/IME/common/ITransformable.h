

#ifndef ITRANSFORMABLE_H
#define ITRANSFORMABLE_H

#include "IME/common/Position.h"

namespace IME {
    class ITransformable {
    public:
        /**
         * @brief Set the position of the object
         * @param X coordinate of the new position
         * @param Y coordinate of the new position
         *
         * This function completely overwrites the previous position.
         * See the move function to apply an offset based on the previous
         * position instead. The default position of a transformable object
         * is (0, 0).
         */
        virtual void setPosition(float x, float y) = 0;

        /**
         * @brief Set the position of the object
         * @param position New position
         *
         * This function completely overwrites the previous position.
         * See the move function to apply an offset based on the previous
         * position instead. The default position of a transformable object
         * is (0, 0).
         */
        virtual void setPosition(Position position) = 0;

        /**
         * @brief Set the orientation of the object
         * @param angle New rotation, in degrees
         *
         * This function completely overwrites the previous rotation.
         * See the rotate function to add an angle based on the previous
         * rotation instead. The default rotation of a transformable object
         * is 0.
         */
        virtual void setRotation(float angle) = 0;

        /**
         * @brief set the scale factors of the object
         * @param factorX New horizontal scale factor
         * @param factorY New vertical scale factor
         *
         * This function completely overwrites the previous scale.
         */
        virtual void setScale(float factorX, float factorY) = 0;

        /**
         * @brief set the local origin of the object
         * @param x X coordinate of the new origin
         * @param y Y coordinate of the new origin
         *
         * The origin of an object defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the object, and ignore all
         * transformations (position, scale, rotation).
         * The default origin of a transformable object is (0, 0).
         */
        virtual void setOrigin(float x, float y) = 0;

        /**
         * @brief Get the position of the object
         * @return Current position of the object
         */
        virtual Position getPosition() const = 0;

        /**
         * @brief Get the local origin of the object
         * @return get the local origin of the object
         */
        virtual Position getOrigin() const = 0;

        /**
         * @brief Get the orientation of the object
         * @return Current rotation, in degrees
         *
         * The rotation is always in the range [0, 360].
         */
        virtual float getRotation() const = 0;

        /**
         * @brief Move the object by a given offset
         * @param offsetX Horizontal offset
         * @param offsetY Vertical offset
         *
         * This function adds to the current position of the object,
         * unlike setPosition which overwrites it.
         */
        virtual void move(float offsetX, float offsetY) = 0;

        /**
         * @brief Rotate the object
         * @param angle Angle of rotation, in degrees
         *
         * This function adds to the current rotation of the object,
         * unlike setRotation which overwrites it
         */
        virtual void rotate(float angle) = 0;

        /**
         * @brief Scale the object
         * @param factorX Horizontal scale factor
         * @param factorY Vertical scale factor
         *
         * This function multiplies the current scale of the object,
         * unlike setScale which overwrites it.
         */
        virtual void scale(float factorX, float factorY) = 0;
    };
}

#endif
