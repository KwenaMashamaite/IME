/**
 * @brief Interface for logging
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace IME {
    namespace Utility {
        enum class MessageType {
            General, // General message
            Status,  // Status reporting message
            Warning, // Warning message
            Error    // Error message
        };

        class ILogger {
        public:
            /**
             * @brief Log message
             * @param type Type of message to be logged
             * @param msg Message to log
             */
            virtual void log(MessageType type, const std::string& msg) = 0;

            /**
             * @brief Destructor
             */
            virtual ~ILogger() = default;
        };
    } // namespace Utility
} // namespace IME
#endif
