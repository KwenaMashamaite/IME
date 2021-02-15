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

#include "IME/graphics/shapes/Shape.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/physics/World.h"

namespace ime {
    Shape::Shape(Type type) :
        type_{type}
    {}

    Shape::Type Shape::getShapeType() const {
        return type_;
    }

    void Shape::attachRigidBody(Body::sharedPtr body) {
        IME_ASSERT(body, "Invalid rigid body, cannot attach a nullptr to a shape");
        IME_ASSERT(!body_, "Shape already has a rigid body attached, remove it first before attaching another one");
        body_ = body;
        setOrigin(getLocalBounds().width / 2.0f, getLocalBounds().height / 2.0f);
        setPosition(body->getPosition());
        setRotation(body->getRotation());
    }

    void Shape::removeRigidBody() {
        if (body_) {
            body_->getWorld()->destroyBody(body_);
            body_.reset();
        }
    }

    Body::sharedPtr Shape::getRigidBody() {
        return body_;
    }

    const Body::sharedPtr Shape::getRigidBody() const {
        return body_;
    }

    bool Shape::hasRigidBody() const {
        return body_ != nullptr;
    }
}

