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

#ifndef IME_UTILS_H
#define IME_UTILS_H

#include "IME/Config.h"
#include "IME/graphics/Colour.h"
#include <random>
#include <ctime>
#include <chrono>
#include <thread>

namespace ime {
    namespace utility {
        /**
         * @brief Generate a random number in a range
         * @param min The start of the range
         * @param max The end of the range
         * @return A random number in the given range
         */
        IME_API extern int generateRandomNum(int min, int max);

        /**
         * @brief Create a callable that generates random numbers in a range
         * @param min The start of the range
         * @param max The end of the range
         * @return A callable object, when called returns a random number in
         *         the specified range
         */
        static auto createRandomNumGenerator(int min, int max) {
            return [distribution = std::uniform_int_distribution(min, max)]() mutable {
                static auto randomEngine = std::mt19937(std::time(nullptr));
                return distribution(randomEngine);
            };
        }

        /**
         * @brief Create a random colour
         * @return A random colour
         */
        IME_API extern Colour generateRandomColour();

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
        void setTimeoutSync(int delay, const Callable& callback, Args&&...args);

        /**
         * @brief Execute a callback function once after a delay
         * @param delay Time to wait before executing callback in milliseconds
         * @param callback Function to execute
         * @param args Arguments passed to the callback function on invocation
         *
         * The callback execution is done in a separate thread, therefore
         * this function is not blocking. It will return immediately after
         * initiating the new thread
         */
        template <typename Callable, typename...Args>
        void setTimeout(int delay, const Callable& callback, Args&&...args);

        /**
         * @brief Execute a callback function repeatedly after a delay
         * @param delay Time to wait before executing callback in milliseconds
         * @param callback Function to execute
         * @param args Arguments passed to the callback function on invocation
         *
         * This function is blocking as the current thread will wait for the
         * callback execution to finish. The callback function will execute
         * forever every delay milliseconds. The interval can be stopped
         * by setting the first argument of the callback to false. This
         * argument must be taken by reference otherwise the callback will
         * continue executing
         *
         * @note Provided arguments will be passed to the callback after
         * the first bool argument which is provided by this function,
         * therefore the callback must take at least one argument of
         * type bool&
         */
        template <typename Callable, typename...Args>
        void setIntervalSync(int delay, const Callable& callback, Args&&...args);

        /**
         * @brief Execute a callback function repeatedly after a delay
         * @param delay Time to wait before executing callback in milliseconds
         * @param callback Function to execute
         * @param args Arguments to pass to the callback on invocation
         *
         * The callback execution is done in a separate thread, therefore
         * this function is not blocking. It will return immediately after
         * initiating the new thread. The callback function will execute
         * forever every delay milliseconds. The interval can be stopped
         * by setting the first argument of the callback to false. This
         * argument must be taken by reference otherwise the callback will
         * continue executing.
         *
         * @note Provided arguments will be passed to the callback after the
         * first bool argument which is provided by this function, therefore
         * the callback must take at least one argument of type bool&
         */
        template <typename Callable, typename...Args>
        void setInterval(int delay, const Callable& callback, Args&&...args);

        #include "IME/utility/Utils.inl"
    }
}

#endif // IME_UTILS_H
