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
        class DiskFileReader {
        public:
            /**
             * @brief Read data from a file on the disk
             * @param filename Name of the file to read data from
             * @param buffer Stores the contents of the read file
             * @throws FileNotFound If the file cannot be found on the disk
             *
             * The file name must be preceded by the path to the file
             */
            void readFileInto(const std::string &filename, std::stringstream &buffer);

            /**
             * @brief Write data to a file on the disk
             * @param buffer Contents to write to file
             * @param filename Name of the file to write data to
             * @throws FileNotFound If the file cannot be found on the disk
             *
             * The file name must be preceded by the path to the file.
             *
             * @note This function will overwrite any data that was previously
             * stored on the file
             */
            void writeToFile(const std::stringstream &buffer, const std::string &filename);

        private:
            //Reads from file
            std::ifstream inFile_;
            //Writes to file
            std::ofstream outFile_;
        };
    } // namespace Utility
} // namespace IME

#endif
