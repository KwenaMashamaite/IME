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

#ifndef IME_TIME_H
#define IME_TIME_H

#include "IME/Config.h"
#include <chrono>

namespace ime {
    /**
     * @brief Represents a time value
     */
    class IME_API Time {
    public:
        /**
         * @brief Default constructor
         *
         * Sets the time value to zero
         */
        Time();

        /**
         * @brief Get the time value in nanoseconds
         * @return The time value in nanoseconds
         */
        Int64 asNanoseconds() const;

        /**
         * @brief Get the time value in microseconds
         * @return The time value in microseconds
         */
        Int64 asMicroseconds() const;

        /**
         * @brief Get the time value in milliseconds
         * @return The time value in milliseconds
         */
        Int32 asMilliseconds() const;

        /**
         * @brief Get the time value in seconds
         * @return The time value in seconds
         */
        float asSeconds() const;

        /**
         * @brief Get the time value in minutes
         * @return The time value in minutes
         */
        Int64 asMinutes() const;

        /**
         * @brief Get the time value in hours
         * @return The time value in hours
         */
        Int64 asHours() const;

        //Member data
        static const Time Zero; //!< Predefined "zero" time value

    private:
        /**
         * @brief Construct the time from a number of nanoseconds
         * @param microseconds Number of nanoseconds to set
         */
        explicit Time(std::chrono::nanoseconds nanoseconds);

        friend IME_API Time nanoseconds(Int64);
        friend IME_API Time microseconds(Int64);
        friend IME_API Time milliseconds(Int32);
        friend IME_API Time seconds(float);
        friend IME_API Time minutes(Int64);
        friend IME_API Time hours(Int64);

    private:
        std::chrono::nanoseconds nanoseconds_; //!< The time value
    };

    /**
     * @relates Time
     * @brief Construct a time value from a number of nanoseconds
     * @param nanoseconds Number of nanoseconds
     * @return The time value constructed from the amount of nanoseconds
     */
    IME_API Time nanoseconds(Int64 nanoseconds);

    /**
     * @relates Time
     * @brief Construct a time value from a number of microseconds
     * @param microseconds Number of microseconds
     * @return The time value constructed from the amount of microseconds
     */
    IME_API Time microseconds(Int64 microseconds);

    /**
     * @relates Time
     * @brief Construct a time value from a number of milliseconds
     * @param milliseconds Number of milliseconds
     * @return The time value constructed from the amount of milliseconds
     */
    IME_API Time milliseconds(Int32 milliseconds);
    
    /**
     * @relates Time
     * @brief Construct a time value from a number of seconds
     * @param seconds Number of seconds
     * @return The time value constructed from the amount of seconds
     */
    IME_API Time seconds(float seconds);

    /**
     * @relates Time
     * @brief Construct a time value from a number of minutes
     * @param minutes Number of minutes
     * @return The time value constructed from the amount of minutes
    */
    IME_API Time minutes(Int64 minutes);

    /**
     * @relates Time
     * @brief Construct a time value from a number of hours
     * @param hours Number of hours
     * @return The time value constructed from the amount of hours
    */
    IME_API Time hours(Int64 hours);

    /**
     * @relates Time
     * @brief Overload of == operator to compare two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return True if @a left is equal to @a right
     */
    IME_API bool operator ==(Time left, Time right);
    
    /**
     * @relates Time
     * @brief Overload of != operator to compare two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return True if @a left is not equal to @a right
     */
    IME_API bool operator !=(Time left, Time right);

    /**
     * @relates Time
     * @brief Overload of < operator to compare two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return True if @a left is less than @a right
     */
    IME_API bool operator <(Time left, Time right);

    /**
     * @relates Time
     * @brief Overload of > operator to compare two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return True if @a left is greater than @a right
     */
    IME_API bool operator >(Time left, Time right);

    /**
     * @relates Time
     * @brief Overload of <= operator to compare two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return True if @a left is lesser or equal than @a right
     */
    IME_API bool operator <=(Time left, Time right);

    /**
     * @relates Time
     * @brief Overload of >= operator to compare two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return True if @a left is greater or equal than @a right
     */
    IME_API bool operator >=(Time left, Time right);

    /**
     * @relates Time
     * @brief Overload of unary - operator to negate a time value
     * @param right Right operand (a time)
     * @return The opposite of the time value
     */
    IME_API Time operator -(Time right);

    /**
     * @relates Time
     * @brief Overload of binary + operator to add two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return The sum of @a left and @a right
     */
    IME_API Time operator +(Time left, Time right);

    /**
     * @relates Time
     * @brief Overload of binary += operator to add/assign two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return The sum of @a left and @a right
     */
    IME_API Time& operator +=(Time& left, Time right);

    /**
     * @relates Time
     * @brief Overload of binary - operator to subtract two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return Difference of the two times values
     */
    IME_API Time operator -(Time left, Time right);

    /**
     * @relates Time
     * @brief Overload of binary -= operator to subtract/assign two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return Difference of the two time values
     */
    IME_API Time& operator -=(Time& left, Time right);

    /**
     * @relates Time
     * @brief Overload of binary * operator to scale a time value
     * @param left Left operand (a time)
     * @param right Right operand (a number)
     * @return @a left multiplied by @a right
     */
    IME_API Time operator *(Time left, float right);

    /**
     * @relates Time
     * @brief Overload of binary * operator to scale a time value
     * @param left Left operand (a time)
     * @param right Right operand (a number)
     * @return @a left multiplied by @a right
     */
    IME_API Time operator *(Time left, Int64 right);

    /**
     * @relates Time
     * @brief Overload of binary * operator to scale a time value
     * @param left Left operand (a number)
     * @param right Right operand (a time)
     * @return @a left multiplied by @a right
     */
    IME_API Time operator *(float left, Time right);

    /**
     * @relates Time
     * @brief Overload of binary * operator to scale a time value
     * @param left Left operand (a number)
     * @param right Right operand (a time)
     * @return @a left multiplied by @a right
     */
    IME_API Time operator *(Int64 left, Time right);

    /**
     * @relates Time
     * @brief Overload of binary *= operator to scale/assign a time value
     * @param left Left operand (a time)
     * @param right Right operand (a number)
     * @return @a left multiplied by @a right
     */
    IME_API Time& operator *=(Time& left, float right);

    /**
     * @relates Time
     * @brief Overload of binary *= operator to scale/assign a time value
     * @param left Left operand (a time)
     * @param right Right operand (a number)
     * @return @a left multiplied by @a right
     */
    IME_API Time& operator *=(Time& left, Int64 right);

    /**
     * @relates Time
     * @brief Overload of binary / operator to scale a time value
     * @param left Left operand (a time)
     * @param right Right operand (a number)
     * @return @a left divided by @a right
     */
    IME_API Time operator /(Time left, float right);

    /**
     * @relates Time
     * @brief Overload of binary / operator to scale a time value
     * @param left Left operand (a time)
     * @param right Right operand (a number)
     * @return @a left divided by @a right
     */
    IME_API Time operator /(Time left, Int64 right);

    /**
     * @relates Time
     * @brief Overload of binary /= operator to scale/assign a time value
     * @param left Left operand (a time)
     * @param right Right operand (a number)
     * @return @a left divided by @a right
     */
    IME_API Time& operator /=(Time& left, float right);

    /**
     * @relates Time
     * @brief Overload of binary /= operator to scale/assign a time value
     * @param left Left operand (a time)
     * @param right Right operand (a number)
     * @return @a left divided by @a right
     */
    IME_API Time& operator /=(Time& left, Int64 right);

    /**
     * @relates Time
     * @brief Overload of binary / operator to compute the ratio of two time values
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return @a left divided by @a right
     */
    IME_API float operator /(Time left, Time right);

    /**
     * @relates Time
     * @brief Overload of binary % operator to compute remainder of a time value
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return @a left modulo @a right
     */
    IME_API Time operator %(Time left, Time right);

    /**
     * @relates Time
     * @brief Overload of binary %= operator to compute/assign remainder of a time value
     * @param left Left operand (a time)
     * @param right Right operand (a time)
     * @return @a left modulo @a right
     */
    IME_API Time& operator %=(Time& left, Time right);
}

#endif //IME_TIME_H
