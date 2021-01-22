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

#include "IME/core/time/Time.h"

namespace ime {
    const Time Time::Zero;

    Time::Time() :
        nanoseconds_{std::chrono::nanoseconds::zero()}
    {}

    Time::Time(std::chrono::nanoseconds nanoseconds) :
        nanoseconds_{nanoseconds}
    {}

    Int64 Time::asNanoseconds() const {
        return nanoseconds_.count();
    }

    Int64 Time::asMicroseconds() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(nanoseconds_).count();
    }

    Int32 Time::asMilliseconds() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(nanoseconds_).count();
    }

    float Time::asSeconds() const {
        return nanoseconds_.count() / 1000000000.f;
    }

    Int64 Time::asMinutes() const {
        return std::chrono::duration_cast<std::chrono::minutes>(nanoseconds_).count();
    }

    Int64 Time::asHours() const {
        return std::chrono::duration_cast<std::chrono::hours>(nanoseconds_).count();
    }

    Time nanoseconds(Int64 nanoseconds) {
        return Time(std::chrono::nanoseconds(nanoseconds));
    }

    Time microseconds(Int64 microseconds) {
        return Time(std::chrono::microseconds(microseconds));
    }

    Time milliseconds(Int32 milliseconds) {
        return Time(std::chrono::milliseconds(milliseconds));
    }

    Time seconds(float seconds) {
        return Time(std::chrono::nanoseconds(static_cast<Int64>(seconds * 1000000000)));
    }

    Time minutes(Int64 minutes) {
        return Time(std::chrono::minutes(minutes));
    }

    Time hours(Int64 hours) {
        return Time(std::chrono::hours(hours));
    }

    bool operator ==(Time left, Time right) {
        return left.asNanoseconds() == right.asNanoseconds();
    }

    bool operator !=(Time left, Time right) {
        return left.asNanoseconds() != right.asNanoseconds();
    }

    bool operator <(Time left, Time right) {
        return left.asNanoseconds() < right.asNanoseconds();
    }

    bool operator >(Time left, Time right) {
        return left.asNanoseconds() > right.asNanoseconds();
    }

    bool operator <=(Time left, Time right) {
        return left.asNanoseconds() <= right.asNanoseconds();
    }

    bool operator >=(Time left, Time right) {
        return left.asNanoseconds() >= right.asNanoseconds();
    }

    Time operator -(Time right) {
        return nanoseconds(-right.asNanoseconds());
    }

    Time operator +(Time left, Time right) {
        return nanoseconds(left.asNanoseconds() + right.asNanoseconds());
    }

    Time& operator +=(Time& left, Time right) {
        return left = left + right;
    }

    Time operator -(Time left, Time right) {
        return nanoseconds(left.asNanoseconds() - right.asNanoseconds());
    }

    Time& operator -=(Time& left, Time right) {
        return left = left - right;
    }

    Time operator *(Time left, float right) {
        return seconds(left.asSeconds() * right);
    }

    Time operator *(Time left, Int64 right) {
        return nanoseconds(left.asNanoseconds() * right);
    }

    Time operator *(float left, Time right) {
        return right * left;
    }

    Time operator *(Int64 left, Time right) {
        return right * left;
    }

    Time& operator *=(Time& left, float right) {
        return left = left * right;
    }

    Time& operator *=(Time& left, Int64 right) {
        return left = left * right;
    }

    Time operator /(Time left, float right) {
        return seconds(left.asSeconds() / right);
    }

    Time operator /(Time left, Int64 right) {
        return nanoseconds(left.asNanoseconds() / right);
    }

    Time& operator /=(Time& left, float right) {
        return left = left / right;
    }

    Time& operator /=(Time& left, Int64 right) {
        return left = left / right;
    }

    float operator /(Time left, Time right) {
        return left.asSeconds() / right.asSeconds();
    }

    Time operator %(Time left, Time right) {
        return nanoseconds(left.asNanoseconds() % right.asNanoseconds());
    }

    Time& operator %=(Time& left, Time right) {
        return left = left % right;
    }
}
