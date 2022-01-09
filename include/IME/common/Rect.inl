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

// All of the source code in this file was taken from SFML

////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

template <typename T>
Rect<T>::Rect() :
    left(0), top(0),
    width(0), height(0)
{}

template <typename T>
Rect<T>::Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight) :
    left(rectLeft), top(rectTop), width(rectWidth), height(rectHeight)
{}

template <typename T>
Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) :
    left(position.x), top(position.y), width(size.x), height(size.y)
{}

template <typename T>
template <typename U>
Rect<T>::Rect(const Rect<U>& rectangle) :
    left  (static_cast<T>(rectangle.left)),
    top   (static_cast<T>(rectangle.top)),
    width (static_cast<T>(rectangle.width)),
    height(static_cast<T>(rectangle.height))
{}

template <typename T>
bool Rect<T>::contains(T x, T y) const {
    // Rectangles with negative dimensions are allowed, so we must handle them correctly

    // Compute the real min and max of the rectangle on both axes
    T minX = std::min(left, static_cast<T>(left + width));
    T maxX = std::max(left, static_cast<T>(left + width));
    T minY = std::min(top, static_cast<T>(top + height));
    T maxY = std::max(top, static_cast<T>(top + height));

    return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
}

template <typename T>
bool Rect<T>::contains(const Vector2<T>& point) const {
    return contains(point.x, point.y);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& other) const {
    Rect<T> intersection;
    return intersects(other, intersection);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& rectangle, Rect<T>& intersection) const {
    // Rectangles with negative dimensions are allowed, so we must handle them correctly

    // Compute the min and max of the first rectangle on both axes
    T r1MinX = std::min(left, static_cast<T>(left + width));
    T r1MaxX = std::max(left, static_cast<T>(left + width));
    T r1MinY = std::min(top, static_cast<T>(top + height));
    T r1MaxY = std::max(top, static_cast<T>(top + height));

    // Compute the min and max of the second rectangle on both axes
    T r2MinX = std::min(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
    T r2MaxX = std::max(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
    T r2MinY = std::min(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
    T r2MaxY = std::max(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));

    // Compute the intersection boundaries
    T interLeft   = std::max(r1MinX, r2MinX);
    T interTop    = std::max(r1MinY, r2MinY);
    T interRight  = std::min(r1MaxX, r2MaxX);
    T interBottom = std::min(r1MaxY, r2MaxY);

    // If the intersection is valid (positive non zero area), then there is an intersection
    if ((interLeft < interRight) && (interTop < interBottom)) {
        intersection = Rect<T>(interLeft, interTop, interRight - interLeft, interBottom - interTop);
        return true;
    } else {
        intersection = Rect<T>(0, 0, 0, 0);
        return false;
    }
}

template <typename T>
Vector2<T> Rect<T>::getPosition() const {
    return {left, top};
}

template <typename T>
Vector2<T> Rect<T>::getSize() const {
    return {width, height};
}

template <typename T>
inline bool operator ==(const Rect<T>& left, const Rect<T>& right) {
    return (left.left == right.left) && (left.width == right.width) &&
           (left.top == right.top) && (left.height == right.height);
}

template <typename T>
inline bool operator !=(const Rect<T>& left, const Rect<T>& right) {
    return !(left == right);
}
