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

#ifndef IME_ANIMATOR_H
#define IME_ANIMATOR_H

#include "IME/Config.h"
#include "Animation.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/graphics/Sprite.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <initializer_list>
#include <utility>

namespace IME {
    /**
     * @brief Class for animating sprites
     *
     * This class takes an Animation object and animates a sprite
     * with the properties of the animation object
     */
    class IME_API Animator {
    public:
        using Animations = std::initializer_list<std::shared_ptr<Animation>>; //!< Alias

        /**
         * @brief Constructor
         * @param target Sprite to animate
         */
        explicit Animator(Graphics::Sprite& target);

        /**
         * @brief Add an animation to the animator
         * @param animation Animation to be added
         * @return True if the animation was added or false if an animation
         *         with the same name as the specified animation already exists
         */
        bool addAnimation(std::shared_ptr<Animation> animation);

        /**
         * @brief Add multiple animations at the same time
         * @param animations Animations to be added
         *
         * @see addAnimation
         */
        void addAnimation(Animations animations);

        /**
         * @brief Update the current animation
         * @param deltaTime Time passed since last animation update
         *
         * This function starts the current animation the first time its
         * called. Subsequent calls determine which frame to display
         */
        void update(float deltaTime);

        /**
         * @brief Change the current animation
         * @param animation New animation
         * @return True if animation was changed or false if animation does
         *         not exist
         */
        bool switchAnimation(const std::string& animation);

        /**
         * @brief Finish the current animation
         *
         * This function will stop the animation and jump straight to the
         * last frame
         */
        void finishAnimation();

        /**
         * @brief Add a function to execute when an animation starts
         * @param name Name of the animation
         * @param callback Function to execute when the animation starts
         * @return Event listeners identification number
         *
         * The animation starts on the first call to update and the
         * callback is invoked when an animation starts for the first.
         * This means that for looped animations, the callback will not
         * be invoked when the animation restarts
         *
         * @see update
         */
        int onAnimationStart(const std::string& name, Callback<> callback);

        /**
         * @brief Add a function to execute when an animation finishes
         * @param name Name of the animation
         * @param callback Function to execute when the animation finishes
         * @return Event listeners identification number
         *
         * The callback function is only invoked for animations that are
         * not looped since a looped animation does not finish
         */
        int onAnimationFinish(const std::string& name, Callback<> callback);

        /**
         * @brief Remove an event listener from an animation event
         * @param name Name of the animation to remove listener from
         * @param onTrigger When the event is fired ("onStart" or "onFinish")
         * @param id Identification number of the event listener
         * @return True if the event listener was removed or false if either
         *        the given event does not exist or it does not have an event
         *        listener with the given id
         *
         * The identification number is issued when an event listener is
         * registered to an animation event
         *
         * @see onAnimationStart, onAnimationFinish
         */
        bool removeEventListener(const std::string& name, const std::string& onTrigger, int id);

    private:
        Graphics::Sprite& animationTarget_;                                      //!< Sprite to be animated
        std::unordered_map<std::string, std::shared_ptr<Animation>> animations_; //!< Animations container
        std::shared_ptr<Animation> currentAnimation_;                            //!< Pointer to the current animation
        float totalTime_;                                                        //!< Time passed since animation was started
        EventEmitter eventEmitter_;                                              //!< Event publisher
    };
}

#endif // IME_ANIMATOR_H
