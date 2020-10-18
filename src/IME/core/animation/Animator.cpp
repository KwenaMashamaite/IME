#include "IME/core/animation/Animator.h"
#include "IME/core/managers/ResourceManager.h"
#include <algorithm>
#include <cassert>

namespace IME{
    Animator::Animator(Graphics::Sprite& target)
        : animationTarget_(target), totalTime_(0.0f)
    {}

    bool Animator::addAnimation(std::shared_ptr<Animation> animation) {
        assert(animation && "A null animation cannot be added to an Animator");
        return animations_.insert({animation->getName(), std::move(animation)}).second;
    }

    void Animator::addAnimation(Animator::Animations animations) {
        std::for_each(animations.begin(), animations.end(),
            [this](const auto& animation) {
                addAnimation(animation);
            }
        );
    }

    void Animator::update(float deltaTime) {
        if (currentAnimation_) {
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
            auto currentFrame = currentAnimation_->getFrameAt(currentFrameIndex);
            animationTarget_.setTextureRect(currentFrame.left, currentFrame.top, currentFrame.width, currentFrame.height);
        }
    }

    bool Animator::switchAnimation(const std::string &animation) {
        if (auto found = animations_.find(animation); found != animations_.end()){
            auto newAnimation = found->second;
            animationTarget_.setTexture(newAnimation->getSpriteSheet());
            auto firstFrame = newAnimation->getFrameAt(0);
            animationTarget_.setTextureRect(firstFrame.left, firstFrame.top, firstFrame.width, firstFrame.height);
            currentAnimation_ = newAnimation;
            totalTime_ = 0.0f;
            return true;
        }
        return false;
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
        if (currentAnimation_ && totalTime_ != 0.0f){
            totalTime_ = 0.0f;
            auto lastFrame = currentAnimation_->getFrameAt(currentAnimation_->getNumOfFrames() - 1);
            animationTarget_.setTextureRect(lastFrame.left, lastFrame.top, lastFrame.width, lastFrame.height);
            auto animationName = currentAnimation_->getName();
            currentAnimation_ = nullptr;
            eventEmitter_.emit(animationName + "AnimationFinished");
        }
    }
}
