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

#ifndef IME_ANIMATOR_H
#define IME_ANIMATOR_H

#include "IME/Config.h"
#include "IME/core/animation/Animation.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/core/time/Time.h"
#include <optional>
#include <string>
#include <memory>
#include <unordered_map>
#include <initializer_list>
#include <utility>
#include <queue>

namespace ime {
    class Sprite;

    /**
     * @brief An animator for ime::Sprite
     */
    class IME_API Animator {
    public:
        /**
         * @brief Animation events
         *
         * These events are triggered by the current active animation
         */
        enum class Event {
            AnimationPlay,     //!< Emitted when an animation is played
            AnimationStart,    //!< Emitted when an animation starts to play (Animation may be start delayed)
            AnimationPause,    //!< Emitted when the animation is paused
            AnimationResume,   //!< Emitted when the animation is resumed
            AnimationStop,     //!< Emitted when the animation is stopped
            AnimationComplete, //!< Emitted when the animation completes playing
            AnimationRepeat,   //!< Emitted when an animation is repeated
            AnimationRestart,  //!< Emitted when the animation is restarted from the beginning
            AnimationSwitch    //!< Emitted when the animation is changed to a different animation
        };

        /**
         * @brief Default constructor
         *
         * @warning When this constructor is used, you must call setTarget()
         * before using the animator, otherwise undefined behavior
         *
         * @see setTarget
         */
        Animator();

        /**
         * @brief Constructor
         * @param target Sprite to be animated
         *
         * You don't have to call setTarget when this constructor is used
         */
        explicit Animator(Sprite& target);

        /**
         * @brief Construct the animator from an existing animator
         * @param other The animator to construct this animator from
         *
         * @warning The target of @a other will not be copied because an
         * animation target can only be owned by one animator. Therefore,
         * the target to be animated will be null after construction. This
         * means that you have to initialize the target yourself by calling
         * the setTarget() function
         *
         * @see setTarget
         */
        Animator(const Animator& other);

        /**
         * @brief Copy assignment operator
         */
        Animator& operator=(Animator);

        /**
         * @brief Create an animation in the animator
         * @param name Name of the animation
         * @param spriteSheet The spritesheet containing the animation frames
         * @param duration The duration of the animation
         * @return The created animation or a nullptr if an animation with
         *         the same name already exists in the animator
         *
         * @see ime::Animation::create
         */
        Animation::Ptr createAnimation(const std::string &name,
            const SpriteSheet& spriteSheet, const Time& duration = Time::Zero);

        /**
         * @brief Set the animation target
         * @param target The target to be animated
         *
         * Note that this function does not enforce the one animator per
         * target rule. This means that if you call this function on multiple
         * animator instances with the same argument, then @a target will be
         * animated by multiple animators at once and the result may not be
         * what you want or expect
         */
        void setTarget(Sprite& target);

        /**
         * @brief Set the timescale factor
         * @param timescale The new timescale factor
         *
         * The timescale factor controls the playback speed of the current
         * animation. For example, a timescale of 2.0f will make the animation
         * play twice as fast, a timescale of 0.5f will make the animation
         * play at half its normal playback speed and a timescale of 0.0f will
         * freeze the animation. Note that if @a timescale is negative then the
         * timescale will be set to 1.0f (real-time)
         *
         * @note The timescale of the animator is multiplied with the timescale
         * of the current animation. For example, if the timescale of the current
         * animation is 2.0f and the timescale of the animator is 2.0f, then
         * the current animation will play 4 times as fast
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
         * @brief Add an animation to the animator
         * @param animation The animation to be added
         * @return True if the animation was added or false if an animation
         *         with the same name as the specified animation already
         *         exists in the animator
         */
        bool addAnimation(Animation::Ptr animation);

        /**
         * @brief Add multiple animations at the same time to the animator
         * @param animations Animations to be added
         *
         * @note If an animation with the same name as one of the animations
         * to be added already exist in the animator, then that animation will
         * be skipped
         *
         * @see addAnimation
         */
        void addAnimation(std::initializer_list<Animation::Ptr> animations);

        /**
         * @brief Get an animation in the animator
         * @param name The name of the animation to retrieve
         * @return Pointer to the requested animation if it exists, otherwise
         *         a nullptr
         */
        Animation::Ptr getAnimation(const std::string& name) const;

        /**
         * @brief Get the animation that's currently playing
         * @return Pointer to the current active animation if there is one,
         *         otherwise a nullptr
         */
        Animation::Ptr getActiveAnimation() const;

        /**
         * @brief Get the frame that is currently displayed by the active animation
         * @return The current frame of the active animation or a std::nullopt if
         *         there is no active animation
         */
        std::optional<AnimationFrame> getCurrentFrame() const;

        /**
         * @brief Get the frame that comes after the frame that is currently
         *        displayed by the active animation
         * @return The next frame of the active animation or a std::nullopt if
         *         there is no active animation or the is no next frame
         */
        std::optional<AnimationFrame> getNextFrame() const;

        /**
         * @brief Get the frame that comes before the frame that is currently
         *        displayed by the active animation
         * @return The current frame of the active animation or a std::nullopt if
         *         there is no active animation or there is no previous frame
         */
        std::optional<AnimationFrame> getPreviousFrame() const;

        /**
         * @brief Remove an animation from the animator
         * @param name The name of the animation to be removed
         * @return True if the animation was removed or false if it does
         *         not exist in the animator
         */
        bool removeAnimation(const std::string& name);

        /**
         * @brief Remove all animations from the animator
         */
        void removeAll();

        /**
         * @brief Check whether or not an animation exists in the animator
         * @param animation The animation to be checked
         * @return True if the animation exists, otherwise false
         */
        bool hasAnimation(const Animation::Ptr& animation) const;

        /**
         * @brief Check whether or not an animation exists in the animator
         * @param name The name of the animation to be checked
         * @return True if the animation exists, otherwise false
         */
        bool hasAnimation(const std::string& name) const;

        /**
         * @brief Chain an animation to the current animation
         * @param animation The animation to be chained
         *
         * A chained animation is an animation that plays immediately after,
         * the current animation finishes. If there is no current animation
         * then this @a animation will be set as the current animation and
         * played. If the current animation is chained to another animation
         * then then the given animation will be chained to that animation
         */
        void chainAnimation(Animation::Ptr animation);

        /**
         * @brief Chain an animation to the current animation
         * @param name The name of the animation to be chained
         *
         * A chained animation is an animation that plays immediately after,
         * the current animation finishes. If there is no current animation
         * then this @a animation will be set as the current animation and
         * played. If the current animation is chained to another animation
         * then then the given animation will be chained to that animation
         */
        void chainAnimation(const std::string& name);

        /**
         * @brief Unchain an animation from a the current animations chain
         * @param name The name of the animation to be unchained
         * @return True if the animation was unchained or false if the
         *         animation is not part of the current animations chain
         *
         * @see chainAnimation
         */
        bool unchain(const std::string& name);

        /**
         * @brief Remove all the animations chained to the current animation
         *
         * @see chainAnimation and unchain
         */
        void clearAllChains();

        /**
         * @brief Change the current active animation
         * @param name The name of the new animation
         * @param ignorePlaying True to ignore switch if an animation is
         *         currently playing otherwise false to switch anyway
         * @return True if the animation was switched, of false if it
         *         does not exist in the animator
         *
         * This function does not start the animation, it only sets the current
         * active animation to the specified animation such that when play()
         * is called, the given animation is played. To switch and immediately
         * play an animation use the startAnimation() function
         *
         * @see startAnimation
         */
        bool switchAnimation(const std::string& name, bool ignorePlaying = false);

        /**
         * @brief Play an animation immediately
         * @param name The name of the animation to play
         * @param unchain True to clear all chained animations, or false
         *        to chained pending chains to the specified animation
         *
         * This function will stop the current animation if there is any
         * and immediately play the specified animation. If the specified
         * animation does not exist in the animator the current animation
         * will continue playing
         *
         * Note that by default, animations that were pending to be chained
         * to the active animation prior to function call will be chained to
         * the specified animation. This property can be override by setting
         * @a unchain to true
         *
         * To switch the animation without playing it, use the switchAnimation()
         * function
         *
         * @see switchAnimation and chainAnimation
         */
        void startAnimation(const std::string& name, bool unchain = false);

        /**
         * @brief Play the current animation if any
         *
         * This function will start playing the current animation if it was
         * pending a start. If the animation is paused, you have to call resume
         * to play it.
         *
         * This function has no effect if there is no active animation waiting
         * to be played or when there is one but it is paused
         *
         * @see pause, resume, stop and isAnimationStarted
         */
        void play();

        /**
         * @brief Pause the current animation
         *
         * @see play, resume and stop
         */
        void pause();

        /**
         * @brief Resume a paused animation
         *
         * see play, pause and stop
         */
        void resume();

        /**
         * @brief Stop the current animation
         *
         * @see play, pause and resume
         */
        void stop();

        /**
         * @brief Restart the current animation from the beginning
         */
        void restart();

        /**
         * @brief Force the current animation to complete
         */
        void complete();

        /**
         * @brief Check if an animation is playing or not
         * @return True if an animation is playing, otherwise false
         *
         * This function will return false if there is no current animation
         * or when the animation is paused or stopped
         */
        bool isAnimationPlaying() const;

        /**
         * @brief Check if the animation is paused or not
         * @return True if the animation is paused, otherwise false
         *
         * This function returns false if there is no current animation
         * or the animation is playing or is stopped
         */
        bool isAnimationPaused() const;

        /**
         * @brief Check if the current animation has started or not
         * @return True if the animation has started, otherwise false
         *
         * Note that when play() or startAnimation() is called, the animation
         * may not start immediately depending on whether it has a start delay
         * or not. Therefore, isAnimationPlaying() may return true whilst this
         * function returns false
         *
         * @see play and startAnimation
         */
        bool isAnimationStarted() const;

        /**
         * @brief Subscribe a callback to any animation event
         * @param event The name of the event to subscribe a callback to
         * @param callback The function to be executed when the event is fired
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The callbacks unique identification number
         *
         * The callback function is optionally passed the animation that
         * triggered the event
         *
         * @see unsubscribe
         */
        int on(Event event, const Callback<Animation::Ptr>& callback, bool oneTime = false);
        int on(Event event, const Callback<>& callback, bool oneTime = false);

        /**
         * @brief Subscribe a callback to a specific animation event
         * @param event The event to subscribe a callback to
         * @param name The name of the animation to subscribe callback to
         * @param callback The Function to be executed when the event is fired
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The callbacks unique identification number
         *
         * This function subscribes a callback to events triggered by a
         * specific animation only. The callback will not be invoked for
         * events triggered by animations whose name do not match @a name
         *
         * To unsubscribe callbacks registered with this function, use the
         * unsubscribe function that removes only callbacks that were
         * subscribed to events triggered by specific animation objects
         *
         * The callback function is optionally passed the animation that
         * triggered the event which in this case its always the animation
         * specified by @a name
         *
         * @see unsubscribe(ime::Animator::Event, const std::string&, ime::Callback)
         */
        int on(Event event, const std::string& name, const Callback<Animation::Ptr>& callback, bool oneTime = false);
        int on(Event event, const std::string& name, const Callback<>& callback, bool oneTime = false);

        /**
         * @brief Remove a callback from an animation event
         * @param event The event to remove the callback from
         * @param id The unique identification number of the callback
         * @return True if the callback was removed or false if the given
         *         event does not have a callback associated with the
         *         given id
         *
         * @see on
         */
        bool unsubscribe(Event event, int id);

        /**
         * @brief Remove a callback from a specific animation
         * @param event The type of event to remove the callback from
         * @param name The name of the animation to remove the callback from
         * @param id The unique identification number of the callback
         * @return True if the callback was removed or false if the given
         *         event does not have a callback associated with the
         *         given id
         *
         * Note that this function is only applicable to callbacks that were
         * registered with on(ime::Animator::Event, const std::string&, ime::Callback)
         * function. For other callbacks, unsubscribe using the
         * unsubscribe(ime::Animator::Event, int) function
         */
        bool unsubscribe(Event event, const std::string& name, int id);

        /**
         * @internal
         * @brief Update the animator
         * @param deltaTime Time passed since last update
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
        */
        void update(Time deltaTime);

    private:
        /**
         * @brief Handle a start playback request
         *
         * This function dispatches ime::Animator::Event::AnimationStart event
         */
        void onStart();

        /**
         * @brief Handle an animation complete event
         *
         * This function dispatches ime::Animator::Event::AnimationComplete event
         */
        void onComplete();

        /**
         * @brief Advance the frame of the current animation by one
         *
         * This function will attempt to set the frame of the current
         * animation to the frame that comes after the one that is
         * currently displayed
         */
        void advanceFrame();

        /**
         * @brief Reverse the frame of the current animation by one
         *
         * This function will attempt to set the frame of the current
         * animation to the frame that comes before the frame that is
         * currently displayed
         */
        void reverseFrame();

        /**
         * @brief Set the current frame
         * @param frame The frame to be set
         *
         * This function sets the frame to be displayed on the target
         */
        void setCurrentFrame(const AnimationFrame& frame);

        /**
         * @brief Reset the current frame to the starting frame
         */
        void resetCurrentFrame();

        /**
          * @brief Dispatch an animation event
          * @param event Event event to e dispatched
          * @param animation The animation that triggered the event
          */
        void fireEvent(Event event, const Animation::Ptr& animation);

        /**
         * @brief Swap another animator with this animator
         * @param other Animator object to be swapped with this object
         */
        void swap(Animator& other);

        /**
         * @brief Determines the direction of the current animation cycle
         */
        void setCycleDirection();

        /**
         * @brief Cycle current animation sequence
         * @param isAlternating True if animation is alternating, otherwise false
         */
        void cycle(bool isAlternating);

        /**
         * @brief Make alternating animation play in the opposite direction
         */
        void reverseAlternateDirection();

    private:
        unsigned int currentFrameIndex_;                             //!< The index of the animation frame that is currently displayed
        Time totalTime_;                                             //!< Time passed since animation was started
        float timescale_;                                            //!< Timescale factor for the current animation
        bool isPlaying_;                                             //!< A flag indicating whether or not an animation is playing
        bool isPaused_;                                              //!< A flag indicating whether or not an animation is paused
        bool hasStarted_;                                            //!< A flag indicating whether or not a playing animation has started or is still waiting for a delay to expire
        EventEmitter eventEmitter_;                                  //!< Publishes animation events
        Animation::Ptr currentAnimation_;                            //!< Pointer to the current animation
        std::queue<Animation::Ptr> chains_;                          //!< Animations that play immediately after the current animation finishes
        std::unique_ptr<std::reference_wrapper<Sprite>> target_;     //!< Sprite to be animated
        std::unordered_map<std::string, Animation::Ptr> animations_; //!< Animations container

        /**
         * @brief Direction of the current animation cycle
         */
        enum class Direction {
            Unknown, //!< An unknown direction (No cycling takes place)
            Forward, //!< Cycles forwards one animation frame at a time
            Backward //!< Cycles backwards one animation frame at a time
        };

        Direction cycleDirection_;  //!< Current cycle direction
        unsigned int cycleCount_;   //!< Indicates how many cycles an alternating animation has completed
    };
}

/**
 * @class ime::Animator
 * @ingroup core
 *
 * An ime::Animator takes an ime::Animation object and animates an ime::Sprite
 * with the properties of the ime::Animation. The animator can store multiple
 * animations but only one can be played at a time. The animator must not be
 * instantiated directly, a ime::Sprite is bundled with its animator which can
 * be accessed with the ime::Sprite::getAnimator function
 */

#endif // IME_ANIMATOR_H
