#include "IME/graphics/AnimatableSprite.h"
#include "IME/core/animation/Animator.h"

namespace IME::Graphics {
    AnimatableSprite::AnimatableSprite() : Sprite(), animator_(std::make_shared<Animator>(*this))
    {}

    bool AnimatableSprite::addAnimation(std::shared_ptr<Animation> animation) {
        return animator_->addAnimation(std::move(animation));
    }

    void AnimatableSprite::updateAnimation(float deltaTime) {
        animator_->update(deltaTime);
    }

    void AnimatableSprite::finishAnimation() {
        animator_->finishAnimation();
    }

    bool AnimatableSprite::changeAnimation(const std::string &name) {
        return animator_->changeAnimation(name);
    }

    int AnimatableSprite::onAnimationStart(const std::string &name, Callback<> callback) {
        return animator_->onAnimationFinish(name, std::move(callback));
    }

    int AnimatableSprite::onAnimationFinish(const std::string &name, Callback<> callback) {
        return animator_->onAnimationFinish(name, std::move(callback));
    }

    bool AnimatableSprite::removeEventListener(const std::string &name,const std::string &onTrigger, int id) {
        return animator_->removeEventListener(name, onTrigger, id);
    }
}