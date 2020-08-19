#include "IME/utility/DiskFileLogger.h"
#include "IME/utility/DiskFileReader.h"

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
        auto message = std::stringstream();
        switch (messageType) {
            case MessageType::General:
                message << "\n" << msg;
                break;
            case MessageType::Status:
                message << "\n" << "STATUS: " + msg;
                break;
            case MessageType::Warning:
                message << "\n" << "WARNING: " + msg;
                break;
            case MessageType::Error:
                message << "\n" << "ERROR: " + msg;
                break;
        }
        static auto diskFileReader = DiskFileReader();
        diskFileReader.writeToFile(message, getFullPath(), WriteMode::Append);
    }
}
