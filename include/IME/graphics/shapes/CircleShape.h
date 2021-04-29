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
#include "IME/graphics/shapes/Shape.h"
#include <memory>

namespace ime {
    /**
     * @brief A closed 2D curved shape
     */
    class IME_API CircleShape : public Shape {
    public:
        using Ptr = std::unique_ptr<CircleShape>; //!< Shared shape pointer

        /**
         * @brief Default constructor
         * @param radius The radius of the circle
         * 
         * By default the radius is zero
         */
        explicit CircleShape(float radius = 0.0f);

        /**
         * @brief Copy constructor
         */
        CircleShape(const CircleShape&);

        /**
         * @brief Copy assignment operator
         */
        CircleShape& operator=(const CircleShape&);

        /**
         * @brief Move constructor
         */
        CircleShape(CircleShape&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        CircleShape& operator=(CircleShape&&) noexcept;

        /**
         * @brief Create a new circle shape
         * @param radius The radius of the circle
         * @return The created circle shape
         */
        static CircleShape::Ptr create(float radius = 0.0f);

        /**
         * @brief Create a copy of this shape
         * @return A copy of this shape
         *
         * @see clone
         */
        CircleShape::Ptr copy() const;

        /**
         * @brief Make a copy of this shape
         * @return A copy of this shape
         *
         * You should use this function if you don't care about the type
         * of the shape, otherwise use the shapes copy function
         *
         * @see copy
         */
        Shape::Ptr clone() const override;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;
        
        /**
         * @brief Set the radius of the circle
         * @param radius The new radius of the circle
         */
        void setRadius(float radius);
        
        /**
         * @brief Get the radius of the circle
         * @return The radius of teh circle
         */
        float getRadius() const;

        /**
         * @brief Destructor
         */
        ~CircleShape() override;

    private:
        struct CircleShapeImpl;
        std::unique_ptr<CircleShapeImpl> pimpl_;
    };
}

#endif //IME_CIRCLESHAPE_H
