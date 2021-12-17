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
#include <string>

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
         * @brief Set the name of the frame
         * @param name The name of the frame
         *
         * The name property allows you to retrieve or remove an animation frame
         * from an Animation by its name instead of its index. Here is an example
         * that plays an explosion effect when the animation reaches the 3rd frame:
         *
         * @code
         * ime::Animation::Ptr explosionAnim = ime::Animation::create("explosion", spritesheet, ime::seconds(5));
         * explosionAnim->addFrame(ime::Index{0, 0}, 5);
         * explosionAnim->getFrame(2).setName("audioTrigger");
         *
         * ...
         *
         * if (animator.getCurrentFrame().getName() == "audioTrigger")
         *      explosionSfx.play()
         *
         * @endcode
         *
         * By default the frame name is an empty string
         *
         * @see getName
         */
        void setName(const std::string& name);

        /**
         * @brief Get the name of the frame
         * @return The name of the frame
         *
         * @see setName
         */
        const std::string& getName() const;

        /**
         * @brief Get position information of the frame on the Spritesheet
         * @return Position information on the animations spritesheet
         */
        const UIntRect& getSpritesheetRect() const;

        /**
         * @brief Check if the frame is currently displayed by the animation
         * @return True if currently displayed, otherwise false
         */
        bool isCurrent() const;

        /**
         * @brief Get the position of the frame in the animation sequence
         * @return The index of the frame in the animation sequence
         */
        unsigned int getIndex() const;

    private:
        UIntRect rect_;       //!< Position information of the frame
        unsigned int index_;  //!< The position of the frame in the animation sequence
        bool isCurrent_;      //!< A flag indicating whether or not the frame is currently displayed by the animation
        std::string name_;    //!< The name of the frame

        friend class Animation;
    };
}

#endif //IME_ANIMATIONFRAME_H
