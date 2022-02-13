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

#include "IME/common/Rect.h"
#include <doctest.h>

TEST_CASE("ime::Rect class template")
{
    SUBCASE("Constructors")
    {
        SUBCASE("Default constructor")
        {
            ime::IntRect rectangle;
            CHECK_EQ(rectangle.left, 0);
            CHECK_EQ(rectangle.top, 0);
            CHECK_EQ(rectangle.width, 0);
            CHECK_EQ(rectangle.height, 0);
        }

        SUBCASE("(left, top, width, height) constructor")
        {
            ime::IntRect rectangle({1, 2}, {3, 4});
            CHECK_EQ(rectangle.left, 1);
            CHECK_EQ(rectangle.top, 2);
            CHECK_EQ(rectangle.width, 3);
            CHECK_EQ(rectangle.height, 4);
        }

        SUBCASE("(Vector2, Vector2) constructor")
        {
            ime::Vector2i position(1, 2);
            ime::Vector2i dimension(3, 4);
            ime::IntRect rectangle(position, dimension);

            CHECK_EQ(rectangle.left, 1);
            CHECK_EQ(rectangle.top, 2);
            CHECK_EQ(rectangle.width, 3);
            CHECK_EQ(rectangle.height, 4);
        }

        SUBCASE("Conversion constructor")
        {
            ime::FloatRect sourceRectangle({1.0f, 2.0f}, {3.0f, 4.0f});
            ime::IntRect rectangle(sourceRectangle);

            CHECK_EQ(rectangle.left, static_cast<int>(sourceRectangle.left));
            CHECK_EQ(rectangle.top, static_cast<int>(sourceRectangle.top));
            CHECK_EQ(rectangle.width, static_cast<int>(sourceRectangle.width));
            CHECK_EQ(rectangle.height, static_cast<int>(sourceRectangle.height));
        }
    }

    SUBCASE("Setters and getters")
    {
        SUBCASE("getPosition()")
        {
            ime::IntRect rectangle({4, 5}, {7, 9});

            CHECK_EQ(rectangle.getPosition().x, 4);
            CHECK_EQ(rectangle.getPosition().y, 5);
        }

        SUBCASE("getSize()")
        {
            ime::IntRect rectangle({4, 5}, {7, 9});

            CHECK_EQ(rectangle.getSize().x, 7);
            CHECK_EQ(rectangle.getSize().y, 9);
        }
    }

    SUBCASE("operators")
    {
        SUBCASE("operator==")
        {
            ime::IntRect rect1({1, 3}, {2, 5});
            ime::IntRect rect2({7, 11}, {2, 5});

            CHECK(rect1 == rect1);
            CHECK_FALSE(rect1 == rect2);
        }

        SUBCASE("operator!=")
        {
            ime::IntRect rect1({1, 3}, {2, 5});
            ime::IntRect rect2({7, 11}, {2, 5});

            CHECK(rect1 != rect2);
            CHECK_FALSE(rect1 != rect1);
        }
    }

    SUBCASE("contains()")
    {
        SUBCASE("contains(Vector2)")
        {
            ime::IntRect rectangle({0, 0}, {10, 10});

            CHECK(rectangle.contains(ime::Vector2i(0, 0)));
            CHECK(rectangle.contains(ime::Vector2i(9, 0)));
            CHECK(rectangle.contains(ime::Vector2i(0, 9)));
            CHECK(rectangle.contains(ime::Vector2i(9, 9)));
            CHECK_FALSE(rectangle.contains(ime::Vector2i(9, 10)));
            CHECK_FALSE(rectangle.contains(ime::Vector2i(10, 9)));
            CHECK_FALSE(rectangle.contains(ime::Vector2i(10, 10)));
            CHECK_FALSE(rectangle.contains(ime::Vector2i(15, 15)));
        }

        SUBCASE("contains(point, point)")
        {
            ime::IntRect rectangle({0, 0}, {10, 10});

            CHECK(rectangle.contains(0, 0));
            CHECK(rectangle.contains(9, 0));
            CHECK(rectangle.contains(0, 9));
            CHECK(rectangle.contains(9, 9));
            CHECK_FALSE(rectangle.contains(9, 10));
            CHECK_FALSE(rectangle.contains(10, 9));
            CHECK_FALSE(rectangle.contains(10, 10));
            CHECK_FALSE(rectangle.contains(15, 15));
        }
    }

    SUBCASE("intersects()")
    {
        SUBCASE("intersects(Rect)")
        {
            ime::IntRect rectangle({0, 0}, {10, 10});
            ime::IntRect intersectingRectangle({5, 5}, {10, 10});
            ime::IntRect nonIntersectingRectangle({-5, -5}, {5, 5});

            CHECK(rectangle.intersects(intersectingRectangle));
            CHECK_FALSE(rectangle.intersects(nonIntersectingRectangle));
        }

        SUBCASE("intersects(Rect, Rect)")
        {
            ime::IntRect rectangle({0, 0}, {10, 10});
            ime::IntRect intersectingRectangle({5, 5}, {10, 10});
            ime::IntRect nonIntersectingRectangle({-5, -5}, {5, 5});
            ime::IntRect intersectionResult;

            CHECK(rectangle.intersects(intersectingRectangle, intersectionResult));
            CHECK_EQ(intersectionResult.top, 5);
            CHECK_EQ(intersectionResult.left, 5);
            CHECK_EQ(intersectionResult.width, 5);
            CHECK_EQ(intersectionResult.height, 5);
            CHECK_FALSE(rectangle.intersects(nonIntersectingRectangle, intersectionResult));
        }
    }
}
