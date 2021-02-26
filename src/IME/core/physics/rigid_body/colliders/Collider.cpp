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
    namespace {
        auto static idCounter{0u}; // Collider instance id counter
    } // anonymous namespace

    Collider::Collider(Collider::Type type) :
        type_{type}
    {}

    Collider::Collider(Collider &&) = default;
    Collider &Collider::operator=(Collider &&) = default;

    Collider::Type Collider::getType() const {
        return type_;
    }

    void Collider::setBody(Body::Ptr body) {
        IME_ASSERT(body, "A body attached to a collider cannot be a nullptr");
        id_ = idCounter++;
        auto b2FixtureDefinition = std::make_unique<b2FixtureDef>();
        b2FixtureDefinition->shape = &getInternalShape();
        b2FixtureDefinition->userData.pointer = id_;

        fixture_.reset(body->getInternalBody()->CreateFixture(b2FixtureDefinition.get()));
        body_ = body;
    }

    Body::Ptr Collider::getBody() {
        return body_;
    }

    const Body::Ptr& Collider::getBody() const {
        return body_;
    }

    void Collider::setSensor(bool sensor) {
        fixture_->SetSensor(sensor);
    }

    bool Collider::isSensor() const {
        return fixture_->IsSensor();
    }

    void Collider::setCollisionFilter(const CollisionFilterData& filterData) {
        filterData_ = filterData;
        updateCollisionFilter();
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
    }

    bool Collider::containsPoint(Vector2f point) const {
        return fixture_->TestPoint({utility::pixelsToMetres(point.x),
            utility::pixelsToMetres(point.y)});
    }

    void Collider::setDensity(float density) {
        IME_ASSERT(density >= 0, "A collider cannot have a negative density");
        fixture_->SetDensity(density);
        body_->getInternalBody()->ResetMassData();
    }

    float Collider::getDensity() const {
        return fixture_->GetDensity();
    }

    void Collider::setFriction(float friction) {
        fixture_->SetFriction(friction);
    }

    float Collider::getFriction() const {
        return fixture_->GetFriction();
    }

    void Collider::setRestitution(float restitution) {
        fixture_->SetRestitution(restitution);
    }

    float Collider::getRestitution() const {
        return fixture_->GetRestitution();
    }

    void Collider::setRestitutionThreshold(float threshold) {
        fixture_->SetRestitutionThreshold(threshold);
    }

    float Collider::getRestitutionThreshold() const {
        return fixture_->GetRestitutionThreshold();
    }

    PropertyContainer &Collider::getUserData() {
        return userData_;
    }

    unsigned int Collider::getId() const {
        return id_;
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
