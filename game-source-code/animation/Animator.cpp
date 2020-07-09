#include "Animator.h"
#include "resources/ResourceManager.h"
#include <algorithm>
#include <cassert>

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
    if (currentAnimation_ == nullptr)
        return;

    totalTime_ += deltaTime;
    auto getCurrentFrameIndex = [this]{
        auto numOfAnimFrames = currentAnimation_->getNumOfFrames();
        auto currentFrameIndex = static_cast<unsigned int>(
            (totalTime_ / currentAnimation_->getDuration()) * numOfAnimFrames
        );

        if (currentAnimation_->isLooped())
            return currentFrameIndex %= numOfAnimFrames;
        else if (currentFrameIndex >= numOfAnimFrames) {
            currentAnimation_ = nullptr;
            eventEmitter_.emit("animationFinished");
            return --numOfAnimFrames;
        }
        return currentFrameIndex;
    };
    target_.setTextureRect(currentAnimation_->getFrameAt(getCurrentFrameIndex()));
}

void Animator::changeAnimation(const std::string &animation) {
    auto found = animations_.find(animation);
    if (found != animations_.end()){
        auto newAnimation = found->second;
        target_.setTexture(ResourceManager::getTexture(newAnimation->getSpriteSheet()));
        currentAnimation_ = newAnimation;
        totalTime_ = 0.0f;
    }
}

sf::Sprite Animator::getCurrentAnimSprite() const {
    if (currentAnimation_ == nullptr)
        return sf::Sprite();
    return target_;
}
