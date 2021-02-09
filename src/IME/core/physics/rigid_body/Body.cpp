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
#include "IME/utility/Helpers.h"
#include <box2d/b2_body.h>
#include <box2d/b2_world.h>

namespace ime {
    Body::Body(const BodyDefinition &definition, World::sharedPtr world) {
        auto b2Definition = new b2BodyDef();
        b2Definition->type = static_cast<b2BodyType>(definition.bodyType);
        b2Definition->position = {utility::pixelsToMetres(definition.position.x), utility::pixelsToMetres(definition.position.y)};
        b2Definition->angle = utility::degToRad(definition.angle);
        b2Definition->linearVelocity = {definition.linearVelocity.x, definition.linearVelocity.y};
        b2Definition->angularVelocity = definition.angularVelocity;
        b2Definition->linearDamping = definition.linearDamping;
        b2Definition->angularDamping = definition.angularDamping;
        b2Definition->allowSleep = definition.canSleep;
        b2Definition->awake = definition.isAwake;
        b2Definition->fixedRotation = definition.isFixedRotation;
        b2Definition->bullet = definition.isFastBody;
        b2Definition->enabled = definition.isEnabled;
        b2Definition->gravityScale = definition.gravityScale;

        world_ = world;
        userData_ = definition.userData;
        body_ = world_->getInternalWorld()->CreateBody(b2Definition);
        delete b2Definition;
        b2Definition = nullptr;
    }

    Fixture::sharedPtr Body::createFixture(const FixtureDefinition& definition) {
        if (world_ && !world_->isLocked()) {
            auto fixture = Fixture::sharedPtr(new Fixture(definition, shared_from_this()));
            fixtures_.push_back(fixture);
            return fixture;
        }
        return nullptr;
    }

    Fixture::sharedPtr Body::createFixture(const Collider* collider, float density) {
        if (world_ && !world_->isLocked()) {
            auto fixtureDef = FixtureDefinition();
            fixtureDef.collider = collider;
            fixtureDef.density = density;
            return createFixture(fixtureDef);
        }
        return nullptr;
    }

    void Body::destroyFixture(Fixture::sharedPtr fixture) {
        if (world_ && !world_->isLocked()) {
            if (auto [found, index] = utility::findIn(fixtures_, fixture); found) {
                body_->DestroyFixture(fixtures_[index]->fixture_);
                fixtures_.erase(fixtures_.begin() + index);
            }
        }
    }

    void Body::setTransform(const Transform& transform) {
        body_->SetTransform({utility::pixelsToMetres(transform.getPosition().x),
            utility::pixelsToMetres(transform.getPosition().y)},
            utility::degToRad(transform.getRotation()));
    }

    Transform Body::getTransform() const {
        auto transform = Transform();
        transform.setPosition(getPosition());
        transform.setRotation(getRotation());
        transform.setOrigin(getLocalCenter());
        transform.setScale(1.0f, 1.0f);

        return transform;
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
        body_->SetLinearVelocity({velocity.x, velocity.y});
    }

    Vector2f Body::getLinearVelocity() const {
        return {body_->GetLinearVelocity().x, body_->GetLinearVelocity().y};
    }

    void Body::setAngularVelocity(float omega) {
        body_->SetAngularVelocity(omega);
    }

    float Body::getAngularVelocity() const {
        return body_->GetAngularVelocity();
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

        return {utility::metresToPixels(worldVector.x),
                utility::metresToPixels(worldVector.y)};
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

        return {utility::metresToPixels(localVector.x),
                utility::metresToPixels(localVector.y)};
    }

    Vector2f Body::getLinearVelocityFromWorldPoint(Vector2f worldPoint) const {
        auto velocity = body_->GetLinearVelocityFromLocalPoint({utility::pixelsToMetres(worldPoint.x),
            utility::pixelsToMetres(worldPoint.y)});

        return {velocity.x, velocity.y};
    }

    Vector2f Body::getLinearVelocityFromLocalPoint(Vector2f localPoint) const {
        auto velocity = body_->GetLinearVelocityFromLocalPoint({utility::pixelsToMetres(localPoint.x),
            utility::pixelsToMetres(localPoint.y)});

        return {velocity.x, velocity.y};
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

    Body::WorldPtr Body::getWorld() {
        return world_;
    }

    const Body::WorldPtr &Body::getWorld() const {
        return world_;
    }

    PropertyContainer &Body::getUserData() {
        return userData_;
    }

    Body::~Body() {
        // We don't call delete because memory is deallocated by World
        // instance when it goes ot of scope
        body_ = nullptr;
    }
}