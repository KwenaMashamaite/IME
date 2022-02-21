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

#include "IME/common/Preference.h"
#include <doctest.h>

TEST_CASE("ime::Preference class")
{
    SUBCASE("Constructors")
    {
        SUBCASE("(key, type) constructor")
        {
            ime::Preference preference("VOLUME", ime::PrefType::Float);

            CHECK_EQ(preference.getKey(), "VOLUME");
            CHECK_EQ(preference.getType(), ime::PrefType::Float);
            CHECK_EQ(preference.getDescription(), "");
            CHECK_FALSE(preference.hasValue());
        }

        SUBCASE("(key, type, value) constructor")
        {
            ime::Preference preference("NAME", ime::PrefType::String, std::string("IME"));

            CHECK_EQ(preference.getKey(), "NAME");
            CHECK_EQ(preference.getType(), ime::PrefType::String);
            CHECK_EQ(preference.getDescription(), "");
            CHECK(preference.hasValue());
            CHECK_EQ(preference.getValue<std::string>(), std::string("IME"));
        }

        SUBCASE("(key, type, value, description) constructor")
        {
            ime::Preference preference("FULL_SCREEN", ime::PrefType::Bool, true, "Game window full screen option");

            CHECK_EQ(preference.getKey(), "FULL_SCREEN");
            CHECK_EQ(preference.getType(), ime::PrefType::Bool);
            CHECK_EQ(preference.getDescription(), "Game window full screen option");
            CHECK(preference.hasValue());
            CHECK_EQ(preference.getValue<bool>(), true);
        }
    }

    SUBCASE("Setters and getters")
    {
        SUBCASE("setValue()")
        {
            ime::Preference preference("VOLUME", ime::PrefType::Float);
            preference.setValue(10.0f);

            CHECK_EQ(preference.getValue<float>(), 10.0f);

            SUBCASE("getValue() throws ime::InvalidArgument when the template argument does not match the contained type")
            {
                CHECK_THROWS_AS(preference.getValue<bool>(), ime::InvalidArgumentException);
            }
        }

        SUBCASE("setDescription()")
        {
            ime::Preference preference("VOLUME", ime::PrefType::Float);
            preference.setDescription("The master volume");

            CHECK_EQ(preference.getDescription(), "The master volume");
        }
    }
}