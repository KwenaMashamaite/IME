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

#include "IME/graphics/RenderTarget.h"
#include "IME/graphics/RenderTargetImpl.h"

namespace ime::priv {
    RenderTarget::RenderTarget() :
        pImpl_{std::make_unique<priv::RenderTargetImpl>()}
    {}

    void RenderTarget::create(const std::string& title, unsigned int width, unsigned int height, Uint32 style) {
        pImpl_->create(title, width, height, style);

        if (onCreate_)
            onCreate_();
    }

    void RenderTarget::onCreate(Callback<> callback) {
        onCreate_ = std::move(callback);
    }

    void RenderTarget::setIcon(const std::string &filename) {
        pImpl_->setIcon(filename);
    }

    bool RenderTarget::pollEvent(Event& event) {
        return pImpl_->pollEvent(event);
    }

    void RenderTarget::display() {
        pImpl_->display();
    }

    void RenderTarget::clear(Colour colour) {
        pImpl_->clear(colour);
    }

    const std::unique_ptr<priv::RenderTargetImpl> &RenderTarget::getImpl() const {
        return pImpl_;
    }

    void RenderTarget::draw(const Drawable &drawable) {
        drawable.draw(*this);
    }

    RenderTarget::~RenderTarget() = default;
}
