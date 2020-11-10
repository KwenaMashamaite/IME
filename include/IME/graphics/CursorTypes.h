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
 * @brief Mouse cursor types
*/

#ifndef CURSORTYPES_H
#define CURSORTYPES_H

namespace IME {
    enum class CursorType {
        Arrow,                  //!< Arrow cursor (default)
        Text,                   //!< I-beam, cursor when hovering over a text field
        Hand,                   //!< Pointing hand cursor
        SizeLeft,               //!< Left arrow on Linux, horizontal double arrow cursor on Windows and macOS
        SizeRight,              //!< Right arrow on Linux, horizontal double arrow cursor on Windows and macOS
        SizeTop,                //!< Up arrow on Linux, vertical double arrow cursor on Windows and macOS
        SizeBottom,             //!< Down arrow on Linux, vertical double arrow cursor on Windows and macOS
        SizeTopLeft,            //!< Top-left arrow on Linux, double arrow cursor going from top-left to bottom-right on Windows and macOS
        SizeBottomRight,        //!< Bottom-right arrow on Linux, double arrow cursor going from top-left to bottom-right on Windows and
        SizeBottomLeft,         //!< Bottom-left arrow on Linux, double arrow cursor going from bottom-left to top-right on Windows and macOS
        SizeTopRight,           //!< Top-right arrow on Linux, double arrow cursor going from bottom-left to top-right on Windows and macOS
        Crosshair,              //!< Crosshair cursor
        Help,                   //!< Help cursor
        NotAllowed              //!< Action not allowed cursor
    };
}

#endif
