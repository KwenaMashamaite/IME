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

#ifndef IME_RECTANGLESHAPE_H
#define IME_RECTANGLESHAPE_H

#include "IME/Config.h"
#include "IME/core/physics/rigid_body/Shape.h"
#include "IME/common/Vector2.h"

class b2PolygonShape;

namespace ime {
    /**
     * @brief Specialized shape representing a rectangle
     */
    class IME_API RectangleShape : public Shape {
    public:
        /**
         * @brief Default constructor
         * @param size The sie of the rectangle
         */
        explicit RectangleShape(Vector2f size = {0.0f, 0.0f});

        /**
         * @brief Set the size of the rectangle
         * @param width The width of the rectangle
         * @param height The height of the rectangle
         */
        void setSize(float width, float height);

        /**
         * @brief Set the size of the rectangle
         * @param size The size of the rectangle
         */
        void setSize(Vector2f size);

        /**
         * @brief Get the size of the rectangle
         * @return The size of the rectangle
         */
        Vector2f getSize() const;

        /**
         * @internal
         * @brief Get the internal shape
         * @return The internal shape
         *
         * @warning This function is intended for internal use and should never
         * be called outside of IME
         */
        b2Shape *getInternalShape() override;
        const b2Shape *getInternalShape() const override;

        /**
         * @brief Destructor
         */
        ~RectangleShape();

    private:
        Vector2f size_;             //!< The size of the rectangle
        b2PolygonShape* rectangle_; //!< Internal rectangle
    };
}

#endif //IME_RECTANGLESHAPE_H
