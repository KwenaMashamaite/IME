/**
 * @brief Reads/writes data to/from the disk drive
 */

#ifndef DISKFILEREADER_H
#define DISKFILEREADER_H

#include <fstream>
#include <sstream>
#include <string>

namespace IME {
    namespace Utility {
        /**
         * @brief Modes in which a file can be written to in
         */
        enum class WriteMode {
            Overwrite, // Overwrites file content with new data
            Append     // Appends (At the end of file) new data to existing data
        };

        class DiskFileReader {
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
             * @note The file name must be preceded by the path to the file.
             */
            void writeToFile(const std::stringstream &buffer,const std::string &filename,
                WriteMode mode = WriteMode::Overwrite);

        private:
            //Reads from file
            std::ifstream inFile_;
            //Writes to file
            std::ofstream outFile_;
        };
    } // namespace Utility
} // namespace IME

#endif
