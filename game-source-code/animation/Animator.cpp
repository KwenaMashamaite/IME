#include "Animator.h"
#include "resources/ResourceManager.h"
#include <algorithm>
#include <cassert>

Animator::Animator()
    : totalTime_(0.0f)
{}

void Animator::addAnimation(const std::string &name, std::shared_ptr<Animation> animation) {
    assert(animation && "A null animation cannot be added to an Animator");
    animations_.insert(std::pair(name, std::move(animation)));
    if (animations_.size() == 1)
        changeAnimation(name);
}

void Animator::addAnimation(Animator::Animations animations) {
    std::for_each(animations.begin(), animations.end(),
        [this](const auto& animation) {
            addAnimation(animation.first, animation.second);
        }
    );
}

//@todo Reset var totaltime due to some condition (Overflow risk)
void Animator::update(float deltaTime) {
    totalTime_ += deltaTime;
    auto getCurrentFrameIndex = [this]{
        auto numOfAnimFrames = currentAnimation_->getNumOfFrames();
        auto currentFrameIndex = static_cast<unsigned int>(
            (totalTime_ / currentAnimation_->getDuration()) * numOfAnimFrames
        );

        if (currentAnimation_->isLooped())
            return currentFrameIndex %= numOfAnimFrames;
        else if (currentFrameIndex >= numOfAnimFrames) {
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
    return target_;
}
