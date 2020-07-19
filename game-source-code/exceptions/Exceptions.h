/**
 * @brief Defines possible exceptions that may be thrown in the game
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

namespace IME {
/**
 * @brief Exception class for when a disk file cannot be found (e.g disk file containing high scores)
 */
    class FileNotFound : public std::runtime_error {
    public:
        explicit FileNotFound(const std::string &message) : std::runtime_error(message) {}
    };
}

#endif
