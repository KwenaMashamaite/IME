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

#ifndef IME_CLOCK_H
#define IME_CLOCK_H

#include "IME/Config.h"

namespace IME {
    namespace Time {
        /**
         * @brief This class models a clock
         */
        class IME_API Clock {
        public:
            /**
             * @brief Constructor
             */
            Clock();

            /**
             * @brief Get the time passed since the clock was reset
             * @return Time passed since the clock was reset in seconds
             */
            double getElapsedTimeInSeconds();

            /**
             * @brief Reset the clock and get the time passed since the clock
             *        last reset
             * @return Time passed since the clock was reset in seconds
             */
            double restart();

        private:
            /**
             * @brief Get the amount of time in seconds that has passed
             *        since the process started executing
             * @return Time that has passed since the process
             *         started executing
             */
            double getProcessTimeInSeconds();

        private:
            double timeWhenClockWasLastReset_; //!< Stores the amount of time passed since last call to restart
        };
    }
}

#endif // IME_CLOCK_H
