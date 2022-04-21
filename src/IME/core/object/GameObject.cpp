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

#include "IME/core/object/GameObject.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/physics/rigid_body/PhysicsEngine.h"
#include "IME/utility/Helpers.h"

namespace ime {
    GameObject::GameObject(Scene& scene) :
        scene_{scene},
        state_{-1},
        isActive_{true},
        postStepId_{-1},
        destructionId_{-1}
    {
        initEvents();
    }

    GameObject::GameObject(const GameObject &other) :
        Object(other),
        scene_{other.scene_},
        state_{other.state_},
        isActive_{other.isActive_},
        transform_{other.transform_},
        sprite_{other.sprite_},
        postStepId_{-1},
        destructionId_{-1}
    {
        initEvents();

        if (other.hasRigidBody())
            attachRigidBody(other.body_->copy());
    }

    GameObject &GameObject::operator=(const GameObject &other) {
        if (this != &other) {
            auto temp{other};
            Object::operator=(temp);
            swap(temp);
            initEvents();
        }

        return *this;
    }

    GameObject::GameObject(GameObject&& other) noexcept :
        scene_(other.scene_)
    {
        *this = std::move(other);
        initEvents();
    }

    GameObject &GameObject::operator=(GameObject&& rhs) noexcept {
        if (this != &rhs) {
            Object::operator=(std::move(rhs));
            swap(rhs);
        }

        return *this;
    }

    void GameObject::swap(GameObject &other) {
        std::swap(scene_, other.scene_);
        std::swap(state_, other.state_);
        std::swap(isActive_, other.isActive_);
        std::swap(transform_, other.transform_);
        std::swap(sprite_, other.sprite_);
        std::swap(body_, other.body_);
        std::swap(userData_, other.userData_);
        std::swap(postStepId_, other.postStepId_);
        std::swap(destructionId_, other.destructionId_);
    }

    GameObject::Ptr GameObject::create(Scene &scene) {
        return std::make_unique<GameObject>(scene);
    }

    GameObject::Ptr GameObject::copy() const {
        return std::make_unique<GameObject>(*this);
    }

    void GameObject::setState(int state) {
        if (state_ == state)
            return;

        state_ = state;
        emitChange(Property{"state", state_});
    }

    int GameObject::getState() const {
        return state_;
    }

    void GameObject::setActive(bool isActive) {
        if (isActive_ == isActive)
            return;

        isActive_ = isActive;

        if (body_)
            body_->setEnabled(isActive_);

        emitChange(Property{"active", isActive_});
    }

    bool GameObject::isActive() const {
        return isActive_;
    }

    PropertyContainer& GameObject::getUserData() {
        return userData_;
    }

    const PropertyContainer &GameObject::getUserData() const {
        return userData_;
    }

    std::string GameObject::getClassName() const {
        return "GameObject";
    }

    std::string GameObject::getClassType() const {
        return "GameObject";
    }

    void GameObject::attachRigidBody(RigidBody::Ptr body) {
        IME_ASSERT(body, "Invalid rigid body, cannot attach a nullptr to an entity")
        IME_ASSERT(!body_, "Game object already has a rigid body attached, remove it first before attaching another one")
        body_ = std::move(body);
        body_->setGameObject(this);
        resetSpriteOrigin();
        body_->setPosition(transform_.getPosition());
        body_->setRotation(transform_.getRotation());
    }

    RigidBody* GameObject::getRigidBody() {
        return body_.get();
    }

    const RigidBody* GameObject::getRigidBody() const {
        return body_.get();
    }

    void GameObject::removeRigidBody() {
        if (body_) {
            body_.reset();
        }
    }

    int GameObject::onRigidBodyCollisionStart(const CollisionCallback& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GameObject_contactBegin", callback, oneTime);
    }

    int GameObject::onRigidBodyCollisionEnd(const CollisionCallback& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GameObject_contactEnd", callback, oneTime);
    }

    int GameObject::onRigidBodyCollisionStay(const CollisionCallback &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "GameObject_contactStay", callback, oneTime);
    }

    bool GameObject::hasRigidBody() const {
        return body_ != nullptr;
    }

    Transform &GameObject::getTransform() {
        return transform_;
    }

    const Transform &GameObject::getTransform() const {
        return transform_;
    }

    Scene &GameObject::getScene() {
        return scene_;
    }

    const Scene &GameObject::getScene() const {
        return scene_;
    }

    void GameObject::resetSpriteOrigin() {
        transform_.setOrigin(sprite_.getLocalBounds().width / 2.0f, sprite_.getLocalBounds().height / 2.0f);
    }

    Sprite &GameObject::getSprite() {
        return sprite_;
    }

    const Sprite &GameObject::getSprite() const {
        return sprite_;
    }

    void GameObject::emitRigidBodyCollisionEvent(const std::string &event, GameObject* other) {
        IME_ASSERT(other, "Internal Error, cannot collide with nullptr")

        // Prevent self collisions
        if (this == other)
            return;

        eventEmitter_.emit("GameObject_" + event, this, other);
    }

    void GameObject::initEvents() {
        postStepId_ = scene_.get().on_("postStep", Callback<Time>([this](Time) {
            if (body_) {
                transform_.setPosition(body_->getPosition());
                transform_.setRotation(body_->getRotation());
            }
        }));

        destructionId_ = scene_.get().onDestruction([this] {
            postStepId_ = destructionId_ = -1;
        });

        transform_.onPropertyChange([this](const Property& property) {
            const auto& name = property.getName();
            if (name == "position") {
                if (body_)
                    body_->setPosition(transform_.getPosition());

                sprite_.setPosition(transform_.getPosition());
                emitChange(Property{name, transform_.getPosition()});
            } else if (name == "origin") {
                sprite_.setOrigin(transform_.getOrigin());
                emitChange(Property{name, transform_.getOrigin()});
            } else if (name == "scale") {
                sprite_.setScale(transform_.getScale());
                emitChange(Property{name, transform_.getScale()});
            } else if (name == "rotation") {
                if (body_)
                    body_->setRotation(transform_.getRotation());

                sprite_.setRotation(transform_.getRotation());
                emitChange(Property{name, transform_.getRotation()});
            }
        });
    }

    GameObject::~GameObject() {
        emitDestruction();
        
        if (postStepId_ != -1)
            scene_.get().unsubscribe_("postStep", postStepId_);

        if (destructionId_ != -1)
            scene_.get().removeEventListener(destructionId_);

        if (body_)
            body_->setGameObject(nullptr);
    }
}
