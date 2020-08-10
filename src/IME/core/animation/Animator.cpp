#include "IME/core/animation/Animator.h"
#include "IME/core/resources/ResourceManager.h"
#include <algorithm>
#include <cassert>

namespace IME{
    Animator::Animator()
        : totalTime_(0.0f)
    {}

    void Animator::addAnimation(std::shared_ptr<Animation> animation) {
        assert(animation && "A null animation cannot be added to an Animator");
        auto animationName = animation->getName();
        animations_.insert(std::pair(animationName, std::move(animation)));
        if (animations_.size() == 1)
            changeAnimation(animationName);
    }

    void Animator::addAnimation(Animator::Animations animations) {
        std::for_each(animations.begin(), animations.end(),
            [this](const auto& animation) {
                addAnimation(animation);
            }
        );
    }

    void Animator::update(float deltaTime) {
        if (currentAnimation_ != nullptr) {
            if (totalTime_ == 0.0f)
                eventEmitter_.emit(currentAnimation_->getName() + "AnimationStarted");

            totalTime_ += deltaTime;
            auto numOfAnimFrames = currentAnimation_->getNumOfFrames();
            auto currentFrameIndex = static_cast<unsigned int>(
                (totalTime_ / currentAnimation_->getDuration()) * numOfAnimFrames);

            if (currentAnimation_->isLooped())
                currentFrameIndex %= numOfAnimFrames;
            else if (currentFrameIndex >= numOfAnimFrames) {
                finishAnimation();
                return;
            }
            animationSprite_.setTextureRect(currentAnimation_->getFrameAt(currentFrameIndex));
        }
    }

    void Animator::changeAnimation(const std::string &animation) {
        auto found = animations_.find(animation);
        if (found != animations_.end()){
            auto newAnimation = found->second;
            animationSprite_.setTexture(ResourceManager::getTexture(newAnimation->getSpriteSheet()));
            currentAnimation_ = newAnimation;
            totalTime_ = 0.0f;
        }
    }

    sf::Sprite Animator::getCurrentAnimSprite() const {
        if (currentAnimation_ == nullptr || totalTime_ == 0.0f)
            return sf::Sprite();
        return animationSprite_;
    }

    int Animator::onAnimationStart(const std::string &name, Callback<> callback) {
        return eventEmitter_.addEventListener(name + "AnimationStarted", std::move(callback));
    }

    int Animator::onAnimationFinish(const std::string &name, Callback<> callback) {
        return eventEmitter_.addEventListener(name + "AnimationFinished", std::move(callback));
    }

    bool Animator::removeEventListener(const std::string &name, const std::string &onTrigger, int id) {
        auto fullEventName = name;
        if (onTrigger == "start")
            fullEventName += "AnimationStarted";
        else if (onTrigger == "finish")
            fullEventName += "AnimationFinished";
        else
            return false;
        return eventEmitter_.removeEventListener(fullEventName, id);
    }

    void Animator::finishAnimation() {
        if (currentAnimation_ != nullptr && totalTime_ != 0.0f){
            totalTime_ = 0.0f;
            animationSprite_.setTextureRect(
                currentAnimation_->getFrameAt(currentAnimation_->getNumOfFrames() - 1)
            );
            auto animationName = currentAnimation_->getName();
            currentAnimation_ = nullptr;
            eventEmitter_.emit(animationName + "AnimationFinished");
        }
    }
}
