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

#ifndef IME_COLOUR_H
#define IME_COLOUR_H

#include "IME/Config.h"
#include <string>

namespace ime {
    /**
     * @brief RGBA colour
     */
    class IME_API Colour {
    public:
        // Predefined colours
        static const Colour Black;       //!< Black
        static const Colour White;       //!< White
        static const Colour Red;         //!< Red
        static const Colour Green;       //!< Green
        static const Colour Blue;        //!< Blue
        static const Colour Yellow;      //!< Yellow
        static const Colour Orange;      //!< Orange
        static const Colour Cyan;        //!< Cyan
        static const Colour Magenta;     //!< Magenta
        static const Colour Purple;      //!< Purple
        static const Colour Pink;        //!< Pink
        static const Colour Grey;        //!< Grey
        static const Colour Violet;      //!< Violet
        static const Colour Turquoise;   //!< Turquoise
        static const Colour Gold;        //!< Gold
        static const Colour Transparent; //!< Transparent

        /**
         * @brief Default constructor
         *
         * Constructs an opaque black color
         */
        Colour();

        /**
         * @brief Construct the color from its 4 RGBA components
         * @param r Red component
         * @param g Green component
         * @param b Blue component
         * @param alpha Alpha component
         *
         * All components must be in the range [0, 255]
         */
        Colour(unsigned int r, unsigned int g, unsigned int b, unsigned alpha = 255);

        /**
         * @brief Construct colour from hex code
         * @param colour The colour in hex code
         *
         * The format of the hex code is "#rrggbb" or "#rrggbbaa" where:
         *
         * 1. rr is the red component
         * 2. gg is the green component
         * 3. bb is the blue component
         * 4. aa is the alpha component
         *
         * For the #rrggbb format, the alpha component is implicitly set to FF.
         * Note that the hex colour code must begin with a '#' symbol
         *
         * @code
         * auto colour = Colour("#ff0000")
         * auto colour = Colour("#ff000b4")
         * @endcode
         */
        explicit Colour(const std::string& colour);

        /**
         * @brief Check if a colour is the same as this colour
         * @param rhs Right operand
         * @return True if the colours are the same, otherwise false
         */
        bool operator==(const Colour& rhs) const;

        /**
         * @brief Check if a colour is not the same as this colour
         * @param rhs Right operand
         * @return True if the colours are not the same, otherwise false
         */
        bool operator!=(const Colour& rhs) const;

        // Colour components
        unsigned int red = 0;        //!< Red component
        unsigned int green = 0;      //!< Green component
        unsigned int blue = 0;       //!< Blue component
        unsigned int opacity = 255;  //!< Opacity
    };
}

#endif // IME_COLOUR_H
