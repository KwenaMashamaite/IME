/**
 * @brief Utility class for logging messages to a file on the disk
 */

#ifndef DISKFILELOGGER_H
#define DISKFILELOGGER_H

#include "ILogger.h"

namespace IME {
    namespace Utility {
        class DiskFileLogger : public ILogger {
        public:
            /**
             * @brief Constructor
             * @param path path to the file where messages are logged
             * @param filename Name of the file where log messages are written
             */
            DiskFileLogger(const std::string& path, const std::string& filename);

            /**
             * @brief Set the path to the file where messages are logged
             * @param path Path to the file where messages are logged
             */
            void setPath(const std::string& path);

            /**
             * @brief Set the file where messages are logged
             * @param filename Name of the file where log messages are written
             */
            void setFile(const std::string& filename);

            /**
             * @brief Get the path to the file used for writing log messages
             * @return The path t the file used for writing log messages
             */
            const std::string& getPath() const;

            /**
             * @brief Get the name of the file used for writing log messages
             * @return The name of the file used for writing log messages
             */
            const std::string& getFile() const;

            /**
             * @brief Get the full path to the file used for writing log messages
             * @return The full path to the file used for writing log messages
             *
             * The full path includes the path and the name in the form : path/filename
             */
            std::string getFullPath() const;

            /**
             * @brief Log message to a file on the disk
             * @param messageType Log message type
             * @param msg Message to be logged
             *
             * This function will precede the log message with the date and time
             * when the message was logged and message type.
             */
            void log(MessageType messageType, const std::string& msg) override;

        private:
            //Path to the log file
            std::string path_;
            //Log file
            std::string file_;
        };
    } // namespace Utility
} // namespace IME

#endif
