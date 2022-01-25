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

#include "IME/core/physics/rigid_body/RigidBody.h"
#include "IME/core/game_object/GameObject.h"
#include "IME/core/physics/rigid_body/PhysicsEngine.h"
#include "IME/utility/Helpers.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

namespace ime {
    RigidBody::RigidBody(PhysicsEngine* world, Type bodyType) :
        gameObject_{nullptr}
    {
        IME_ASSERT(world, "Cannot construct body from a nullptr")
        world_ = world;

        auto b2Definition = std::make_unique<b2BodyDef>();
        b2Definition->type = static_cast<b2BodyType>(bodyType);
        b2Definition->userData.pointer = getObjectId();

        // b2Body has a private destructor
        auto b2BodyDeleter = [](b2Body* body) {
            body->GetWorld()->DestroyBody(body);
        };

        body_ = std::unique_ptr<b2Body, std::function<void(b2Body*)>>(
            world_->getInternalWorld()->CreateBody(b2Definition.get()), std::move(b2BodyDeleter));
    }

    RigidBody::RigidBody(RigidBody&&) noexcept = default;
    RigidBody &RigidBody::operator=(RigidBody &&) noexcept = default;

    RigidBody::Ptr RigidBody::copy() const {
        // b2Body does not have any public constructors, so we use setters to simulate a copy
        RigidBody::Ptr body = world_->createBody(getType());
        body->setPosition(getPosition());
        body->setRotation(getRotation());
        body->setFixedRotation(isFixedRotation());
        body->setLinearVelocity(getLinearVelocity());
        body->setAngularVelocity(getAngularVelocity());
        body->setLinearDamping(getLinearDamping());
        body->setAngularDamping(getAngularDamping());
        body->setFastBody(isFastBody());
        body->setEnabled(isEnabled());
        body->setAwake(isAwake());
        body->setGravityScale(getGravityScale());
        body->setSleepingAllowed(isSleepingAllowed());
        body->setTag(getTag());

        for (const auto& [id, collider] : colliders_) {
            IME_UNUSED(id);
            body->attachCollider(collider->clone());
        }

        return body;
    }

    std::string RigidBody::getClassName() const {
        return "RigidBody";
    }

    Collider* RigidBody::attachCollider(Collider::Ptr collider) {
        IME_ASSERT(collider, "Cannot attach a nullptr to a rigid body")
        IME_ASSERT(!collider->isAttachedToBody(), "The collider is already attached to another rigid body: One body per collider")
        if (!world_->isLocked()) {
            collider->setBody(this);
            auto insertionPair = colliders_.insert({collider->getObjectId(), std::move(collider)}).first;
            emit("attachCollider");
            return insertionPair->second.get();
        } else {
            IME_PRINT_WARNING("Operation ignored: AttachCollider() called inside a world callback")
            return nullptr;
        }
    }

    Collider* RigidBody::getColliderById(unsigned int id) {
        return const_cast<Collider*>(std::as_const(*this).getColliderById(id));
    }

    const Collider* RigidBody::getColliderById(unsigned int id) const {
        if (utility::findIn(colliders_, id))
            return colliders_.at(static_cast<int>(id)).get();
        return nullptr;
    }

    void RigidBody::removeColliderWithId(unsigned int id) {
        if (!world_->isLocked()) {
            if (colliders_.find(static_cast<int>(id)) != colliders_.end()) {
                colliders_.erase(static_cast<int>(id));
                emit("removeCollider");
            }
        } else {
            IME_PRINT_WARNING("Operation ignored: removeColliderWithId() called inside a world callback")
        }
    }

    void RigidBody::setPosition(const Vector2f& position) {
        if (getPosition() == position)
            return;

        body_->SetTransform(
            {utility::pixelsToMetres(position.x), utility::pixelsToMetres(position.y)},
            body_->GetAngle());

        emitChange(Property{"position", position});
    }

    Vector2f RigidBody::getPosition() const {
        return utility::metresToPixels({body_->GetPosition().x, body_->GetPosition().y});
    }

    void RigidBody::setRotation(float angle) {
        if (isFixedRotation() || getRotation() == angle)
            return;

        body_->SetTransform(body_->GetTransform().p, utility::degToRad(angle));
        emitChange(Property{"rotation", angle});
    }

    float RigidBody::getRotation() const {
        return utility::radToDeg(body_->GetAngle());
    }

    Vector2f RigidBody::getWorldCenter() const {
        return utility::metresToPixels({body_->GetWorldCenter().x, body_->GetWorldCenter().y});
    }

    Vector2f RigidBody::getLocalCenter() const {
        return Vector2f{utility::metresToPixels(body_->GetLocalCenter().x),
                utility::metresToPixels(body_->GetLocalCenter().y)};
    }

    void RigidBody::setLinearVelocity(const Vector2f& velocity) {
        if (getLinearVelocity() == velocity)
            return;

        body_->SetLinearVelocity({utility::pixelsToMetres(velocity.x), utility::pixelsToMetres(velocity.y)});
        emitChange(Property{"linearVelocity", velocity});
    }

    Vector2f RigidBody::getLinearVelocity() const {
        return Vector2f{utility::metresToPixels(body_->GetLinearVelocity().x), utility::metresToPixels(body_->GetLinearVelocity().y)};
    }

    void RigidBody::setAngularVelocity(float degrees) {
        if (getAngularVelocity() == degrees)
            return;

        body_->SetAngularVelocity(utility::degToRad(degrees));
        emitChange(Property{"angularVelocity",  degrees});
    }

    float RigidBody::getAngularVelocity() const {
        return utility::radToDeg(body_->GetAngularVelocity());
    }

    void RigidBody::applyForce(const Vector2f& force, const Vector2f& point, bool wake) {
        body_->ApplyForce(b2Vec2{force.x, force.y},
            b2Vec2{utility::pixelsToMetres(point.x), utility::pixelsToMetres(point.y)},
            wake);
    }

    void RigidBody::applyForceToCenter(const Vector2f& force, bool wake) {
        body_->ApplyForceToCenter(b2Vec2{force.x, force.y}, wake);
    }

    void RigidBody::applyTorque(float torque, bool wake) {
        body_->ApplyTorque(torque, wake);
    }

    void RigidBody::applyLinearImpulse(const Vector2f& impulse, const Vector2f& point, bool wake) {
        body_->ApplyLinearImpulse(b2Vec2{impulse.x, impulse.y},
            b2Vec2{utility::pixelsToMetres(point.x), utility::pixelsToMetres(point.y)},
            wake);
    }

    void RigidBody::applyLinearImpulseToCenter(const Vector2f& impulse, bool wake) {
        body_->ApplyLinearImpulseToCenter(b2Vec2{impulse.x, impulse.y}, wake);
    }

    void RigidBody::applyAngularImpulse(float impulse, bool wake) {
        body_->ApplyAngularImpulse(impulse, wake);
    }

    float RigidBody::getMass() const {
        return body_->GetMass();
    }

    float RigidBody::getInertia() const {
        return body_->GetInertia();
    }

    Vector2f RigidBody::getWorldPoint(const Vector2f& localPoint) const {
        b2Vec2 worldPoint = body_->GetWorldPoint(b2Vec2{utility::pixelsToMetres(localPoint.x), utility::pixelsToMetres(localPoint.y)});

        return Vector2f{utility::metresToPixels(worldPoint.x), utility::metresToPixels(worldPoint.y)};
    }

    Vector2f RigidBody::getWorldRotation(const Vector2f& localVector) const {
        b2Vec2 worldVector = body_->GetWorldVector(b2Vec2{utility::pixelsToMetres(localVector.x), utility::pixelsToMetres(localVector.y)});

        return Vector2f{utility::radToDeg(worldVector.x), utility::radToDeg(worldVector.y)};
    }

    Vector2f RigidBody::getLocalPoint(const Vector2f& worldPoint) const {
        b2Vec2 localPoint = body_->GetLocalPoint(b2Vec2{utility::pixelsToMetres(worldPoint.x), utility::pixelsToMetres(worldPoint.y)});

        return Vector2f{utility::metresToPixels(localPoint.x), utility::metresToPixels(localPoint.y)};
    }

    Vector2f RigidBody::getLocalRotation(const Vector2f& worldVector) const {
        b2Vec2 localVector = body_->GetLocalVector(b2Vec2{utility::pixelsToMetres(worldVector.x), utility::pixelsToMetres(worldVector.y)});

        return Vector2f{utility::radToDeg(localVector.x), utility::radToDeg(localVector.y)};
    }

    Vector2f RigidBody::getLinearVelocityFromWorldPoint(const Vector2f& worldPoint) const {
        b2Vec2 velocity = body_->GetLinearVelocityFromLocalPoint(b2Vec2{utility::pixelsToMetres(worldPoint.x), utility::pixelsToMetres(worldPoint.y)});

        return Vector2f{utility::metresToPixels(velocity.x), utility::metresToPixels(velocity.y)};
    }

    Vector2f RigidBody::getLinearVelocityFromLocalPoint(const Vector2f& localPoint) const {
        b2Vec2 velocity = body_->GetLinearVelocityFromLocalPoint(b2Vec2{utility::pixelsToMetres(localPoint.x), utility::pixelsToMetres(localPoint.y)});

        return Vector2f{utility::metresToPixels(velocity.x), utility::metresToPixels(velocity.y)};
    }

    void RigidBody::setLinearDamping(float damping) {
        if (getLinearDamping() == damping)
            return;

        body_->SetLinearDamping(damping);
        emitChange(Property{"linearDamping", damping});
    }

    float RigidBody::getLinearDamping() const {
        return body_->GetLinearDamping();
    }

    void RigidBody::setAngularDamping(float damping) {
        body_->SetAngularDamping(damping);
        emitChange(Property{"angularDamping", damping});
    }

    float RigidBody::getAngularDamping() const {
        return body_->GetAngularDamping();
    }

    void RigidBody::setGravityScale(float scale) {
        if (getGravityScale() == scale)
            return;

        body_->SetGravityScale(scale);
        emitChange(Property{"gravityScale", scale});
    }

    float RigidBody::getGravityScale() const {
        return body_->GetGravityScale();
    }

    void RigidBody::setType(Type type) {
        if (getType() == type)
            return;

        if (world_->isLocked()) {
            IME_PRINT_WARNING("Operation ignored: setType() called inside a world callback")
            return;
        }

        body_->SetType(static_cast<b2BodyType>(type));
        emitChange(Property{"type", type});
    }

    RigidBody::Type RigidBody::getType() const {
        return static_cast<Type>(body_->GetType());
    }

    void RigidBody::setFastBody(bool fast) {
        if (isFastBody() == fast)
            return;

        body_->SetBullet(fast);
        emitChange(Property{"fastBody", fast});
    }

    bool RigidBody::isFastBody() const {
        return body_->IsBullet();
    }

    void RigidBody::setSleepingAllowed(bool sleeps) {
        if (isSleepingAllowed() == sleeps)
            return;

        body_->SetSleepingAllowed(sleeps);
        emitChange(Property{"sleepingAllowed", sleeps});
    }

    bool RigidBody::isSleepingAllowed() const {
        return body_->IsSleepingAllowed();
    }

    void RigidBody::setAwake(bool awake) {
        if (isAwake() == awake)
            return;

        body_->SetAwake(awake);
        emitChange(Property{"awake", awake});
    }

    bool RigidBody::isAwake() const {
        return body_->IsAwake();
    }

    void RigidBody::setEnabled(bool enable) {
        if (isEnabled() == enable)
            return;

        if (world_->isLocked()) {
            IME_PRINT_WARNING("Operation ignored: setEnabled() called inside a world callback")
            return;
        }

        body_->SetEnabled(enable);
        emitChange(Property{"enable", enable});
    }

    bool RigidBody::isEnabled() const {
        return body_->IsEnabled();
    }

    void RigidBody::setFixedRotation(bool rotate) {
        if (isFixedRotation() == rotate)
            return;

        body_->SetFixedRotation(rotate);
        emitChange(Property{"fixedRotation", rotate});
    }

    bool RigidBody::isFixedRotation() const {
        return body_->IsFixedRotation();
    }

    void RigidBody::setGameObject(GameObject* gameObject) {
        if (gameObject_ == gameObject)
            return;

        gameObject_ = gameObject;
        emitChange(Property{"gameObject", gameObject_});
    }

    GameObject* RigidBody::getGameObject() {
        return gameObject_;
    }

    const GameObject* RigidBody::getGameObject() const {
        return gameObject_;
    }

    PhysicsEngine* RigidBody::getWorld() {
        return world_;
    }

    const PhysicsEngine* RigidBody::getWorld() const {
        return world_;
    }

    PropertyContainer &RigidBody::getUserData() {
        return userData_;
    }

    void RigidBody::forEachCollider(const Callback<Collider*>& callback) const {
        std::for_each(colliders_.begin(), colliders_.end(), [&callback](auto& pair) {
            callback(pair.second.get());
        });
    }

    std::size_t RigidBody::getColliderCount() const {
        return colliders_.size();
    }

    std::unique_ptr<b2Body, std::function<void(b2Body*)>>& RigidBody::getInternalBody() {
        return body_;
    }

    const std::unique_ptr<b2Body, std::function<void(b2Body*)>>& RigidBody::getInternalBody() const {
        return body_;
    }

    RigidBody::~RigidBody() {
        emit("destruction");
        gameObject_ = nullptr;
    }
}