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
#include "Animation.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/core/time/Time.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <initializer_list>
#include <utility>
#include <queue>

namespace ime {
    class Sprite; // Sprite class forward declaration

    /**
     * @brief Class for animating sprites
     *
     * This class takes an Animation object and animates a sprite
     * with the properties of the animation object. The animator
     * can store multiple animations but only one can be played at
     * a time
     */
    class IME_API Animator {
    public:
        using Animations = std::initializer_list<Animation::sharedPtr>; //!< Alias

        /**
         * @brief Animation events (Triggered by the current animation)
         */
        enum class Event {
            AnimationPlay,     //!< An animation is started playing
            AnimationStart,    //!< An animation is started animating (Fires after the start delay has expired)
            AnimationPause,    //!< An animation is paused
            AnimationResume,   //!< An animation is resumed
            AnimationStop,     //!< An animation is stopped
            AnimationComplete, //!< An animation is completed
            AnimationRepeat,   //!< An animation is repeating
            AnimationRestart,  //!< An animation is restarted from the beginning
            AnimationSwitch    //!< An animation was changed while another was playing
        };

        /**
         * @brief Constructor
         * @param target Sprite to animate
         */
        explicit Animator(Sprite& target);

        /**
         * @brief Copy constructor
         */
        Animator(const Animator&) = delete;

        /**
         * @brief Copy assignment operator
         */
        Animator& operator=(const Animator&) = delete;

        /**
         * @brief Move constructor
         */
        Animator(Animator&&) = default;

        /**
         * @brief Move assignment operator
         */
        Animator& operator=(Animator&&);

        /**
         * @brief Create an animation in the animator
         * @param name Name of the animation
         * @param spriteSheet The spritesheet containing the animation frames
         * @param duration The duration of the animation
         * @return The create animation or a nullptr if an animation with
         *         the same name already exists
         *
         * The animation will be created and added to the Animator and
         * a pointer to it will be returned. Therefore calling
         * addAnimation with the returned pointer will always fail
         * since it already exist in the animator
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
        Animation::sharedPtr createAnimation(const std::string &name,
            const SpriteSheet& spriteSheet, Time duration = Time::Zero);

        /**
         * @brief Set the timescale factor
         * @param timescale The new timescale factor
         *
         * The timescale factor control the speed of the current animation
         * For example, a timescale of 2 will make the animation twice as
         * fast whilst a timescale of 0.5 will slow down the animation
         *
         * The timescale will be set to 1 if @a timescale is negative.
         *
         * By default the timescale is 1
         */
        void setTimescale(float timescale);

        /**
         * @brief Get the timescale factor of the current animation
         * @return The timescale of the current animation
         *
         * @see setTimescale
         */
        float getTimescale() const;

        /**
         * @brief Add an animation to the animator
         * @param animation Animation to be added
         * @return True if the animation was added or false if an animation
         *         with the same name as the specified animation already
         *         exists
         */
        bool addAnimation(Animation::sharedPtr animation);

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
        void addAnimation(Animations animations);

        /**
         * @brief Get an animation in the animator
         * @param name The name of the animation to retrieve
         * @return Pointer to the requested animation if it exists, otherwise
         *         a nullptr
         */
        Animation::sharedPtr getAnimation(const std::string& name) const;

        /**
         * @brief Get the current animation
         * @return Pointer to the current animation if there is one, otherwise
         *         a nullptr
         */
        Animation::sharedPtr getCurrentAnimation() const;

        /**
         * @brief Remove an animation from the animator
         * @param name Name of the animation to be removed
         * @return True if the animation was removed or false if it does
         *         not exist in the animator
         */
        bool removeAnimation(const std::string& name);

        /**
         * @brief Remove an animation from the animator
         * @param animation Animation to be removed
         * @return True if the animation was removed or false if it does
         *         not exist in the animator
         */
        bool removeAnimation(Animation::sharedPtr animation);

        /**
         * @brief Remove all animations from the animator
         */
        void removeAll();

        /**
         * @brief Check whether or not an animation exists in the animator
         * @param animation Animation to be checked
         * @return True if the animation exists, otherwise false
         */
        bool hasAnimation(const Animation::sharedPtr& animation) const;

        /**
         * @brief Check whether or not an animation exists in the animator
         * @param name Name of the animation to be checked
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
        void chainAnimation(Animation::sharedPtr animation);

        /**
         * @brief Chain an animation to play after the current animation
         * @param name Name of the animation to be chained
         *
         * A chained animation is an animation that plays immediately after,
         * the current animation finishes. If there is no current animation
         * then this @a animation will be set as the current animation and
         * played. If the current animation is chained to another animation
         * then then the given animation will be chained to that animation
         */
        void chainAnimation(const std::string& name);

        /**
         * @brief Remove an animation from a chain
         * @param name Name of the animation to be removed
         * @return True if the animation was removed or false if the
         *         is there is no such chain
         */
        bool removeChain(const std::string& name);

        /**
         * @brief Remove all the animations chained to the current animation
         */
        void clearAllChains();

        /**
         * @brief Change the current animation
         * @param name Name of the new animation
         * @param ignorePlaying True to ignore switch if an animation is
         *         currently playing otherwise false to switch anyway
         * @return True if the animation was switched, of false if it
         *         does not exist
         *
         * This function does not start the animation, it only sets the
         * current animation to the given animation such that when play()
         * is called, the given animation is played.
         *
         * By default the animation will be switched whether or not there
         * is an active animation
         *
         * To switch and immediately play an animation use the playAnimation
         * function
         *
         * @see playAnimation
         */
        bool switchAnimation(const std::string& name, bool ignorePlaying = false);

        /**
         * @brief Play an animation immediately
         * @param name Name of the animation to play
         * @param unchain True to clear all chained animations, or false
         *        to chained pending chains to the specified animation
         *
         * This function will stop the current animation if there is any
         * and immediately play the specified animation. If the specified
         * animation does not exist in the animator the current animation
         * will continue playing
         *
         * By default, animations that were pending to be chained to the
         * previous animation will be chained to the specified animation
         *
         * To switch the animation without playing it, use the switchAnimation
         * function
         *
         * @see switchAnimation
         */
        void startAnimation(const std::string& name, bool unchain = false);

        /**
         * @brief Play the current animation if any
         *
         * This function will start playing the current animation if
         * it was pending a start. If the animation is paused, you
         * have to call resume to play it
         *
         *
         *
         * @see pause and resume
         */
        void play();

        /**
         * @brief Pause the current animation
         *
         * This function will dispatch an Event::AnimationPause event
         * if the current animation was playing
         */
        void pause();

        /**
         * @brief Resume a paused animation
         *
         * This function will dispatch an Event::AnimationResume event
         * if the current animation was paused
         */
        void resume();

        /**
         * @brief Stop the current animation
         *
         * This function will dispatch an Event::AnimationStop event if
         * the current animation was playing. The event is dispatched
         * whether or not the current animation was started or waiting
         * for a delay to expire
         */
        void stop();

        /**
         * @brief Restart the current animation from the beginning
         *
         * This function will dispatch an Event::AnmationRestart event
         */
        void restart();

        /**
         * @brief Finish the current animation
         *
         * This function will force the current animation to complete
         * and any chained animations will start playing
         *
         * This function will dispatch an Event::AnimationComplete event
         */
        void complete();

        /**
         * @brief Check whether or not the current animation is playing
         * @return True if an animation is playing, otherwise false
         *
         * This function will return false if there is no current
         * animation or the animation is paused or stopped
         */
        bool isAnimationPlaying() const;

        /**
         * @brief Check whether or not the current animation is paused
         * @return True if the animation is paused, otherwise false
         *
         * This function returns false if there is no current animation
         * or the animation is playing or is stopped
         */
        bool isAnimationPaused() const;

        /**
         * @brief Check if the current animation has started
         * @return True if the animation has started otherwise false
         *
         * This function returns false if either the current animation
         * is not playing or the animation is playing but it is still
         * waiting for the start delay to expire
         */
        bool hasAnimationStarted() const;

        /**
        * @brief Update the current animation
        * @param deltaTime Time passed since last animation update
        */
        void update(Time deltaTime);

        /**
         * @brief Subscribe a callback to an animation event
         * @param event Name of the event to subscribe a callback to
         * @param callback Function to be executed when the event is fired
         * @return The callbacks identification number
         *
         * The callback id must be remembered if the callback must be
         * removed from the event at a later time
         *
         * The callback function is optionally passed the animation that
         * triggered the event
         *
         * @see unsubscribe
         */
        int on(Event event, Callback<Animation::sharedPtr> callback);
        int on(Event event, Callback<> callback);

        /**
         * @brief Subscribe a callback to a specific animation event
         * @param event The event to subscribe a callback to
         * @param name The name of the animation to subscribe callback to
         * @param callback The Function to be executed when the event is fired
         * @return The callback identification number
         *
         * This function subscribes a callback to events triggered by a
         * specific animation only. The callback will not be invoked for
         * events triggered by animations whose name do not match @a name.
         *
         * To unsubscribe callbacks registered with this function, use the
         * unsubscribe function that removes only callbacks that were
         * subscribed to events triggered by specific animation objects
         *
         * @note The callback id must be remembered if the callback must be
         * removed from the event at a later time
         *
         * The callback function is optionally passed the animation that
         * triggered the event which in this case its always the animation
         * with the @a name
         *
         * @see unsubscribe(Event, const std::string, Callback)
         */
        int on(Event event, const std::string& name, Callback<Animation::sharedPtr> callback);
        int on(Event event, const std::string& name, Callback<> callback);

        /**
         * @brief Remove a callback from an animation event
         * @param event The event to remove the callback from
         * @param id Identification number of the callback
         * @return True if the callback was removed or false if the given
         *         event does not have a callback associated with the
         *         given id
         *
         * @see on
         */
        bool unsubscribe(Event event, int id);

        /**
         * @brief Remove a callback from a specific animation
         * @param event Th event to remove callback from
         * @param name The name of the animation to remove the callback from
         * @param id The identification number of the callback
         * @return True if the callback was removed or false if the given
         *         event does not have a callback associated with the
         *         given id
         *
         * Note that this function removes only callbacks that were subscribed
         * to animation events triggered by a specific animation. In other
         * words, it is only applicable to callbacks that were registered
         * using the on(Event, const std::string&, Callback) function. For
         * other callbacks, unsubscribe using the unsubscribe(Event, int)
         * function
         *
         * @see on(Event, const std::string&, Callback)
         */
        bool unsubscribe(Event event, const std::string& name, int id);

    private:
        /**
         * @brief Handle a start playback request
         *
         * This function dispatches an Event::AnimationStart event
         */
        void onStart();

        /**
         * @brief Handle an animation complete event
         *
         * This function dispatches an Event::AnimationComplete event
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
        void setCurrentFrame(Animation::Frame frame);

        /**
         * @brief Reset the current frame to the starting frame
         */
        void resetCurrentFrame();

        /**
          * @brief Dispatch an animation event
          * @param event Event event to e dispatched
          * @param animation The animation that triggered the event
          */
        void fireEvent(Event event, Animation::sharedPtr animation);

    private:
        Sprite& target_;                          //!< Sprite to be animated
        unsigned int currentFrameIndex_;          //!< The index of the animation frame that is currently displayed
        Time totalTime_;                          //!< Time passed since animation was started
        float timescale_;                         //!< Timescale factor for the current animation
        bool isPlaying_;                          //!< Flags whether or not an animation is playing
        bool isPaused_;                           //!< Flags whether or not an animation is paused
        bool hasStarted_;                         //!< Flags whether or not a playing animation has started or is still waiting o a delay to expire
        EventEmitter eventEmitter_;               //!< Publishes animation events
        Animation::sharedPtr currentAnimation_;   //!< Pointer to the current animation
        std::queue<Animation::sharedPtr> chains_; //!< Animations that play immediately after the current animation finishes

        std::unordered_map<std::string, Animation::sharedPtr> animations_; //!< Animations container
    };
}

#endif // IME_ANIMATOR_H
