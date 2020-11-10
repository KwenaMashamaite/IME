////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

namespace IME{
    Animation::Animation(const std::string& name, const std::string& spriteSheetFilename,
         float duration) : name_(name), spriteSheet_(spriteSheetFilename), duration_(duration)
    {}

    std::string Animation::getSpriteSheet() const {
        return spriteSheet_;
    }

    void Animation::addFrames(Position startPos, Dimensions frameSize,
        unsigned int numOfFrames, unsigned int spacing, Arrangement arrangement)
    {
        auto currentPosition = startPos;
        for (auto i = 0u; i < numOfFrames; ++i) {
            addFrame({currentPosition, frameSize});
            if (arrangement == Arrangement::Horizontal)
                currentPosition.x += frameSize.width + spacing;
            else
                currentPosition.y += frameSize.height + spacing;
        }
    }

    void Animation::setLoop(bool isLooped) {
        isLooped_ = isLooped;
    }

    void Animation::setDuration(float duration) {
        if (duration < 0.0f)
            duration_ = 0.0f;
        else
            duration_ = duration;
    }

    void Animation::adjustDuration(float offset) {
        setDuration(getDuration() + offset);
    }

    bool Animation::isLooped() const {
        return isLooped_;
    }

    void Animation::addFrame(Frame frame) {
        auto [position, frameSize] = frame;
        frames_.emplace_back(position.x, position.y, frameSize.width, frameSize.height);
    }

    float Animation::getDuration() const {
        return duration_;
    }

    sf::IntRect Animation::getFrameAt(unsigned int index) const {
        return frames_.at(index);
    }

    unsigned int Animation::getNumOfFrames() const {
        return frames_.size();
    }

    const std::string &Animation::getName() const {
        return name_;
    }

    Dimensions Animation::getFrameSizeAt(unsigned int index) const {
        return {static_cast<float>(frames_.at(index).width),
                static_cast<float>(frames_.at(index).height)};
    }

    void Animation::addFrames(const std::initializer_list<Frame>& frames) {
        for (const auto& frame : frames)
            addFrame(frame);
    }
}
