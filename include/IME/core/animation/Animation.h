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
 * @brief Class for creating animations
 */

#ifndef IME_ANIMATION_H
#define IME_ANIMATION_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include <string>
#include <vector>

namespace IME {
    /**
     * @brief Defines how the frames are arranged
     */
    enum class Arrangement {
        Horizontal,
        Vertical
    };

    class IME_API Animation {
    public:
        /**
         * @brief Create a new animation
         * @param name Name of the animation
         * @param spriteSheetFilename Texture file with animation frames
         * @param duration How long the animation plays before it stops/loops around
         *
         * The sprite sheet must be large enough to accommodate all the animation
         * frames.
         */
        Animation(const std::string &name, const std::string &spriteSheetFilename, float duration);

        /**
         * @brief Get the filename of the animation sprite sheet
         * @return Filename of the animation sprite sheet
         */
        std::string getSpriteSheet() const;

        /**
         * @brief Add an animation frame
         * @param startPos Position of the first frame on the sprite sheet
         * @param frameSize Size of each animation frame
         * @param numOfFrames Number of animation frames
         * @param spacing Space between frames
         * @param arrangement How the frames are arranged on the sprite sheet
         *
         * This function will create contiguous frames of the same size. To
         * create an animation from frames at different position on the sprite
         * sheet and different frame sizes @see addFrame(std::initializer_list<Frame>)
         */
        void addFrames(Vector2i startPos, Vector2i frameSize, unsigned int numOfFrames,
            unsigned int spacing = 1, Arrangement arrangement = Arrangement::Horizontal);

        /**
         * @brief Add frames to the animation
         * @param frames Frames to add
         *
         * This function allows creation of animation from non contiguous frames
         * of different sizes. As a result frame coordinates and frame sizes must
         * be provided for each frame that will be created. To create an animation
         * from contiguous frames of the same size
         * @see addFrame(Position, Dimensions, unsigned int, Arrangement)
         */
        void addFrames(const std::initializer_list<IntRect>& frames);

        /**
         * @brief Loop/unloop the animation
         * @param isLooped True to loop animation, otherwise set to false
         *
         * Animation is not looped by default
         */
        void setLoop(bool isLooped);

        /**
         * @brief Set the duration of the animation
         * @param duration Duration to set
         *
         * This function will overwrite the previous duration. To add to the
         * current duration @see adjustDuration(float)
         * If the duration is negative, the animation will last zero seconds
         */
        void setDuration(float duration);

        /**
         * @brief Offset the current duration by a value
         * @param offset Value to offset duration width
         *
         * This function does not overwrite the current duration, it  adds
         * or subtracts from it
         */
        void adjustDuration(float offset);

        /**
         * @brief Check if animation is looped or not
         * @return True if animation is looped, false if the animation
         *         is not looped
         */
        bool isLooped() const;

        /**
         * @brief Get the duration of the animation
         * @return Animation duration
         */
        float getDuration() const;

        /**
         * @brief Get the frame at a specific location
         * @param Index location of the frame to retrieve
         * @return The frame at the specified location
         * @throw std::out_of_range if the specified index is invalid
         *
         * The returned frame is not textured. It only specifies the position
         * and the size of the sprite sheet area that should be displayed. In
         * other words, the presentation sprite must be textured with the
         * appropriate sprite sheet before displaying it, otherwise a white
         * rectangle will be displayed instead.
         */
        IntRect getFrameAt(unsigned int frameNumber) const;

        /**
         * @brief Get the total number of frames
         * @return Number of animation frames
         */
        unsigned int getNumOfFrames() const;

        /**
         * @brief Get the name of the animation
         * @return Name of the animation
         */
        const std::string &getName() const;

    private:
        //Animation frames
        std::vector<IntRect> frames_;
        //Name of the animation
        std::string name_;
        //Animation sprite sheet filename
        std::string spriteSheet_;
        //Total duration of the animation
        float duration_;
        //Looping state
        bool isLooped_;
    };
}

#endif
