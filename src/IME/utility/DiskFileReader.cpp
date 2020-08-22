#include "IME/utility/DiskFileReader.h"
#include "IME/core/exceptions/Exceptions.h"

void IME::Utility::DiskFileReader::readFileInto(const std::string &filename,
    std::stringstream& buffer)
{
    inFile_.open(filename);
	if(!inFile_.good())
		throw FileNotFound(R"(Cannot find file ")" + filename + R"(")");
	buffer << inFile_.rdbuf(); //Read file content
	inFile_.close();
}

void IME::Utility::DiskFileReader::writeToFile(const std::stringstream &buffer,
    const std::string &filename, WriteMode writeMode)
{
    if (writeMode == WriteMode::Overwrite)
        outFile_.open(filename);
    else
        outFile_.open(filename, std::ios::app);

	if(!outFile_.good())
        throw FileNotFound(R"(Cannot find file ")" + filename + R"(")");
	outFile_ << buffer.str(); //Write data to file
    outFile_.close();
}
