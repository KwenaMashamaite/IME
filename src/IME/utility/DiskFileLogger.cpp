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

#include "IME/utility/DiskFileLogger.h"
#include "IME/utility/DiskFileReader.h"
#include <chrono>
#include <ctime>
#include <algorithm>

namespace ime::utility {
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

#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4996 )
#endif
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
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
}
