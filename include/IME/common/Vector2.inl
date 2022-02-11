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

namespace {
    auto constexpr PI = 3.14159265358979323846f;
}

template <typename T>
inline Vector2<T>::Vector2() : x(0), y(0)
{}

template <typename T>
inline Vector2<T>::Vector2(T X, T Y) : x(X), y(Y)
{}

template <typename T>
template <typename U>
inline Vector2<T>::Vector2(const Vector2<U>& vector) :
    x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y))
{}

template <typename T>
inline float Vector2<T>::magnitude() const {
    return static_cast<float>(std::sqrt(std::pow(x, 2.0f) + std::pow(y, 2.0f)));
}

template <typename T>
inline float Vector2<T>::dot(const Vector2<T>& otherVec) const {
    return static_cast<float>(x * otherVec.x + y * otherVec.y);
}

template <typename T>
inline T Vector2<T>::cross(const Vector2<T>& otherVec) const {
    return x * otherVec.y - y * otherVec.x;
}

template <typename T>
inline float Vector2<T>::distanceTo(const Vector2<T>& otherVec) const {
    auto distanceVec = otherVec - *this;
    return distanceVec.magnitude();
}

template <typename T>
inline float Vector2<T>::angle() const {
    auto angle = static_cast<float>(atan2(y, x));

    if (angle < 0)
        angle += 2 * PI;

    return angle * 180.0f / PI;
}

template <typename T>
inline float Vector2<T>::angleTo(const Vector2<T>& otherVec) const {
    return std::fabs(static_cast<float>(atan2(cross(otherVec), dot(otherVec))) * 180.0f / PI);
}

template <typename T>
inline Vector2<float> Vector2<T>::asUnitVector() const {
    return {x / magnitude(), y / magnitude()};
}

template <typename T>
inline Vector2<T> operator -(const Vector2<T>& right) {
    return Vector2<T>(-right.x, -right.y);
}

template <typename T>
inline Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right) {
    left.x += right.x;
    left.y += right.y;
    return left;
}

template <typename T>
inline Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right) {
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

template <typename T>
inline Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) {
    return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
inline Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) {
    return Vector2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
inline Vector2<T> operator *(const Vector2<T>& left, T right) {
    return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
inline Vector2<T> operator *(T left, const Vector2<T>& right) {
    return Vector2<T>(right.x * left, right.y * left);
}

template <typename T>
inline Vector2<T>& operator *=(Vector2<T>& left, T right) {
    left.x *= right;
    left.y *= right;
    return left;
}

template <typename T>
inline Vector2<T> operator /(const Vector2<T>& left, T right) {
    return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
inline Vector2<T>& operator /=(Vector2<T>& left, T right) {
    left.x /= right;
    left.y /= right;
    return left;
}

template <typename T>
inline bool operator ==(const Vector2<T>& left, const Vector2<T>& right) {
    return (left.x == right.x) && (left.y == right.y);
}

template <typename T>
inline bool operator !=(const Vector2<T>& left, const Vector2<T>& right) {
    return (left.x != right.x) || (left.y != right.y);
}

template <typename T>
inline bool operator <(const Vector2<T>& left, const Vector2<T>& right) {
    return (left.x < right.x) && (left.y < right.y);
}

template <typename T>
inline bool operator >(const Vector2<T>& left, const Vector2<T>& right) {
    return (left.x > right.x) && (left.y > right.y);
}

template <typename T>
inline bool operator <=(const Vector2<T>& left, const Vector2<T>& right) {
    return (left.x <= right.x) && (left.y <= right.y);
}

template <typename T>
inline bool operator >=(const Vector2<T>& left, const Vector2<T>& right) {
    return (left.x >= right.x) && (left.y >= right.y);
}
