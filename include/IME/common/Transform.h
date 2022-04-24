////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef IME_TRANSFORM_H
#define IME_TRANSFORM_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Property.h"
#include "IME/core/event/EventEmitter.h"
#include <string>

namespace ime {
    /**
     * @brief Transform defined by a position, a rotation and a scale
     */
    class IME_API Transform {
    public:
        /**
         * @brief Default constructor
         */
        Transform();

        /**
         * @brief Set the position of the object
         * @param x X coordinate of the new position
         * @param y Y coordinate of the new position
         *
         * This function completely overwrites the previous position.
         * See the move function to apply an offset based on the previous
         * position instead. The default position of a transformable object
         * is (0, 0).
         */
        void setPosition(float x, float y);

        /**
         * @brief Set the position of the object
         * @param position New position
         *
         * This function completely overwrites the previous position.
         * See the move function to apply an offset based on the previous
         * position instead. The default position of a transformable object
         * is (0, 0).
         */
        void setPosition(const Vector2f& position);

        /**
         * @brief Get the position of the object
         * @return Current position of the object
         */
        const Vector2f& getPosition() const;

        /**
         * @brief Set the orientation of the object
         * @param angle New rotation, in degrees
         *
         * This function completely overwrites the previous rotation.
         * See the rotate function to add an angle based on the previous
         * rotation instead. The default rotation of a transformable object
         * is 0
         *
         * @see rotate
         */
        void setRotation(float angle);

        /**
         * @brief Rotate the object
         * @param angle Angle of rotation, in degrees
         *
         * This function adds to the current rotation of the object,
         * unlike setRotation which overwrites it
         *
         * @see setRotation
         */
        void rotate(float angle);

        /**
         * @brief Get the orientation of the object
         * @return Current rotation, in degrees
         *
         * The rotation is always in the range [0, 360]
         */
        float getRotation() const;

        /**
         * @brief Set the scale factors of the object
         * @param factorX New horizontal scale factor
         * @param factorY New vertical scale factor
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(float factorX, float factorY);

        /**
         * @brief Set the scale factor of the object
         * @param scale New scale
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(const Vector2f& scale);

        /**
         * @brief Scale the object by an offset
         * @param factorX Horizontal scale factor
         * @param factorY Vertical scale factor
         *
         * This function multiplies the current scale of the object,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(float factorX, float factorY);

        /**
         * @brief Scale the object by an offset
         * @param offset Offset to apply
         *
         * This function multiplies the current scale of the object,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(const Vector2f& offset);

        /**
         * @brief Get the current scale of the object
         * @return Current scale of the object
         */
        const Vector2f& getScale() const;

        /**
         * @brief Set the local origin of the object
         * @param x X coordinate of the new origin
         * @param y Y coordinate of the new origin
         *
         * The origin of an object defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the object, and ignore all
         * transformations (position, scale, rotation).
         *
         * The default origin of a transformable object is (0, 0)
         */
        void setOrigin(float x, float y);

        /**
         * @brief Set the local origin of the object
         * @param origin New origin
         *
         * The origin of an object defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the object, and ignore all
         * transformations (position, scale, rotation).
         * The default origin of a transformable object is (0, 0)
         */
        void setOrigin(const Vector2f& origin);

        /**
         * @brief Get the local origin of the object
         * @return Local origin of the object
         */
        const Vector2f& getOrigin() const;

        /**
         * @brief Move the object by a given offset
         * @param offsetX Horizontal offset
         * @param offsetY Vertical offset
         *
         * This function adds to the current position of the object,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(float offsetX, float offsetY);

        /**
         * @brief Move the object by a given offset
         * @param offset Offset to apply
         *
         * This function adds to the current position of the object,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(const Vector2f& offset);

        /**
         * @brief Add an event listener to a property change event
         * @param callback The function to be executed when a property changes
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * A property change event is triggered by any function that has a
         * 'set' prefix, that is a setter function. The name of the property
         * is the text that appears after the 'set' prefix in lowercase. For
         * example, the setPosition() function will trigger a 'position' change
         * event.
         *
         * The callback is passed a property object that has the name and
         * new value of the property that was changed. For example, the following
         * code prints the position (whenever it changes) to the standard output
         * stream:
         *
         * @code
         * // Register the event listener
         * int id = transform.onPropertyChange([](const ime::Property& property) {
         *      if (property.getName() == "position") {
         *          ime::Vector2f pos = property.getValue<ime::Vector2f>();
         *          std::cout << "New Position = " << pos.x << ", " << pos.y << std::endl;
         *      }
         * });
         *
         * // Trigger the event - This will set the new position and invoke position change listeners
         * transform.setPosition(100.0f, 50.0f);
         *
         * // Remove the event listener
         * transform.unsubscribe(id);
         * @endcode
         *
         * @see unsubscribe
         */
        int onPropertyChange(const Callback<Property>& callback, bool oneTime = false);

        /**
         * @brief Remove a property change event listener
         * @param id The identification number of the event listener
         * @return True if the event listener was removed or false if no such
         *         event listener exists
         *
         * @see onPropertyChange
         */
        bool unsubscribe(int id);

    private:
        Vector2f position_; //!< Position of the object in the 2D world
        Vector2f scale_;    //!< Scale of the object
        Vector2f origin_;   //!< Origin of translation/rotation/scaling of the object
        float rotation_;    //!< Orientation of the object, in degrees
        EventEmitter eventEmitter_; //!< Dispatches property change events
    };
}

#endif //IME_TRANSFORM_H
