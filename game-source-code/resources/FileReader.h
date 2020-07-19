/**
 * @brief Reads/writes data to/from the disk drive
 */

#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <sstream>
#include <string>

namespace IME{
    namespace Utility {
        class FileReader {
        public:
            /**
             * @brief Read data from a file on the disk
             * @param buffer Stores the contents of the read file
             * @param filename Name of the file to read data from
             * @throws FileNotFound If the file cannot be found on the disk
             *
             * The file name must be preceded by the path to the file.
             * In addition, the file to be read must be in the same
             * folder as the generated executable file (or be in a
             * subfolder of the generated executable file's  folder),
             * otherwise a "FileNotFound" exception will be thrown
             */
            void readFileInto(std::stringstream &buffer, const std::string &filename);

            /**
             * @brief Write data to a file on the disk
             * @param buffer Contents to write to file
             * @param filename Name of the file to write data to
             * @throws FileNotFound If the file cannot be found on the disk
             *
             * The file name must be preceded by the path to the file.
             * In addition, the file to be written must be in the same
             * folder as the generated executable file (or be in a subfolder
             * of the generated executable file's folder), otherwise a
             * "FileNotFound" exception will be thrown.
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
    }
}

#endif
