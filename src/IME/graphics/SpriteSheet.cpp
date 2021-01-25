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

#include "IME/graphics/SpriteSheet.h"
#include "IME/core/managers/ResourceManager.h"

namespace ime {
    SpriteSheet::SpriteSheet(const std::string &texture, Vector2u frameSize, Vector2u spacing) :
        filename_{texture},
        frameSize_{frameSize},
        spacing_{spacing}
    {}

    void SpriteSheet::computeDimensions(UIntRect area) {
        offset_ = {0, 0};
        auto texture = ResourceManager::getInstance()->getTexture(filename_);
        if (area.width != 0 && area.height != 0) { // Create spritesheet from sub-rectangle of the spritesheet image
            auto image = ResourceManager::getInstance()->getImage(filename_);
            auto sfArea = sf::IntRect {
                static_cast<int>(area.left), static_cast<int>(area.top),
                static_cast<int>(area.width),static_cast<int>(area.height)
            };

            if(texture.loadFromImage(image, sfArea)) {
                offset_.x = area.left;
                offset_.y = area.top;
            }
        }

        sizeInPixels_ = Vector2u{texture.getSize().x, texture.getSize().y};

        //At this point, the size in frames includes the spacing between frames which may
        //result in the wrong number of rows and columns. We assign it here so that we can
        //know how many spaces should be removed in the statements below
        sizeInFrames_ = {sizeInPixels_.x / frameSize_.x, sizeInPixels_.y / frameSize_.y};

        //Remove the spacing to get the actual number of columns and rows
        auto sizeInPixelsWithoutSpacing = Vector2u{};
        sizeInPixelsWithoutSpacing.x = sizeInPixels_.x - (sizeInFrames_.x * spacing_.x);
        sizeInPixelsWithoutSpacing.y = sizeInPixels_.y - (sizeInFrames_.y * spacing_.y);
        sizeInFrames_ = {sizeInPixelsWithoutSpacing.x / frameSize_.x, sizeInPixelsWithoutSpacing.y / frameSize_.y};
    }

    void SpriteSheet::create(UIntRect area) {
        computeDimensions(area);

        auto currentPos = spacing_;
        for (auto i = 0u; i < sizeInFrames_.y; ++i) {
            for (auto j = 0u; j < sizeInFrames_.x; ++j) {
                frames_.insert({{static_cast<int>(i), static_cast<int>(j)}, {currentPos.x, currentPos.y, frameSize_.x, frameSize_.y}});
                currentPos.x += frameSize_.x + spacing_.x;
            }
            currentPos.x = spacing_.x;
            currentPos.y += frameSize_.y + spacing_.y;
        }
    }

    Vector2u SpriteSheet::getFrameSize() const {
        return frameSize_;
    }

    std::size_t SpriteSheet::getFramesCount() const {
        return frames_.size();
    }

    std::optional<SpriteSheet::Frame> SpriteSheet::getFrame(Index index) const {
        if (hasFrame(index))
            return frames_.at(index);
        return std::nullopt;
    }

    std::optional<SpriteSheet::Frame> SpriteSheet::getFrame(const std::string &alias) const {
        if (hasFrame(alias))
            return frames_.at(aliases_.at(alias));
        return std::nullopt;
    }

    Vector2u SpriteSheet::getSize() const {
        return sizeInPixels_;
    }

    unsigned int SpriteSheet::getWidth() const {
        return sizeInPixels_.x;
    }

    unsigned int SpriteSheet::getHeight() const {
        return sizeInPixels_.y;
    }

    Vector2u SpriteSheet::getSizeInFrames() const {
        return sizeInFrames_;
    }

    unsigned int SpriteSheet::getNumberOfRows() const {
        return sizeInFrames_.y;
    }

    unsigned int SpriteSheet::getNumberOfColumns() const {
        return sizeInFrames_.x;
    }

    Sprite SpriteSheet::getSprite(Index index) {
        if (hasFrame(index)) {
            auto frame = frames_.at(index);
            auto sprite = Sprite();
            sprite.setTexture(filename_);
            sprite.setTextureRect(frame.left + offset_.x, frame.top + offset_.y, frame.width, frame.height);
            return sprite;
        }
        return Sprite();
    }

    Sprite SpriteSheet::getSprite(const std::string &alias) {
        if (hasFrame(alias))
            return getSprite(aliases_[alias]);
        return Sprite();
    }

    const std::string &SpriteSheet::getTextureFilename() const {
        return filename_;
    }

    bool SpriteSheet::hasFrame(Index index) const {
        return frames_.find(index) != frames_.end();
    }

    bool SpriteSheet::hasFrame(const std::string &alias) const {
        return aliases_.find(alias) != aliases_.end();
    }

    bool SpriteSheet::assignAlias(Index index, const std::string &alias) {
        if (hasFrame(index))
            return aliases_.insert({alias, index}).second;
        return false;
    }
}
