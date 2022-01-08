////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_DISKFILEREADER_H
#define IME_DISKFILEREADER_H

#include "IME/Config.h"
#include <fstream>
#include <sstream>
#include <string>

namespace ime {
    namespace utility {
        /**
         * @brief Modes in which a file can be written to in
         */
        enum class WriteMode {
            Overwrite, //!< Overwrites file content with new data
            Append     //!< Appends (At the end of file) new data to existing data
        };

        /**
         * @brief Reads/writes data to/from the disk
         */
        class IME_API DiskFileReader {
        public:
            /**
             * @brief Read data from a file on the disk
             * @param filename Name of the file to read data from
             * @param buffer Stores the contents of the read file
             * @throws FileNotFound If the file cannot be found on the disk
             *
             * @note The file name must be preceded by the path to the file
             */
            void readFileInto(const std::string &filename, std::stringstream &buffer);

            /**
             * @brief Write data to a file on the disk
             * @param buffer Contents to write to file
             * @param filename Name of the file to write data to
             * @param mode Mode in which file is opened in
             * @throws FileNotFound If the file cannot be found on the disk
             *
             * @note The file name must be preceded by the path to the file
             */
            void writeToFile(const std::stringstream &buffer,const std::string &filename,
                WriteMode mode = WriteMode::Overwrite);

        private:
            std::ifstream inFile_;  //!< File reader
            std::ofstream outFile_; //!< File writer
        };
    }
}

#endif // IME_DISKFILEREADER_H
