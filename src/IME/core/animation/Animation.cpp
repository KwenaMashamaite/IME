#include "IME/core/animation/Animation.h"

namespace IME{
    Animation::Animation(const std::string& name, const std::string& spriteSheetFilename,
         float duration) : name_(name), spriteSheet_(spriteSheetFilename), duration_(duration)
    {}

    std::string Animation::getSpriteSheet() const {
        return spriteSheet_;
    }

    void Animation::addFrames(Position startPos, Dimensions frameSize,
        unsigned int numOfFrames, Arrangement arrangement)
    {
        auto currentPosition = startPos;
        for (auto i = 0u; i < numOfFrames; ++i) {
            addFrame({currentPosition, frameSize});
            if (arrangement == Arrangement::Horizontal)
                currentPosition.x += frameSize.width;
            else
                currentPosition.y += frameSize.height;
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
