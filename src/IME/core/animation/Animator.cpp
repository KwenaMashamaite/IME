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
#include "IME/graphics/Sprite.h"
#include <algorithm>

namespace ime {
    Animator::Animator(Sprite& target) :
        target_{target},
        timescale_{1.0f},
        isPlaying_{false},
        isPaused_{false},
        hasStarted_{false}
    {}

    Animator &Animator::operator=(Animator && other) {
        //Can't use default one because of reference member
        if (this != &other)
            *this = std::move(other);

        return *this;
    }

    Animation::sharedPtr Animator::createAnimation(const std::string &name,
        const SpriteSheet& spriteSheet, Time duration)
    {
        auto animation = Animation::create(name, spriteSheet, duration);
        if (addAnimation(animation))
            return animation;
        else
            return nullptr;
    }

    void Animator::setTimescale(float timescale) {
        if (timescale < 0.0f)
            timescale_ = 1.0f;
        else
            timescale_ = timescale;
    }

    float Animator::getTimescale() const {
        return timescale_;
    }

    bool Animator::addAnimation(Animation::sharedPtr animation) {
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

    Animation::sharedPtr Animator::getAnimation(const std::string &name) const {
        if (hasAnimation(name))
            return animations_.at(name);
        return nullptr;
    }

    Animation::sharedPtr Animator::getCurrentAnimation() const {
        return currentAnimation_;
    }

    bool Animator::removeAnimation(const std::string &name) {
        if (hasAnimation(name)) {
            animations_.erase(name);
            return true;
        }
        return false;
    }

    bool Animator::removeAnimation(Animation::sharedPtr animation) {
        if (animation)
            removeAnimation(animation->getName());
        return false;
    }

    void Animator::removeAll() {
        animations_.clear();
    }

    bool Animator::hasAnimation(const Animation::sharedPtr &animation) const {
        if (animation)
            return hasAnimation(animation->getName());
        return false;
    }

    bool Animator::hasAnimation(const std::string &name) const {
        return animations_.find(name) != animations_.end();
    }

    void Animator::chainAnimation(Animation::sharedPtr animation) {
        if (!animation || (currentAnimation_ && currentAnimation_ == animation))
            return;

        addAnimation(animation);

        if (!currentAnimation_) {
            currentAnimation_ = animation;
            play();
        } else
            chains_.push(std::move(animation));
    }

    void Animator::chainAnimation(const std::string &name) {
        if (hasAnimation(name))
            chainAnimation(animations_.at(name));
    }

    bool Animator::removeChain(const std::string &name) {
        if (chains_.empty())
            return false;

        auto sizeBeforeOp = chains_.size();
        auto newChains = std::queue<Animation::sharedPtr>{};
        while (!chains_.empty()) {
            if (chains_.front()->getName() != name)
                newChains.push(std::move(chains_.front()));
            chains_.pop();
        }
        chains_.swap(newChains);
        return chains_.size() < sizeBeforeOp;
    }

    void Animator::clearAllChains() {
        for (auto i = 0u; i < chains_.size(); ++i)
            chains_.pop();
    }

    bool Animator::switchAnimation(const std::string &animation, bool ignoreIfPlaying) {
        if (!hasAnimation(animation))
            return false;

        if (!currentAnimation_) {
            currentAnimation_ = animations_.at(animation);
        } else if ((isPlaying_ || isPaused_) && !ignoreIfPlaying) {
            stop();
            currentAnimation_ = animations_.at(animation);
            fireEvent(Event::AnimationSwitch, currentAnimation_);
        } else
            return false;

        return true;
    }

    void Animator::startAnimation(const std::string &name, bool unchain) {
        if (!hasAnimation(name))
            return;

        if (isPlaying_ || isPaused_)
            stop();

        if (unchain)
            clearAllChains();

        currentAnimation_ = animations_.at(name);
        play();
    }

    void Animator::play() {
        if (currentAnimation_ && !isPlaying_ && !isPaused_) {
            isPlaying_ = true;
            fireEvent(Event::AnimationPlay, currentAnimation_);
        }
    }

    void Animator::pause() {
        if (isPlaying_) {
            isPlaying_ = false;
            isPaused_ = true;
            fireEvent(Event::AnimationPause, currentAnimation_);
        }
    }

    void Animator::resume() {
        if (isPaused_) {
            isPlaying_ = true;
            isPaused_ = false;
            fireEvent(Event::AnimationResume, currentAnimation_);
        }
    }

    void Animator::stop() {
        if (isPlaying_ || isPaused_) {
            isPlaying_ = hasStarted_ = isPaused_ = false;
            totalTime_ = Time::Zero;
            currentFrameIndex_ = 0;
            resetCurrentFrame();
            fireEvent(Event::AnimationStop, currentAnimation_);
        }
    }

    void Animator::restart() {
        stop();
        play();
    }

    void Animator::complete() {
        if (currentAnimation_) {
            if (currentAnimation_->getDirection() == Animation::Direction::Forward)
                currentFrameIndex_ = currentAnimation_->getFrameCount() - 1;
            else if (currentAnimation_->getDirection() == Animation::Direction::Reverse)
                currentFrameIndex_ = 0;

            setCurrentFrame(*currentAnimation_->getFrameAt(currentFrameIndex_));
            onComplete();
        }
    }

    bool Animator::isAnimationPlaying() const {
        return isPlaying_;
    }

    bool Animator::isAnimationPaused() const {
        return isPaused_;
    }

    bool Animator::hasAnimationStarted() const {
        return hasStarted_;
    }

    void Animator::update(Time deltaTime) {
        if (!currentAnimation_ || !isPlaying_ || isPaused_)
            return;

        totalTime_ += deltaTime * timescale_;

        // Handle delayed start
        if (!hasStarted_) {
            if (totalTime_ >= currentAnimation_->getStartDelay()) {
                totalTime_ -= currentAnimation_->getStartDelay();
                onStart();
            }
        } else if (totalTime_ >= currentAnimation_->getFrameTime()) {
            totalTime_ = Time::Zero;
            if (currentAnimation_->getDirection() == Animation::Direction::Forward)
                advanceFrame();
            else if (currentAnimation_->getDirection() == Animation::Direction::Reverse)
                reverseFrame();
        }
    }

    int Animator::on(Animator::Event event, Callback<Animation::sharedPtr> callback) {
        return eventEmitter_.on(std::to_string(static_cast<int>(event)), std::move(callback));
    }

    int Animator::on(Animator::Event event, Callback<> callback) {
        return eventEmitter_.on(std::to_string(static_cast<int>(event)), std::move(callback));
    }

    bool Animator::unsubscribe(Animator::Event event, int id) {
        return eventEmitter_.removeEventListener(std::to_string(static_cast<int>(event)), id);
    }

    int Animator::on(Animator::Event event, const std::string &name,
        Callback<Animation::sharedPtr> callback)
    {
        return eventEmitter_.on(std::to_string(static_cast<int>(event)) + name, std::move(callback));
    }

    int Animator::on(Animator::Event event, const std::string &name,
        Callback<> callback)
    {
        return eventEmitter_.on(std::to_string(static_cast<int>(event)) + name, std::move(callback));
    }

    bool Animator::unsubscribe(Animator::Event event, const std::string &name, int id) {
        return eventEmitter_.removeEventListener(std::to_string(static_cast<int>(event)) + name, id);
    }

    void Animator::fireEvent(Animator::Event event, Animation::sharedPtr animation) {
        /**
         * Event handlers are separated into specific and general handlers
         *
         * Specific handlers are only invoked when the event is generated
         * by a specific animation object whilst general handlers are always
         * invoked when an animation is fired regardless of the animation
         * object that triggered the event. This separation of general and
         * specific handlers alleviates the issue of having one monolithic
         * handler in the client code with if-else-if branches that checks
         * the animation name before performing an action
         *
         * We first notify specific handlers (which may not be invoked) about
         * the event, then notify general handlers. Note that the callback
         * argument is optional so we fire the event twice, first without the
         * argument and secondly with the argument.
         */

        // Specific handlers
        eventEmitter_.emit(std::to_string(static_cast<int>(event)) + animation->getName());
        eventEmitter_.emit(std::to_string(static_cast<int>(event)) + animation->getName(), animation);

        //General handlers
        eventEmitter_.emit(std::to_string(static_cast<int>(event)));
        eventEmitter_.emit(std::to_string(static_cast<int>(event)), animation);
    }

    void Animator::onStart() {
        hasStarted_ = true;
        if (currentAnimation_->isTargetShownOnStart())
            target_.setVisible(true);

        resetCurrentFrame();
        fireEvent(Event::AnimationStart, currentAnimation_);
    }

    void Animator::onComplete() {
        if (currentAnimation_->isTargetHiddenOnCompletion())
            target_.setVisible(false);

        isPlaying_ = isPaused_ = hasStarted_ = false;
        totalTime_ = Time::Zero;
        fireEvent(Event::AnimationComplete, currentAnimation_);

        if (!chains_.empty()) {
            currentAnimation_ = chains_.front();
            chains_.pop();
            play();
        }
    }

    void Animator::advanceFrame() {
        if (currentFrameIndex_ == currentAnimation_->getFrameCount() - 1) {
            if (currentAnimation_->isLooped())
                currentFrameIndex_ = 0;
            else if (currentAnimation_->isRepeating()) {
                currentFrameIndex_ = 0;
                currentAnimation_->setRepeatCount(currentAnimation_->getRepeatCount() - 1);
                fireEvent(Event::AnimationRepeat, currentAnimation_);
            } else {
                onComplete();
                return;
            }
        } else
            currentFrameIndex_ += 1;

        setCurrentFrame(*currentAnimation_->getFrameAt(currentFrameIndex_));
    }

    void Animator::reverseFrame() {
        auto lastFrameIndex = currentAnimation_->getFrameCount() - 1;
        if (currentFrameIndex_ == 0) {
            if (currentAnimation_->isLooped())
                currentFrameIndex_ = lastFrameIndex;
            else if (currentAnimation_->isRepeating()) {
                currentFrameIndex_ = lastFrameIndex;
                currentAnimation_->setRepeatCount(currentAnimation_->getRepeatCount() - 1);
                fireEvent(Event::AnimationRepeat, currentAnimation_);
            } else {
                onComplete();
                return;
            }
        } else
            currentFrameIndex_ -= 1;

        setCurrentFrame(*currentAnimation_->getFrameAt(currentFrameIndex_));
    }

    void Animator::setCurrentFrame(Animation::Frame frame) {
        target_.setTexture(currentAnimation_->getSpriteSheet().getTextureFilename());

        /**
         * When the texture is set on the sprite, it uses the original image
         * that was used to construct the spritesheet. However if the
         * spritesheet was constructed from a sub-rectangle then the top-left
         * coordinates of a frame from the spritesheet are relative to the
         * sub-rectangle and not the original image. Therefore we offset the
         * top-left arguments to the sprites sub-rectangle so that the
         * image referred to by the spritesheet frame and the image displayed
         * on the sprite are the same
         */
        auto offset = currentAnimation_->getSpriteSheet().getRelativePosition();
        target_.setTextureRect(offset.x + frame.left, offset.y + frame.top, frame.width, frame.height);
    }

    void Animator::resetCurrentFrame() {
        if (currentAnimation_->getDirection() == Animation::Direction::Forward)
            currentFrameIndex_ = 0;
        else if (currentAnimation_->getDirection() == Animation::Direction::Reverse)
            currentFrameIndex_ = currentAnimation_->getFrameCount() - 1;
        else
            return;

        setCurrentFrame(*currentAnimation_->getFrameAt(currentFrameIndex_));
    }
}
