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

#include "IME/graphics/AnimatableSprite.h"
#include "IME/core/animation/Animator.h"

namespace ime {
    AnimatableSprite::AnimatableSprite() :
        animator_(std::make_shared<Animator>(*this))
    {}

    bool AnimatableSprite::addAnimation(std::shared_ptr<Animation> animation) {
        return animator_->addAnimation(std::move(animation));
    }

    std::shared_ptr<Animation> AnimatableSprite::getCurrentAnimation() const {
        return animator_->getCurrentAnimation();
    }

    void AnimatableSprite::updateAnimation(Time deltaTime) {
        animator_->update(deltaTime);
    }

    void AnimatableSprite::finishAnimation() {
        animator_->finishAnimation();
    }

    bool AnimatableSprite::switchAnimation(const std::string &name) {
        return animator_->switchAnimation(name);
    }

    int AnimatableSprite::onAnimationStart(const std::string &name, Callback<> callback) {
        return animator_->onAnimationStart(name, std::move(callback));
    }

    int AnimatableSprite::onAnimationFinish(const std::string &name, Callback<> callback) {
        return animator_->onAnimationFinish(name, std::move(callback));
    }

    bool AnimatableSprite::removeEventListener(const std::string &name,const std::string &onTrigger, int id) {
        return animator_->removeEventListener(name, onTrigger, id);
    }
}