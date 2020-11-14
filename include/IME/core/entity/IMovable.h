////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Interface for movable entities
 */

#ifndef IME_IMOVABLE_H
#define IME_IMOVABLE_H

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

        /**
         * @brief Destructor
         */
        virtual ~IMovable() = default;
    };
}

#endif
