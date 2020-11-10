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
