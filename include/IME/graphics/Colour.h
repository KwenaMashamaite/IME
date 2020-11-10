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

#ifndef COLOUR_H
#define COLOUR_H

namespace IME{
    namespace Graphics {
        class Colour {
        public:
            // Predefined colours
            static const Colour Black;
            static const Colour White;
            static const Colour Red;
            static const Colour Green;
            static const Colour Blue;
            static const Colour Yellow;
            static const Colour Orange;
            static const Colour Cyan;
            static const Colour Magenta;
            static const Colour Purple;
            static const Colour Pink;
            static const Colour Grey;
            static const Colour Violet;
            static const Colour Turquoise;
            static const Colour Gold;
            static const Colour Transparent;

            /**
             * @brief Default constructor
             *
             * Constructs an opaque black color
             */
            Colour();

            /**
             * @brief Construct the color from its 4 RGBA components
             * @param red Red component
             * @param green Green component
             * @param blue Blue component
             * @param opacity Alpha component
             *
             * All components must be in the range [0, 255]
             */
            Colour(unsigned int red, unsigned int green, unsigned int blue, unsigned opacity = 255);

            /**
             * @brief Check if a colour is the same as this colour
             * @param rhs Right operand
             * @return True if the colours are the same, otherwise false
             */
            bool operator==(const Colour& rhs);

            /**
             * @brief Check if a colour is not the same as this colour
             * @param rhs Right operand
             * @return True if the colours are not the same, otherwise false
             */
            bool operator!=(const Colour& rhs);

            // Colour components
            unsigned int red = 0;
            unsigned int green = 0;
            unsigned int blue = 0;
            unsigned int opacity = 255;
        };
    }
}

#endif