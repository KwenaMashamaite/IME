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

#ifndef IME_VECTOR2_H
#define IME_VECTOR2_H

namespace ime {
    /**
     * @brief 2D vector
     */
    template<typename T>
    class Vector2 {
    public:
        /**
         * @brief Default constructor
         *
         * Creates a Vector2(0, 0)
         */
        Vector2();

        /**
         * @brief Construct the vector from its coordinates
         * @param X X coordinate
         * @param Y Y coordinate
         */
        Vector2(T X, T Y);

        /**
         * @brief Construct the vector from another type of vector
         * @param vector Vector to convert
         *
         * This constructor doesn't replace the copy constructor, it's called
         * only when U != T. A call to this constructor will fail to compile if
         * U is not convertible to T
         */
        template<typename U>
        explicit Vector2(const Vector2<U> &vector);
        
        // Member data
        T x; //!< X coordinate of the vector
        T y; //!< Y coordinate of the vector
    };

    /**
     * @relates Vector2
     * @brief Overload of unary operator -
     * @param right Vector to negate
     * @return Memberwise opposite of the vector
     */
    template <typename T>
    Vector2<T> operator -(const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator +=
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return Overload of binary operator +=
     *
     * This operator performs a memberwise addition of both vectors,
     * and assigns the result to @a left.
     */
    template <typename T>
    Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator -=
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return Reference to @a left
     *
     * This operator performs a memberwise subtraction of both vectors,
     *  and assigns the result to @a left.
     */
    template <typename T>
    Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator +
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return Memberwise addition of both vectors
     */
    template <typename T>
    Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator -
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return Memberwise subtraction of both vectors
     */
    template <typename T>
    Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator *
     * @param left Left operand (a vector)
     * @param right Right operand (a scalar value)
     * @return Memberwise multiplication by @a right
     */
    template <typename T>
    Vector2<T> operator *(const Vector2<T>& left, T right);

    /**
     * @brief relates Vector2
     * @brief Overload of binary operator *
     * @param left Left operand (a scalar value)
     * @param right Right operand (a vector)
     * @return Memberwise multiplication by @a left
     */
    template <typename T>
    Vector2<T> operator *(T left, const Vector2<T>& right);

    /**
     * @brief Overload of binary operator *=
     * @param left Left operand (a vector)
     * @param right Right operand (a scalar value)
     * @return Reference to @a left
     *
     * This operator performs a memberwise multiplication by @a right,
     * and assigns the result to @a left.
     */
    template <typename T>
    Vector2<T>& operator *=(Vector2<T>& left, T right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator /
     * @param left Left operand (a vector)
     * @param right Right operand (a scalar value)
     * @return return Memberwise division by @a right
     */
    template <typename T>
    Vector2<T> operator /(const Vector2<T>& left, T right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator /=
     * @param left Left operand (a vector)
     * @param right Right operand (a scalar value)
     * @return Reference to @a left
     *
     * This operator performs a memberwise division by @a right,
     * and assigns the result to @a left.
     */
    template <typename T>
    Vector2<T>& operator /=(Vector2<T>& left, T right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator ==
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return True if @a left is equal to @a right
     *
     * This operator compares strict equality between two vectors
     */
    template <typename T>
    bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator !=
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return True if @a left is not equal to @a right
     *
     * This operator compares strict difference between two vectors
     */
    template <typename T>
    bool operator !=(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator <
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return True if @a left is less than @a right
     *
     * This function returns true if the x member of @a left is less than
     * the x member of @a right AND the y member of @a left is less than
     * the y member of @a right, otherwise it returns false
     */
    template <typename T>
    bool operator <(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator >
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return True if @a left is greater than @a right
     *
     * This function returns true if the x member of @a left is greater than
     * the x member of @a right AND the y member of @a left is greater than
     * the y member of @a right, otherwise it returns false
     */
    template <typename T>
    bool operator >(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator <=
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return True if @a left is less than or equal to @a right
     *
     * This function returns true if the x member of @a left is less than
     * or equal to the x member of @a right AND the y member of @a left is
     * less than or equal to the y member of @a right, otherwise it returns
     * false
     */
    template <typename T>
    bool operator <=(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @relates Vector2
     * @brief Overload of binary operator >=
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return True if @a left is greater than or equal to @a right
     *
     * This function returns true if the x member of @a left is greater than
     * or equal to the x member of @a right AND the y member of @a left is
     * greater than or equal to the y member of @a right, otherwise it returns
     * false
     */
    template <typename T>
    bool operator >=(const Vector2<T>& left, const Vector2<T>& right);

    #include <IME/common/Vector2.inl>

    ///< Define the most common types
    using Vector2i = Vector2<int>;          //!< 2D int vector
    using Vector2u = Vector2<unsigned int>; //!< 2D unsigned int vector
    using Vector2f = Vector2<float>;        //!< 2D float vector
}

#endif // IME_VECTOR2_H
