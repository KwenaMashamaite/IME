/**
 * @brief Utility class for logging messages to the console
 */

#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "ILogger.h"

namespace IME {
    namespace Utility {
        class ConsoleLogger : public ILogger {
        public:
            /**
             * @brief Log message to the console
             * @param logType Log message type
             * @param msg Message to be logged
             *
             * This function will precede the log message with the message type
             * (in caps) and a colon. If the message type is MessageType::General,
             * then the log message will be logged as it is.
             *
             * @example:
             *  log message "Assets loaded successfully"
             *  log message type = MessageType::Status
             *
             *  console output- STATUS: Assets loaded successfully
             */
            void log(MessageType logType, const std::string& msg) override;
        };
    } // namespace Utility
} // namespace IME

#endif
