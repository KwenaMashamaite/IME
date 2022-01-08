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

#ifndef IME_CLOCK_H
#define IME_CLOCK_H

#include "IME/Config.h"
#include "IME/core/time/Time.h"

namespace ime {
    /**
     * @brief Class that measures time
     */
    class IME_API Clock {
    public:
        /**
         * @brief Default constructor
         *
         * The clock is started immediately after construction
         */
        Clock();

        /**
         * @brief Get the elapsed time
         * @return The elapsed time
         *
         * This function returns the time passed since the clock was
         * created or the time passed since the last call to restart
         *
         * @see restart
         */
        Time getElapsedTime() const;

        /**
         * @brief Restart the clock
         * @return The elapsed time
         *
         * This function resets the counter to zero and returns the
         * time passed since the clock was started
         */
        Time restart();

    private:
        Time startTime_; //!< The time when the clock was last reset
    };
}

#endif // IME_CLOCK_H
