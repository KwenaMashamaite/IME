////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Class for timing purposes
 */

#ifndef TIMER_H
#define TIMER_H

#include "IME/core/event/EventEmitter.h"
#include <chrono>
#include <thread>

namespace IME {
    namespace Time {
        class Timer {
        public:
            /**
             * @brief Execute a one time callback function after a delay
             * @param delay Time to wait before executing callback in milliseconds
             * @param callback Callback function to execute
             * @param args Arguments passed to the callback function on invocation
             *
             * This function is blocking as the current thread will wait for the
             * callback execution to finish. The countdown is initiated right
             * away
             */
            template <typename Callable, typename...Args>
            void setTimeoutSync(int delay, Callable callback, Args&&...args);

            /**
             * @brief Execute a callback function once after a delay
             * @param callback Function to execute
             * @param delay Time to wait before executing callback in milliseconds
             *
             * The callback execution is done in a separate thread, therefore
             * this function is not blocking. It will return immediately after
             * initiating the new thread
             */
            template <typename Callable, typename...Args>
            void setTimeout(int delay, Callable callback, Args...args);

            /**
             * @brief Execute a callback function repeatedly after a delay
             * @param callback Function to execute
             * @param delay Time to wait before executing callback in milliseconds
             *
             * This function is blocking as the current thread will wait for the
             * callback execution to finish. The callback function will execute
             * forever every delay milliseconds. The interval can be stopped
             * by setting the first argument of the callback to false. This
             * argument must be taken by reference otherwise the callback will
             * continue executing. @note Provided arguments will be passed to
             * the callback after the first bool& argument which is provided by
             * this function
             */
            template <typename Callable, typename...Args>
            void setIntervalSync(int delay, Callable callback, Args...args);

            /**
             * @brief Execute a callback function repeatedly after a delay
             * @param callback Function to execute
             * @param delay Time to wait before executing callback in milliseconds
             *
             * The callback execution is done in a separate thread, therefore
             * this function is not blocking. It will return immediately after
             * initiating the new thread. The callback function will execute
             * forever every delay milliseconds. The interval can be stopped
             * by setting the first argument of the callback to false. This
             * argument must be taken by reference otherwise the callback will
             * continue executing. @note Provided arguments will be passed to
             * the callback after the first bool& argument which is provided by
             * this function
             */
            template <typename Callable, typename...Args>
            void setInterval(int delay, Callable callback, Args...args);
        };

        #include "IME/core/time/Timer.inl"
    }
}

#endif
