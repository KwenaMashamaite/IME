/**
 * @brief Class for animating sprites
 *
 * This class takes an Animation object and animates a sprite
 * with the properties of the animation object
 */

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Animation.h"
#include "event/EventEmitter.h"
#include <string>
#include <memory>
#include <unordered_map>
#include <initializer_list>
#include <utility>

class Animator {
public:
    using Animations = std::initializer_list<std::pair<std::string, std::shared_ptr<Animation>>>;

    /**
     * @brief Constructor
     */
    Animator();

    /**
     * @brief Add animation
     * @param name Name of the animation
     * @param animation Animation to be added
     *
     * The animation that's added first becomes the current animation
     * by default. The name of the animation must be unique (Must not
     * be the same as that of previously added animations)
     */
    void addAnimation(const std::string& name, std::shared_ptr<Animation> animation);

    /**
     * @brief Add multiple animations at the same time
     * @param animations Animations to be added
     */
    void addAnimation(Animations animations);

    /**
	 * @brief Update animation
	 * @param deltaTime Time passed since animation update
	 */
    void update(float deltaTime);

    /**
	 * @brief Change the current animation
	 * @param animation New animation
     *
     * The new animation must have been added to the animator
     * beforehand. Otherwise the current animation will continue
     * playing
	 */
    void changeAnimation(const std::string& animation);

    /**
     * @brief Get the animation representation
     * @return The animation representation sprite
     */
    sf::Sprite getCurrentAnimSprite() const;

    /**
     * @brief Add an event listener to an animation finished event
     * @tparam Args Parameter pack
     * @param callback Function to execute when the animation finishes
     * @return Event listeners identification number
     *
     * The callback function will only be executed once - when the animation
     * finishes
     */
    template<typename...Args>
    void onAnimationFinish(Callback<Args...> callback){
        eventEmitter_.addOnceEventListener("animationFinished", callback);
    }

private:
    //Animation sprite
    sf::Sprite target_;
    //Animations container
    std::unordered_map<std::string, std::shared_ptr<Animation>> animations_;
    //Pointer to the currently running animation
    std::shared_ptr<Animation> currentAnimation_;
    //Elapsed time so far
    float totalTime_;
    //Event publisher
    EventEmitter eventEmitter_;
};

#endif
