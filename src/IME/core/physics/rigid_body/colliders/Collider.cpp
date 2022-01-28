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

#include "IME/core/physics/rigid_body/colliders/Collider.h"
#include "IME/core/physics/rigid_body/RigidBody.h"
#include "IME/core/object/GameObject.h"
#include "IME/utility/Helpers.h"
#include <box2d/b2_fixture.h>

namespace ime {
    Collider::Collider(Collider::Type type) :
        type_{type},
        body_{nullptr},
        prevCollisionBitMask_{filterData_.collisionBitMask},
        hasRigidBody_{false}
    {}

    Collider::Collider(const Collider& other) :
        Object(other),
        type_{other.type_},
        body_{nullptr},
        filterData_{other.filterData_},
        prevCollisionBitMask_{other.prevCollisionBitMask_},
        hasRigidBody_{false}
    {
        // Other member data are initialized when the collider is attached
        // to a rigid body because b2Fixture is not copy constructable
    }

    Collider &Collider::operator=(const Collider& rhs) {
        if (this != &rhs) {
            Object::operator=(rhs);
            type_ = rhs.type_;
            filterData_ = rhs.filterData_;
            prevCollisionBitMask_ = rhs.prevCollisionBitMask_;
            body_ = nullptr;
            hasRigidBody_ = false;

            // Other member data are initialized when the collider is attached
            // to a rigid body because b2Fixture is not copy assignable
        }

        return *this;
    }

    Collider::Collider(Collider &&) noexcept = default;
    Collider &Collider::operator=(Collider &&) noexcept = default;

    std::string Collider::getClassType() const {
        return "Collider";
    }

    Collider::Type Collider::getType() const {
        return type_;
    }

    void Collider::setBody(RigidBody* body) {
        if (body && body_ == body)
            return;

        IME_ASSERT(body, "Body must not be a nullptr")
        auto b2FixtureDefinition = std::make_unique<b2FixtureDef>();
        b2FixtureDefinition->shape = &getInternalShape();
        b2FixtureDefinition->density = 1.0f;
        b2FixtureDefinition->userData.pointer = reinterpret_cast<uintptr_t>(this);

        auto b2FixtureDeleter = [](b2Fixture*) {
            // The b2Fixture is destroyed in the destruction listener of body_
            // because it's only created when the collider is attached to a
            // body. Without this empty custom deleter, the application crashes
            // and the reason is unknown
        };

        body->onDestruction([this] {
            body_->getInternalBody()->DestroyFixture(fixture_.get());
            fixture_ = nullptr;
        });

        fixture_ = std::unique_ptr<b2Fixture, std::function<void(b2Fixture*)>>(
            body->getInternalBody()->CreateFixture(b2FixtureDefinition.get()), std::move(b2FixtureDeleter));

        body_ = body;
        hasRigidBody_ = true;

        emitChange(Property{"body", body_});
    }

    RigidBody* Collider::getBody() {
        return body_;
    }

    const RigidBody* Collider::getBody() const {
        return body_;
    }

    void Collider::setSensor(bool sensor) {
        if (isSensor() == sensor)
            return;

        fixture_->SetSensor(sensor);
        emitChange(Property{"sensor", sensor});
    }

    bool Collider::isSensor() const {
        return fixture_->IsSensor();
    }

    void Collider::setCollisionFilter(const CollisionFilterData& filterData) {
        filterData_ = filterData;
        updateCollisionFilter();
        emitChange(Property{"collisionFilter", filterData});
    }

    const CollisionFilterData& Collider::getCollisionFilterData() const {
        return filterData_;
    }

    void Collider::resetCollisionFilterData() {
        filterData_ = CollisionFilterData();
        updateCollisionFilter();
    }

    void Collider::setEnable(bool enable) {
        // collisionBitMask == 0 implies disabled and != 0 implies enabled
        if ((!enable && filterData_.collisionBitMask == 0) || (enable && filterData_.collisionBitMask != 0))
            return;

        if (!enable) {
            prevCollisionBitMask_ = filterData_.collisionBitMask;
            filterData_.collisionBitMask = 0;
        } else {
            filterData_.collisionBitMask = prevCollisionBitMask_;
        }
        updateCollisionFilter();

        emitChange(Property{"enable", enable});
    }

    bool Collider::isAttachedToBody() const {
        return hasRigidBody_;
    }

    bool Collider::containsPoint(const Vector2f& point) const {
        return fixture_->TestPoint(b2Vec2{utility::pixelsToMetres(point.x), utility::pixelsToMetres(point.y)});
    }

    void Collider::setDensity(float density) {
        if (getDensity() == density)
            return;

        IME_ASSERT(density >= 0, "A collider cannot have a negative density")
        fixture_->SetDensity(density);
        body_->getInternalBody()->ResetMassData();
        emitChange(Property{"density", density});
    }

    float Collider::getDensity() const {
        return fixture_->GetDensity();
    }

    void Collider::setFriction(float friction) {
        if (getFriction() == friction)
            return;

        fixture_->SetFriction(friction);
        emitChange(Property{"friction", friction});
    }

    float Collider::getFriction() const {
        return fixture_->GetFriction();
    }

    void Collider::setRestitution(float restitution) {
        if (getRestitution() == restitution)
            return;

        fixture_->SetRestitution(restitution);
        emitChange(Property{"restitution", restitution});
    }

    float Collider::getRestitution() const {
        return fixture_->GetRestitution();
    }

    void Collider::setRestitutionThreshold(float threshold) {
        if (getRestitutionThreshold() == threshold)
            return;

        fixture_->SetRestitutionThreshold(threshold);
        emitChange(Property{"restitutionThreshold", threshold});
    }

    float Collider::getRestitutionThreshold() const {
        return fixture_->GetRestitutionThreshold();
    }

    PropertyContainer &Collider::getUserData() {
        return userData_;
    }

    void Collider::onContactBegin(const Collider::CollisionCallback &callback) {
        onContactBegin_ = callback;
    }

    void Collider::onContactEnd(const Collider::CollisionCallback &callback) {
        onContactEnd_ = callback;
    }

    void Collider::onContactStay(const Collider::CollisionCallback &callback) {
        onContactStay_ = callback;
    }

    void Collider::emitContact(const std::string &event, Collider *other) {
        if (this == other)
            return;

        if (event == "contactBegin" && onContactBegin_)
            onContactBegin_(this, other);
        else if (event == "contactEnd" && onContactEnd_)
            onContactEnd_(this, other);
        else if (event == "contactStay" && onContactStay_)
            onContactStay_(this, other);

        GameObject* gameObjectA = body_->getGameObject();
        GameObject*  gameObjectB = other->getBody()->getGameObject();

        if (gameObjectA && gameObjectB)
            gameObjectA->emitCollisionEvent(event, gameObjectB);

        gameObjectA = gameObjectB = nullptr;
    }

    void Collider::updateCollisionFilter() {
        b2Filter b2FilterData;
        b2FilterData.categoryBits = filterData_.categoryBitMask;
        b2FilterData.maskBits = filterData_.collisionBitMask;
        b2FilterData.groupIndex = filterData_.groupIndex;
        fixture_->SetFilterData(b2FilterData);
    }

    Collider::~Collider() = default;
}
