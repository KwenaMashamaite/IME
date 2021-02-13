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

#include "IME/core/physics/rigid_body/Fixture.h"
#include "IME/core/physics/rigid_body/Body.h"
#include "IME/utility/Helpers.h"
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

namespace ime {
    namespace {
        auto static idCounter{0u};
    }

    Fixture::Fixture(const FixtureDefinition& definition, Body::sharedPtr body) :
        id_{idCounter++}
    {
        IME_ASSERT(definition.collider, "Fixture definition does not have a collider");
        auto b2FixtureDefinition = std::make_unique<b2FixtureDef>();
        b2FixtureDefinition->restitution = definition.restitution;
        b2FixtureDefinition->restitutionThreshold = definition.restitutionThreshold;
        b2FixtureDefinition->friction = definition.friction;
        b2FixtureDefinition->density = definition.density;
        b2FixtureDefinition->isSensor = definition.isSensor;
        b2FixtureDefinition->shape = definition.collider->getInternalShape();
        b2FixtureDefinition->filter.categoryBits = definition.filterData.categoryBitMask;
        b2FixtureDefinition->filter.maskBits = definition.filterData.collisionBitMask;
        b2FixtureDefinition->filter.groupIndex = definition.filterData.groupIndex;
        b2FixtureDefinition->userData.pointer = id_;

        fixture_.reset(body->getInternalBody()->CreateFixture(b2FixtureDefinition.get()));
        userData_ = definition.userData;
        body_ = body;
    }

    void Fixture::setSensor(bool sensor) {
        fixture_->SetSensor(sensor);
    }

    bool Fixture::isSensor() const {
        return fixture_->IsSensor();
    }

    Body::sharedPtr Fixture::getBody() {
        return body_;
    }

    const Body::sharedPtr& Fixture::getBody() const {
        return body_;
    }

    bool Fixture::containsPoint(Vector2f point) const {
        return fixture_->TestPoint({utility::pixelsToMetres(point.x),
                                    utility::pixelsToMetres(point.y)});
    }

    void Fixture::setDensity(float density) {
        fixture_->SetDensity(density);
        body_->getInternalBody()->ResetMassData();
    }

    float Fixture::getDensity() const {
        return fixture_->GetDensity();
    }

    void Fixture::setFriction(float friction) {
        fixture_->SetFriction(friction);
    }

    float Fixture::getFriction() const {
        return fixture_->GetFriction();
    }

    void Fixture::setRestitution(float restitution) {
        fixture_->SetRestitution(restitution);
    }

    float Fixture::getRestitution() const {
        return fixture_->GetRestitution();
    }

    void Fixture::setRestitutionThreshold(float threshold) {
        fixture_->SetRestitutionThreshold(threshold);
    }

    float Fixture::getRestitutionThreshold() const {
        return fixture_->GetRestitutionThreshold();
    }

    PropertyContainer &Fixture::getUserData() {
        return userData_;
    }

    unsigned int Fixture::getId() const {
        return id_;
    }
}
