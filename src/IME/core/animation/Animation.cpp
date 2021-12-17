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

#include "IME/core/animation/Animation.h"
#include <iterator>
#include <cmath>

namespace ime {
    namespace {
        // If the frame rate or the duration of the animation is unspecified,
        // it is set to this value
        const auto defaultFrameRate = 24u;
    }

    Animation::Animation(const std::string& name, const SpriteSheet&  spriteSheet, const Time& duration) :
         name_{name},
         spriteSheet_{spriteSheet},
         duration_{duration},
         frameRate_{0},
         direction_{Direction::Forward},
         repeatCounter_{0},
         isShownOnStart_{true},
         isHiddenOnComplete_{false},
         isFrameResetOnStop_{true},
         isStartDelayedOnce_{false},
         completionFrame_{-1},
         timescale_{1.0f}
    {
        isDurationDerived_ = (duration == Time::Zero);
    }

    std::shared_ptr<Animation> Animation::create(const std::string &name,
        const SpriteSheet& spriteSheet, const Time& duration)
    {
        return std::make_shared<Animation>(name, spriteSheet, duration);
    }

    const SpriteSheet& Animation::getSpriteSheet() const {
        return spriteSheet_;
    }

    void Animation::setRepeatCount(int count) {
        if (count < 0 && count != -1)
            repeatCounter_ = 0;
        else
            repeatCounter_ = count;
    }

    int Animation::getRepeatCount() const {
        return repeatCounter_;
    }

    bool Animation::isRepeating() const {
        return repeatCounter_ > 0 || repeatCounter_ == -1;
    }

    void Animation::setLoop(bool loop) {
        if (loop)
            repeatCounter_ = -1;
        else
            repeatCounter_ = 0;
    }

    bool Animation::isLooped() const {
        return repeatCounter_ == -1;
    }

    void Animation::setDuration(const Time& duration) {
        if (duration <= Time::Zero) {
            isDurationDerived_ = true;
            setFrameRate(defaultFrameRate);
        } else {
            isDurationDerived_ = false;
            calculateFrameRate(duration, 0);
        }
    }

    const Time& Animation::getDuration() const {
        return duration_;
    }

    void Animation::setTimescale(float timescale) {
        if (timescale < 0.0f)
            timescale_ = 1.0f;
        else
            timescale_ = timescale;
    }

    float Animation::getTimescale() const {
        return timescale_;
    }

    void Animation::setFrameRate(unsigned int frameRate) {
        isDurationDerived_ = true;

        if (frameRate == 0)
            calculateFrameRate(Time::Zero, defaultFrameRate); // Reset to default frame rate
        else
            calculateFrameRate(Time::Zero, frameRate);
    }

    unsigned int Animation::getFrameRate() const {
        return frameRate_;
    }

    void Animation::setDirection(Animation::Direction direction) {
        direction_ = direction;
        if (direction_ == Direction::Alternate_Forward || direction == Direction::Reverse)
            finishOnFirstFrame();
    }

    Animation::Direction Animation::getDirection() const {
        return direction_;
    }

    const std::string &Animation::getName() const {
        return name_;
    }

    void Animation::setStartDelay(const Time& delay, bool oneTime) {
        startDelay_ = delay;
        isStartDelayedOnce_ = oneTime;
    }

    const Time& Animation::getStartDelay() const {
        return startDelay_;
    }

    bool Animation::isStartDelayed() const {
        return startDelay_ > Time::Zero;
    }

    bool Animation::isStartDelayedOnce() const {
        return isStartDelayedOnce_;
    }

    void Animation::showTargetOnStart(bool show) {
        isShownOnStart_ = show;
    }

    bool Animation::isTargetShownOnStart() const {
        return isShownOnStart_;
    }

    void Animation::hideTargetOnCompletion(bool hide) {
        isHiddenOnComplete_ = hide;
    }

    bool Animation::isTargetHiddenOnCompletion() const {
        return isHiddenOnComplete_;
    }

    void Animation::setCurrentFrameResetOnInterrupt(bool reset) {
        isFrameResetOnStop_ = reset;
    }

    bool Animation::isCurrentFrameResetOnInterrupt() const {
        return isFrameResetOnStop_;
    }

    void Animation::addFrames(const Index& startPos, unsigned int numOfFrames, FrameArrangement arrangement) {
        auto newFrames = std::vector<SpriteSheet::Frame>{};
        if (arrangement == FrameArrangement::Horizontal)
            newFrames = spriteSheet_.getFramesInRange(startPos, {startPos.row, (startPos.colm + static_cast<int>(numOfFrames)) - 1});
        else
            newFrames = spriteSheet_.getFramesInRange(startPos, {(startPos.row + static_cast<int>(numOfFrames)) - 1, startPos.colm});

        IME_ASSERT(!newFrames.empty(), "Failed to construct frames, either start position or number of frames is invalid")

        std::move(newFrames.begin(), newFrames.end(), std::back_inserter(frames_));
        updateIndexes();
        calculateFrameRate(duration_, isDurationDerived_ ? frameRate_ : 0);
    }

    void Animation::addFrame(const Index& index) {
        if (auto frame = spriteSheet_.getFrame(index); frame) {
            frames_.emplace_back(*frame);
            frames_.back().index_ = frames_.size() - 1;
            calculateFrameRate(duration_, isDurationDerived_ ? frameRate_ : 0);
        }
    }

    void Animation::insertFrameAt(unsigned int index, const Index& frameIndex) {
        if (index >= frames_.size())
            addFrame(frameIndex); //Add frame at the back instead of issuing error
        else if (auto frame = spriteSheet_.getFrame(frameIndex); frame) {
            frames_.insert(frames_.begin() + index, *frame);
            updateIndexes();
            calculateFrameRate(duration_, isDurationDerived_ ? frameRate_ : 0);
        }
    }

    std::optional<AnimationFrame> Animation::getFirstFrame() const {
        if (!frames_.empty())
            return frames_.front();
        return std::nullopt;
    }

    std::optional<AnimationFrame> Animation::getLastFrame() const {
        if (!frames_.empty())
            return frames_.back();
        return std::nullopt;
    }

    std::optional<AnimationFrame> Animation::getFrameAt(unsigned int index) const {
        if (index < frames_.size())
            return frames_.at(index);
        return std::nullopt;
    }

    const std::vector<AnimationFrame> &Animation::getAllFrames() const {
        return frames_;
    }

    unsigned int Animation::getFrameCount() const {
        return static_cast<unsigned int>(frames_.size());
    }

    const Time& Animation::getFrameTime() const {
        return frameTime_;
    }

    bool Animation::hasFrameAtIndex(unsigned int index) const {
        return frames_.size() > index;
    }

    void Animation::removeFirstFrame() {
        if (!frames_.empty()) {
            frames_.erase(frames_.begin());
            updateIndexes();
        }
    }

    void Animation::removeLastFrame() {
        if (!frames_.empty())
            frames_.pop_back();
    }

    void Animation::removeFrameAt(unsigned int index) {
        if (!frames_.empty() && index < frames_.size()) {
            frames_.erase(frames_.begin() + index);
            updateIndexes();
        }
    }

    void Animation::removeAll() {
        frames_.clear();
    }

    void Animation::finishOnFrame(int index) {
        if (hasFrameAtIndex(index))
            completionFrame_ = index;
    }

    void Animation::finishOnFirstFrame() {
        completionFrame_ = 0;
    }

    void Animation::finishOnLastFrame() {
        // We don't use frames_.size() - 1 here because frames may be added or
        // removed after this function is called
        completionFrame_ = -1;
    }

    unsigned int Animation::getCompletionFrameIndex() const {
        return completionFrame_ >= 0 ? completionFrame_ : static_cast<unsigned int>(frames_.size() - 1);
    }

    void Animation::updateIndexes() {
        for (unsigned int i = 0; i < frames_.size(); i++)
            frames_[i].index_ = i;
    }

    void Animation::calculateFrameRate(const Time& duration, unsigned int frameRate) {
        if (duration == Time::Zero && frameRate == 0) {
            frameRate_ = defaultFrameRate;
            duration_ = ime::seconds(static_cast<float>(getFrameCount()) / frameRate_);
        } else if (duration > Time::Zero && frameRate == 0) {
            duration_ = duration;

            float newFrameRate = getFrameCount() / duration.asSeconds();

            // Frames are counted per 1 second, so we only set the frame rate if
            // it is a whole number, otherwise it is set to zero so that the frame
            // time is derived from the duration instead of the frame rate.
            if (floorf(newFrameRate) == newFrameRate)
                frameRate_ = static_cast<int>(newFrameRate);
            else
                frameRate_ = 0;
        } else {
            frameRate_ = frameRate;
            duration_ = ime::seconds(static_cast<float>(getFrameCount()) / frameRate);
        }

        // A frame rate of zero implies that the same frame will be shown for more
        // than 1 second, therefore we derive the frame time from the duration instead
        frameTime_ = frameRate_ != 0 ? ime::seconds(1.0f / frameRate_) : ime::seconds(duration_.asSeconds() / getFrameCount());
    }
}
