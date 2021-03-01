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

#include "IME/core/physics/rigid_body/Body.h"
#include "IME/core/physics/World.h"
#include "../../../utility/Helpers.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world.h>

namespace ime {
    Body::Body(const BodyDefinition &definition, World::Ptr world) {
        auto b2Definition = std::make_unique<b2BodyDef>();
        b2Definition->type = static_cast<b2BodyType>(definition.bodyType);
        b2Definition->position = {utility::pixelsToMetres(definition.position.x), utility::pixelsToMetres(definition.position.y)};
        b2Definition->angle = utility::degToRad(definition.angle);
        b2Definition->linearVelocity = {utility::pixelsToMetres(definition.linearVelocity.x), utility::pixelsToMetres(definition.linearVelocity.y)};
        b2Definition->angularVelocity = utility::degToRad(definition.angularVelocity);
        b2Definition->linearDamping = definition.linearDamping;
        b2Definition->angularDamping = definition.angularDamping;
        b2Definition->allowSleep = definition.canSleep;
        b2Definition->awake = definition.isAwake;
        b2Definition->fixedRotation = definition.isFixedRotation;
        b2Definition->bullet = definition.isFastBody;
        b2Definition->enabled = definition.isEnabled;
        b2Definition->gravityScale = definition.gravityScale;
        b2Definition->userData.pointer = getObjectId();

        world_ = world;
        userData_ = definition.userData;

        auto b2BodyDeleter = [this](b2Body* body) {
            if (body != nullptr) {
                body->GetWorld()->DestroyBody(body);
                getWorld()->removeBodyById(body->GetUserData().pointer);
                body = nullptr;
            }
        };

        body_ = std::unique_ptr<b2Body, std::function<void(b2Body*)>>(
            world_->getInternalWorld()->CreateBody(b2Definition.get()), std::move(b2BodyDeleter));
    }

    std::string Body::getClassName() const {
        return "Body";
    }

    void Body::attachCollider(Collider::Ptr collider) {
        IME_ASSERT(collider, "Cannot attach a nullptr to a rigid body");
        IME_ASSERT(!collider->getBody(), "The collider is already attached to another rigid body: One body per collider");
        if (!world_->isLocked()) {
            collider->setBody(shared_from_this());
            colliders_.insert({collider->getObjectId(), collider});
        } else
            IME_PRINT_WARNING("Operation ignored: AttachCollider() called inside a world callback");
    }

    Collider::Ptr Body::getColliderById(unsigned int id) {
        if (utility::findIn(colliders_, id))
            return colliders_.at(id);
        return nullptr;
    }

    void Body::removeColliderWithId(unsigned int id) {
        if (!world_->isLocked()) {
            if (colliders_.find(id) != colliders_.end()) {
                body_->DestroyFixture(colliders_[id]->fixture_.get());
                colliders_.erase(id);
            }
        } else
            IME_PRINT_WARNING("Operation ignored: removeColliderWithId() called inside a world callback");
    }

    void Body::removeCollider(Collider::Ptr collider) {
        IME_ASSERT(collider, "RemoveCollider() called with a nullptr");
        if (!world_->isLocked()) {
            if (utility::findIn(colliders_, collider->getObjectId())) {
                body_->DestroyFixture(colliders_[collider->getObjectId()]->fixture_.get());
                colliders_.erase(collider->getObjectId());
            }
        } else
            IME_PRINT_WARNING("Operation ignored: removeCollider() called inside a world callback");
    }

    void Body::setPosition(Vector2f position) {
        body_->SetTransform(
            {utility::pixelsToMetres(position.x), utility::pixelsToMetres(position.y)},
            body_->GetAngle());
    }

    Vector2f Body::getPosition() const {
        return utility::metresToPixels({body_->GetPosition().x, body_->GetPosition().y});
    }

    void Body::setRotation(float angle) {
        body_->SetTransform(body_->GetTransform().p, utility::degToRad(angle));
    }

    float Body::getRotation() const {
        return utility::radToDeg(body_->GetAngle());
    }

    Vector2f Body::getWorldCenter() const {
        return utility::metresToPixels({body_->GetWorldCenter().x, body_->GetWorldCenter().y});
    }

    Vector2f Body::getLocalCenter() const {
        return {utility::metresToPixels(body_->GetLocalCenter().x),
                utility::metresToPixels(body_->GetLocalCenter().y)};
    }

    void Body::setLinearVelocity(Vector2f velocity) {
        body_->SetLinearVelocity({utility::pixelsToMetres(velocity.x), utility::pixelsToMetres(velocity.y)});
    }

    Vector2f Body::getLinearVelocity() const {
        return {utility::metresToPixels(body_->GetLinearVelocity().x), utility::metresToPixels(body_->GetLinearVelocity().y)};
    }

    void Body::setAngularVelocity(float degrees) {
        body_->SetAngularVelocity(utility::degToRad(degrees));
    }

    float Body::getAngularVelocity() const {
        return utility::radToDeg(body_->GetAngularVelocity());
    }

    void Body::applyForce(Vector2f force, Vector2f point, bool wake) {
        body_->ApplyForce({force.x, force.y},
            {utility::pixelsToMetres(point.x), utility::pixelsToMetres(point.y)},
            wake);
    }

    void Body::applyForceToCenter(Vector2f force, bool wake) {
        body_->ApplyForceToCenter({force.x, force.y}, wake);
    }

    void Body::applyTorque(float torque, bool wake) {
        body_->ApplyTorque(torque, wake);
    }

    void Body::applyLinearImpulse(Vector2f impulse, Vector2f point, bool wake) {
        body_->ApplyLinearImpulse({impulse.x, impulse.y},
            {utility::pixelsToMetres(point.x), utility::pixelsToMetres(point.y)},
            wake);
    }

    void Body::applyLinearImpulseToCenter(Vector2f impulse, bool wake) {
        body_->ApplyLinearImpulseToCenter({impulse.x, impulse.y}, wake);
    }

    void Body::applyAngularImpulse(float impulse, bool wake) {
        body_->ApplyAngularImpulse(impulse, wake);
    }

    float Body::getMass() const {
        return body_->GetMass();
    }

    float Body::getInertia() const {
        return body_->GetInertia();
    }

    Vector2f Body::getWorldPoint(Vector2f localPoint) const {
        auto worldPoint = body_->GetWorldPoint({utility::pixelsToMetres(localPoint.x),
            utility::pixelsToMetres(localPoint.y)});

        return {utility::metresToPixels(worldPoint.x),
                utility::metresToPixels(worldPoint.y)};
    }

    Vector2f Body::getWorldRotation(Vector2f localVector) const {
        auto worldVector = body_->GetWorldVector({utility::pixelsToMetres(localVector.x),
            utility::pixelsToMetres(localVector.y)});

        return {utility::radToDeg(worldVector.x),
                utility::radToDeg(worldVector.y)};
    }

    Vector2f Body::getLocalPoint(Vector2f worldPoint) const {
        auto localPoint = body_->GetLocalPoint({utility::pixelsToMetres(worldPoint.x),
            utility::pixelsToMetres(worldPoint.y)});

        return {utility::metresToPixels(localPoint.x),
                utility::metresToPixels(localPoint.y)};
    }

    Vector2f Body::getLocalRotation(Vector2f worldVector) const {
        auto localVector = body_->GetLocalVector({utility::pixelsToMetres(worldVector.x),
            utility::pixelsToMetres(worldVector.y)});

        return {utility::radToDeg(localVector.x),
                utility::radToDeg(localVector.y)};
    }

    Vector2f Body::getLinearVelocityFromWorldPoint(Vector2f worldPoint) const {
        auto velocity = body_->GetLinearVelocityFromLocalPoint({utility::pixelsToMetres(worldPoint.x),
            utility::pixelsToMetres(worldPoint.y)});

        return {utility::metresToPixels(velocity.x), utility::metresToPixels(velocity.y)};
    }

    Vector2f Body::getLinearVelocityFromLocalPoint(Vector2f localPoint) const {
        auto velocity = body_->GetLinearVelocityFromLocalPoint({utility::pixelsToMetres(localPoint.x),
            utility::pixelsToMetres(localPoint.y)});

        return {utility::metresToPixels(velocity.x), utility::metresToPixels(velocity.y)};
    }

    void Body::setLinearDamping(float damping) {
        body_->SetLinearDamping(damping);
    }

    float Body::getLinearDamping() const {
        return body_->GetLinearDamping();
    }

    void Body::setAngularDamping(float damping) {
        body_->SetAngularDamping(damping);
    }

    float Body::getAngularDamping() const {
        return body_->GetAngularDamping();
    }

    void Body::setGravityScale(float scale) {
        body_->SetGravityScale(scale);
    }

    float Body::getGravityScale() const {
        return body_->GetGravityScale();
    }

    void Body::setType(BodyType type) {
        if (world_->isLocked()) {
            IME_PRINT_WARNING("Operation ignored: setType() called inside a world callback");
            return;
        }

        body_->SetType(static_cast<b2BodyType>(type));
    }

    BodyType Body::getType() const {
        return static_cast<BodyType>(body_->GetType());
    }

    void Body::setFastBody(bool fast) {
        body_->SetBullet(fast);
    }

    bool Body::isFastBody() const {
        return body_->IsBullet();
    }

    void Body::setSleeps(bool sleeps) {
        body_->SetSleepingAllowed(sleeps);
    }

    bool Body::sleeps() const {
        return body_->IsSleepingAllowed();
    }

    void Body::setAwake(bool awake) {
        body_->SetAwake(awake);
    }

    bool Body::isAwake() const {
        return body_->IsAwake();
    }

    void Body::setEnabled(bool enable) {
        if (world_->isLocked()) {
            IME_PRINT_WARNING("Operation ignored: setEnabled() called inside a world callback");
            return;
        }

        body_->SetEnabled(enable);
    }

    bool Body::isEnabled() const {
        return body_->IsEnabled();
    }

    void Body::setFixedRotation(bool rotate) {
        body_->SetFixedRotation(rotate);
    }

    bool Body::isFixedRotation() const {
        return body_->IsFixedRotation();
    }

    std::shared_ptr<GameObject> Body::getGameObject() {
        return gameObject_;
    }

    std::shared_ptr<GameObject> Body::getGameObject() const {
        return gameObject_;
    }

    Body::WorldPtr Body::getWorld() {
        return world_;
    }

    const Body::WorldPtr &Body::getWorld() const {
        return world_;
    }

    PropertyContainer &Body::getUserData() {
        return userData_;
    }

    void Body::forEachCollider(std::function<void(Collider::Ptr)> callback) {
        std::for_each(colliders_.begin(), colliders_.end(), [&callback](auto pair) {
            callback(pair.second);
        });
    }

    void Body::onCollisionStart(Callback<Body::Ptr, Body::Ptr> callback) {
        onContactBegin_ = std::move(callback);
    }

    void Body::onCollisionEnd(Callback<Body::Ptr, Body::Ptr> callback) {
        onContactEnd_ = std::move(callback);
    }

    void Body::emitCollisionEvent(const std::string &event, Body::Ptr other) {
        if (event == "contactBegin" && onContactBegin_)
            onContactBegin_(shared_from_this(), other);
        else if (event == "contactEnd" && onContactEnd_)
            onContactEnd_(shared_from_this(), other);
    }

    std::unique_ptr<b2Body, std::function<void(b2Body*)>>& Body::getInternalBody() {
        return body_;
    }

    const std::unique_ptr<b2Body, std::function<void(b2Body*)>>& Body::getInternalBody() const {
        return body_;
    }
}