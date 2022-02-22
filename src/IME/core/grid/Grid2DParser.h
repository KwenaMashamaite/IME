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

#ifndef IME_GRID2DPARSER_H
#define IME_GRID2DPARSER_H

#include <vector>
#include <string>

namespace ime {
    /**
     * @brief Reads a file containing the grid data and returns it in grid form
     */
    class Grid2DParser {
    public:
        using Map = std::vector<std::vector<char>>; //!< Alias for 2D vector of chars

        /**
         * @brief Parse a map file
         * @param filename Name of the map file
         * @param separator Character used to separate column entries
         * @return Tile map data
         * @throws InvalidParseException If the contents of @a filename cannot
         *         be successfully parsed into Grid2D map data
         *
         * This function parses a map file and returns a map object created
         * form the parsed date
         */
        static Map parse(const std::string& filename, char separator = ',');
    };
}

#endif
