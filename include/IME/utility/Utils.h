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

#ifndef IME_UTILS_H
#define IME_UTILS_H

/**
 * @brief Utility functions
 */

#include "IME/Config.h"
#include "IME/graphics/Colour.h"
#include <random>

namespace IME {
    namespace Utility {
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
         * @return A callable object, when called returns a random number in the
         *         specified range
         */
        static auto createRandomNumGenerator(int min, int max) {
            return [distribution = std::uniform_int_distribution(min, max),
                    randomEngine = std::mt19937{std::random_device{}()}]() mutable {
                return distribution(randomEngine);
            };
        }

        /**
         * @brief Create a random colour
         * @return A random colour
         */
        IME_API extern Colour generateRandomColour();
    }
}

#endif
