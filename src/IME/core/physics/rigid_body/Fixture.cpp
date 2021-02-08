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
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

namespace ime {
    Fixture::Fixture(const FixtureDefinition& definition, Body *body) {
        IME_ASSERT(definition.shape, "Fixture definition does not have a shape set");
        auto b2FixtureDef = new struct b2FixtureDef();
        b2FixtureDef->restitution = definition.restitution;
        b2FixtureDef->restitutionThreshold = definition.restitutionThreshold;
        b2FixtureDef->friction = definition.friction;
        b2FixtureDef->density = definition.density;
        b2FixtureDef->isSensor = definition.isSensor;
        b2FixtureDef->shape = definition.shape->getInternalShape();

        fixture_ = body->body_->CreateFixture(b2FixtureDef);
        body_ = body;
        delete b2FixtureDef;
        b2FixtureDef = nullptr;
    }

    void Fixture::setSensor(bool sensor) {
        fixture_->SetSensor(sensor);
    }

    bool Fixture::isSensor() const {
        return fixture_->IsSensor();
    }

    Body *Fixture::getBody() {
        return body_;
    }

    const Body *Fixture::getBody() const {
        return body_;
    }

    bool Fixture::containsPoint(Vector2f point) const {
        return fixture_->TestPoint({point.x, point.y});
    }

    void Fixture::setDensity(float density) {
        fixture_->SetDensity(density);
        body_->body_->ResetMassData();
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

    Fixture::~Fixture() {
        fixture_ = nullptr;
        body_ = nullptr;
    }
}
