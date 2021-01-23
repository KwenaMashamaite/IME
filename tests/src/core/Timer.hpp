////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "doctest.h"
#include "IME/core/time/Timer.h"

TEST_CASE("A timer is stopped by default") {
    CHECK_EQ(ime::Timer().getStatus(), ime::Timer::Status::Stopped);
}

TEST_CASE("A timer is not repeating by default") {
    CHECK_FALSE(ime::Timer().isRepeating());
}

TEST_CASE("A timer can be set to repeat") {
    auto timer = ime::Timer();
    REQUIRE_FALSE(timer.isRepeating());
    timer.setRepeat(true);
    CHECK(timer.isRepeating());
}

TEST_CASE("The remaining duration of a timer is zero by default") {
    CHECK_EQ(ime::Timer().getRemainingDuration(), ime::Time::Zero);
}

TEST_CASE("A timer has an interval of zero by default") {
    CHECK_EQ(ime::Timer().getInterval(), ime::Time::Zero);
}

TEST_CASE("A timer cannot be started if the interval is zero") {
    auto timer = ime::Timer::create(ime::seconds(0.0f), []{});
    REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
    REQUIRE_EQ(timer.getInterval(), ime::Time::Zero);
    CHECK_FALSE(timer.canStart());
    timer.start();
    CHECK_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
}

TEST_CASE("A timer cannot be started if the timeout callback is not set") {
    auto timer = ime::Timer();
    REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);

    timer.setInterval(ime::seconds(10.0f));
    REQUIRE_EQ(timer.getInterval(), ime::seconds(10.0f));
    CHECK_FALSE(timer.canStart());
    timer.start();
    CHECK_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
}

TEST_CASE("A timer can be started if the timeout callback is set and the interval is greater than zero") {
    auto timer = ime::Timer();
    REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
    REQUIRE_FALSE(timer.canStart());

    timer.setInterval(ime::seconds(5.0f));
    REQUIRE_GT(timer.getInterval(), ime::Time::Zero);
    timer.setTimeoutCallback([]{}); //timeout callback set implies the callback is not a nullptr (default)
    CHECK(timer.canStart());
    timer.start();
    CHECK_EQ(timer.getStatus(), ime::Timer::Status::Running);
}

TEST_CASE("If a timer is running and the countdown reaches zero, a callback is invoked") {
    auto callbackInvoked = false;
    auto timer = ime::Timer();
    timer.setTimeoutCallback([&callbackInvoked]{callbackInvoked = true;});
    timer.setInterval(ime::seconds(2.0f));
    timer.start();

    REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
    REQUIRE_EQ(timer.getInterval(), ime::seconds(2.0f));
    REQUIRE_EQ(timer.getRemainingDuration(), ime::seconds(2.0f));
    REQUIRE_FALSE(callbackInvoked);
    timer.update(ime::seconds(2.0f));
    CHECK(callbackInvoked);

    WHEN("the timer is not repeating") {
        REQUIRE_FALSE(timer.isRepeating());
        THEN("the timer is stopped after the callback is invoked for the first time") {
            REQUIRE(callbackInvoked);
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
        }
        AND_THEN("the remaining duration is reset to the value of the interval") {
            CHECK_EQ(timer.getRemainingDuration(), timer.getInterval());
        }
    }
}

SCENARIO("The interval of the timer needs to be changed") {
    auto timer = ime::Timer();
    auto interval = ime::Time::Zero;

    WHEN("the given interval is greater than zero") {
        interval = ime::seconds(5.0f);
        REQUIRE_GT(interval, ime::Time::Zero);
        timer.setInterval(interval);

        THEN("the timers interval is set to the given value") {
            CHECK_EQ(timer.getInterval(), ime::seconds(5.0f));

            SUBCASE("The remaining duration is also set to the given interval") {
                REQUIRE_EQ(timer.getInterval(), ime::seconds(5.0f));
                CHECK_EQ(timer.getRemainingDuration(), ime::seconds(5.0f));
            }
        }
    }

    WHEN("the given interval is less than zero") {
        interval = ime::seconds(-5.0f);
        REQUIRE_LT(interval, ime::Time::Zero);
        timer.setInterval(interval);

        THEN("the timers interval is set to zero") {
            CHECK_EQ(timer.getInterval(), ime::Time::Zero);

            SUBCASE("The remaining duration is also set to zero") {
                REQUIRE_EQ(timer.getInterval(), ime::Time::Zero);
                CHECK_EQ(timer.getRemainingDuration(), ime::Time::Zero);
            }
        }
    }
}

SCENARIO("A timer is running and its member functions are invoked") {
    auto timer = ime::Timer::create(ime::seconds(5.0f), []{});
    timer.start();
    timer.update(ime::seconds(1.0f));

    WHEN("start() is called") {
        REQUIRE_NE(timer.getRemainingDuration(), timer.getInterval());
        timer.start();
        THEN("the timer restarts") {
            REQUIRE_EQ(timer.getRemainingDuration(), timer.getInterval());
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
        }
    }

    AND_WHEN("pause() is called") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
        auto remainingDurationBeforeCallingPause = timer.getRemainingDuration();
        timer.pause();
        THEN("the timer gets paused") {
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Paused);

            SUBCASE("The remaining duration is not reset") {
                REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Paused);
                CHECK_EQ(timer.getRemainingDuration(), remainingDurationBeforeCallingPause);
            }
        }
    }

    AND_WHEN("stop() is called") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
        REQUIRE_NE(timer.getRemainingDuration(), timer.getInterval());
        timer.stop();
        THEN("the timer is stopped") {
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Stopped);

            SUBCASE("The remaining duration is reset to have the same value as the interval") {
                REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
                CHECK_EQ(timer.getRemainingDuration(), timer.getInterval());
            }
        }
    }

    WHEN("setInterval(float) is called with the current interval as the argument") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
        REQUIRE_LT(timer.getRemainingDuration(), timer.getInterval());
        auto remainingDurationBeforeCallingSetInterval = timer.getRemainingDuration();
        timer.setInterval(timer.getInterval());
        THEN("the timers state is not modified") {
            CHECK_LT(timer.getRemainingDuration(), timer.getInterval());
            CHECK_EQ(timer.getRemainingDuration(), remainingDurationBeforeCallingSetInterval);
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Running);
        }
    }

    AND_WHEN("setInterval(float) is called with a new positive argument") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
        REQUIRE_LT(timer.getRemainingDuration(), timer.getInterval());
        REQUIRE_NE(timer.getInterval(), ime::seconds(10.0f));
        timer.setInterval(ime::seconds(10.0f));
        REQUIRE_GT(timer.getInterval(), ime::Time::Zero);
        THEN("the timer restarts") {
            CHECK_EQ(timer.getRemainingDuration(), timer.getInterval());
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Running);
        }
    }

    AND_WHEN("setInterval(float) is called with an argument of zero") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
        REQUIRE_NE(timer.getRemainingDuration(), timer.getInterval());
        timer.setInterval(ime::Time::Zero);
        THEN("the timer stops") {
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Stopped);

            SUBCASE("The remaining duration and the interval have the same value") {
                CHECK_EQ(timer.getRemainingDuration(), timer.getInterval());
            }
        }
    }

    AND_WHEN("setInterval(float) is called with a negative value") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
        REQUIRE_NE(timer.getRemainingDuration(), timer.getInterval());
        timer.setInterval(ime::seconds(-1.0f));
        THEN("the timer stops") {
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Stopped);

            SUBCASE("The remaining duration and the interval have the same value") {
                CHECK_EQ(timer.getRemainingDuration(), timer.getInterval());
            }
        }
    }
}

SCENARIO("A timer is stopped and its member functions are invoked") {
    auto timer = ime::Timer::create(ime::seconds(1.0f), []{});
    REQUIRE(timer.canStart()); //The timer has been properly initialized such that calling start will make it run

    WHEN("start() is called") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
        timer.start();
        THEN("the timer will start running") {
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Running);
        }
    }

    AND_WHEN("pause() is called") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
        timer.pause();
        THEN("there is no effect, the timer will remain stopped") {
            REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
        }
    }

    AND_WHEN("stop() is called") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
        timer.stop();
        THEN("there is no effect, the timer will remain stopped") {
            CHECK_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
        }
    }
}

SCENARIO("The time is updates under different states (running, paused and stopped") {
    auto timer = ime::Timer::create(ime::seconds(5.0f), []{});
    REQUIRE(timer.canStart());

    WHEN("the timer is running") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
        timer.start();
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
        auto remainingDurationBeforeUpdate = timer.getRemainingDuration();
        timer.update(ime::seconds(2.0f));

        THEN("the given delta time will be subtracted from the remaining duration") {
            CHECK_EQ(timer.getRemainingDuration(), remainingDurationBeforeUpdate - ime::seconds(2.0f));
        }
    }

    AND_WHEN("the timer is paused") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
        timer.start();
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Running);
        timer.pause();
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Paused);
        auto remainingDurationBeforeUpdate = timer.getRemainingDuration();
        timer.update(ime::seconds(2.0f));
        THEN("the given delta time will have no effect on the remaining duration") {
            CHECK_EQ(timer.getRemainingDuration(), remainingDurationBeforeUpdate);
        }
    }

    AND_WHEN("the timer is stopped") {
        REQUIRE_EQ(timer.getStatus(), ime::Timer::Status::Stopped);
        auto remainingDurationBeforeUpdate = timer.getRemainingDuration();
        timer.update(ime::seconds(2.0f));
        THEN("the given delta time will have no effect on the remaining duration") {
            CHECK_EQ(timer.getRemainingDuration(), remainingDurationBeforeUpdate);
        }
    }
}
