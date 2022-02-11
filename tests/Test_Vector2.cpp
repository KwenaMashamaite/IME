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

#include "IME/common/Vector2.h"
#include <doctest.h>

TEST_CASE("ime::Vector2 class template")
{
    SUBCASE("Constructors")
    {
        SUBCASE("Default constructor")
        {
            ime::Vector2i vector;

            CHECK(vector.x == 0);
            CHECK(vector.y == 0);
        }

        SUBCASE("(x, y) coordinate constructor")
        {
            ime::Vector2i vector(1, 2);

            CHECK(vector.x == 1);
            CHECK(vector.y == 2);
        }

        SUBCASE("Conversion constructor")
        {
            ime::Vector2f v1(1.0f, 2.0f);
            ime::Vector2i v2(v1);

            CHECK(v1.x == static_cast<int>(v2.x));
            CHECK(v1.y == static_cast<int>(v2.y));
        }
    }

    SUBCASE("Operators between vectors")
    {
        SUBCASE("Negation operator")
        {
            ime::Vector2i v1(7, 11);
            ime::Vector2i v2 = -v1;

            CHECK_EQ(v2.x, -7);
            CHECK_EQ(v2.y, -11);
        }

        SUBCASE("operator+")
        {
            ime::Vector2i v1(5, 5);
            ime::Vector2i v2(10, 3);

            CHECK_EQ(v1 + v2, ime::Vector2i(15, 8));
        }

        SUBCASE("operator-")
        {
            ime::Vector2i v1(5, 5);
            ime::Vector2i v2(10, 3);

            CHECK_EQ(v1 - v2, ime::Vector2i(-5, 2));
        }

        SUBCASE("operator+=")
        {
            ime::Vector2i vector(2, 7);
            vector += ime::Vector2i(1, 15);

            CHECK_EQ(vector, ime::Vector2i(3, 22));
        }

        SUBCASE("operator-=")
        {
            ime::Vector2i vector(15, 2);
            vector -= ime::Vector2i(10, 10);

            CHECK_EQ(vector, ime::Vector2i(5, -8));
        }

        SUBCASE("operator==")
        {
            CHECK(ime::Vector2i(10, 5) == ime::Vector2i(10, 5));
            CHECK_FALSE(ime::Vector2i(3, 7) == ime::Vector2i(5, 2));
        }

        SUBCASE("operator!=")
        {
            CHECK(ime::Vector2i(10, 5) != ime::Vector2i(5, 5));
            CHECK_FALSE(ime::Vector2i(7, 4) != ime::Vector2i(7, 4));
        }

        SUBCASE("operator<")
        {
            ime::Vector2i v1(1, 2);
            ime::Vector2i v2(3, 4);

            CHECK(v1 < v2);
            CHECK_FALSE(v2 < v1);
        }

        SUBCASE("operator>")
        {
            ime::Vector2i v1(1, 2);
            ime::Vector2i v2(3, 4);

            CHECK(v2 > v1);
            CHECK_FALSE(v1 > v2);
        }

        SUBCASE("operator<=")
        {
            ime::Vector2i v1(1, 2);
            ime::Vector2i v2(3, 4);

            CHECK(v1 <= v1);
            CHECK(v1 <= v2);
            CHECK_FALSE(v2 <= v1);
        }

        SUBCASE("operator>=")
        {
            ime::Vector2i v1(1, 2);
            ime::Vector2i v2(3, 4);

            CHECK(v1 >= v1);
            CHECK(v2 >= v1);
            CHECK_FALSE(v1 >= v2);
        }
    }

    SUBCASE("Operators between a vector and a scalar")
    {
        SUBCASE("operator*")
        {
            SUBCASE("vector * scalar")
            {
                ime::Vector2i v1(2, 4);
                ime::Vector2i v2 = v1 * 10;

                CHECK_EQ(v2.x, 20);
                CHECK_EQ(v2.y, 40);
            }
            
            SUBCASE("scalar * vector")
            {
                ime::Vector2i v1(3, 6);
                ime::Vector2i v2 = 3 * v1;

                CHECK_EQ(v2.x, 9);
                CHECK_EQ(v2.y, 18);
            }
        }

        SUBCASE("operator/")
        {
            ime::Vector2i v1(9, 15);
            ime::Vector2i v2 = v1 / 3;

            CHECK(v2.x == 3);
            CHECK(v2.y == 5);
        }

        SUBCASE("operator*=")
        {
            ime::Vector2i vector(2, 8);
            vector *= 5;

            CHECK_EQ(vector.x, 10);
            CHECK_EQ(vector.y, 40);
        }

        SUBCASE("vector /= scalar")
        {
            ime::Vector2i v1(50, 100);
            v1 /= 10;

            CHECK_EQ(v1.x, 5);
            CHECK_EQ(v1.y, 10);
        }
    }

    SUBCASE("magnitude()")
    {
        ime::Vector2i vector(-3, 4);
        CHECK_EQ(vector.magnitude(), 5.0f);
    }

    SUBCASE("dot()")
    {
        ime::Vector2i v1(-3, 4);
        ime::Vector2i v2(5, 10);

        CHECK_EQ(v1.dot(v2), 25.0f);
        CHECK_EQ(v2.dot(v1), 25.0f);
    }

    SUBCASE("cross()")
    {
        ime::Vector2i v1(-3, 4);
        ime::Vector2i v2(5, 10);

        CHECK_EQ(v1.cross(v2), -50);
        CHECK_EQ(v2.cross(v1), 50);
    }

    SUBCASE("distanceTo()")
    {
        ime::Vector2i v1(-4, -3);
        ime::Vector2i v2(4, 3);

        CHECK_EQ(v1.distanceTo(v2), 10.0f);
        CHECK_EQ(v2.distanceTo(v1), 10.0f);
    }

    SUBCASE("angleTo()")
    {
        ime::Vector2i v1(0, 7);
        ime::Vector2i v2(10, 0);
        ime::Vector2i v3(2, 2);
        ime::Vector2i v4(0, 3);

        CHECK_EQ(static_cast<int>(v1.angleTo(v2)), 90);
        CHECK_EQ(static_cast<int>(v2.angleTo(v1)), 90);
        CHECK_EQ(static_cast<int>(v3.angleTo(v4)), 45);
        CHECK_EQ(static_cast<int>(v4.angleTo(v3)), 45);
    }

    SUBCASE("asUnitVector()")
    {
        ime::Vector2i originalVector(5, 11);
        ime::Vector2f unitVector = originalVector.asUnitVector();

        CHECK_EQ(unitVector.x, originalVector.x / originalVector.magnitude());
        CHECK_EQ(unitVector.y, originalVector.y / originalVector.magnitude());
        CHECK_EQ(unitVector.magnitude(), 1.0f);
    }
}
