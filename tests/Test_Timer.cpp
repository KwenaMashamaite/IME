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

#include "IME/core/time/Timer.h"
#include <doctest.h>

TEST_CASE("ime::Timer class")
{
    SUBCASE("Constructors")
    {
        SUBCASE("Default constructor")
        {
            ime::Timer timer;

            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
            CHECK_EQ(timer.getInterval(), ime::Time::Zero);
            CHECK_EQ(timer.getElapsedTime(), ime::Time::Zero);
            CHECK_EQ(timer.getRemainingDuration(), ime::Time::Zero);
            CHECK_EQ(timer.getRepeatCount(), 0);
            CHECK_EQ(timer.getDispatchCount(), 0);
            CHECK_EQ(timer.getTimescale(), 1);
            CHECK(timer.isStopped());
            CHECK_FALSE(timer.isRunning());
            CHECK_FALSE(timer.isPaused());
            CHECK_FALSE(timer.isLooped());
            CHECK_FALSE(timer.isRepeating());
            CHECK_FALSE(timer.isDispatched());
        }
    }

    SUBCASE("Setters and getters")
    {
        SUBCASE("setInterval()")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(5));
            CHECK_EQ(timer.getInterval(), ime::seconds(5));

            SUBCASE("The remaining duration is the same as the interval")
            {
                CHECK_EQ(timer.getInterval(), timer.getRemainingDuration());
            }
        }

        SUBCASE("setRepeatCount()")
        {
            ime::Timer timer;
            timer.setRepeatCount(75);
            CHECK_EQ(timer.getRepeatCount(), 75);

            SUBCASE("A negative repeat count sets the timer to repeat indefinitely")
            {
                timer.setRepeatCount(-1);
                CHECK(timer.isLooped());
            }
        }

        SUBCASE("setLoop()")
        {
            ime::Timer timer;

            timer.setLoop(true);
            CHECK(timer.isLooped());

            timer.setLoop(false);
            CHECK_FALSE(timer.isLooped());

            SUBCASE("Setting the timer to 'loop' sets the repeat count to '-1'")
            {
                timer.setLoop(true);
                REQUIRE(timer.isLooped());
                CHECK_EQ(timer.getRepeatCount(), -1);
            }
        }

        SUBCASE("setTimescale()")
        {
            ime::Timer timer;

            timer.setTimescale(3.0f);
            CHECK_EQ(timer.getTimescale(), 3.0f);

            SUBCASE("A negative timescale value is ignored")
            {
                REQUIRE_EQ(timer.getTimescale(), 3.0f);
                timer.setTimescale(-2.0f);
                CHECK_EQ(timer.getTimescale(), 3.0f);
            }

            SUBCASE("A timescale value of 0 is ignored")
            {
                REQUIRE_EQ(timer.getTimescale(), 3.0f);
                timer.setTimescale(0.0f);
                CHECK_EQ(timer.getTimescale(), 3.0f);
            }
        }
    }

    SUBCASE("update()")
    {
        SUBCASE("Updating a 'running' timer increases the elapsed time by the delta time")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(10));
            timer.onTimeout([]{});

            timer.start();
            REQUIRE(timer.isRunning());
            REQUIRE_EQ(timer.getElapsedTime().asSeconds(), 0);

            timer.update(ime::seconds(1));
            CHECK_EQ(timer.getElapsedTime().asSeconds(), 1);

            timer.update(ime::seconds(1));
            CHECK_EQ(timer.getElapsedTime().asSeconds(), 2);

            timer.update(ime::seconds(3));
            CHECK_EQ(timer.getElapsedTime().asSeconds(), 5);
        }

        SUBCASE("A 'stopped' timer does not update")
        {
            ime::Timer timer;

            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
            REQUIRE_EQ(timer.getElapsedTime().asSeconds(), 0.0f);

            timer.update(ime::seconds(2));
            CHECK_EQ(timer.getElapsedTime().asSeconds(), 0.0f);
        }

        SUBCASE("A 'paused' timer does not update")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(5));

            // The timer cannot start without a registered timeout callback
            timer.onTimeout([]{});

            // A ime::Timer can ony be paused if it was previously running
            timer.start();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);

            timer.pause();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Paused);

            REQUIRE_EQ(timer.getElapsedTime().asSeconds(), 0);
            timer.update(ime::seconds(7));

            CHECK_EQ(timer.getElapsedTime().asSeconds(), 0);
        }

        SUBCASE("Updating a 'running' timer decreases the remaining duration by the delta time")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(7));

            // The timer cannot start without a registered timeout callback
            timer.onTimeout([]{});
            timer.start();

            REQUIRE_EQ(timer.getRemainingDuration().asSeconds(), 7.0f);

            timer.update(ime::seconds(1));
            CHECK_EQ(timer.getRemainingDuration().asSeconds(), 6.0f);

            timer.update(ime::seconds(3));
            CHECK_EQ(timer.getRemainingDuration().asSeconds(), 3.0f);

            timer.update(ime::seconds(2));
            CHECK_EQ(timer.getRemainingDuration().asSeconds(), 1.0f);
        }

        SUBCASE("Updating a 'running' timer with a timescale that is not 1 (real-time)")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(5));
            timer.onTimeout([] {}); // Timer cannot start without a timout callback
            timer.start();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);

            WHEN("The timescale is greater than 1")
            {
                timer.setTimescale(4.0f);
                REQUIRE_EQ(timer.getTimescale(), 4.0f);

                THEN("The timer counts down faster than real time")
                {
                    REQUIRE_EQ(timer.getElapsedTime().asSeconds(), 0.0f);
                    timer.update(ime::seconds(1));
                    REQUIRE_EQ(timer.getElapsedTime().asSeconds(), 4.0f);

                }
            }

            WHEN("The timescale is less than 1")
            {
                timer.setTimescale(0.5f);
                REQUIRE_EQ(timer.getTimescale(), 0.5f);

                THEN("The timer counts down slower than real timer")
                {
                    REQUIRE_EQ(timer.getElapsedTime().asSeconds(), 0.0f);
                    timer.update(ime::seconds(1));
                    REQUIRE_EQ(timer.getElapsedTime().asSeconds(), 0.5f);
                }
            }
        }

        WHEN("The countdown of a non repeating timer reaches zero")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(2.0f));
            REQUIRE_EQ(timer.getRemainingDuration().asSeconds(), 2.0f);

            bool isInvoked = false;
            timer.onTimeout([&isInvoked] (ime::Timer&) {
                isInvoked = true;
            });

            timer.start();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);;
            timer.update(ime::seconds(2.0f));

            THEN("The timeout callback is invoked")
            {
                CHECK(isInvoked);
            }
            AND_THEN("isDispatched() returns true")
            {
                CHECK(timer.isDispatched());
            }
            AND_THEN("The timeout callback dispatch count increases by 1")
            {
                CHECK_EQ(timer.getDispatchCount(), 1);
            }
        }
    }

    SUBCASE("Callbacks")
    {
        SUBCASE("onStart()")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(3.0f));
            timer.onTimeout([] {}); // Timer cannot start without a timeout callback

            bool isInvoked = false;
            timer.onStart([&isInvoked] (ime::Timer&) {
                isInvoked = true;
            });

            timer.start();
            CHECK(isInvoked);
        }

        SUBCASE("onPause()")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(3.0f));
            timer.onTimeout([] {}); // Timer cannot start without a timeout callback

            timer.start();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);

            bool isInvoked = false;
            timer.onPause([&isInvoked] (ime::Timer&) {
                isInvoked = true;
            });

            timer.pause();
            CHECK(isInvoked);
        }

        SUBCASE("onResume()")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(3.0f));
            timer.onTimeout([] {}); // Timer cannot start without a timeout callback

            timer.start();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
            timer.pause();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Paused);

            bool isInvoked = false;
            timer.onResume([&isInvoked] (ime::Timer&) {
                isInvoked = true;
            });

            timer.resume();
            CHECK(isInvoked);
        }

        SUBCASE("onRestart()")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(3.0f));
            timer.onTimeout([] {}); // Timer cannot start without a timeout callback

            timer.start();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);

            bool isInvoked = false;
            timer.onRestart([&isInvoked] (ime::Timer&) {
                isInvoked = true;
            });

            timer.restart();
            CHECK(isInvoked);
        }

        SUBCASE("onStop()")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(3.0f));
            timer.onTimeout([] {}); // Timer cannot start without a timeout callback

            timer.start();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);

            bool isInvoked = false;
            timer.onStop([&isInvoked] (ime::Timer&) {
                isInvoked = true;
            });

            timer.stop();
            CHECK(isInvoked);
        }

        SUBCASE("onUpdate()")
        {
            ime::Timer timer;
            timer.setInterval(ime::seconds(3.0f));
            timer.onTimeout([] {}); // Timer cannot start without a timeout callback

            timer.start();
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);

            bool isInvoked = false;
            timer.onUpdate([&isInvoked] (ime::Timer&) {
                isInvoked = true;
            });

            timer.update(ime::seconds(1));
            CHECK(isInvoked);
        }
    }
}