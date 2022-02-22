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

#include "IME/core/grid/Grid2DParser.h"
#include "IME/utility/DiskFileReader.h"
#include "IME/core/exceptions/Exceptions.h"
#include <sstream>

namespace ime {
    Grid2DParser::Map Grid2DParser::parse(const std::string &filename, char separator) {
        Map map;
        std::stringstream mapData;
        utility::DiskFileReader().readFileInto(filename, mapData);
        std::string line;

        while (std::getline(mapData, line)) {
            ////Skip lines that are empty or begin with a comment
            if (line.empty() || line[0] == '#')
                continue;

            std::vector<char> row;
            for (const auto& character : line) {
                if (character != separator)
                    row.push_back(character);
            }
            map.push_back(row);
        }

        if (map.empty())
            throw InvalidParseException("Failed to parse \'" + filename + "\', 'ime::Grid2D' map data not found. Recall empty lines and comments (lines that start with a '#') are ignored.");

        return map;
    }
}