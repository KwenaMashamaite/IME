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

#ifndef IME_ANIMATION_H
#define IME_ANIMATION_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include "IME/core/time/Time.h"
#include "IME/graphics/SpriteSheet.h"
#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace ime {
    /**
     * @brief Defines how the frames are arranged on a spritesheet
     */
    enum class FrameArrangement {
        Horizontal, //!< Horizontal frame alignment
        Vertical    //!< Vertical frame alignment
    };

    /**
     * @brief A frame based animation
     *
     * This class defines the properties of a an animation such
     * as playback and
     *
     * The frame data is extracted from the spritesheet
     *
     * This class is not meant to be instantiated directly, use the create
     * function of the Animator class to create an animation
     */
    class IME_API Animation {
    public:
        using Frame = UIntRect; //!< Animation Frame
        using sharedPtr = std::shared_ptr<Animation>; //!< Shared animation pointer

        /**
         * @brief The playing direction of the animation
         */
        enum class Direction {
            Forward,           //!< The animation is played forwards
            Reverse,           //!< The animation is played in reverse
            Alternate_Forward, //!< The animation alternates back and forth starting in the forward direction
            Alternate_Reverse  //!< The animation alternates back and forth starting in the reverse direction
        };

       /**
         * @brief Construct an animation
         * @param name Name of the animation
         * @param spriteSheet The spritesheet containing the animation frames
         * @param duration How long the animation should play for
         *
         * All the frame data used by the animation will be extracted from
         * the spritesheet. As a result, the spritesheet must already be
         * constructed before passed it as an argument. Passing an uncreated
         * SpriteSheet is undefined behavior
         *
         * By default the duration is derived from the frame rate. If the
         * duration is specified then the frame rate will be overridden and
         * derived from the given duration
         *
         * @see setFrameRate
         */
        Animation(const std::string &name, const SpriteSheet& spriteSheet,
            Time duration = Time::Zero);

        /**
         * @brief Create a new animation object
         * @param name Name of the animation
         * @param spriteSheet Filename of the image file with the animation frames
         * @param duration How long the animation plays before it stops or
         *        loops around
         * @return The new animation object
         *
         * All the frame data used by the animation will be extracted from
         * the spritesheet. As a result, the spritesheet must already be
         * constructed before passed it as an argument. Passing an uncreated
         * SpriteSheet is undefined behavior
         *
         * By default the duration is derived from the frame rate. If the
         * duration is specified then the frame rate will be overridden and
         * derived from the given duration
         */
        static sharedPtr create(const std::string &name, const SpriteSheet& spriteSheet,
            Time duration = Time::Zero);

        /**
         * @brief Get the spritesheet used by the animation
         * @return The spritesheet used by the animation
         */
        const SpriteSheet& getSpriteSheet() const;

        /**
         * @brief Enable or disable animation repetition
         * @param count The number of times to repeat the animation
         *
         * Set @a count to -1 to repeat forever or set it to some number x,
         * where x is the number of times to repeat the animation before it
         * completes or set it to 0 to disable repetition if the animation is
         * currently repeating. Note that if @a count is set to value that is
         * less than zero but not '-1', then the repeat count will be set to
         * zero meaning that the animation will not repeat
         *
         * By default, the animation does not repeat (repeat count is 0), it
         * plays once then completes
         */
        void setRepeatCount(int count);

        /**
         * @brief Get the number of times the animation is repeated before
         *        completing
         * @return The number of times the animation is repeated
         *
         * The return value of this function imply the following:
         *
         * -1 = The animation repeats forever
         *  0 = The animation does not repeat
         *  x = The animation repeats x times
         *
         * @see setRepeatCount
         */
        int getRepeatCount() const;

        /**
         * @brief Check if the animation is repeating or not
         * @return True if the animation repeats, otherwise false
         *
         * Note that a repeating animation and a looping animation are
         * not the same
         *
         * @see setLoop and setRepeatCount
         */
        bool isRepeating() const;

        /**
         * @brief Set the new duration of the animation
         * @param duration Duration to set
         *
         * By default the duration is determined by the frame rate. When
         * the duration is explicitly set, the frame rate is overridden
         * and derived from the given duration. Therefore you only need
         * to set either the frame rate or the duration
         *
         * If the specified duration is less than or equal to zero then
         * the duration will be set to the default one
         *
         * @see setFrameRate
         */
        void setDuration(Time duration);

        /**
         * @brief Get the duration of the animation
         * @return The duration of the animation
         */
        Time getDuration() const;

        /**
         * @brief Set the frame rate playback of the animation
         * @param frameRate The frame rate to set
         *
         * When the frame rate is explicitly set, the duration of the
         * animation is overridden and derived from the given frame rate.
         * Therefore you only need to set either the duration or the frame
         * rate. Also not that if the frame rate is less than or equal to
         * zero then it will be set to the default frame rate
         *
         * By default, the frame rate is 24 frames per second
         *
         * @see setDuration
         */
        void setFrameRate(unsigned int frameRate);

        /**
         * @brief Get the animations playback frame rate
         * @return The animations playback frame rate
         */
        unsigned int getFrameRate() const;

        /**
         * @brief Set the direction in which the animation should be played
         * @param direction The animations direction of play
         *
         * Note that if the animation is set to alternate but it is not
         * looped or it does not repeat, it will play once like a normal
         * forward or reverse animation (depending on the initial direction
         * of alternation)
         *
         * By default the animation is played forwards
         */
        void setDirection(Direction direction);

        /**
         * @brief Get the animations playing direction
         * @return The animations playing direction
         *
         * @see setDirection
         */
        Direction getDirection() const;

        /**
         * @brief Get the name of the animation
         * @return The name of the animation
         */
        const std::string &getName() const;

        /**
         * @brief Play the animation after a delay
         * @param delay The time to wait before the animation is played
         *
         * By default, the animation is not delayed
         */
        void delayStart(Time delay);

        /**
         * @brief Get the time waited before the animation is played
         * @return The start delay of the animation
         */
        Time getStartDelay() const;

        /**
         * @brief Check whether or not the animation is played after a delay
         * @return True if the animation is played after a delay, otherwise
         *         false
         */
        bool isStartDelayed() const;

        /**
         * @brief Set whether or not the target is shown when the animation
         *        starts
         * @param show True to show the target or false to leave the targets
         *             visibility state unmodified
         *
         * By default, the target is shown when the animation starts.
         * This means that if the target was hidden prior (explicitly,
         * or via an animation finish event) then its visible property
         * will be set to true when the animation starts playing
         *
         * hideTargetOnStart
         */
        void showTargetOnStart(bool show);

        /**
         * @brief Check whether or not the target is shown when the
         *        animation starts
         * @return True if the target is shown or false if the visibility
         *         state of the target is unmodified
         *
         * @see showTargetOnStart
         */
        bool isTargetShownOnStart() const;

        /**
         * @brief Set whether or not the target is hidden when the animation
         *        completes
         * @param show True to hide the target or false to leave the targets
         *             visibility state unmodified
         *
         * By default the targets visibility state is unmodified. This means
         * that if the target was shown when the animation completed, then
         * it will remain shown and if the target was hidden, it will remain
         * hidden
         *
         * @see showTargetOnStart
         */
        void hideTargetOnCompletion(bool hide);

        /**
         * @brief Check whether or not the target is hidden when the
         *        animation completes
         * @return True if the target is hidden or false if the visibility
         *         state of the target is unmodified
         *
         * @see hideTargetOnStart
         */
        bool isTargetHiddenOnCompletion() const;

        /**
         * @brief Add frames from the spritesheet to the animation
         * @param startPos Position of the first frame on the spritesheet
         * @param numOfFrames Number of animation frames
         * @param arrangement How the frames are arranged on the spritesheet
         */
        void addFrames(Index startPos, unsigned int numOfFrames,
            FrameArrangement arrangement = FrameArrangement::Horizontal);

        /**
         * @brief Add an animation frame to the end of the animation
         * @param frame Index of the frame to be added from the spritesheet
         */
        void addFrame(Index frame);

        /**
         * @brief Insert an animation frame within the current animation sequence
         * @param frameIndex The index of the frame to insert from the spritesheet
         * @param index The index where the frame should be inserted
         *
         * If @a index is negative or higher than the current number of
         * frames, the frame will be added at the end instead
         */
        void insertFrameAt(unsigned int index, Index frameIndex);

        /**
         * @brief Get the first frame of the animation
         * @return The first frame of the animation or an empty value if
         *         the animation has no frames
         *
         * @see addFrame and addFrames
         */
        std::optional<Frame> getFirstFrame() const;

        /**
         * @brief Get the last frame of the animation
         * @return The last frame or an empty value if the animation has
         *         no frames
         *
         * @see addFrame and addFrames
         */
        std::optional<Frame> getLastFrame() const;

        /**
         * @brief Get the frame at an index
         * @param index The index to get the frame of
         * @return The frame at the specified index or an empty value if
         *         the index is out of bounds
         */
        std::optional<Frame> getFrameAt(unsigned int index) const;

        /**
         * @brief Get all the frames in the animation
         * @return All the frames in he animation
         */
        const std::vector<Frame>& getAllFrames() const;

        /**
         * @brief Get the total number of frames in the animation
         * @return The total number of frames in the animation
         */
        unsigned int getFrameCount() const;

        /**
         * @brief Get the time spent on the current frame before switching
         *        to the next animation frame
         * @return The time spent on the current frame before changing to the
         *         next frame
         */
        Time getFrameTime() const;

        /**
         * @brief Check if the animation has a frame at an index
         * @param index Index to be checked
         * @return True if the animation has a frame at the given index
         *         or false if the index is out of bounds
         */
        bool hasFrameAtIndex(unsigned int index) const;

        /**
         * @brief Remove the first frame from the animation
         */
        void removeFirstFrame();

        /**
         * @brief Remove the last frame from the animation
         */
        void removeLastFrame();

        /**
         * @brief Remove an animation frame withing the animation sequence
         * @param index The index of the animation frame to be removed
         */
        void removeFrameAt(unsigned int index);

        /**
         * @brief Remove all of the animation frames
         */
        void removeAll();

        /**
         * @brief Set the frame the animation should finish on
         * @param index The index of the frame the animation should finish on
         *
         * Note that @a index will be ignored if it is out of bounds
         *
         * By default, the animation finishes on the last frame
         *
         * @warning If the completion frame is not the last or the first frame
         * then this function must be called every time a frame is removed
         * from the sequence
         */
        void finishOnFrame(unsigned int index);

        /**
         * @brief Set the animation to finish on the first frame
         *
         * By default, the animation finishes on the last frame
         *
         * @see finishOnFrame
         */
        void finishOnFirstFrame();

        /**
         * @brief Set the animation to finish on the last frame
         *
         * By default, the animation finishes on the last frame
         *
         * @see finishOnFrame
         */
        void finishOnLastFrame();

        /**
         * @brief Get the index of the completion frame
         * @return The index of the completion frame
         *
         * @see finishOnFrame
         */
        unsigned int getCompletionFrameIndex() const;

    private:
        /**
         * @brief Calculate the duration and frame rate of the animation
         *
         * This function will derive the duration from the frame rate
         * if the duration is Time::Zero (or less than) or it will
         * derive the frame rate from the duration if the frame rate
         * is 0. The function will set the frame rate to the default
         * one and use it to derive the duration if both the specified
         * duration and frame rate are Time::Zero and 0 respectively
         */
        void calculateFrameRate(Time duration, unsigned int frameRate);

    private:
        std::vector<Frame> frames_; //!< Animation frames container
        std::string name_;          //!< Name of the animation
        SpriteSheet spriteSheet_;   //!< The spritesheet used by the animation
        Time duration_;             //!< How long the animation plays before completing, repeating or looping
        unsigned int frameRate_;    //!< The frame rate playback
        Time frameTime_;            //!< The amount of time spent on each frame before switching to the next one
        Direction direction_;       //!< The direction in which the animation is played
        Time startDelay_;           //!< Time to wait before playing animation
        int repeatCounter_;         //!< The number of times the animation is repeated before it completes
        bool isShownOnStart_;       //!< Flags whether or not the sprite is shown when the animations starts
        bool isHiddenOnComplete_;   //!< Flags whether or not the sprite is hidden when the animation completes
        int completionFrame_;       //!< The index of the frame to be shown when the animation finishes
    };
}

#endif // IME_ANIMATION_H
