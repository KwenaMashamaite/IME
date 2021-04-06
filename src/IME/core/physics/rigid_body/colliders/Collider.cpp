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

#include "IME/core/physics/rigid_body/colliders/Collider.h"
#include "IME/core/physics/rigid_body/Body.h"
#include "../../../../utility/Helpers.h"
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_settings.h>

namespace ime {
    Collider::Collider(Collider::Type type) :
        type_{type},
        prevCollisionBitMask_{filterData_.collisionBitMask}
    {}

    Collider::Collider(const Collider& other) :
        Object(other),
        type_{other.type_},
        filterData_{other.filterData_},
        prevCollisionBitMask_{other.prevCollisionBitMask_}
    {
        // Other member data are initialized when the collider is attached
        // to a rigid body because b2Fixture is not copy constructable
    }

    Collider &Collider::operator=(const Collider& rhs) {
        if (this != &rhs) {
            type_ = rhs.type_;
            filterData_ = rhs.filterData_;
            prevCollisionBitMask_ = rhs.prevCollisionBitMask_;

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

    void Collider::setBody(Body::Ptr body) {
        IME_ASSERT(body, "A body attached to a collider cannot be a nullptr");
        auto b2FixtureDefinition = std::make_unique<b2FixtureDef>();
        b2FixtureDefinition->shape = &getInternalShape();
        b2FixtureDefinition->density = 1.0f;
        b2FixtureDefinition->userData.pointer = getObjectId();

        fixture_.reset(body->getInternalBody()->CreateFixture(b2FixtureDefinition.get()));
        body_ = std::move(body);

        emitChange(Property{"body", body_});
    }

    Body::Ptr Collider::getBody() {
        return body_;
    }

    const Body::Ptr& Collider::getBody() const {
        return body_;
    }

    void Collider::setSensor(bool sensor) {
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

    bool Collider::containsPoint(Vector2f point) const {
        return fixture_->TestPoint({utility::pixelsToMetres(point.x),
            utility::pixelsToMetres(point.y)});
    }

    void Collider::setDensity(float density) {
        IME_ASSERT(density >= 0, "A collider cannot have a negative density");
        fixture_->SetDensity(density);
        body_->getInternalBody()->ResetMassData();
        emitChange(Property{"density", density});
    }

    float Collider::getDensity() const {
        return fixture_->GetDensity();
    }

    void Collider::setFriction(float friction) {
        fixture_->SetFriction(friction);
        emitChange(Property{"friction", friction});
    }

    float Collider::getFriction() const {
        return fixture_->GetFriction();
    }

    void Collider::setRestitution(float restitution) {
        fixture_->SetRestitution(restitution);
        emitChange(Property{"restitution", restitution});
    }

    float Collider::getRestitution() const {
        return fixture_->GetRestitution();
    }

    void Collider::setRestitutionThreshold(float threshold) {
        fixture_->SetRestitutionThreshold(threshold);
        emitChange(Property{"restitutionThreshold", threshold});
    }

    float Collider::getRestitutionThreshold() const {
        return fixture_->GetRestitutionThreshold();
    }

    PropertyContainer &Collider::getUserData() {
        return userData_;
    }

    void Collider::updateCollisionFilter() {
        auto b2FilterData = b2Filter();
        b2FilterData.categoryBits = filterData_.categoryBitMask;
        b2FilterData.maskBits = filterData_.collisionBitMask;
        b2FilterData.groupIndex = filterData_.groupIndex;
        fixture_->SetFilterData(b2FilterData);
    }

    Collider::~Collider() = default;
}
