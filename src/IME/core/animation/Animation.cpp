#include "IME/core/animation/Animation.h"

namespace IME{
    Animation::Animation(const std::string& name,
            const std::string& spriteSheetFilename,
            Dimensions frameSize, Position startPos,
            unsigned int numOfFrames,
            float duration) : name_(name), spriteSheet_(spriteSheetFilename),
            frameSize_(frameSize), duration_(duration), isLooped_(false)
    {
        createFrames(numOfFrames, startPos, frameSize);
    }

    std::string Animation::getSpriteSheet() const {
        return spriteSheet_;
    }

    void Animation::setLoop(bool isLooped) {
        isLooped_ = isLooped;
    }

    bool Animation::isLooped() const {
        return isLooped_;
    }

    void Animation::createFrames(unsigned int numOfFrames, Position startingPos, Dimensions frameSize) {
        auto currentPosition = startingPos;
        for (auto i = 0u; i < numOfFrames; ++i){
            frames_.emplace_back(
                currentPosition.x,
                currentPosition.y,
                frameSize.width,
                frameSize.height
            );
            currentPosition.x += frameSize.width;
        }
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

    Dimensions Animation::getFrameSize() const {
        return frameSize_;
    }
}
