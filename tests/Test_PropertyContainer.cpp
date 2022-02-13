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

#include "IME/common/PropertyContainer.h"
#include <string>
#include <doctest.h>

TEST_CASE("ime::PropertyContainer class")
{
    SUBCASE("Constructors")
    {
        SUBCASE("Default constructor")
        {
            ime::PropertyContainer propertyContainer;

            CHECK_EQ(propertyContainer.getCount(), 0);
        }
    }

    SUBCASE("Setters and getters")
    {
        SUBCASE("setValue()")
        {
            ime::PropertyContainer propertyContainer;
            propertyContainer.addProperty(ime::Property("data"));

            REQUIRE(propertyContainer.hasProperty("data"));

            propertyContainer.setValue("data", 100);
            CHECK_EQ(propertyContainer.getValue<int>("data"), 100);

            propertyContainer.setValue("data", std::string("IME"));
            CHECK_EQ(propertyContainer.getValue<std::string>("data"), std::string("IME"));

            propertyContainer.setValue("data", 10.0f);
            CHECK_EQ(propertyContainer.getValue<float>("data"), 10.0f);

            propertyContainer.setValue("data", false);
            CHECK_EQ(propertyContainer.getValue<bool>("data"), false);
        }
    }

    SUBCASE("addProperty()")
    {
        ime::PropertyContainer propertyContainer;
        propertyContainer.addProperty(ime::Property("Master_Volume"));
        propertyContainer.addProperty(ime::Property("Player_Name"));
        propertyContainer.addProperty(ime::Property("V_Sync"));

        CHECK_EQ(propertyContainer.getCount(), 3);
        CHECK(propertyContainer.hasProperty("Master_Volume"));
        CHECK(propertyContainer.hasProperty("Player_Name"));
        CHECK(propertyContainer.hasProperty("V_Sync"));
        CHECK_FALSE(propertyContainer.hasProperty(""));
        CHECK_FALSE(propertyContainer.hasProperty("Sound_Enable"));

        SUBCASE("Multiple properties with the same name are not allowed")
        {
            propertyContainer.clear();
            REQUIRE_EQ(propertyContainer.getCount(), 0);

            propertyContainer.addProperty(ime::Property("Master_Volume"));
            propertyContainer.addProperty(ime::Property("Master_Volume"));
            propertyContainer.addProperty(ime::Property("Master_Volume"));
            propertyContainer.addProperty(ime::Property("Master_Volume"));

            CHECK_EQ(propertyContainer.getCount(), 1);
        }
    }

    SUBCASE("removeProperty()")
    {
        ime::PropertyContainer propertyContainer;
        propertyContainer.addProperty(ime::Property("Master_Volume"));
        propertyContainer.addProperty(ime::Property("Player_Name"));
        propertyContainer.addProperty(ime::Property("V_Sync"));

        REQUIRE(propertyContainer.hasProperty("Master_Volume"));
        REQUIRE_EQ(propertyContainer.getCount(), 3);

        propertyContainer.removeProperty("Master_Volume");
        CHECK_FALSE(propertyContainer.hasProperty("Master_Volume"));
        CHECK_EQ(propertyContainer.getCount(), 2);
    }

    SUBCASE("clear()")
    {
        ime::PropertyContainer propertyContainer;
        propertyContainer.addProperty(ime::Property("Master_Volume"));
        propertyContainer.addProperty(ime::Property("Player_Name"));
        propertyContainer.addProperty(ime::Property("V_Sync"));

        REQUIRE_EQ(propertyContainer.getCount(), 3);

        propertyContainer.clear();
        CHECK_EQ(propertyContainer.getCount(), 0);
    }

    SUBCASE("propertyHasValue()")
    {
        ime::PropertyContainer propertyContainer;
        propertyContainer.addProperty(ime::Property("data"));

        REQUIRE(propertyContainer.hasProperty("data"));
        CHECK_FALSE(propertyContainer.propertyHasValue("data"));

        propertyContainer.setValue("data", 100);
        CHECK(propertyContainer.propertyHasValue("data"));
    }

    SUBCASE("forEachProperty()")
    {
        ime::PropertyContainer propertyContainer;
        propertyContainer.addProperty(ime::Property("data1", 10));
        propertyContainer.addProperty(ime::Property("data2", 20));
        propertyContainer.addProperty(ime::Property("data3", 40));

        REQUIRE_EQ(propertyContainer.getCount(), 3);

        propertyContainer.forEachProperty([](ime::Property& property) {
            property.setValue(100);
        });

        CHECK_EQ(propertyContainer.getValue<int>("data1"), 100);
        CHECK_EQ(propertyContainer.getValue<int>("data2"), 100);
        CHECK_EQ(propertyContainer.getValue<int>("data3"), 100);
    }

    SUBCASE("onValueChange()")
    {
        ime::PropertyContainer propertyContainer;
        propertyContainer.addProperty(ime::Property("Master_Volume"));

        bool isInvoked = false;
        int newValue = -1;
        propertyContainer.onValueChange("Master_Volume", [&isInvoked, &newValue](ime::Property* const p) {
            isInvoked = true;
            newValue = p->getValue<int>();
        });

        propertyContainer.setValue("Master_Volume", 45);

        CHECK(isInvoked);
        CHECK_EQ(newValue, 45);
    }

    SUBCASE("unsubscribe()")
    {
        ime::PropertyContainer propertyContainer;
        propertyContainer.addProperty(ime::Property("Master_Volume"));

        bool isInvoked = false;
        int newValue = -1;
        int valueChangeListener = propertyContainer.onValueChange("Master_Volume", [&isInvoked, &newValue](ime::Property* const p) {
            isInvoked = true;
            newValue = p->getValue<int>();
        });

        propertyContainer.unsubscribe("Master_Volume", valueChangeListener);
        propertyContainer.setValue("Master_Volume", 45);

        CHECK_FALSE(isInvoked);
        CHECK_EQ(newValue, -1);
    }
}