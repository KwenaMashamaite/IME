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

#include "IME/core/animation/Animator.h"
#include "IME/core/managers/ResourceManager.h"
#include <algorithm>

namespace ime {
    Animator::Animator(Sprite& target) :
        animationTarget_(target),
        totalTime_(0.0f)
    {}

    bool Animator::addAnimation(std::shared_ptr<Animation> animation) {
        IME_ASSERT(animation, "Cannot add nullptr to animator");
        return animations_.insert({animation->getName(), std::move(animation)}).second;
    }

    void Animator::addAnimation(Animator::Animations animations) {
        std::for_each(animations.begin(), animations.end(),
            [this](const auto& animation) {
                addAnimation(animation);
            }
        );
    }

    std::shared_ptr<Animation> Animator::getCurrentAnimation() const {
        return currentAnimation_;
    }

    void Animator::update(float deltaTime) {
        if (currentAnimation_) {
            if (totalTime_ == 0.0f)
                eventEmitter_.emit(currentAnimation_->getName() + "AnimationStart");

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
        return eventEmitter_.addEventListener(name + "AnimationStart", std::move(callback));
    }

    int Animator::onAnimationFinish(const std::string &name, Callback<> callback) {
        return eventEmitter_.addEventListener(name + "AnimationFinish", std::move(callback));
    }

    bool Animator::removeEventListener(const std::string &name, const std::string &onTrigger, int id) {
        auto fullEventName = name;
        if (onTrigger == "onStart")
            fullEventName += "AnimationStart";
        else if (onTrigger == "onFinish")
            fullEventName += "AnimationFinish";
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
            eventEmitter_.emit(animationName + "AnimationFinish");
        }
    }
}
