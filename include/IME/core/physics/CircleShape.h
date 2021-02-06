////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_CIRCLESHAPE_H
#define IME_CIRCLESHAPE_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/core/physics/Shape.h"

class b2CircleShape;

namespace ime {
    /**
     * @brief Specialized shape representing a circle
     */
    class IME_API CircleShape final : public Shape {
    public:
        /**
         * @brief Default constructor
         */
        CircleShape();

        /**
         * @brief Set the position of the circle
         * @param position The position of the circle
         */
        void setPosition(Vector2f position);

        /**
         * @brief Get the position of the circle
         * @return The position of the circle
         */
        Vector2f getPosition() const;

        /**
         * @brief Set the radius of the circle
         * @param radius The radius of the circle
         */
        void setRadius(float radius);

        /**
         * @brief Get the radius of the circle
         * @return The radius of the circle
         */
        float getRadius() const;

        /**
         * @internal
         * @brief Get the internal shape
         * @return The internal shape
         *
         * @warning This function is intended for internal use and should never
         * be called outside of IME
         */
        b2Shape* getInternalShape() override;
        const b2Shape* getInternalShape() const override;

        /**
         * @brief Destructor
         */
        ~CircleShape();

    private:
        b2CircleShape* circle_;  //!< Internal collision circle
    };
}

#endif //IME_CIRCLESHAPE_H
