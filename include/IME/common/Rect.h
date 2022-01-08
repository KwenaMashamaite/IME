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

#ifndef IME_RECT_H
#define IME_RECT_H

#include "IME/common/Vector2.h"
#include <algorithm>

namespace ime {
    /**
     * @brief Class for manipulating 2D axis aligned rectangles
     */
    template <typename T>
    class Rect {
    public:
        /**
         * @brief Default constructor
         *
         * Creates an empty rectangle (it is equivalent to calling
         * Rect(0, 0, 0, 0))
         */
        Rect();

        /**
         * @brief Construct the rectangle from its coordinates
         * @param rectLeft Left coordinate of the rectangle
         * @param rectTop Top coordinate of the rectangle
         * @param rectWidth Width of the rectangle
         * @param rectHeight Height of the rectangle
         *
         * @note the last two parameters are the width and height, not the
         * right and bottom coordinates!
         */
        Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight);

        /**
         * @brief Construct the rectangle from position and size
         * @param position Position of the top-left corner of the rectangle
         * @param size Size of the rectangle
         *
         * @note The last parameter is the size, not the bottom-right corner!
         */
        Rect(const Vector2<T>& position, const Vector2<T>& size);

        /**
         * @brief Construct the rectangle from another type of rectangle
         * @param rectangle Rectangle to convert
         *
         * This constructor doesn't replace the copy constructor, it's called
         * only when U != T. A call to this constructor will fail to compile
         * if U is not convertible to T
         */
        template <typename U>
        explicit Rect(const Rect<U>& rectangle);

        /**
         * @brief Check if a point is inside the rectangle's area
         * @param x X coordinate of the point to test
         * @param y Y coordinate of the point to test
         * @return True if the point is inside, false otherwise
         *
         * This check is non-inclusive. If the point lies on the
         * edge of the rectangle, this function will return false.
         *
         * @see intersect
         */
        bool contains(T x, T y) const;

        /**
         * @brief Check if a point is inside the rectangle's area
         * @param point Point to test
         * @return True if the point is inside, false otherwise
         *
         * This check is non-inclusive. If the point lies on the
         * edge of the rectangle, this function will return false.
         *
         * @see intersects
         */
        bool contains(const Vector2<T>& point) const;

        /**
         * @brief Check the intersection between two rectangles
         * @param other Rectangle to test
         * @return True if rectangles overlap, false otherwise
         *
         * @see contains
         */
        bool intersects(const Rect<T>& other) const;

        /**
         * @brief Check the intersection between two rectangles
         * @param rectangle Rectangle to test
         * @param intersection Rectangle to be filled with the intersection
         * @return True if rectangles overlap, false otherwise
         *
         * This overload returns the overlapped rectangle in the
         * @a intersection parameter
         *
         * @see contains
         */
        bool intersects(const Rect<T>& rectangle, Rect<T>& intersection) const;

        /**
         * @brief Get the position of the rectangle's top-left corner
         * @return Position of rectangle
         *
         * @see getSize
         */
        Vector2<T> getPosition() const;

        /**
         * @brief Get the size of the rectangle
         * @return Size of rectangle
         *
         * @see getPosition
         */
        Vector2<T> getSize() const;

        // Member data
        T left;   //!< Left coordinate of the rectangle
        T top;    //!< Top coordinate of the rectangle
        T width;  //!< Width of the rectangle
        T height; //!< Height of the rectangle
    };

    /**
     * @relates Rect
     * @brief Overload of binary operator ==
     * @param left Left operand (a rectangle)
     * @param right Right operand (a rectangle)
     * @return True if @a left is equal to @a right
     *
     * This operator compares strict equality between two rectangles
     */
    template <typename T>
    bool operator ==(const Rect<T>& left, const Rect<T>& right);

    /**
     * @relates Rect
     * @brief Overload of binary operator !=
     * @param left Left operand (a rectangle)
     * @param right Right operand (a rectangle)
     * @return True if @a left is not equal to @a right
     *
     * This operator compares strict difference between two rectangles
     */
    template <typename T>
    bool operator !=(const Rect<T>& left, const Rect<T>& right);

    #include <IME/common/Rect.inl>

    ///< Create most common types
    using UIntRect = Rect<unsigned int>; //!< Unsigned int rect
    using IntRect = Rect<int>;          //!< Int rect
    using FloatRect = Rect<float>;      //!< Float rect
}

#endif // IME_RECT_H
