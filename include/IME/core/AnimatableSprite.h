#ifndef ANIMATABLESPRITE_H
#define ANIMATABLESPRITE_H

#include "Sprite.h"
#include "IME/core/animation/Animation.h"
#include "IME/event/EventEmitter.h"

namespace IME {
    class Animator;

    class AnimatableSprite : public Sprite {
    public:
        /**
         * @brief Construct an animatable sprite
         */
        AnimatableSprite();

        /**
         * @brief Add a sprite animation
         * @param animation Animation to be added
         * @return True if the animation was added or false if an animation
         *         with the same name as the specified animation already exists
         */
        bool addAnimation(std::shared_ptr<Animation> animation);

        /**
         * @brief Update the current animation
         * @param deltaTime Time passed since last animation update
         *
         * This function starts the current animation the first time its called.
         * Subsequent calls determine which frame to display
         */
        void updateAnimation(float deltaTime);

        /**
         * @brief Finish the currently playing animation
         *
         * This function will stop the animation and jump straight to the last
         * animation frame
         */
        void finishAnimation();

        /**
         * @brief Change the current animation
         * @param name New animation
         * @return True if animation was changed or false if animation does
         *          not exist
         */
        bool changeAnimation(const std::string& name);

        /**
         * @brief Add a function to execute when an animation starts
         * @param name Name of the animation
         * @param callback Function to execute when the animation starts
         * @return Event listeners identification number
         *
         * The animation starts on the first call to the update(float) function
         * and the callback is invoked when an animation starts for the first.
         * This means that for looped animations,  the "animationStart" event
         * will not fire when the animation restarts
         */
        int onAnimationStart(const std::string& name, Callback<> callback);

        /**
         * @brief Add a function to execute when an animation finishes
         * @param name Name of the animation
         * @param callback Function to execute when the animation finishes
         * @return Event listeners identification number
         *
         * The callback function is only executed for animations that are not
         * looped
         */
        int onAnimationFinish(const std::string& name, Callback<> callback);

        /**
         * @brief Remove an event listener from an animation event
         * @param name Name of the animation to remove listener from
         * @param onTrigger When the event is fired ("start" or "finish")
         * @param id Identification number of the event listener
         */
        bool removeEventListener(const std::string& name, const std::string& onTrigger, int id);

    private:
        //Sprite animator
        std::shared_ptr<Animator> animator_;
    };
}

#endif
