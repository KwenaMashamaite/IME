////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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
