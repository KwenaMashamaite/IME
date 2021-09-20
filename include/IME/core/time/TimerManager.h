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

#ifndef IME_TIMERMANAGER_H
#define IME_TIMERMANAGER_H

#include "IME/Config.h"
#include "IME/core/time/Timer.h"
#include "IME/core/time/Time.h"
#include <functional>
#include <list>
#include <stack>

namespace ime {
    /**
     * @brief Manages multiple Timer instances
     *
     * This class is not meant to be instantiated directly, use ime::Scene::timer
     * or ime::Engine::setTimeout and ime::Engine::setInterval
     */
    class IME_API TimerManager {
    public:
        template <typename... Args>
        using Callback = std::function<void(Args...)>; //!< Event listener

        /**
         * @brief Schedule a one time callback
         * @param delay The time to wait before executing the callback
         * @param callback The function to be executed
         * @return A reference to the callback execution timer
         *
         * On invocation, the callback is passed the Timer that is responsible
         * for the callback execution, the timer can be used to extend the
         * duration, stop the schedule and so on...
         *
         * @note The returned reference will be invalidated when the timer
         * stops, either explicitly or when it expires
         *
         * @warning The callback must not be a nullptr
         */
        Timer& setTimeout(Time delay, Callback<Timer&> callback);

        /**
         * @brief Schedule a one time callback
         * @param delay The time to wait before executing the callback
         * @param callback The function to be executed
         * @return A reference to the callback execution timer
         *
         * @note The returned reference will be invalidated when the timer
         * stops, either explicitly or when it expires
         *
         * @warning The callback must not be a nullptr
         */
        Timer& setTimeout(Time delay, Callback<> callback);

        /**
         * @brief Schedule a repeated callback
         * @param delay The time to wait before executing the callback
         * @param callback The callback to be executed
         * @param repeatCount The number of times to repeat the callback
         * @return A reference to the callback execution timer
         *
         * On invocation, the callback is passed the Timer that is responsible
         * for the callback execution, the timer can be used to extend the
         * duration, stop the schedule and so on... However note that the
         * timer will be destroyed after the callback is invoked or if it is
         * stopped before the callback is invoked.
         *
         * By default, if @a repeatCounter is left unspecified then the
         * callback will be executed forever every @a delay
         *
         * @note The returned reference will be invalidated when the timer
         * stops, either explicitly or when it expires
         *
         * @warning The callback must not be a nullptr
         */
        Timer& setInterval(Time delay, Callback<Timer&> callback, int repeatCount = -1);

        /**
         * @brief Schedule a repeated callback
         * @param delay The time to wait before executing the callback
         * @param callback The callback to be executed
         * @param repeatCount The number of times to repeat the callback
         * @return A reference to the callback execution timer
         *
         * By default, if @a repeatCounter is left unspecified then the
         * callback will be executed forever every @a delay. The callback
         * must not be a nullptr
         *
         * @note The returned reference will be invalidated when the timer
         * stops, either explicitly or when it expires
         */
        Timer& setInterval(Time delay, Callback<> callback, int repeatCount = -1);

        /**
         * @brief Get the total number of timers
         * @return The total number of timers
         */
        std::size_t getTimerCount() const;

        /**
         * @brief Remove all timers
         */
        void clear();

        /**
         * @internal
         * @brief Update the active timers
         * @param time Time passed since last update
         *
         * @warning This function is called internally by IME, do not
         * call it directly
         */
        void update(Time time);

        /**
         * @internal
         * @brief Remove inactive timers
         *
         * @warning This function is called internally by IME, do not
         * call it directly
         */
        void preUpdate();

    private:
        /**
         * @brief Add a timer to active timers
         * @param timer The timer to be added
         * @return A reference to the timer after its added to the manager
         */
        Timer& addTimer(Timer::Ptr timer);

    private:
        std::list<Timer::Ptr> activeTimers_;   //!< Timers that are counting down
    };
}

#endif //IME_TIMERMANAGER_H
