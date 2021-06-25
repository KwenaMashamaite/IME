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
#include "IME/core/time/Time.h"
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include <functional>

namespace ime {
    namespace utility {
        /**
         * @brief Get a value between two other values on a linear scale
         * @param min The value to interpolate from
         * @param max The value to interpolate to
         * @param ratio The interpolation point between 0 and 1 (inclusive)
         * @return The lerp value
         *
         * This function is usually used to smoothen a value over time.
         * For example it can be used to change the colour of something
         * gradually over time or smoothly move an object to a new
         * position (look up "linear interpolation" for more info).
         *
         * The interpolation ratio is used to determine the point to be
         * returned on the scale. It acts like a percentage between
         * @a min and @a max:
         *
         * @code
         * auto value = lerp(0, 100.0f, 0.0f); Returns the minimum value
         * auto value = lerp(0, 100.0f, 1.0f); Returns the maximum value
         * auto value = lerp(0, 100.0f, 0.5f); Returns the 50.0f
         * auto value = lerp(0, 100.0f, 0.85f); Returns the 85.0f
         * // and so on ...
         * @endcode
         *
         * To make the interpolation frame rate independent, multiply
         * the lerp ration by the frame time
         *
         * @note This function does not account for situations where the
         * interpolation point is less than 0 or greater than 1 or when
         * the minimum value is greater than the maximum value. This means
         * that the program will continue as normal, you may experience an
         * unexpected behavior
         *
         * @code
         * void update(Time deltaTime) {
         *     // Move the sprite from its current x position to 50.0f by a ratio
         *     // of 0.3f per update
         *     sprite.setPosition(lerp(sprite.getX(), 50.0f, 0.3f), sprite.getY());
         *
         *     // Move the sprite from its current x position to 50.0f by a ratio
         *     // of 0.3f per frame
         *     sprite.setPosition(lerp(sprite.getX(), 50.0f, 0.3f * deltaTime.asMilliseconds()),
         *          sprite.getY());
         * }
         * @endcode
         */
        IME_API extern float lerp(float min, float max, float ratio);

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
         [[maybe_unused]]
        static auto createRandomNumGenerator(int min, int max) {
            return [distribution = std::uniform_int_distribution(min, max)]() mutable {
#if defined(__GNUC__)
                // MinGW compiler on windows does not provide non-deterministic
                // values from its std::random_device, so the random numbers
                // are the same on every run
                static auto randomEngine = std::mt19937(std::time(nullptr));
                return distribution(randomEngine);
#else
                static auto randomEngine = std::mt19937(std::random_device{}());
                return distribution(randomEngine);
#endif
            };
        }

        /**
         * @brief Create a random colour
         * @return A random colour
         */
        IME_API extern Colour generateRandomColour();

        /**
         * @brief Execute a one time callback function after a delay
         * @param delay Time to wait before executing callback
         * @param callback Callback function to execute
         * @param args Arguments passed to the callback function on invocation
         *
         * This function is blocking as the current thread will wait for the
         * callback execution to finish. The countdown is initiated right
         * away
         */
        template <typename Callable, typename...Args>
        void setTimeoutSync(Time delay, const Callable& callback, Args&&...args);

        /**
         * @brief Execute a callback function once after a delay
         * @param delay Time to wait before executing callback
         * @param callback Function to execute
         * @param args Arguments passed to the callback function on invocation
         *
         * The callback execution is done in a separate thread, therefore
         * this function is not blocking. It will return immediately after
         * initiating the new thread
         */
        template <typename Callable, typename...Args>
        void setTimeout(Time delay, const Callable& callback, Args&&...args);

        /**
         * @brief Execute a callback function repeatedly after a delay
         * @param delay Time to wait before executing callback
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
        void setIntervalSync(Time delay, const Callable& callback, Args&&...args);

        /**
         * @brief Execute a callback function repeatedly after a delay
         * @param delay Time to wait before executing callback
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
        void setInterval(Time delay, const Callable& callback, Args&&...args);

        #include "IME/utility/Utils.inl"
    }
}

#endif // IME_UTILS_H
