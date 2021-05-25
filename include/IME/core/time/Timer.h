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

#ifndef IME_TIMER_H
#define IME_TIMER_H

#include "IME/Config.h"
#include "IME/core/time/Time.h"
#include <functional>

namespace ime {
    /**
     * @brief Execute a callback after an interval/delay
     *
     * This class is not meant to be instantiated directly, use ime::Scene::timer
     * or ime::Engine::setTimeout and ime::Engine::setInterval
     */
    class IME_API Timer {
    public:
        template <typename... Args>
        using Callback = std::function<void(Args...)>; //!< Event listener

        /**
         * @brief States the timer can be in
         */
        enum class Status {
            Running, //!< Timer is running
            Paused,  //!< Timer is paused
            Stopped, //!< Timer is stopped
        };

        /**
         * @brief Constructor
         */
        Timer();

        /**
         * @brief Create a timer
         * @param interval Countdown starting point
         * @param callback Function to execute when the timer reaches zero
         * @param repeatCounter The number of timer the timer should repeat
         * @return The new timer
         *
         * The timer is not repeated be default (@a repeatCounter = 0), this
         * means that the timer will stop after invoking the callback
         *
         * @note The timer is not started after creation, start function must
         * be called on the returned timer when it is ready to be started
         *
         * @see start and setRepeat
         */
        static Timer create(Time interval, Callback<> callback, int repeatCounter = 0);

        /**
         * @brief Create a timer
         * @param interval Countdown starting point
         * @param callback Function to execute when the timer reaches zero
         * @param repeatCounter The number of timer the timer should repeat
         * @return The new timer
         *
         * The timer is not repeated be default (@a repeatCounter = 0), this
         * means that the timer will stop after invoking the callback
         *
         * @note The timer is not started after creation, start function must
         * be called on the returned timer when it is ready to be started
         *
         * @see start and setRepeat
         */
        static Timer create(Time interval, Callback<Timer&> callback, int repeatCounter = 0);

        /**
         * @brief Set the countdown starting point
         * @param interval Countdown starting point
         *
         * if the interval is set while the timer is running and the
         * interval is not zero, then the timer will restart. If the
         * interval is less than zero, it will be set to zero and the
         * timer will stop immediately without executing the callback
         * if it was running
         *
         * @see restart
         */
        void setInterval(Time interval);

        /**
         * @brief Get the countdown starting point
         * @return The countdown starting point
         */
        Time getInterval() const;

        /**
         * @brief Get time remaining before the timer reaches zero
         * @return The time remaining before the timer reaches zero
         */
        Time getRemainingDuration() const;

        /**
         * @brief Set whether or not the timer restarts after reaching zero
         * @param repeatCount The number of times the timer repeats
         *
         * Pass -1 to repeat the timer indefinitely or 0 to stop the
         * repetition if the timer is currently repeating
         *
         * By default, the repeat counter is 0, this means that the timer
         * stops after invoking the callback for the first time
         *
         * @note If the repetition is cancelled while the timer is running,
         * the timer will continue execution and stop immediately after
         * executing the callback
         *
         * @see stop and setInterval
         */
        void setRepeat(int repeatCount);

        /**
         * @brief Get the number of times the timer restarts before coming
         *        to a stop
         * @return The number of times the timer is restarts after counting
         *          down
         *
         * -1 = The timer repeats forever
         *  0 = The timer does not repeat after invoking the callback (default)
         *  x = The timer repeats x times before stopping
         */
        int getRepeatCount() const;

        /**
         * @brief Check whether or not the timer restarts after reaching zero
         * @return True if the timer restarts, otherwise false
         *
         * @see setRepeat
         */
        bool isRepeating() const;

        /**
         * @brief Set the function that is executed when the timer reaches zero
         * @param callback Function to execute
         *
         * @note The timer will not start the countdown if the start
         * function is called and there is no callback set for when
         * the timer reaches zero.
         *
         * Note that setting a new callback resets the dispatch count
         *
         * @see start
         */
        void setTimeoutCallback(Callback<> callback);

        /**
         * @brief Set the function that is executed when the timer reaches zero
         * @param callback Function to be executed
         *
         * @note The timer will not start the countdown if the start
         * function is called and there is no callback set for when
         * the timer reaches zero.
         *
         * Note that setting a new callback resets the dispatch count
         *
         * The callback is passed the Timer on invocation
         *
         * @see start
         */
        void setTimeoutCallback(Callback<Timer&> callback);

        /**
         * @brief Start the countdown/timer
         *
         * The callback function will be called when the countdown reaches
         * zero
         *
         * @note This function will start the countdown if it was not started
         * or resume it if it was paused. If called while the timer is running
         * then, the timer will restart
         *
         * @warning This function must be called only if the interval is
         * greater than zero and the timeout callback is set, otherwise
         * undefined behavior
         *
         * @see setInterval, setTimeoutCallback, restart and pause
         */
        void start();

        /**
         * @brief Stop the timer
         *
         * This function resets the remaining duration to the value of the
         * interval and stops the timer without executing the callback. This
         * behavior is similar to the restart function except the timer is
         * not immediately started after it has been stooped. The function
         * start must be called to restart the timer after it has been stopped
         *
         * @see start and getRemainingDuration
         */
        void stop();

        /**
         * @brief Stop the timer without resetting the remaining duration
         *
         * When the timer is paused it can be resumed by calling the start
         * function. The timer will begin the countdown from the remaining
         * duration instead of restarting from the interval
         *
         * @see start and setInterval
         */
        void pause();

        /**
         * @brief Restart the countdown
         *
         * Unlike stop, this function stops the timer and immediately
         * starts it. The countdown will start from the interval. The
         * remaining duration will also be reset to the value of the
         * interval
         *
         * @see setInterval
         */
        void restart();

        /**
         * @brief Get the current status of the timer (running, paused, stopped)
         * @return The current status of the timer
         *
         * By default, the timer is stopped
         */
        Status getStatus() const;

        /**
         * @brief Get the number of times the callback has been invoked
         * @return The number of times the callback has been invoked
         *
         * This function will return 0 if the callback is not yet invoked,
         * and 1 if the callback is invoked but not repeating
         */
        int getDispatchCount() const;

        /**
         * @brief Check whether or not the callback is invoked
         * @return True if the callback was called, otherwise false
         */
        bool isDispatched() const;

        /**
         * @internal
         * @brief Update the time
         * @param deltaTime Time passed since last update
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void update(Time deltaTime);

    private:
        Status status_;          //!< The current state of the timer
        bool isDispatched_;      //!< A flag indicating whether or not the callback has been invoked
        int repeatCount_;        //!< The number of times the timer repeats
        int dispatchCount_;      //!< Indicates how many times the callback has been invoked
        Time interval_;          //!< Countdown starting point
        Time remainingDuration_; //!< The time remaining before the timer reaches zero
        Callback<> callback_;    //!< Function executed when the timer reaches zero
    };
}

#endif // IME_TIMER_H
