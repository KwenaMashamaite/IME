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

#include "IME/core/physics/rigid_body/RigidBody.h"
#include "IME/core/game_object/GameObject.h"
#include "IME/core/physics/PhysicsWorld.h"
#include "IME/utility/Helpers.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

namespace ime {
    RigidBody::RigidBody(PhysicsWorld* world, Type bodyType) :
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
        auto body = world_->createBody(getType());

        // b2Body does not have any public constructors, so we use setters to simulate a copy
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

    void RigidBody::setPosition(Vector2f position) {
        body_->SetTransform(
            {utility::pixelsToMetres(position.x), utility::pixelsToMetres(position.y)},
            body_->GetAngle());
        emitChange(Property{"position", position});
    }

    Vector2f RigidBody::getPosition() const {
        return utility::metresToPixels({body_->GetPosition().x, body_->GetPosition().y});
    }

    void RigidBody::setRotation(float angle) {
        if (isFixedRotation())
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
        return {utility::metresToPixels(body_->GetLocalCenter().x),
                utility::metresToPixels(body_->GetLocalCenter().y)};
    }

    void RigidBody::setLinearVelocity(Vector2f velocity) {
        body_->SetLinearVelocity({utility::pixelsToMetres(velocity.x), utility::pixelsToMetres(velocity.y)});
        emitChange(Property{"linearVelocity", velocity});
    }

    Vector2f RigidBody::getLinearVelocity() const {
        return {utility::metresToPixels(body_->GetLinearVelocity().x), utility::metresToPixels(body_->GetLinearVelocity().y)};
    }

    void RigidBody::setAngularVelocity(float degrees) {
        body_->SetAngularVelocity(utility::degToRad(degrees));
        emitChange(Property{"angularVelocity",  degrees});
    }

    float RigidBody::getAngularVelocity() const {
        return utility::radToDeg(body_->GetAngularVelocity());
    }

    void RigidBody::applyForce(Vector2f force, Vector2f point, bool wake) {
        body_->ApplyForce({force.x, force.y},
            {utility::pixelsToMetres(point.x), utility::pixelsToMetres(point.y)},
            wake);
    }

    void RigidBody::applyForceToCenter(Vector2f force, bool wake) {
        body_->ApplyForceToCenter({force.x, force.y}, wake);
    }

    void RigidBody::applyTorque(float torque, bool wake) {
        body_->ApplyTorque(torque, wake);
    }

    void RigidBody::applyLinearImpulse(Vector2f impulse, Vector2f point, bool wake) {
        body_->ApplyLinearImpulse({impulse.x, impulse.y},
            {utility::pixelsToMetres(point.x), utility::pixelsToMetres(point.y)},
            wake);
    }

    void RigidBody::applyLinearImpulseToCenter(Vector2f impulse, bool wake) {
        body_->ApplyLinearImpulseToCenter({impulse.x, impulse.y}, wake);
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

    Vector2f RigidBody::getWorldPoint(Vector2f localPoint) const {
        auto worldPoint = body_->GetWorldPoint({utility::pixelsToMetres(localPoint.x),
            utility::pixelsToMetres(localPoint.y)});

        return {utility::metresToPixels(worldPoint.x),
                utility::metresToPixels(worldPoint.y)};
    }

    Vector2f RigidBody::getWorldRotation(Vector2f localVector) const {
        auto worldVector = body_->GetWorldVector({utility::pixelsToMetres(localVector.x),
            utility::pixelsToMetres(localVector.y)});

        return {utility::radToDeg(worldVector.x),
                utility::radToDeg(worldVector.y)};
    }

    Vector2f RigidBody::getLocalPoint(Vector2f worldPoint) const {
        auto localPoint = body_->GetLocalPoint({utility::pixelsToMetres(worldPoint.x),
            utility::pixelsToMetres(worldPoint.y)});

        return {utility::metresToPixels(localPoint.x),
                utility::metresToPixels(localPoint.y)};
    }

    Vector2f RigidBody::getLocalRotation(Vector2f worldVector) const {
        auto localVector = body_->GetLocalVector({utility::pixelsToMetres(worldVector.x),
            utility::pixelsToMetres(worldVector.y)});

        return {utility::radToDeg(localVector.x),
                utility::radToDeg(localVector.y)};
    }

    Vector2f RigidBody::getLinearVelocityFromWorldPoint(Vector2f worldPoint) const {
        auto velocity = body_->GetLinearVelocityFromLocalPoint({utility::pixelsToMetres(worldPoint.x),
            utility::pixelsToMetres(worldPoint.y)});

        return {utility::metresToPixels(velocity.x), utility::metresToPixels(velocity.y)};
    }

    Vector2f RigidBody::getLinearVelocityFromLocalPoint(Vector2f localPoint) const {
        auto velocity = body_->GetLinearVelocityFromLocalPoint({utility::pixelsToMetres(localPoint.x),
            utility::pixelsToMetres(localPoint.y)});

        return {utility::metresToPixels(velocity.x), utility::metresToPixels(velocity.y)};
    }

    void RigidBody::setLinearDamping(float damping) {
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
        body_->SetGravityScale(scale);
        emitChange(Property{"gravityScale", scale});
    }

    float RigidBody::getGravityScale() const {
        return body_->GetGravityScale();
    }

    void RigidBody::setType(Type type) {
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
        body_->SetBullet(fast);
        emitChange(Property{"fastBody", fast});
    }

    bool RigidBody::isFastBody() const {
        return body_->IsBullet();
    }

    void RigidBody::setSleepingAllowed(bool sleeps) {
        body_->SetSleepingAllowed(sleeps);
        emitChange(Property{"sleepingAllowed", sleeps});
    }

    bool RigidBody::isSleepingAllowed() const {
        return body_->IsSleepingAllowed();
    }

    void RigidBody::setAwake(bool awake) {
        body_->SetAwake(awake);
        emitChange(Property{"awake", awake});
    }

    bool RigidBody::isAwake() const {
        return body_->IsAwake();
    }

    void RigidBody::setEnabled(bool enable) {
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
        body_->SetFixedRotation(rotate);
        emitChange(Property{"fixedRotation", rotate});
    }

    bool RigidBody::isFixedRotation() const {
        return body_->IsFixedRotation();
    }

    void RigidBody::setGameObject(GameObject* gameObject) {
        gameObject_ = gameObject;
    }

    GameObject* RigidBody::getGameObject() {
        return gameObject_;
    }

    const GameObject* RigidBody::getGameObject() const {
        return gameObject_;
    }

    PhysicsWorld* RigidBody::getWorld() {
        return world_;
    }

    const PhysicsWorld* RigidBody::getWorld() const {
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