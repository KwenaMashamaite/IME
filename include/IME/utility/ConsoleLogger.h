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

#ifndef IME_CONSOLELOGGER_H
#define IME_CONSOLELOGGER_H

#include "IME/Config.h"
#include "ILogger.h"
#include <mutex>

namespace ime {
    namespace utility {
        /**
         * @brief Utility class for logging messages to the console
         */
        class IME_API ConsoleLogger : public ILogger {
        public:
            /**
             * @brief Log message to the console
             * @param logType Message type
             * @param msg Message to be logged
             *
             * This function will precede the log message with the message
             * type (in caps) and a colon. If the message type is
             * MessageType::General, then the log message will be logged
             * as it is.
             */
            void log(MessageType logType, const std::string& msg) override;

        private:
            std::mutex mutex_; //!< std::cout synchronization
        };
    }
}

#endif // IME_CONSOLELOGGER_H
