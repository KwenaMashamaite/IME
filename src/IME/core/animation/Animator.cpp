////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
#include "IME/graphics/Sprite.h"
#include "IME/utility/Helpers.h"
#include <algorithm>
#include <memory>

namespace ime {
    Animator::Animator() :
        currentFrameIndex_{0},
        timescale_{1.0f},
        isPlaying_{false},
        isPaused_{false},
        hasStarted_{false},
        cycleDirection_{Direction::Unknown},
        cycleCount_{0}
    {}

    Animator::Animator(Sprite &target) :
        Animator()
    {
        setTarget(target);
    }

    Animator::Animator(const Animator& other) :
        currentFrameIndex_{other.currentFrameIndex_},
        totalTime_{other.totalTime_},
        timescale_{other.timescale_},
        isPlaying_{other.isPlaying_},
        isPaused_{other.isPaused_},
        hasStarted_{other.hasStarted_},
        eventEmitter_{other.eventEmitter_},
        currentAnimation_{other.currentAnimation_ ? std::make_shared<Animation>(*other.currentAnimation_) : nullptr},
        chains_{other.chains_},
        cycleDirection_{other.cycleDirection_},
        cycleCount_{other.cycleCount_}
    {
        for (const auto& [name, animation] : other.animations_) {
            animations_.insert({name, std::make_shared<Animation>(*animation)});
        }
    }

    Animator &Animator::operator=(Animator other) {
        swap(other);
        return *this;
    }

    void Animator::swap(Animator &other) {
        std::swap(currentFrameIndex_, other.currentFrameIndex_);
        std::swap(totalTime_, other.totalTime_);
        std::swap(timescale_, other.timescale_);
        std::swap(isPlaying_, other.isPlaying_);
        std::swap(isPaused_, other.isPaused_);
        std::swap(hasStarted_, other.hasStarted_);
        std::swap(eventEmitter_, other.eventEmitter_);
        std::swap(currentAnimation_, other.currentAnimation_);
        std::swap(chains_, other.chains_);
        std::swap(target_, other.target_);
        std::swap(animations_, other.animations_);
        std::swap(cycleDirection_, other.cycleDirection_);
        std::swap(cycleCount_, other.cycleCount_);
    }

    Animation::Ptr Animator::createAnimation(const std::string &name,
        const SpriteSheet& spriteSheet, const Time& duration)
    {
        auto animation = Animation::create(name, spriteSheet, duration);
        if (addAnimation(animation))
            return animation;
        else
            return nullptr;
    }

    void Animator::setTarget(Sprite &target) {
        target_ = std::make_unique<std::reference_wrapper<Sprite>>(target);
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

    bool Animator::addAnimation(Animation::Ptr animation) {
        IME_ASSERT(animation, "Animation cannot be a nullptr")
        IME_ASSERT(animation->getFrameCount() > 0, "Cannot add animation with zero animation frames")
        return animations_.insert({animation->getName(), std::move(animation)}).second;
    }

    void Animator::addAnimation(std::initializer_list<Animation::Ptr> animations) {
        std::for_each(animations.begin(), animations.end(),
            [this](const auto& animation) {
                addAnimation(animation);
            }
        );
    }

    Animation::Ptr Animator::getAnimation(const std::string &name) const {
        if (hasAnimation(name))
            return animations_.at(name);
        return nullptr;
    }

    Animation::Ptr Animator::getActiveAnimation() const {
        return currentAnimation_;
    }

    AnimationFrame *Animator::getCurrentFrame() {
        return const_cast<AnimationFrame*>(std::as_const(*this).getCurrentFrame());
    }

    const AnimationFrame* Animator::getCurrentFrame() const {
        return currentAnimation_ ? currentAnimation_->getCurrentFrame() : nullptr;
    }

    AnimationFrame *Animator::getNextFrame() {
        return const_cast<AnimationFrame*>(std::as_const(*this).getNextFrame());
    }

    const AnimationFrame* Animator::getNextFrame() const {
        return currentAnimation_ ? currentAnimation_->getNextFrame() : nullptr;
    }

    AnimationFrame *Animator::getPreviousFrame() {
        return const_cast<AnimationFrame*>(std::as_const(*this).getPreviousFrame());
    }

    const AnimationFrame* Animator::getPreviousFrame() const {
        return currentAnimation_ ? currentAnimation_->getPreviousFrame() : nullptr;
    }

    bool Animator::removeAnimation(const std::string &name) {
        if (hasAnimation(name)) {
            animations_.erase(name);
            return true;
        }
        return false;
    }

    void Animator::removeAll() {
        animations_.clear();
    }

    bool Animator::hasAnimation(const Animation::Ptr &animation) const {
        if (animation)
            return hasAnimation(animation->getName());
        return false;
    }

    bool Animator::hasAnimation(const std::string &name) const {
        return animations_.find(name) != animations_.end();
    }

    void Animator::chainAnimation(Animation::Ptr animation) {
        if (!animation || (currentAnimation_ && currentAnimation_ == animation))
            return;

        IME_ASSERT(animation->getFrameCount() > 0, "Cannot chain animation with zero animation frames")
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

    bool Animator::unchain(const std::string &name) {
        if (chains_.empty())
            return false;

        auto sizeBeforeOp = chains_.size();
        auto newChains = std::queue<Animation::Ptr>{};
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
            setCycleDirection();
        } else if ((isPlaying_ || isPaused_) && !ignoreIfPlaying) {
            stop();
            currentAnimation_ = animations_.at(animation);
            setCycleDirection();
            fireEvent(Event::AnimationSwitch, currentAnimation_);
        } else
            return false;

        return true;
    }

    void Animator::startAnimation(const std::string &name, bool unchain) {
        if (!hasAnimation(name))
            return;

        IME_ASSERT(animations_.at(name)->getFrameCount() > 0, "Cannot start animation with zero frames")

        if (isPlaying_ || isPaused_)
            stop();

        if (unchain)
            clearAllChains();

        currentAnimation_ = animations_.at(name);
        setCycleDirection();

        play();
    }

    void Animator::play() {
        if (currentAnimation_ && !isPlaying_ && !isPaused_) {
            isPlaying_ = true;
            (*target_).get().setTexture(currentAnimation_->getSpriteSheet().getTexture());
            resetCurrentFrame();

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

            if (currentAnimation_->isCurrentFrameResetOnInterrupt())
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
            if (currentAnimation_->getDirection() == Animation::Direction::Forward
                || currentAnimation_->getDirection() == Animation::Direction::Alternate_Reverse)
            {
                currentFrameIndex_ = currentAnimation_->getFrameCount() - 1;
            } else if (currentAnimation_->getDirection() == Animation::Direction::Reverse
                || currentAnimation_->getDirection() == Animation::Direction::Alternate_Forward)
            {
                currentFrameIndex_ = 0;
            }

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

    bool Animator::isAnimationStarted() const {
        return hasStarted_;
    }

    void Animator::update(Time deltaTime) {
        IME_ASSERT(target_, "Cannot start Animator without a target to animate")
        if (!currentAnimation_ || !isPlaying_ || isPaused_)
            return;

        totalTime_ += deltaTime * timescale_ * currentAnimation_->getTimescale();

        // Handle delayed start
        if (!hasStarted_) {
            if (totalTime_ >= currentAnimation_->getStartDelay()) {
                totalTime_ -= currentAnimation_->getStartDelay();
                onStart();
            }
        } else if (totalTime_ >= currentAnimation_->getFrameTime()) {
            totalTime_ = Time::Zero;
            if (currentAnimation_->getDirection() == Animation::Direction::Forward
                || currentAnimation_->getDirection() == Animation::Direction::Reverse)
            {
                cycle(false);
            } else
                cycle(true);
        }
    }

    int Animator::on(Animator::Event event, const Callback<Animation::Ptr>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, std::to_string(static_cast<int>(event)), callback, oneTime);
    }

    int Animator::on(Animator::Event event, const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, std::to_string(static_cast<int>(event)), callback, oneTime);
    }

    bool Animator::unsubscribe(Animator::Event event, int id) {
        return eventEmitter_.removeEventListener(std::to_string(static_cast<int>(event)), id);
    }

    int Animator::on(Animator::Event event, const std::string &name, const Callback<Animation::Ptr>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, std::to_string(static_cast<int>(event)) + name, callback, oneTime);
    }

    int Animator::on(Animator::Event event, const std::string &name, const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, std::to_string(static_cast<int>(event)) + name, callback, oneTime);
    }

    bool Animator::unsubscribe(Animator::Event event, const std::string &name, int id) {
        return eventEmitter_.removeEventListener(std::to_string(static_cast<int>(event)) + name, id);
    }

    void Animator::fireEvent(Animator::Event event, const Animation::Ptr& animation) {
        // Specific handlers
        eventEmitter_.emit(std::to_string(static_cast<int>(event)) + animation->getName());
        eventEmitter_.emit(std::to_string(static_cast<int>(event)) + animation->getName(), animation);

        //General handlers
        eventEmitter_.emit(std::to_string(static_cast<int>(event)));
        eventEmitter_.emit(std::to_string(static_cast<int>(event)), animation);
    }

    void Animator::setCycleDirection() {
        if (currentAnimation_->getDirection() == Animation::Direction::Forward
            || currentAnimation_->getDirection() == Animation::Direction::Alternate_Forward)
        {
            cycleDirection_ = Direction::Forward;
        } else
            cycleDirection_ = Direction::Backward;
    }

    void Animator::reverseAlternateDirection() {
        cycleDirection_ = (cycleDirection_ == Direction::Forward) ? Direction::Backward : Direction::Forward;
    }

    void Animator::cycle(bool isAlternating) {
        /// @TODO - Reduce conditional branches in this function
        /// When I wrote this code I was very tired as it was very late in the am's
        /// My focus was on getting it to work so code quality out the window
        /// I intended on refactoring it later that day after getting some rest.
        /// Well it is true what they say, "A temporary solution tends to be a
        /// permanent one more often than not" - It's been 3 months :) as of this text

        // Handle end of sequence
        if ((cycleDirection_ == Direction::Backward && currentFrameIndex_ == 0)
            || (cycleDirection_ == Direction::Forward && currentFrameIndex_ == currentAnimation_->getFrameCount() - 1))
        {
            if (!currentAnimation_->isRepeating()) {
                if (isAlternating) {
                    if (cycleCount_ == 1) {
                        cycleCount_ = 0;
                        onComplete();
                        return;
                    } else {
                        reverseAlternateDirection();
                        cycleCount_++;
                    }
                } else {
                    onComplete();
                    return;
                }
            } else {
                // Update start delay
                if (!currentAnimation_->isStartDelayedOnce()) {
                    if (!isAlternating || (isAlternating && cycleCount_ == 1))
                        hasStarted_ = false;
                }

                // Update repeat counter
                if (!isAlternating || (isAlternating && cycleCount_ == 1)) {
                    if (!currentAnimation_->isLooped()) // Repeats a fixed number of times
                        currentAnimation_->setRepeatCount(currentAnimation_->getRepeatCount() - 1);
                }

                // Repeat animation
                if (isAlternating) {
                    if (cycleCount_ == 1) { // Completed two cycles
                        reverseAlternateDirection();
                        cycleCount_ = 0;
                        fireEvent(Event::AnimationRepeat, currentAnimation_);
                    } else { // Complete first cycle
                        reverseAlternateDirection();
                        cycleCount_++;
                    }
                } else {
                    if (currentFrameIndex_ == 0)
                        currentFrameIndex_ = currentAnimation_->getFrameCount() - 1;
                    else
                        currentFrameIndex_ = 0;

                    fireEvent(Event::AnimationRepeat, currentAnimation_);
                }
            }
        } else { // Advance frame
            if (cycleDirection_ == Direction::Forward)
                currentFrameIndex_++;
            else
                currentFrameIndex_--;
        }

        setCurrentFrame(*currentAnimation_->getFrameAt(currentFrameIndex_));
    }

    void Animator::onStart() {
        hasStarted_ = true;
        if (currentAnimation_->isTargetShownOnStart())
            (*target_).get().setVisible(true);

        resetCurrentFrame();
        fireEvent(Event::AnimationStart, currentAnimation_);
    }

    void Animator::onComplete() {
        setCurrentFrame(*currentAnimation_->getFrameAt(currentAnimation_->getCompletionFrameIndex()));

        if (currentAnimation_->isTargetHiddenOnCompletion())
            (*target_).get().setVisible(false);

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
        /// @see See cycle(bool). Code must come here after refactoring that function
    }

    void Animator::reverseFrame() {
        /// @See cycle(bool). Code must come here after refactoring that function
    }

    void Animator::setCurrentFrame(const AnimationFrame& frame) {
        currentAnimation_->setCurrentFrameIndex(currentFrameIndex_);
        auto& [leftPos, topPos, width, height] = frame.getSpritesheetRect();
        (*target_).get().setTextureRect(leftPos, topPos, width, height);
    }

    void Animator::resetCurrentFrame() {
        if (cycleDirection_ == Direction::Forward)
            currentFrameIndex_ = 0;
        else if (cycleDirection_ == Direction::Backward)
            currentFrameIndex_ = currentAnimation_->getFrameCount() - 1;
        else
            return;

        setCurrentFrame(*currentAnimation_->getFrameAt(currentFrameIndex_));
    }
}
