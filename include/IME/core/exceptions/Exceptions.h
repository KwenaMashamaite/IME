/**
 * @brief Defines possible exceptions that may be thrown in the game
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace IME {
    /**
     * @brief Exception class for when a file cannot be found
     */
    class FileNotFound : public std::runtime_error {
    public:
        explicit FileNotFound(const std::string &message) : std::runtime_error(message) {}
    };

    /**
     * @brief Exception class for when an argument is invalid
     */
    class InvalidArgument: public std::runtime_error {
    public:
        explicit InvalidArgument(const std::string& message) : std::runtime_error(message) {}
    };
} // namespace IME

#endif
