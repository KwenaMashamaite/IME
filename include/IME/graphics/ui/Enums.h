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
 * @brief
 */

#ifndef ENUMS_H
#define ENUMS_H

namespace IME {
    enum class Orientation {
        Horizontal,
        Vertical
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief The horizontal text alignment
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class HorizontalAlignment
    {
        Left,   //!< Put the text on the left side (default)
        Center, //!< Center the text horizontally
        Right   //!< Put the text on the right side (e.g. for numbers)
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief The vertical text alignment
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    enum class VerticalAlignment
    {
        Top ,   //!< Put the text at the top (default)
        Center, //!< Center the text vertically
        Bottom  //!< Put the text at the bottom
    };

    /**
     * @brief Position of the text within the widgets border
     */
    enum class TextAlignment {
        Center,      //!< Center the widget in the cell
        UpperLeft,   //!< Draw the widget in the upper left corner of the cell
        Up,          //!< Draw the widget at the upper side of the cell (horizontally centered)
        UpperRight,  //!< Draw the widget in the upper right corner of the cell
        Right,       //!< Draw the widget at the right side of the cell (vertically centered)
        BottomRight, //!< Draw the widget in the bottom right corner of the cell
        Bottom,      //!< Draw the widget at the bottom of the cell (horizontally centered)
        BottomLeft,  //!< Draw the widget in the bottom left corner of the cell
        Left         //!< Draw the widget at the left side of the cell (vertically centered)
    };

    enum class TextStyle {
        Regular       = 0,      //!< Regular characters, no style
        Bold          = 1 << 0, //!< Bold characters
        Italic        = 1 << 1, //!< Italic characters
        Underlined    = 1 << 2, //!< Underlined characters
        StrikeThrough = 1 << 3  //!< Strike through characters
    };
}

#endif
