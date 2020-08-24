#include "IME/utility/DiskFileLogger.h"
#include "IME/utility/DiskFileReader.h"
#include <chrono>
#include <ctime>
#include <algorithm>

namespace IME::Utility {
    DiskFileLogger::DiskFileLogger(const std::string &path, const std::string &filename)
        : path_(path), file_(filename)
    {}

    void DiskFileLogger::setPath(const std::string &path) {
        path_ = path;
    }

    void DiskFileLogger::setFile(const std::string &filename) {
        file_ = filename;
    }

    const std::string &DiskFileLogger::getPath() const {
        return path_;
    }

    const std::string &DiskFileLogger::getFile() const {
        return file_;
    }

    std::string DiskFileLogger::getFullPath() const {
        return path_ + file_;
    }

    void DiskFileLogger::log(MessageType messageType, const std::string &msg) {
        auto logMessageType = std::string();
        switch (messageType) {
            case MessageType::General:
                break;
            case MessageType::Status:
                logMessageType = "[STATUS]";
                break;
            case MessageType::Warning:
                logMessageType = "[WARNING]";
                break;
            case MessageType::Error:
                logMessageType =  "[ERROR]";
                break;
        }
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        auto message = std::stringstream();
        auto dateAndTime = std::string(ctime(&now));
        //ctime() function inserts a newline character at the end of the returned string but we don't want it
        dateAndTime.erase(std::remove(dateAndTime.begin(), dateAndTime.end(), '\n'), dateAndTime.end());
        message << dateAndTime << " " << logMessageType << " " << msg << "\n";
        static auto diskFileReader = DiskFileReader();
        diskFileReader.writeToFile(message, getFullPath(), WriteMode::Append);
    }
}
