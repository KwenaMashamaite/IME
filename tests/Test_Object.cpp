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

#include "IME/core/object/Object.h"
#include <doctest.h>

class TestObject : public ime::Object {
public:
    using ime::Object::emitDestruction;

    std::string getClassName() const override {
        return "TestObject";
    }
};

TEST_CASE("ime::Object class")
{
    SUBCASE("Constructors")
    {
        SUBCASE("Default constructor")
        {
            TestObject object;

            CHECK_EQ(object.getTag(), "");
            CHECK_EQ(object.getObjectId(), 0);
            CHECK_EQ(object.getClassType(), "Object");

            SUBCASE("Objects have unique id's")
            {
                TestObject object2;
                TestObject object3;

                CHECK_NE(object.getObjectId(), object2.getObjectId());
                CHECK_NE(object.getObjectId(), object3.getObjectId());
                CHECK_NE(object2.getObjectId(), object3.getObjectId());
            }
        }
    }

    SUBCASE("Setters and getters")
    {
        SUBCASE("setTag()")
        {
            TestObject object;
            object.setTag("test_object");

            CHECK_EQ(object.getTag(), "test_object");
        }
    }

    SUBCASE("isSameObjectAs()")
    {
        TestObject object1;
        TestObject object2;

        CHECK(object1.isSameObjectAs(object1));
        CHECK_FALSE(object1.isSameObjectAs(object2));
    }

    SUBCASE("Callbacks")
    {
        SUBCASE("onDestruction()")
        {
            SUBCASE("Destruction listeners are invoked when the object goes out of scope")
            {
                auto object = std::make_unique<TestObject>();

                bool isInvoked = false;
                object->onDestruction([&isInvoked] {
                    isInvoked = true;
                });

                object.reset(); // Destroy object

                CHECK(isInvoked);
            }

            SUBCASE("Destruction listeners are invoked once")
            {
                auto object = std::make_unique<TestObject>();

                bool isInvoked = false;
                int invocationCount = 0;
                object->onDestruction([&isInvoked, &invocationCount] {
                    isInvoked = true;
                    invocationCount++;
                });

                object->emitDestruction();
                object->emitDestruction();
                object->emitDestruction();
                object->emitDestruction();

                REQUIRE(isInvoked);
                CHECK_EQ(invocationCount, 1);
            }
        }

        SUBCASE("onPropertyChange(property, callback, oneTime = false)")
        {
            TestObject object;
            bool isInvoked = false;
            std::string propertyValue;
            std::string propertyName;

            object.onPropertyChange("tag", [&](const ime::Property& property) {
                isInvoked = true;
                propertyName = property.getName();
                propertyValue = property.getValue<std::string>();
            }, false);

            object.setTag("playerOne");
            object.setTag("playerTwo");

            CHECK(isInvoked);
            CHECK_EQ(propertyName, "tag");
            CHECK_EQ(propertyValue, "playerTwo");
        }

        SUBCASE("onPropertyChange(property, callback, oneTime = true)")
        {
            TestObject object;
            bool isInvoked = false;
            std::string propertyValue;
            std::string propertyName;

            object.onPropertyChange("tag", [&](const ime::Property& property) {
                isInvoked = true;
                propertyName = property.getName();
                propertyValue = property.getValue<std::string>();
            }, true);

            object.setTag("playerOne");
            object.setTag("playerTwo");
            object.setTag("playerThree");

            CHECK(isInvoked);
            CHECK_EQ(propertyName, "tag");
            CHECK_EQ(propertyValue, "playerOne");
        }

        SUBCASE("A suspended property change event listener is not invoked when the event is emitted")
        {
            TestObject object;
            bool isInvoked = false;

            int tagChangeListener = object.onPropertyChange("tag", [&isInvoked](const ime::Property&) {
                isInvoked = true;
            });

            object.suspendedEventListener(tagChangeListener, true);
            REQUIRE(object.isEventListenerSuspended(tagChangeListener));

            object.setTag("playerOne");

            CHECK_FALSE(isInvoked);

            SUBCASE("When unsuspended, invocation resumes")
            {
                object.suspendedEventListener(tagChangeListener, false);
                REQUIRE_FALSE(object.isEventListenerSuspended(tagChangeListener));

                object.setTag("playerTwo");

                CHECK(isInvoked);
            }
        }

        SUBCASE("removeEventListener()")
        {
            SUBCASE("Removing a non-existent event listener returns 'false'")
            {
                CHECK_FALSE(TestObject().removeEventListener(-1));
            }

            SUBCASE("Removing an existing event listener returns 'true'")
            {
                TestObject object;

                int tagChangeListener = object.onPropertyChange("tag", [](const ime::Property&) {});

                CHECK(object.removeEventListener(tagChangeListener));
            }

            SUBCASE("A removed event listener is not invoked when an event is raised")
            {
                TestObject object;
                bool isInvoked = false;

                int tagChangeListener = object.onPropertyChange("tag", [&isInvoked](const ime::Property&) {
                    isInvoked = true;
                });

                object.removeEventListener(tagChangeListener);
                object.setTag("player_1");

                CHECK_FALSE(isInvoked);
            }
        }
    }
}