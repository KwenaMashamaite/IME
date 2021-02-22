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

#ifndef IME_NONCOPYABLE_H
#define IME_NONCOPYABLE_H

#include "IME/Config.h"

namespace ime {
    namespace utility {
        /**
         * @brief Class for making other classes non copyable
         *
         * @note Classes that inherit from this class will implicitly have their move
         * constructor deleted
         */
        class IME_API NonCopyable {
        public:
            /**
             * @brief Copy constructor
             */
            NonCopyable(const NonCopyable&) = delete;

            /**
             * @brief Assignment operator
             */
            NonCopyable& operator=(const NonCopyable&) = delete;

        protected:
            /**
             * @brief Default constructor
             */
            NonCopyable() = default;

            /**
             * @brief Move constructor
             */
            NonCopyable(NonCopyable&&) = default;

            /**
             * @brief Move assignment operator
             */
            NonCopyable& operator=(NonCopyable&&) = default;

            /**
             * @brief Destructor
             */
            ~NonCopyable() = default;
        };
    }
}

#endif // IME_NONCOPYABLE_H
