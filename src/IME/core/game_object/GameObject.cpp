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

#include "IME/core/game_object/GameObject.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/physics/rigid_body/PhysicsEngine.h"
#include "IME/utility/Helpers.h"
#include "IME/core/physics/grid/GridMover.h"

namespace ime {
    GameObject::GameObject(Scene& scene) :
        scene_{scene},
        state_{-1},
        isObstacle_{false},
        isActive_{true},
        postStepId_{-1},
        destructionId_{-1},
        collisionId_{0},
        gridMover_{nullptr}
    {
        initEvents();
    }

    GameObject::GameObject(const GameObject &other) :
        Object(other),
        scene_{other.scene_},
        state_{other.state_},
        isObstacle_{other.isObstacle_},
        isActive_{other.isActive_},
        transform_{other.transform_},
        sprite_{other.sprite_},
        postStepId_{-1},
        destructionId_{-1},
        emitter_{other.emitter_},
        collisionGroup_{other.collisionGroup_},
        collisionId_{other.collisionId_},
        gridMover_{nullptr}
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
        // We don't want to copy event listeners of the rhs object
        if (this != &rhs) {
            Object::operator=(std::move(rhs));
            swap(rhs);
            gridMover_ = nullptr;
        }

        return *this;
    }

    void GameObject::swap(GameObject &other) {
        std::swap(scene_, other.scene_);
        std::swap(state_, other.state_);
        std::swap(isObstacle_, other.isObstacle_);
        std::swap(isActive_, other.isActive_);
        std::swap(transform_, other.transform_);
        std::swap(sprite_, other.sprite_);
        std::swap(body_, other.body_);
        std::swap(userData_, other.userData_);
        std::swap(postStepId_, other.postStepId_);
        std::swap(emitter_, other.emitter_);
        std::swap(destructionId_, other.destructionId_);
        std::swap(collisionGroup_, other.collisionGroup_);
        std::swap(collisionId_, other.collisionId_);
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

    void GameObject::setCollisionId(int id) {
        if (collisionId_ == id)
            return;

        collisionId_ = id;
        emitChange(Property{"collisionId", collisionId_});
    }

    int GameObject::getCollisionId() const {
        return collisionId_;
    }

    void GameObject::setCollisionGroup(const std::string &name) {
        if (collisionGroup_ == name)
            return;

        collisionGroup_ = name;
        emitChange(Property{"collisionGroup", collisionGroup_});
    }

    const std::string &GameObject::getCollisionGroup() const {
        return collisionGroup_;
    }

    ExcludeList &GameObject::getCollisionExcludeList() {
        return excludeList_;
    }

    const ExcludeList &GameObject::getCollisionExcludeList() const {
        return excludeList_;
    }

    ExcludeList &GameObject::getObstacleCollisionFilter() {
        return obstacleColFilter_;
    }

    const ExcludeList &GameObject::getObstacleCollisionFilter() const {
        return obstacleColFilter_;
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

    void GameObject::setAsObstacle(bool isObstacle) {
        if (isObstacle_ == isObstacle)
            return;

        isObstacle_ = isObstacle;
        emitChange(Property{"asObstacle", isObstacle_});
    }

    bool GameObject::isObstacle() const {
        return isObstacle_;
    }

    void GameObject::attachRigidBody(RigidBody::Ptr body) {
        IME_ASSERT(body, "Invalid rigid body, cannot attach a nullptr to an entity")
        IME_ASSERT(!body_, "Game object already has a rigid body attached, remove it first before attaching another one")
        body_ = std::move(body);
        body_->setGameObject(this);
        resetSpriteOrigin();
        body_->setPosition(transform_.getPosition());
        body_->setRotation(transform_.getRotation());

        emit("attachRigidBody");
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
            emit("removeRigidBody");
        }
    }

    int GameObject::onCollision(const CollisionCallback& callback, bool oneTime) {
        return utility::addEventListener(emitter_, "collision", callback, oneTime);
    }

    bool GameObject::removeCollisionListener(int id) {
        return emitter_.removeEventListener("collision", id);
    }

    void GameObject::onCollisionStart(const CollisionCallback& callback) {
        onContactBegin_ = callback;
    }

    void GameObject::onCollisionEnd(const CollisionCallback& callback) {
        onContactEnd_ = callback;
    }

    void GameObject::onCollisionStay(const CollisionCallback &callback) {
        onContactStay_ = callback;
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

    GridMover *GameObject::getGridMover() {
        return gridMover_;
    }

    const GridMover *GameObject::getGridMover() const {
        return gridMover_;
    }

    void GameObject::setGridMover(GridMover *gridMover) {
        gridMover_ = gridMover;
    }

    void GameObject::emitCollisionEvent(const std::string &event, GameObject* other) {
        IME_ASSERT(other, "Internal Error, cannot collide with nullptr")

        // Prevent self collisions
        if (this == other)
            return;

        if (event == "contactBegin" && onContactBegin_)
            onContactBegin_(this, other);
        else if (event == "contactEnd" && onContactEnd_)
            onContactEnd_(this, other);
        else if (event == "contactStay" && onContactStay_)
            onContactStay_(this, other);
    }

    void GameObject::emitCollisionEvent(GameObject *other) {
        IME_ASSERT(other, "Internal Error, cannot collide with nullptr")

        // Prevent self collisions
        if (this == other)
            return;

        emitter_.emit("collision", this, other);
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
        if (postStepId_ != -1)
            scene_.get().unsubscribe_("postStep", postStepId_);

        if (destructionId_ != -1)
            scene_.get().removeDestructionListener(destructionId_);

        if (body_)
            body_->setGameObject(nullptr);

        emit("destruction");
    }
}
