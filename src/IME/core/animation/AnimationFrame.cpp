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

#include "IME/core/animation/AnimationFrame.h"

namespace ime {
    AnimationFrame::AnimationFrame(unsigned int rectLeft, unsigned int rectTop, unsigned int rectWidth, unsigned int rectHeight) :
        rect_{rectLeft, rectTop, rectWidth, rectHeight},
        index_{0},
        isCurrent_{false}
    {}

    AnimationFrame::AnimationFrame(const UIntRect& rect) :
        AnimationFrame{rect.left, rect.top, rect.width, rect.height}
    {}

    const UIntRect& AnimationFrame::getSpritesheetRect() const {
        return rect_;
    }

    bool AnimationFrame::isCurrent() const {
        return isCurrent_;
    }

    unsigned int AnimationFrame::getIndex() const {
        return index_;
    }
}
