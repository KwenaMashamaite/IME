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

#include "IME/core/game_object/GameObject.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/physics/World.h"

namespace ime {
    GameObject::GameObject(Scene& scene, Type type) :
        scene_{scene},
        type_{type},
        state_{-1},
        isActive_{true},
        isCollidable_{true},
        postStepId_{-1}
    {
        initEvents();
    }

    GameObject::GameObject(const GameObject &other) :
        Object(other),
        std::enable_shared_from_this<GameObject>(other),
        scene_{other.scene_},
        type_{other.type_},
        state_{other.state_},
        isActive_{other.isActive_},
        isCollidable_{other.isCollidable_},
        transform_{other.transform_},
        sprite_{other.sprite_},
        postStepId_{other.postStepId_}
    {
        initEvents();
        if (other.hasRigidBody())
            attachRigidBody(other.body_->copy());
    }

    GameObject &GameObject::operator=(const GameObject &other) {
        if (this != &other) {
            auto temp{other};
            Object::operator=(temp);
            std::enable_shared_from_this<GameObject>::operator=(temp);
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
        // We don't want to copy event listeners of the rhs object
        if (this != &rhs) {
            Object::operator=(std::move(rhs));
            std::enable_shared_from_this<GameObject>::operator=(rhs);
            swap(rhs);
        }

        return *this;
    }

    void GameObject::swap(GameObject &other) {
        std::swap(scene_, other.scene_);
        std::swap(type_, other.type_);
        std::swap(state_, other.state_);
        std::swap(isActive_, other.isActive_);
        std::swap(isCollidable_, other.isCollidable_);
        std::swap(transform_, other.transform_);
        std::swap(sprite_, other.sprite_);
        std::swap(body_, other.body_);
        std::swap(userData_, other.userData_);
    }

    GameObject::Ptr GameObject::create(Scene &scene, GameObject::Type type) {
        return std::make_shared<GameObject>(scene, type);
    }

    GameObject::Ptr GameObject::copy() const {
        return std::make_shared<GameObject>(*this);
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

    void GameObject::setCollidable(bool isCollidable) {
        if (isCollidable_ != isCollidable) {
            isCollidable_ = isCollidable;
            if (body_) {
                body_->forEachCollider([isCollidable](const Collider::Ptr& collider) {
                    if (isCollidable)
                        collider->resetCollisionFilterData();
                    else
                        collider->setEnable(false);
                });
            }

            emitChange(Property{"collidable", isCollidable_});
        }
    }

    bool GameObject::isActive() const {
        return isActive_;
    }

    bool GameObject::isCollidable() const {
        return isCollidable_;
    }

    PropertyContainer& GameObject::getUserData() {
        return userData_;
    }

    std::string GameObject::getClassName() const {
        return "GameObject";
    }

    std::string GameObject::getClassType() const {
        return "GameObject";
    }

    void GameObject::setType(GameObject::Type type) {
        type_ = type;
        emitChange(Property{"type", type_});
    }

    GameObject::Type GameObject::getType() const {
        return type_;
    }

    void GameObject::attachRigidBody(Body::Ptr body) {
        IME_ASSERT(body, "Invalid rigid body, cannot attach a nullptr to an entity")
        IME_ASSERT(!body_, "Entity already has a rigid body attached, remove it first before attaching another one")
        body_ = std::move(body);
        resetSpriteOrigin();
        body_->setPosition(transform_.getPosition());
        body_->setRotation(transform_.getRotation());

        emit("attachRigidBody");
    }

    Body::Ptr &GameObject::getRigidBody() {
        return body_;
    }

    const Body::Ptr &GameObject::getRigidBody() const {
        return body_;
    }

    void GameObject::removeRigidBody() {
        if (body_) {
            body_->getWorld()->destroyBody(body_);
            body_.reset();

            emit("removeRigidBody");
        }
    }

    void GameObject::onCollisionStart(Callback<GameObject::Ptr, GameObject::Ptr> callback) {
        onContactBegin_ = std::move(callback);
        emit("collisionStart");
    }

    void GameObject::onCollisionEnd(Callback<GameObject::Ptr, GameObject::Ptr> callback) {
        onContactEnd_ = std::move(callback);
        emit("collisionEnd");
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

    void GameObject::resetSpriteOrigin() {
        transform_.setOrigin(sprite_.getLocalBounds().width / 2.0f, sprite_.getLocalBounds().height / 2.0f);
    }

    Sprite &GameObject::getSprite() {
        return sprite_;
    }

    const Sprite &GameObject::getSprite() const {
        return sprite_;
    }

    void GameObject::update(Time deltaTime) {
        sprite_.updateAnimation(deltaTime);
    }

    void GameObject::emitCollisionEvent(const std::string &event, const GameObject::Ptr& other) {
        if (event == "contactBegin" && onContactBegin_)
            onContactBegin_(shared_from_this(), other);
        else if (event == "contactEnd" && onContactEnd_)
            onContactEnd_(shared_from_this(), other);
    }

    void GameObject::initEvents() {
        postStepId_ = scene_.get().on_("postStep", Callback<Time>([this](Time) {
            if (body_) {
                transform_.setPosition(body_->getPosition());
                transform_.setRotation(body_->getRotation());
            }
        }));

        scene_.get().onDestruction([this] {
            postStepId_ = -1;
        });

        transform_.onPropertyChange([this](const Property& property) {
            const auto& name = property.getName();
            if (name == "position") {
                sprite_.setPosition(transform_.getPosition());
                emitChange(Property{name, transform_.getPosition()});
            } else if (name == "origin") {
                sprite_.setOrigin(transform_.getOrigin());
                emitChange(Property{name, transform_.getOrigin()});
            } else if (name == "scale") {
                sprite_.setScale(transform_.getScale());
                emitChange(Property{name, transform_.getScale()});
            } else if (name == "rotation") {
                sprite_.setRotation(transform_.getRotation());
                emitChange(Property{name, transform_.getRotation()});
            }
        });
    }

    GameObject::~GameObject() {
        if (postStepId_ != -1)
            scene_.get().unsubscribe_("postStep", postStepId_);

        emit("destruction");
    }
}
