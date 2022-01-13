////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
#include "IME/common/Rect.h"
#include "IME/core/time/Time.h"
#include "IME/graphics/SpriteSheet.h"
#include "IME/core/animation/AnimationFrame.h"
#include "IME/core/event/EventEmitter.h"
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
     * @brief A SpriteSheet based animation
     */
    class IME_API Animation {
    public:
        using Ptr = std::shared_ptr<Animation>; //!< Shared animation pointer

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
         * @param name The name of the animation
         * @param spriteSheet The spritesheet containing the animation frames
         * @param duration How long the animation should play for before it
         *                 stops or loops around
         *
         * If the @a duration argument is unspecified (i.e left as ime::Time::Zero)
         * the duration will be derived from the frame rate. If the duration is
         * specified then the frame rate will be overridden and derived from the
         * given duration
         *
         * @see setFrameRate
         */
        Animation(const std::string &name, const SpriteSheet& spriteSheet,
            const Time& duration = Time::Zero);

        /**
         * @brief Create a new animation object
         * @param name The name of the animation
         * @param spriteSheet The spritesheet containing the animation frames
         * @param duration How long the animation should play for before it
         *                 stops or loops around
         * @return The new animation object
         *
         * If the @a duration argument is unspecified (i.e left as ime::Time::Zero)
         * the duration will be derived from the frame rate. If the duration is
         * specified then the frame rate will be overridden and derived from the
         * given duration
         */
        static Animation::Ptr create(const std::string &name, const SpriteSheet& spriteSheet,
            const Time& duration = Time::Zero);

        /**
         * @brief Get the spritesheet used to construct the animation
         * @return The spritesheet used by the animation
         */
        const SpriteSheet& getSpriteSheet() const;

        /**
         * @brief Set the repetition count of the animation
         * @param count The number of times to repeat the animation
         *
         * Set @a count to '-1' to repeat the animation forever or set it to
         * some positive number x, where x is the number of times to repeat the
         * animation before it completes or set it to '0' to disable repetition
         * if the animation is currently repeating.
         *
         * Note that if @a count is set to a negative value that is not '-1',
         * then the repeat count will be set to '0', meaning that the animation
         * will not repeat
         *
         * By default, the animation does not repeat (repeat count is 0), it
         * plays once then completes
         *
         * @see setLoop
         */
        void setRepeatCount(int count);

        /**
         * @brief Get the number of times the animation repeats before completing
         * @return The number of times the animation is repeated
         *
         * The return value of this function imply the following:
         *
         * -1 = The animation repeats forever and never completes
         *  0 = The animation does not repeat
         *  x = The animation repeats x times, where x is some positive number
         *
         * @see setRepeatCount
         */
        int getRepeatCount() const;

        /**
         * @brief Check if the animation is repeating or not
         * @return True if the animation repeats, otherwise false
         *
         * @see setRepeatCount and getRepeatCount
         */
        bool isRepeating() const;

        /**
         * @brief Set whether or not the animation should be repeated continuously
         * @param loop True to loop animation, otherwise false
         *
         * This function is a simplification of setRepeatCount(). When the
         * @a loop argument is @a true, the repeat count will be set to -1
         * and when it is @a false, the repeat count will be set to zero
         *
         * @see setRepeatCount, isLooped
         */
        void setLoop(bool loop);

        /**
         * @brief Check if the animation is looped or not
         * @return True if the animation is looped or false if it is not looped
         *
         * @see setLoop
         */
        bool isLooped() const;

        /**
         * @brief Change the duration of the animation
         * @param duration The new duration of the animation
         *
         * By default the duration is determined by the frame rate. When
         * the duration is explicitly set, the frame rate is overridden
         * and derived from the given duration. Therefore you only need
         * to set either the frame rate or the duration
         *
         * Note that if the specified duration is less than or equal to
         * ime::Time::Zero, then the duration will be set to the default
         * one. In addition, if the specified duration results in a frame
         * @e time of more than @a 1 second, the frame @e rate will be set
         * to @a zero.
         *
         * @see setFrameRate and getFrameTime
         */
        void setDuration(const Time& duration);

        /**
         * @brief Get the duration of the animation
         * @return The duration of the animation
         */
        const Time& getDuration() const;

        /**
         * @brief Set the timescale factor of the animation
         * @param timescale The new timescale factor
         *
         * The timescale factor controls the playback speed of the animation.
         * For example, a timescale of 2.0f will make the animation play twice
         * as fast, a timescale of 0.5f will make the animation play at half
         * its normal playback speed and a timescale of 0.0f will freeze the
         * animation. Note that if @a timescale is negative then the timescale
         * will be set to 1.0f (real-time)
         *
         * By default the timescale is 1.0f (real-time)
         */
        void setTimescale(float timescale);

        /**
         * @brief Get the timescale factor
         * @return The timescale factor
         *
         * @see setTimescale
         */
        float getTimescale() const;

        /**
         * @brief Set the frame rate playback of the animation
         * @param frameRate The frame rate to be set
         *
         * When the frame rate is explicitly set, the duration of the animation
         * is overridden and derived from the given frame rate. Therefore you
         * only need to set either the duration or the frame rate. In addition.
         * you should note that if the frame rate is less than or equal to zero
         * then it will be set to the default frame rate
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
         * Note that if the animation is set to alternate but not repeat, then
         * it will play once like a normal forward or reverse animation
         * (depending on the initial direction of alternation)
         *
         * By default the direction of play is ime::Animation::Direction::Forward
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
         * @brief Set the time to wait before that animation is started
         * @param delay The time to wait before the animation is played
         * @param oneTime True to apply the start delay only when the animation
         *                is played for the first time or false (default) to
         *                apply the start delay every time the animation starts
         *                from the beginning
         *
         * Note that @a oneTime parameter only applies if the animation is
         * repeating (see setRepeat()). For non-repeating animations, the
         * start delay will always be applied
         *
         * By default, the animation plays immediately
         */
        void setStartDelay(const Time& delay, bool oneTime = false);

        /**
         * @brief Get the time waited before the animation is played
         * @return The start delay of the animation
         *
         * @see setStartDelay
         */
        const Time& getStartDelay() const;

        /**
         * @param Check if the start delay is applied when the animation restarts
         * @return True if it is applied, or false if it is applied once
         *
         * @see setStartDelay
         */
        bool isStartDelayedOnce() const;

        /**
         * @brief Check whether or not the animation is played after a delay
         * @return True if the animation is played after a delay, or false if
         *         if is played immediately
         *
         * @see setStartDelay
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
         * @see hideTargetOnCompletion
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
         * @param hide True to hide the target or false to leave the targets
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
         * @see hideTargetOnCompletion
         */
        bool isTargetHiddenOnCompletion() const;

        /**
         * @brief Set whether or not the current animation frame is reset to
         *        the first frame when the animation is stopped before completing
         * @param reset True to reset the frame or false to leave it as is
         *
         * By default, the current frame is reset to the first frame
         *
         * @see isCurrentFrameResetOnInterrupt
         */
        void setCurrentFrameResetOnInterrupt(bool reset);

        /**
         * @brief Check if the current frame is reset or not when animation is interrupted
         * @return True if the frame is reset on interrupt, otherwise false
         *
         * @see setCurrentFrameResetOnInterrupt
         */
        bool isCurrentFrameResetOnInterrupt() const;

        /**
         * @brief Add frames from the spritesheet to the animation
         * @param startPos Position of the first frame on the spritesheet
         * @param numOfFrames Number of frames to add to the animation
         * @param arrangement How the frames are arranged on the spritesheet
         *
         * Note that if left unspecified, this function assumes that the
         * animation frames are contiguously arranged horizontally on the
         * spritesheet
         *
         * @warning The position of the first and the last frame must be within
         * the bounds of the spritesheet
         */
        void addFrames(const Index& startPos, unsigned int numOfFrames,
            FrameArrangement arrangement = FrameArrangement::Horizontal);

        /**
         * @brief Add an animation frame to the end of the animation
         * @param frame Index of the frame to be added from the spritesheet
         *
         * This function allows the animation to be created from frames that
         * are not contiguously arranged on the spritesheet. If @a frame is
         * out of the spritesheet bounds, then this function has no effect
         */
        void addFrame(const Index& frame);

        /**
         * @brief Insert an animation frame within the current animation sequence
         * @param frameIndex The index of the frame to insert from the spritesheet
         * @param index The index where the frame should be inserted
         *
         * If @a index is negative or higher than the current number of frames,
         * then the frame will be added at the end of the sequence instead. In
         * addition, if @a frameIndex is out of the spritesheet bounds, then
         * this function has no effect
         */
        void insertFrameAt(unsigned int index, const Index& frameIndex);

        /**
         * @brief Get the first frame of the animation
         * @return The first frame of the animation or an empty value if
         *         the animation has no frames
         *
         * @see addFrame, addFrames and getLastFrame
         */
        AnimationFrame* getFirstFrame();
        const AnimationFrame* getFirstFrame() const;

        /**
         * @brief Get the last frame of the animation
         * @return The last frame or an empty value if the animation has
         *         no frames
         *
         * @see addFrame, addFrames and getFirstFrame
         */
        AnimationFrame* getLastFrame();
        const AnimationFrame* getLastFrame() const;

        /**
         * @brief Get the frame at an index
         * @param index The index to get the frame of
         * @return The frame at the specified index or an empty value if
         *         the index is out of bounds
         *
         * @see getFirstFrame and getLastFrame
         */
        AnimationFrame* getFrameAt(unsigned int index);
        const AnimationFrame* getFrameAt(unsigned int index) const;

        /**
         * @brief Get the frame with a given name
         * @param name The name of the frame
         * @return The frame at the specified name or nullptr if there is
         *         no such frame
         *
         * @see getFirstFrame and getLastFrame
         */
        AnimationFrame* getFrame(const std::string& name);
        const AnimationFrame* getFrame(const std::string& name) const;

        /**
         * @brief Get all the frames in the animation
         * @return All the frames in he animation
         */
        const std::vector<AnimationFrame>& getAllFrames() const;

        /**
         * @brief Get the total number of frames in the animation sequence
         * @return The total number of frames in the animation sequence
         */
        unsigned int getFrameCount() const;

        /**
         * @brief Get the time spent on the current frame before switching
         *        to the next animation frame
         * @return The time spent on the current frame before changing to the
         *         next frame
         */
        const Time& getFrameTime() const;

        /**
         * @brief Check if the animation has a frame at an index
         * @param index Index to be checked
         * @return True if the animation has a frame at the given index
         *         or false if the index is out of bounds
         */
        bool hasFrameAtIndex(unsigned int index) const;

        /**
         * @brief Remove the first frame from the animation
         *
         * The function has no effect if the animation has no frames
         */
        void removeFirstFrame();

        /**
         * @brief Remove the last frame from the animation
         *
         * The function has no effect if the animation has no frames
         */
        void removeLastFrame();

        /**
         * @brief Remove an animation frame withing the animation sequence
         * @param index The index of the animation frame to be removed
         *
         * The function has no effect if the animation has no frames
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
         * Note that @a index will be ignored if it is higher than the number
         * frames in the animation sequence and the default behavior will take
         * place when the animation finishes. When set to a negative value, the
         * animation will end on the last frame, otherwise it will end of the
         * frame specified by @ index
         *
         * By default, the animation finishes on the last frame
         *
         * @note If the current completion frame is not the last or the first
         * frame then this function must be called every time a frame is removed
         * from the sequence
         */
        void finishOnFrame(int index);

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

        /**
         * @brief Get the current frame
         * @return The current frame or nullptr if the animation does not have any frames
         */
        AnimationFrame* getCurrentFrame();
        const AnimationFrame* getCurrentFrame() const;

        /**
         * @brief Get the frame that comes after the current frame
         * @return The next frame or nullptr if there is no next frame
         */
        AnimationFrame* getNextFrame();
        const AnimationFrame* getNextFrame() const;

        /**
         * @brief Get the frame that comes before the current frame
         * @return The previous frame or nullptr if there is no previous frame
         */
        AnimationFrame* getPreviousFrame();
        const AnimationFrame* getPreviousFrame() const;

        /**
         * @brief Get the completion progress of the animation in the range [0, 1]
         * @return The completion progress
         */
        float getProgress() const;

        /**
         * @brief Prevent further executions of an event listener
         * @param id The event listeners unique identification number
         * @param suspend True to suspend or false to unsuspend
         *
         * When suspended an event listener will be ignored when the event
         * its listening to is fired. Execution will resume once it is
         * unsuspended
         *
         * @see isEventListenerSuspended
         */
        void suspendedEventListener(int id, bool suspend);

        /**
         * @brief Check if an event listener is suspended or not
         * @param id The identification number of the listener to be checked
         * @return True if suspended, otherwise false
         *
         * This function also returns false if the specified event listener
         * does not exist
         *
         * @see suspendedEventListener
         */
        bool isEventListenerSuspended(int id) const;

        /**
         * @brief Remove an event listener from an event
         * @param id The unique identification number of the event listener
         * @return True if the event listener was removed or false if no such
         *         event listener exists
         */
        bool removeEventListener(int id);

        /**
         * @brief Add a callback to a frame switch event
         * @param callback The function to be called when the animation frame changes
         *
         * The callback will be passed the new animation frame as the argument.
         * Pass nullptr to remove the callback
         *
         * By default there is no callback registered to this event
         */
        void onFrameSwitch(const Callback<const AnimationFrame&>& callback);

        /**
         * @brief Add an event listener to a start event
         * @param callback The function to be executed when the animation starts
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * This event is emitted @em before the start delay timer executes. To
         * perform an action after the start delay timer expires, use onPlay().
         *
         * The callback is passed a pointer to the animation on invocation.
         * You can add as many event listeners as you like to this event
         *
         * @see onPlay, setStartDelay
         */
        int onStart(const Callback<Animation*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a play event
         * @param callback The function to be executed when the animation
         *                 starts animating
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * This event is emitted @em after the start delay expires. At this
         * point the animation starts to animate. To perform an action before
         * the start delay executes, use onStart().
         *
         * The callback is passed a pointer to the animation on invocation.
         * You can add as many event listeners as you like to this event
         *
         * @see onStart, setStartDelay
         */
        int onPlay(const Callback<Animation*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a pause event
         * @param callback The function to be executed when the animation is
         *                 paused
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * The callback is passed a pointer to the animation on invocation.
         * You can add as many event listeners as you like to this event
         *
         * @see onResume
         */
        int onPause(const Callback<Animation*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a resume event
         * @param callback The function to be executed when the animation is
         *                 resumed from a paused state
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * The callback is passed a pointer to the animation on invocation.
         * You can add as many event listeners as you like to this event
         *
         * @see onPause
         */
        int onResume(const Callback<Animation*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a restart event
         * @param callback The function to be executed when the animation is
         *                 restarted
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * The callback is passed a pointer to the animation on invocation.
         * You can add as many event listeners as you like to this event
         *
         * @see onPlay
         */
        int onRestart(const Callback<Animation*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a stop event
         * @param callback The function to be executed when the animation is
         *                 stopped from a playing or paused state
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * The callback is passed a pointer to the animation on invocation.
         * You can add as many event listeners as you like to this event
         *
         * @see onPlay, onPause, onResume
         */
        int onStop(const Callback<Animation*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a repeat event
         * @param callback The function to be executed when the animation is
         *                 repeated
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * You can add as many event listeners as you like to this event
         */
        int onRepeat(const Callback<Animation*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a complete event
         * @param callback The function to be executed when the animation completes
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * You can add as many event listeners as you like to this event
         */
        int onComplete(const Callback<Animation*>& callback, bool oneTime = false);

        /**
         * @internal
         * @brief Emit an event
         * @param event The event to be emitted
         *
         * @warning This function is intended for internal use only and
         * must not be called outside of IME
         */
        void emit(const std::string& event);

        /**
         * @internal
         * @brief Set the index of the current frame
         * @param index The new index
         *
         * By default the index is 0
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void setCurrentFrameIndex(unsigned int index);

    private:
        /**
         * @brief Update the animation frame index
         */
        void updateIndexes();

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
        void calculateFrameRate(const Time& duration, unsigned int frameRate);

    private:
        std::vector<AnimationFrame> frames_; //!< Stores the frames of the animation sequence
        std::string name_;          //!< The name of the animation
        SpriteSheet spriteSheet_;   //!< The spritesheet used to construct the animation frames
        Time duration_;             //!< How long the animation plays before completing or repeating
        unsigned int frameRate_;    //!< The frame rate playback
        Time frameTime_;            //!< The amount of time spent on each frame before switching to the next one
        Direction direction_;       //!< The direction in which the animation is played
        Time startDelay_;           //!< Time to wait before playing animation
        int repeatCounter_;         //!< The number of times the animation is repeated before it completes
        bool isShownOnStart_;       //!< A flag indicating whether or not the sprite is shown when the animations starts
        bool isHiddenOnComplete_;   //!< A flag indicating whether or not the sprite is hidden when the animation completes
        bool isFrameResetOnStop_;   //!< A flag indicating whether or not the current frame is reset to the first frame when animation is interrupted
        bool isDurationDerived_;    //!< A flag indicating whether or not the duration was derived from the frame rate
        bool isStartDelayedOnce_;   //!< A flag indicating whether or not the animation is start delayed once or every time it starts from the beginning
        int completionFrame_;       //!< The index of the frame to be shown when the animation finishes
        unsigned int currentFrameIndex_; //!< The index of the current frame displayed by the animation
        float timescale_;           //!< Playback speed of the animation
        Callback<const AnimationFrame&> onFrameSwitch_; //!< A function called when the animation frame changes
        EventEmitter eventEmitter_; //!< Dispatches events
    };
}

/**
 * @class ime::Animation
 * @ingroup core
 *
 * An ime::Animation specifies how a ime::Sprite object is animated. In order
 * to play the animation it must be added to a ime::Animator
 */

#endif // IME_ANIMATION_H
