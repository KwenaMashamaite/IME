#include "IME/utility/ConsoleLogger.h"
#include <iostream>

namespace IME::Utility {
    void ConsoleLogger::log(MessageType logType, const std::string &msg) {
        std::scoped_lock lock(mutex_);
        switch (logType) {
            case MessageType::General:
                std::cout << msg << std::endl;
                break;
            case MessageType::Status:
                std::cout << "STATUS: " << msg << std::endl;
                break;
            case MessageType::Warning:
                std::cout << "WARNING: " << msg << std::endl;
                break;
            case MessageType::Error:
                std::cout << "ERROR: " << msg << std::endl;
                break;
        }
    }
}