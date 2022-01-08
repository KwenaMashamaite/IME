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

#ifndef IME_INDEX_H
#define IME_INDEX_H

#include "IME/Config.h"
#include <functional>

namespace ime {
    /**
     * @brief Represents a position TileMap Tile
     */
    struct IME_API Index {
        /**
         * @brief Default constructor
         *
         * Constructs Index with row = 0, and colm = 0
         */
        Index();

        /**
         * @brief Constructor
         * @param row Y coordinate of the tile
         * @param colm X coordinate of the tile
         */
        Index(int row, int colm);

        int row;    //!< Y coordinate of the tile
        int colm;   //!< X coordinate of the tile
    };

    /**
     * @brief Overload of binary operator ==
     * @param lhs Left operand
     * @param rhs Right operand
     * @return True if @a lhs is equal to @a rhs
     */
    IME_API extern bool operator==(const Index& lhs, const Index& rhs);

    /**
     * @brief Overload of binary operator !=
     * @param lhs Left operand
     * @param rhs Right operand
     * @return True if @a lhs is not equal to @a rhs
     */
    IME_API extern bool operator!=(const Index& lhs, const Index& rhs);
}

namespace std {
    /**
     * @brief Hash specialization for ime::Index so that it can be used
     *        as a key in an std::unordered_map
     */
    template <>
    struct hash<ime::Index> {
        size_t operator()(const ime::Index& index) const {
            return hash<int>()(index.row) + hash<int>()(index.colm);
        }
    };
}

#endif
