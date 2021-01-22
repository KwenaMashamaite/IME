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

namespace ime {
    Animation::Animation(const std::string& name, const std::string& spriteSheet,
         Time duration) :
         name_{name},
         spriteSheet_{spriteSheet},
         duration_{duration}
    {}

    std::string Animation::getSpriteSheet() const {
        return spriteSheet_;
    }

    void Animation::addFrames(Vector2i startPos, Vector2i frameSize,
        unsigned int numOfFrames, unsigned int spacing, Arrangement arrangement)
    {
        auto currentPosition = startPos;
        for (auto i = 0u; i < numOfFrames; ++i) {
            frames_.emplace_back(IntRect{currentPosition.x, currentPosition.y, frameSize.x, frameSize.y});
            if (arrangement == Arrangement::Horizontal)
                currentPosition.x += frameSize.x + spacing;
            else
                currentPosition.y += frameSize.y + spacing;
        }
    }

    void Animation::setLoop(bool isLooped) {
        isLooped_ = isLooped;
    }

    void Animation::setDuration(Time duration) {
        if (duration < Time::Zero)
            duration_ = Time::Zero;
        else
            duration_ = duration;
    }

    bool Animation::isLooped() const {
        return isLooped_;
    }

    Time Animation::getDuration() const {
        return duration_;
    }

    IntRect Animation::getFrameAt(unsigned int index) const {
        return frames_.at(index);
    }

    unsigned int Animation::getNumOfFrames() const {
        return frames_.size();
    }

    const std::string &Animation::getName() const {
        return name_;
    }

    void Animation::addFrames(const std::initializer_list<IntRect>& frames) {
        for (const auto& frame : frames)
            frames_.emplace_back(frame);
    }
}
