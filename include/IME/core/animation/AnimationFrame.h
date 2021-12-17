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

#ifndef IME_ANIMATIONFRAME_H
#define IME_ANIMATIONFRAME_H

#include "IME/Config.h"
#include "IME/common/Rect.h"

namespace ime {
    /**
     * @brief An animation frame
     */
    class IME_API AnimationFrame {
    public:
        /**
         * @brief Construct the frame from its coordinates
         * @param rectLeft Left coordinate of the frame
         * @param rectTop Top coordinate of the frame
         * @param rectWidth Width of the frame
         * @param rectHeight Height of the frame
         *
         * @note the last two parameters are the width and height, not the
         * right and bottom coordinates!
         */
        AnimationFrame(unsigned int rectLeft, unsigned int rectTop, unsigned int rectWidth, unsigned int rectHeight);

        /**
         * @brief Construct the frame from
         * @param rect
         */
        AnimationFrame(const UIntRect& rect);

        /**
         * @brief Copy constructor
         */
        AnimationFrame(const AnimationFrame&) = default;

        /**
         * @brief Copy assignment operator
         */
        AnimationFrame& operator=(const AnimationFrame&) = default;

        /**
         * @brief Get position information of the frame on the Spritesheet
         * @return Position information on the animations spritesheet
         */
        const UIntRect& getSpritesheetRect() const;

        /**
         * @brief Get the position of the frame in the animation sequence
         * @return The index of the frame in the animation sequence
         */
        unsigned int getIndex() const;

    private:
        UIntRect rect_;       //!< Position information of the frame
        unsigned int index_;  //!< The position of the frame in the animation sequence
        friend class Animation;
    };
}

#endif //IME_ANIMATIONFRAME_H
