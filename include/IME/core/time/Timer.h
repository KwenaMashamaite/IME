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

#ifndef IME_TIMER_H
#define IME_TIMER_H

#include "IME/Config.h"
#include "IME/core/time/Time.h"
#include <functional>
#include <memory>

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

#if defined(__GNUC__)
        using Ptr = std::unique_ptr<Timer>; //!< Timer ptr
#else
        using Ptr = std::shared_ptr<Timer>;
#endif

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
        static Timer::Ptr create(Time interval, const Callback<>& callback,
            int repeatCounter = 0);

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
        static Timer::Ptr create(Time interval, const Callback<Timer&>& callback,
            int repeatCounter = 0);

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
         *
         * @see setInterval, getElapsedTime
         */
        Time getInterval() const;

        /**
         * @brief Get the time elapsed since the timer was started
         * @return The time elapsed since the timer was started
         *
         * Note that the elapsed time is reset to ime::Time::Zero after each
         * invocation of the callback or when the timer is stopped before its
         * expiry time
         *
         * @see start, getInterval and getRemainingDuration
         */
        Time getElapsedTime() const;

        /**
         * @brief Get time remaining before the timer reaches zero
         * @return The time remaining before the timer reaches zero
         *
         * @see getElapsedTime and getInterval
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
         * @deprecated Since v2.6.0 and will be removed in v2.7.0. Use
         *             ime::Timer::onTimeout instead.
         *
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
        [[deprecated("Use 'onTimeout' instead.")]]
        void setTimeoutCallback(const Callback<>& callback);

        /**
         * @deprecated Since v2.6.0 and will be removed in v2.7.0. Use
         *             ime::Timer::onTimeout instead.
         *
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
         [[deprecated("Use 'onTimeout' instead.")]]
        void setTimeoutCallback(const Callback<Timer&>& callback);

        /**
         * @brief Start the timer
         *
         * This function will start the timer if it was not started
         * or resume it if it was paused. If start() is called while
         * the timer is running then, the timer will restart
         *
         * @note Calling this function without a registered timeout callback
         * is undefined behaviour (see onTimeout())
         *
         * @see onStart, setInterval, onTimeout, restart and pause
         */
        void start();

        /**
         * @brief Stop the timer
         *
         * This function resets the remaining duration to the value of the
         * interval and stops the timer @em without executing the callback. This
         * behavior is similar to the restart function except the timer is
         * not immediately started after it has been stooped. The function
         * start must be called to restart the timer after it has been stopped
         *
         * @see onStop, forceTimeout, start and getRemainingDuration
         */
        void stop();

        /**
         * @brief Stop the timer
         *
         * This function resets the remaining duration to the value of the
         * interval and stops the timer. However unlike stop(), the timeout
         * callback @em is executed
         *
         * @see stop
         */
        void forceTimeout();

        /**
         * @brief Stop the timer without resetting the remaining duration
         *
         * When the timer is paused it can be resumed by calling the start()
         * or resume() functions. The timer will begin the countdown from the
         * remaining duration instead of restarting from the interval
         *
         * @see onPause, start and setInterval
         */
        void pause();

        /**
         * @brief Resume a paused timer
         *
         * @see onResume, pause and start
         */
        void resume();

        /**
         * @brief Restart the countdown
         *
         * Unlike stop, this function stops the timer and immediately
         * starts it. However, the start and stop events will not be
         * triggered, only the restart event. The countdown will start
         * from the interval and the remaining duration will be reset to
         * the value of the interval
         *
         * @see onRestart, setInterval
         */
        void restart();

        /**
         * @brief Get the current status of the timer (running, paused, stopped)
         * @return The current status of the timer
         *
         * By default, the timer is stopped
         *
         * @see isRunning, isPaused, isStopped
         */
        Status getStatus() const;

        /**
         * @brief Check if the timer is running or not
         * @return True if the timer is running, otherwise false
         *
         * @see isPaused, isStopped, getStatus
         */
        bool isRunning() const;

        /**
         * @brief Check if the timer is paused or not
         * @return True if the timer is paused, otherwise false
         *
         * @see isRunning, isStopped, getStatus
         */
        bool isPaused() const;

        /**
         * @brief Check if the timer is stopped or not
         * @return True if the timer is stopped, otherwise false
         *
         * @see isRunning, isPaused, getStatus
         */
        bool isStopped() const;

        /**
         * @brief Get the number of times the callback has been invoked
         * @return The number of times the callback has been invoked
         */
        int getDispatchCount() const;

        /**
         * @brief Check whether or not the callback is invoked
         * @return True if the callback was called, otherwise false
         */
        bool isDispatched() const;

        /**
         * @brief Set the timescale factor
         * @param timescale The new timescale factor
         *
         * A timescale controls the countdown speed of the timer and can
         * be set to the following values:
         *
         * @li 1 = Normal/Real-time countdown
         * @li < 1 = Slower countdown
         * @li > 1 = Faster countdown
         *
         * For example, a timescale of 2.0f will make the timer countdown
         * twice as fast whilst a timescale of 0.5f will make the timer
         * countdown at half its normal countdown speed.
         *
         * Note that zero or negative timescale values will be ignored
         *
         * By default the timescale is 1.0f (real-time)
         *
         * @see getTimescale
         */
        void setTimescale(float timescale);

        /**
         * @brief Get the timescale factor
         * @return The timescale factor
         *
         * @see setTimescale
         */
        float getTimescale() const;

        /**
         * @brief Add the function that is executed when countdown completes
         * @param callback Function to be executed when the countdown terminates
         *
         * @see start
         */
        void onTimeout(const Callback<>& callback);

        /**
         * @brief Add the function that is executed when countdown completes
         * @param callback Function to be executed when the countdown terminates
         *
         * The callback is passed the execution timer as an argument on invocation
         *
         * @see start
         */
        void onTimeout(const Callback<Timer&>& callback);

        /**
         * @brief Add an event listener to a start event
         * @param callback The function to be executed when the timer is started
         *
         * This event is triggered when the timer is started from a stopped
         * state
         *
         * By default, there is no callback registered to this event. Pass
         * @a nullptr to remove any registered event listener. In addition,
         * note that adding a new event listener removes the previous event
         * listener
         *
         * @see start, onStop, onPause and onRestart
         */
        void onStart(const Callback<Timer&>& callback);

        /**
         * @brief Add an event listener to a pause event
         * @param callback Function to be executed when the timer is paused
         *
         * By default, there is no callback registered to this event. Pass
         * @a nullptr to remove any registered event listener. In addition,
         * note that adding a new event listener removes the previous event
         * listener
         *
         * @see pause, onStart, onStop and onRestart
         */
        void onPause(const Callback<Timer&>& callback);

        /**
         * @brief Add an event listener to a resume event
         * @param callback Function to be executed when the timer is resumed
         *
         * By default, there is no callback registered to this event. Pass
         * @a nullptr to remove any registered event listener. In addition,
         * note that adding a new event listener removes the previous event
         * listener
         *
         * @see pause, onStart, onStop and onRestart
         */
        void onResume(const Callback<Timer&>& callback);

        /**
         * @brief Add an event listener to a stop event
         * @param callback Function to b execute when the timer is stopped
         *
         * By default, there is no callback registered to this event. Pass
         * @a nullptr to remove any registered event listener. In addition,
         * note that adding a new event listener removes the previous event
         * listener
         *
         * @see stop, onStart, onPause and onRestart
         */
        void onStop(const Callback<Timer&>& callback);

        /**
         * @brief Add an event listener to a restart event
         * @param callback Function to be executed when the timer is restarted
         *
         * By default, there is no callback registered to this event. Pass
         * @a nullptr to remove any registered event listener. In addition,
         * note that adding a new event listener removes the previous event
         * listener
         *
         * @see restart, onStart, onPause and onStop
         */
        void onRestart(const Callback<Timer&>& callback);

        /**
         * @brief Add an event listener to an update event
         * @param callback Function to be executed when the timer ticks
         *
         * This event is triggered every time the timer advances/updates.
         * Only one event listener may be registered at a time. Pass nullptr
         * to remove the current event listener
         *
         * @see onStart, onPause and onStop, onRestart
         */
        void onUpdate(const Callback<Timer&>& callback);

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
        Status status_;              //!< The current state of the timer
        float timescale_;            //!< The timescale factor
        bool isExecutionComplete_;   //!< A flag indicating whether or not the timer has completed the callback execution
        bool isRestarting_;          //!< A flag indicating whether or not the timer is in the middle of a restart
        bool isDispatched_;          //!< A flag indicating whether or not the callback has been invoked
        int repeatCount_;            //!< The number of times the timer repeats
        int dispatchCount_;          //!< Indicates how many times the callback has been invoked
        Time interval_;              //!< Countdown starting point
        Time remainingDuration_;     //!< The time remaining before the timer reaches zero
        Callback<> onTimeout_;       //!< A function executed when the countdown reaches zero
        Callback<Timer&> onStart_;   //!< A function executed when the timer is started
        Callback<Timer&> onPause_;   //!< A function executed when the timer is paused
        Callback<Timer&> onResume_;  //!< A function executed when the timer is resumed
        Callback<Timer&> onStop_;    //!< A function executed when the timer is stopped
        Callback<Timer&> onRestart_; //!< A Function executed when the timer is restarted
        Callback<Timer&> onUpdate_;  //!< A function executed when the timer ticks
    };
}

#endif // IME_TIMER_H
