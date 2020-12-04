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

#ifndef IME_ANIMATION_H
#define IME_ANIMATION_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include <string>
#include <vector>

namespace IME {
    /**
     * @brief Defines how the frames are arranged on a spritesheet
     */
    enum class Arrangement {
        Horizontal, //!< Horizontal frame alignment
        Vertical    //!< Vertical frame alignment
    };

    /**
     * @brief Class for creating animations
     */
    class IME_API Animation {
    public:
        /**
         * @brief Create a new animation
         * @param name Name of the animation
         * @param spriteSheet Filename of the texture/image file with the 
         *        animation frames
         * @param duration How long the animation plays before it stops/loops 
         *        around
         */
        Animation(const std::string &name, const std::string &spriteSheet, float duration);

        /**
         * @brief Get the filename of the spritesheet used to create animation
         * @return Filename of the spritesheet
         */
        std::string getSpriteSheet() const;

        /**
         * @brief Add animation frames
         * @param startPos Position of the first frame on the spritesheet
         * @param frameSize Size of each animation frame
         * @param numOfFrames Number of animation frames
         * @param spacing Space between frames
         * @param arrangement How the frames are arranged on the spritesheet
         *
         * This function will create contiguous frames of the same size. To
         * create an animation from frames at different position on the sprite
         * sheet or from frames of different sizes
         *
         * @see addFrame(std::initializer_list)
         */
        void addFrames(Vector2i startPos, Vector2i frameSize,
            unsigned int numOfFrames, unsigned int spacing = 1,
            Arrangement arrangement = Arrangement::Horizontal);

        /**
         * @brief Add animation frames
         * @param frames Frames to add
         *
         * This function allows creation of animation from non contiguous
         * frames of different sizes. As a result frame coordinates and
         * frame sizes must be provided for each frame that will be created
         */
        void addFrames(const std::initializer_list<IntRect>& frames);

        /**
         * @brief Set whether or not the animation should loop after reaching
         *        the end
         * @param isLooped True to play animation in loop, false to play once
         *
         * The animation is not looped by default
         */
        void setLoop(bool isLooped);

        /**
         * @brief Check if animation is looped or not
         * @return True if animation is looped, otherwise false
         */
        bool isLooped() const;

        /**
         * @brief Set the duration of the animation
         * @param duration Duration to set
         *
         * This function will overwrite the previous duration
         *
         * @note If the duration is negative, the animation will last zero
         *       seconds
         */
        void setDuration(float duration);

        /**
         * @brief Get the duration of the animation
         * @return The duration of the animation
         */
        float getDuration() const;

        /**
         * @brief Get the sub-rectangle that is displayed by s given frame
         * @param frameNumber location of the frame to retrieve
         * @throw std::out_of_range if the specified index is invalid
         * @return The frame at the specified location
         */
        IntRect getFrameAt(unsigned int frameNumber) const;

        /**
         * @brief Get the total number of frames
         * @return The total number of frames
         */
        unsigned int getNumOfFrames() const;

        /**
         * @brief Get the name of the animation
         * @return The name of the animation
         */
        const std::string &getName() const;

    private:
        std::vector<IntRect> frames_; //!< Animation frames container
        std::string name_;            //!< Name of the animation
        std::string spriteSheet_;     //!< Filename of the spritesheet
        float duration_;              //!< Duration of the animation
        bool isLooped_;               //!< Looping state of the animation
    };
}

#endif // IME_ANIMATION_H
