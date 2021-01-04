////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_STRUCTS_H
#define IME_STRUCTS_H

namespace IME {
    /**
      * @brief Represents the whitespace around the borders
      *        of the GUI widget
      */
    struct Margin {
        float left = 0.0f;   //!< Lef margin
        float top = 0.0f;    //!< Top margin
        float right = 0.0f;  //!< Right margin
        float bottom = 0.0f; //!< Bottom margin
    };

    /**
     * @brief Represents the spacing between the
     *        text and the border of the GUI widget
     */
    struct Padding {
        float left = 0.0f;   //!< Left padding
        float top = 0.0f;    //!< Top padding
        float right = 0.0f;  //!< Right padding
        float bottom = 0.0f; //!< Bottom padding
    };

    /**
     * @brief Widget borders
     */
    struct Borders {
        float left = 0.0f;   //!< Left border
        float top = 0.0f;    //!< Top border
        float right = 0.0f;  //!< Right border
        float bottom = 0.0f; //!< Bottom border
    };
}

#endif
