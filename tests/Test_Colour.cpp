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

#include "IME/graphics/Colour.h"
#include <doctest.h>

TEST_CASE("ime::Colour class")
{
    SUBCASE("Constructors")
    {
        SUBCASE("Default constructor")
        {
            ime::Colour colour;
            CHECK_EQ(colour.red, 0);
            CHECK_EQ(colour.green, 0);
            CHECK_EQ(colour.blue, 0);
            CHECK_EQ(colour.opacity, 255);
        }

        SUBCASE("Construct from RGB components")
        {
            ime::Colour colour{5, 10, 15};
            CHECK_EQ(colour.red, 5);
            CHECK_EQ(colour.green, 10);
            CHECK_EQ(colour.blue, 15);
            CHECK_EQ(colour.opacity, 255);
        }

        SUBCASE("Construct from RGBA components")
        {
            ime::Colour colour{10, 20, 30, 40};
            CHECK_EQ(colour.red, 10);
            CHECK_EQ(colour.green, 20);
            CHECK_EQ(colour.blue, 30);
            CHECK_EQ(colour.opacity, 40);
        }

        SUBCASE("Construct from #RRGGBB hex code")
        {
            ime::Colour colour{"#000000"};
            CHECK_EQ(colour.red, 0);
            CHECK_EQ(colour.green, 0);
            CHECK_EQ(colour.blue, 0);
            CHECK_EQ(colour.opacity, 255);
        }

        SUBCASE("Construct from #RRGGBBAA hex code")
        {
            ime::Colour colour{"#00FF00C8"};
            CHECK_EQ(colour.red, 0);
            CHECK_EQ(colour.green, 255);
            CHECK_EQ(colour.blue, 0);
            CHECK_EQ(colour.opacity, 200);
        }
    }

    SUBCASE("Operators")
    {
        SUBCASE("operator+")
        {
            ime::Colour c1(1, 1, 1, 1);
            ime::Colour c2(1, 2, 3, 4);
            CHECK_EQ(c1 + c2, ime::Colour(2, 3, 4, 5));

            SUBCASE("clamped")
            {
                ime::Colour c3(255, 255, 255, 255);
                CHECK_EQ(c3 + c1, ime::Colour(255, 255, 255, 255));
            }
        }

        SUBCASE("operator-")
        {
            ime::Colour c1(10, 20, 30, 40);
            ime::Colour c2(5, 10, 15, 20);
            CHECK_EQ(c1 - c2, ime::Colour(5, 10, 15, 20));

            SUBCASE("clamped")
            {
                CHECK_EQ(c2 - c1, ime::Colour(0, 0, 0, 0));
            }
        }

        SUBCASE("operator*")
        {
            ime::Colour c1(255, 255, 255, 255);
            ime::Colour c2(2, 4, 6, 8);
            CHECK_EQ(c1 * c2, ime::Colour(2, 4, 6, 8));
        }

        SUBCASE("operator==")
        {
            CHECK(ime::Colour(0, 0, 0) == ime::Colour(0, 0, 0));
        }

        SUBCASE("operator!=")
        {
            CHECK(ime::Colour(0, 0, 0) != ime::Colour(255, 0, 0));
        }

        SUBCASE("operator+=")
        {
            ime::Colour c1(10, 20, 30, 40);
            c1 += ime::Colour(5, 10, 15, 20);
            CHECK_EQ(c1, ime::Colour(15, 30, 45, 60));

            SUBCASE("clamped")
            {
                c1 += ime::Colour(255, 255, 255, 255);
                CHECK_EQ(c1, ime::Colour(255, 255, 255, 255));
            }
        }

        SUBCASE("operator-=")
        {
            ime::Colour c1(10, 20, 30, 40);
            ime::Colour c2(5, 10, 15, 20);

            c1 -= c2;
            CHECK_EQ(c1, ime::Colour(5, 10, 15, 20));

            SUBCASE("clamped")
            {
                c1 -= ime::Colour(255, 255, 255, 255);
                CHECK_EQ(c1, ime::Colour(0, 0, 0, 0));
            }
        }

        SUBCASE("operator*=")
        {
            ime::Colour c1(255, 255, 255, 255);
            c1 *= ime::Colour(2, 4, 6, 8);
            CHECK_EQ(c1, ime::Colour(2, 4, 6, 8));
        }
    }

    SUBCASE("Predefined colours")
    {
        CHECK_EQ(ime::Colour::Black, ime::Colour(0, 0, 0, 255));
        CHECK_EQ(ime::Colour::White, ime::Colour(255, 255, 255, 255));
        CHECK_EQ(ime::Colour::Red, ime::Colour(255, 0, 0, 255));
        CHECK_EQ(ime::Colour::Green, ime::Colour(0, 255, 0, 255));
        CHECK_EQ(ime::Colour::Blue, ime::Colour(0, 0, 255, 255));
        CHECK_EQ(ime::Colour::Yellow, ime::Colour(255, 255, 0, 255));
        CHECK_EQ(ime::Colour::Orange, ime::Colour(255, 165, 0, 255));
        CHECK_EQ(ime::Colour::Brown, ime::Colour(165, 42, 42, 255));
        CHECK_EQ(ime::Colour::Maroon, ime::Colour(128, 0, 0, 255));
        CHECK_EQ(ime::Colour::Indigo, ime::Colour(75, 0, 130, 255));
        CHECK_EQ(ime::Colour::Cyan, ime::Colour(0, 255, 255, 255));
        CHECK_EQ(ime::Colour::Magenta, ime::Colour(255, 0, 255, 255));
        CHECK_EQ(ime::Colour::Purple, ime::Colour(128, 0, 128, 255));
        CHECK_EQ(ime::Colour::Pink, ime::Colour(255, 192, 203, 255));
        CHECK_EQ(ime::Colour::Grey, ime::Colour(128, 128, 128, 255));
        CHECK_EQ(ime::Colour::Violet, ime::Colour(238, 130, 238, 255));
        CHECK_EQ(ime::Colour::Turquoise, ime::Colour(64, 224, 208, 255));
        CHECK_EQ(ime::Colour::Gold, ime::Colour(255, 215, 0, 255));
        CHECK_EQ(ime::Colour::Silver, ime::Colour(192, 192, 192, 255));
        CHECK_EQ(ime::Colour::Transparent, ime::Colour(0, 0, 0, 0));
    }
}