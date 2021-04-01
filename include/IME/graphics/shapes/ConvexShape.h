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

#ifndef IME_CONVEXSHAPE_H
#define IME_CONVEXSHAPE_H

#include "IME/Config.h"
#include "IME/graphics/shapes/Shape.h"
#include <memory>

namespace ime {
    /**
     * @brief A convex shape
     */
    class IME_API ConvexShape : public Shape {
    public:
        using Ptr = std::shared_ptr<ConvexShape>; //!< Shared shape pointer

        /**
         * @brief Default constructor
         * @param pointCount The number of points of the polygon
         */
        explicit ConvexShape(std::size_t pointCount = 0);

        /**
         * @brief Copy constructor
         */
        ConvexShape(const ConvexShape&);

        /**
         * @brief Copy assignment operator
         */
        ConvexShape& operator=(const ConvexShape&);

        /**
         * @brief Move constructor
         */
        ConvexShape(ConvexShape&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        ConvexShape& operator=(ConvexShape&&) noexcept;

        /**
         * @brief Create a new convex shape
         * @param pointCount The number of points of the polygon
         * @return The created convex shape shape
         */
        static ConvexShape::Ptr create(std::size_t pointCount = 0);

        /**
         * @brief Create a copy of this shape
         * @return A copy of this shape
         *
         * @see clone
         */
        ConvexShape::Ptr copy() const;

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
         * @brief Set the number of points of the polygon
         * @param count The new number of points of the polygon
         * 
         * @note @a count must be greater than 2 to define a valid shape
         */
        void setPointCount(std::size_t count);
        
        /**
         * @brief Get the number of points of the polygon
         * @return The number of points of the polygon
         */
        std::size_t getPointCount() const;
        
        /**
         * @brief Set the position of a point
         * @param index Index of the point to change, in range [0 .. getPointCount() - 1]
         * @param point New position of the point
         * 
         * @warning The polygon must remain convex, and the points need to 
         * stay ordered!. setPointCount must be called first in order to set 
         * the total number of points. The result is undefined if @a index 
         * is out of the valid range
         * 
         * @see getPointCount
         */
        void setPoint(std::size_t index, const Vector2f& point);
        
        /**
         * @brief Get the position of a point
         * @param index Index of the point to get, in range [0 .. getPointCount() - 1]
         * @return Position of the index-th point of the polygon
         * 
         * The returned point is in local coordinates, that is,  the shape's 
         * transforms (position, rotation, scale) are not taken into account
         *
         * @warning The result is undefined if @a index is out of the valid
         * range
         *
         * @see setPointCount
         */
        Vector2f getPoint(std::size_t index) const;

        /**
         * @brief Destructor
         */
        ~ConvexShape() override;

    private:
        struct ConvexShapeImpl;
        std::unique_ptr<ConvexShapeImpl> pimpl_;
    };
}

#endif //IME_CONVEXSHAPE_H
