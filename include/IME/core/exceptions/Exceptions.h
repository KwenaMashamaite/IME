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

#ifndef IME_EXCEPTIONS_H
#define IME_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace ime {
    /**
     * @brief Exception thrown when a file cannot be found
     */
    class FileNotFoundException : public std::runtime_error {
    public:
        /**
         * @brief Constructor
         * @param message Exception message
         */
        explicit FileNotFoundException(const std::string &message) : std::runtime_error(message) {}
    };

    /**
     * @brief Exception thrown when an argument is invalid
     */
    class InvalidArgumentException : public std::runtime_error {
    public:
        /**
         * @brief Constructor
         * @param message Exception message
         */
        explicit InvalidArgumentException(const std::string& message) : std::runtime_error(message) {}
    };

    /**
     * @brief Exception thrown when a data access condition is not satisfied
     */
    class AccessViolationException : public std::runtime_error {
    public:
        /**
         * @brief Constructor
         * @param message Exception message
         */
        explicit AccessViolationException(const std::string& message) : std::runtime_error(message) {}
    };

    /**
     * @brief Exception thrown when parsed data read from the disk is invalid
     */
    class InvalidParseException : public std::runtime_error {
    public:
        /**
         * @brief Constructor
         * @param message Exception message
         */
        explicit InvalidParseException(const std::string& message) : std::runtime_error(message) {}
    };
}

#endif // IME_EXCEPTIONS_H
