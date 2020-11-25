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

/**
 * @brief Represents a position of a tile in the tilemap
 */

#ifndef IME_INDEX_H
#define IME_INDEX_H

#include "IME/Config.h"
#include <unordered_map>

namespace IME {
    struct IME_API Index {
        int row;    //!< Y coordinate of the tile
        int colm;   //!< X coordinate of the tile
    };

    /**
     * @brief Overload of binary operator ==
     * @param lhs Left operand
     * @param rhs Right operand
     * @return True if @param lhs is equal to @param rhs
     */
    IME_API extern bool operator==(const Index& lhs, const Index& rhs);

    /**
     * @brief Overload of binary operator !=
     * @param lhs Left operand
     * @param rhs Right operand
     * @return True if @param lhs is not equal to @param rhs
     */
    IME_API extern bool operator!=(const Index& lhs, const Index& rhs);
}

namespace std {
    // Hash specialization for IME::Index so that it can be used as a key
    // in an std::unordered_map
    template <>
    struct hash<IME::Index> {
        size_t operator()(const IME::Index& index) const {
            return hash<int>()(index.row) + hash<int>()(index.colm);
        }
    };
}

#endif
