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
#include "IME/graphics/Sprite.h"
#include "IME/core/resources/ResourceManager.h"
#include <iterator>
#include <cmath>

namespace ime {
    SpriteSheet::SpriteSheet(const std::string &sourceTexture, Vector2u frameSize,
            Vector2u spacing, UIntRect area) :
        SpriteImage(sourceTexture, area),
        frameSize_{frameSize},
        spacing_{spacing}
    {
        IME_ASSERT((frameSize.x >= 1 && frameSize.y >= 1), "The minimum size of a Spritesheet frame is 1x1")

        //Remove the spacing to get the actual number of columns and rows
        Vector2f numerator{getSize() - spacing_};
        Vector2f denominator{frameSize_ + spacing_};
        sizeInFrames_ = ime::Vector2u{static_cast<unsigned int>(std::round(numerator.x / denominator.x)),
                                      static_cast<unsigned int>(std::round(numerator.y / denominator.y))};

        auto currentPos = spacing_;
        for (auto i = 0u; i < sizeInFrames_.y; ++i) {
            for (auto j = 0u; j < sizeInFrames_.x; ++j) {
                frames_.insert({{static_cast<int>(i), static_cast<int>(j)},
                    {currentPos.x, currentPos.y, frameSize_.x, frameSize_.y}});
                currentPos.x += frameSize_.x + spacing_.x;
            }
            currentPos.x = spacing_.x;
            currentPos.y += frameSize_.y + spacing_.y;
        }
    }

    std::string SpriteSheet::getClassName() const {
        return "SpriteSheet";
    }

    Vector2u SpriteSheet::getFrameSize() const {
        return frameSize_;
    }

    Vector2u SpriteSheet::getSpaceBetweenFrames() const {
        return spacing_;
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

    std::vector<SpriteSheet::Frame> SpriteSheet::getFramesOnRow(unsigned int row) const {
        return getFramesInRange({static_cast<int>(row), 0},
             {static_cast<int>(row), static_cast<int>(getSizeInFrames().x - 1)});
    }

    std::vector<SpriteSheet::Frame> SpriteSheet::getFramesOnColumn(unsigned int column) const {
        return getFramesInRange({0, static_cast<int>(column)},
             {static_cast<int>(getSizeInFrames().y - 1), static_cast<int>(column)});
    }

    std::vector<SpriteSheet::Frame> SpriteSheet::getFramesInRange(Index start, Index end) const {
        auto frames = std::vector<SpriteSheet::Frame>{};
        if (hasFrame(start) && hasFrame(end)) {
            if (start.row == end.row) {
                for (auto colm = start.colm; colm <= end.colm; ++colm)
                    frames.push_back(frames_.at({ start.row, colm}));
            } else if (start.colm == end.colm) {
                for (auto row = start.row; row <= end.row; ++row)
                    frames.push_back(frames_.at({row, start.colm}));
            }
        }
        return frames;
    }

    std::vector<SpriteSheet::Frame> SpriteSheet::getAllFrames() const {
        auto frames = std::vector<Frame>{};
        for (auto row = 0u; row < sizeInFrames_.x; ++row) {
            auto framesOnRow = getFramesOnRow(row);
            std::move(framesOnRow.begin(), framesOnRow.end(), std::back_inserter(frames));
        }
        return frames;
    }

    Vector2u SpriteSheet::getSizeInFrames() const {
        return sizeInFrames_;
    }

    unsigned int SpriteSheet::getRowCount() const {
        return sizeInFrames_.y;
    }

    unsigned int SpriteSheet::getColumnCount() const {
        return sizeInFrames_.x;
    }

    Sprite SpriteSheet::getSprite(Index index) const {
        if (hasFrame(index))
            return Sprite(getTexture(), frames_.at(index));
        return Sprite();
    }

    Sprite SpriteSheet::getSprite(const std::string &alias) const {
        if (hasFrame(alias))
            return Sprite(getTexture(), frames_.at(aliases_.at(alias)));
        return Sprite();
    }

    std::vector<Sprite> SpriteSheet::getSpritesOnRow(unsigned int row) const {
        return getSpritesInRange({static_cast<int>(row), 0},
            {static_cast<int>(row), static_cast<int>(getSizeInFrames().x - 1)});
    }

    std::vector<Sprite> SpriteSheet::getSpritesOnColumn(unsigned int column) const {
        return getSpritesInRange({0, static_cast<int>(column)},
            {static_cast<int>(getSizeInFrames().y - 1), static_cast<int>(column)});
    }

    std::vector<Sprite> SpriteSheet::getSpritesInRange(Index start, Index end) const {
        auto sprites = std::vector<Sprite>{};
        if (hasFrame(start) && hasFrame(end)) {
            if (start.row == end.row) {
                for (auto colm = start.colm; colm <= end.colm; ++colm)
                    sprites.emplace_back(getTexture(), frames_.at({ start.row, colm}));
            } else if (start.colm == end.colm) {
                for (auto row = start.row; row <= end.row; ++row)
                    sprites.emplace_back(getTexture(), frames_.at({row, start.colm}));
            }
        }
        return sprites;
    }

    std::vector<Sprite> SpriteSheet::getAllSprites() const {
        auto sprites = std::vector<Sprite>{};
        for (auto row = 0u; row < sizeInFrames_.x; ++row) {
            auto spritesOnRow = getSpritesOnRow(row);
            std::move(spritesOnRow.begin(), spritesOnRow.end(), std::back_inserter(sprites));
        }
        return sprites;
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
