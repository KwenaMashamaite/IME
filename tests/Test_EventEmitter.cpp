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

#include "IME/core/event/EventEmitter.h"
#include <doctest.h>

TEST_CASE("ime::EventEmitter class")
{
    SUBCASE("Constructors")
    {
        SUBCASE("Default constructor")
        {
            ime::EventEmitter eventEmitter;

            CHECK(eventEmitter.isActive());
            CHECK_EQ(eventEmitter.getEventsCount(), 0);
        }
    }

    SUBCASE("Setters and getters")
    {
        SUBCASE("setActive()")
        {
            ime::EventEmitter eventEmitter;

            eventEmitter.setActive(false);
            CHECK_FALSE(eventEmitter.isActive());

            eventEmitter.setActive(true);
            CHECK(eventEmitter.isActive());
        }
    }

    SUBCASE("Creating events and subscribing event listeners")
    {
        SUBCASE("addEventListener()")
        {
            ime::EventEmitter eventEmitter;
            eventEmitter.addEventListener("event", ime::Callback<>([] {}));
            eventEmitter.addEventListener("event", ime::Callback<>([] {}));

            CHECK(eventEmitter.hasEvent("event"));
            CHECK_EQ(eventEmitter.getEventsCount(), 1);
            CHECK_EQ(eventEmitter.getEventListenerCount("event"), 2);

            SUBCASE("Event listeners have unique identification numbers")
            {
                int handler1Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));
                int handler2Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));
                int handler3Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));

                CHECK_NE(handler1Id, handler2Id);
                CHECK_NE(handler1Id, handler3Id);
                CHECK_NE(handler3Id, handler2Id);
            }
        }

        SUBCASE("on()")
        {
            ime::EventEmitter eventEmitter;
            int id = eventEmitter.on("event", ime::Callback<>([] {}));

            CHECK(eventEmitter.hasEvent("event"));
            CHECK(eventEmitter.hasEventListener("event", id));
            CHECK_EQ(eventEmitter.getEventsCount(), 1);
            CHECK_EQ(eventEmitter.getEventListenerCount("event"), 1);
        }

        SUBCASE("addOnceEventListener()")
        {
            ime::EventEmitter eventEmitter;
            int id = eventEmitter.addOnceEventListener("event", ime::Callback<>([] {}));

            CHECK(eventEmitter.hasEvent("event"));
            CHECK(eventEmitter.hasEventListener("event", id));
            CHECK_EQ(eventEmitter.getEventsCount(), 1);
            CHECK_EQ(eventEmitter.getEventListenerCount("event"), 1);
        }
    }

    SUBCASE("Removing events and event listeners")
    {
        SUBCASE("removeEventListener(event, id)")
        {
            ime::EventEmitter eventEmitter;

            SUBCASE("Removing a non-existent event listener returns 'false'")
            {
                CHECK_FALSE(eventEmitter.removeEventListener("event", -1));
            }

            SUBCASE("Removing an existing event listener returns 'true'")
            {
                int handler1Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));
                int handler2Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));

                CHECK(eventEmitter.removeEventListener("event", handler1Id));
                CHECK(eventEmitter.removeEventListener("event", handler2Id));
            }

            SUBCASE("The event listener count decreases by the number or removed listeners")
            {
                int handler1Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));
                int handler2Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));

                REQUIRE_EQ(eventEmitter.getEventListenerCount("event"), 2);

                eventEmitter.removeEventListener("event", handler1Id);
                CHECK_EQ(eventEmitter.getEventListenerCount("event"), 1);

                eventEmitter.removeEventListener("event", handler2Id);
                CHECK_EQ(eventEmitter.getEventListenerCount("event"), 0);
            }
        }

        SUBCASE("removeEventListener(id)")
        {
            ime::EventEmitter eventEmitter;
            int handler1Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));
            int handler2Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));
            int handler3Id = eventEmitter.addEventListener("event", ime::Callback<>([] {}));

            REQUIRE_EQ(eventEmitter.getEventListenerCount("event"), 3);
            CHECK(eventEmitter.removeEventListener(handler1Id));
            CHECK(eventEmitter.removeEventListener(handler2Id));
            CHECK(eventEmitter.removeEventListener(handler3Id));
            CHECK_FALSE(eventEmitter.removeEventListener(handler1Id));
            CHECK_FALSE(eventEmitter.removeEventListener(handler2Id));
            CHECK_EQ(eventEmitter.getEventListenerCount("event"), 0);
        }

        SUBCASE("removeAllEventListeners(event)")
        {
            ime::EventEmitter eventEmitter;
            eventEmitter.addEventListener("event", ime::Callback<>([] {}));
            eventEmitter.addEventListener("event", ime::Callback<>([] {}));
            eventEmitter.addEventListener("event", ime::Callback<>([] {}));

            REQUIRE_EQ(eventEmitter.getEventListenerCount("event"), 3);
            eventEmitter.removeAllEventListeners("event");
            CHECK_EQ(eventEmitter.getEventListenerCount("event"), 0);
        }

        SUBCASE("clear()")
        {
            ime::EventEmitter eventEmitter;
            eventEmitter.addEventListener("event1", ime::Callback<>([] {}));
            eventEmitter.addEventListener("event2", ime::Callback<>([] {}));
            eventEmitter.addEventListener("event3", ime::Callback<>([] {}));
            eventEmitter.addEventListener("event4", ime::Callback<>([] {}));
            eventEmitter.addEventListener("event5", ime::Callback<>([] {}));

            REQUIRE_EQ(eventEmitter.getEventsCount(), 5);
            eventEmitter.clear();
            CHECK_EQ(eventEmitter.getEventsCount(), 0);
        }
    }

    SUBCASE("Invoking event listeners")
    {
        SUBCASE("emit()")
        {
            SUBCASE("An event listener is invoked every time its event is emitted")
            {
                ime::EventEmitter eventEmitter;

                bool isInvoked = false;
                int invokeCount = 0;
                eventEmitter.addEventListener("event", ime::Callback<>([&isInvoked, &invokeCount] {
                    isInvoked = true;
                    invokeCount++;
                }));

                REQUIRE_EQ(eventEmitter.getEventListenerCount("event"), 1);
                eventEmitter.emit("event");
                eventEmitter.emit("event");
                eventEmitter.emit("event");

                CHECK(isInvoked);
                CHECK_EQ(invokeCount, 3);
            }

            SUBCASE("Emitting an event, invokes all its event listeners")
            {
                ime::EventEmitter eventEmitter;
                int counter = 0;

                eventEmitter.addEventListener("increaseCounter", ime::Callback<>([&counter]() { counter += 1; }));
                eventEmitter.addEventListener("increaseCounter", ime::Callback<>([&counter]() { counter += 5; }));
                eventEmitter.addEventListener("increaseCounter", ime::Callback<>([&counter]() { counter += 4; }));
                eventEmitter.addEventListener("increaseCounter", ime::Callback<>([&counter]() { counter += 10; }));

                REQUIRE_EQ(eventEmitter.getEventListenerCount("increaseCounter"), 4);
                eventEmitter.emit("increaseCounter");

                CHECK_EQ(counter, 20u);
            }

            SUBCASE("An event listener is only invoked if its parameter list matches that of the event arguments")
            {
                ime::EventEmitter eventEmitter;

                bool isListenerOneInvoked = false;
                eventEmitter.addEventListener("event", ime::Callback<int, bool>([&isListenerOneInvoked](int, bool) {
                    isListenerOneInvoked = true;
                }));

                bool isListenerTwoInvoked = false;
                eventEmitter.addEventListener("event", ime::Callback<double, float>([&isListenerTwoInvoked](double, float) {
                    isListenerTwoInvoked = true;
                }));

                eventEmitter.emit("event", 10, true);
                CHECK(isListenerOneInvoked);
                CHECK_FALSE(isListenerTwoInvoked);

                isListenerOneInvoked = false;
                eventEmitter.emit("event", 10.0, 24.0f);

                CHECK(isListenerTwoInvoked);
                CHECK_FALSE(isListenerOneInvoked);
            }

            SUBCASE("Event listeners receive correct event arguments")
            {
                ime::EventEmitter eventEmitter;

                int age = -1;
                double speed = -1.0;
                std::string name;

                eventEmitter.addEventListener("event", ime::Callback<int, double, std::string>([&](int x, double y, std::string z) {
                    age = x;
                    speed = y;
                    name = z;
                }));

                eventEmitter.emit("event", 10, 75.0, std::string("Kwena"));

                CHECK_EQ(age, 10);
                CHECK_EQ(speed, 75.0);
                CHECK_EQ(name, "Kwena");
            }

            SUBCASE("Event listener parameter list matching ignores references")
            {
                ime::EventEmitter eventEmitter;

                int num1, num2 = -1;

                eventEmitter.addEventListener("event", ime::Callback<int>([&num1](int num) {
                    num1 = num;
                }));

                eventEmitter.addEventListener("event", ime::Callback<int&>([&num2](int& num) {
                    num2 = num;
                }));

                eventEmitter.emit("event", 10);

                CHECK_EQ(num1, 10);
                CHECK_EQ(num2, -1);
            }

            SUBCASE("A 'once' event listener is invoked only once")
            {
                ime::EventEmitter eventEmitter;

                bool isInvoked = false;
                int invokeCount = 0;
                eventEmitter.addOnceEventListener("event", ime::Callback<>([&isInvoked, &invokeCount] {
                    isInvoked = true;
                    invokeCount++;
                }));

                REQUIRE_EQ(eventEmitter.getEventListenerCount("event"), 1);
                eventEmitter.emit("event");
                eventEmitter.emit("event");
                eventEmitter.emit("event");

                CHECK(isInvoked);
                CHECK_EQ(invokeCount, 1);
            }

            SUBCASE("A 'once' event listener is immediately removed from the event list after its execution")
            {
                ime::EventEmitter eventEmitter;

                bool isInvoked = false;
                int onceListener = eventEmitter.addOnceEventListener("event", ime::Callback<>([&isInvoked] {
                    isInvoked = true;
                }));

                REQUIRE(eventEmitter.hasEventListener("event", onceListener));
                eventEmitter.emit("event");

                CHECK(isInvoked);
                CHECK_FALSE(eventEmitter.hasEventListener("event", onceListener));
            }

            SUBCASE("A suspended event listener is not invoked when its event is emitted")
            {
                ime::EventEmitter eventEmitter;

                bool isInvoked = false;
                int handlerId = eventEmitter.addEventListener("event", ime::Callback<>([&isInvoked] {
                    isInvoked = true;
                }));

                eventEmitter.suspendEventListener(handlerId, true);
                REQUIRE(eventEmitter.isEventListenerSuspended("event", handlerId));
                eventEmitter.emit("event");

                CHECK_FALSE(isInvoked);
            }

            SUBCASE("A 'disabled' event emitter does not emit events")
            {
                ime::EventEmitter eventEmitter;

                bool isInvoked = false;
                eventEmitter.addEventListener("event", ime::Callback<>([&isInvoked] {
                    isInvoked = true;
                }));

                eventEmitter.setActive(false);
                REQUIRE_FALSE(eventEmitter.isActive());
                eventEmitter.emit("event");

                CHECK_FALSE(isInvoked);
            }
        }
    }
}
