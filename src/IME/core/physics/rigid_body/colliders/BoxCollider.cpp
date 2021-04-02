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

#include "IME/core/physics/rigid_body/colliders/BoxCollider.h"
#include "../../../../utility/Helpers.h"
#include <box2d/b2_polygon_shape.h>

namespace ime {
    BoxCollider::BoxCollider(Vector2f size) :
        Collider(Collider::Type::Box),
        box_{std::make_unique<b2PolygonShape>()}
    {
        setSize(size.x, size.y);
    }

    BoxCollider::BoxCollider(BoxCollider&&) noexcept = default;
    BoxCollider &BoxCollider::operator=(BoxCollider&&) noexcept = default;

    BoxCollider::Ptr BoxCollider::create(Vector2f size) {
        return std::make_shared<BoxCollider>(size);
    }

    Collider::Ptr BoxCollider::copy() {
        return std::as_const(*this).copy();
    }

    const Collider::Ptr BoxCollider::copy() const {
        auto collider = create();
        collider->size_ = this->size_;
        collider->box_.reset(new b2PolygonShape(*(this->box_.get())));
        return collider;
    }

    std::string BoxCollider::getClassName() const {
        return "BoxCollider";
    }

    void BoxCollider::setSize(float width, float height) {
        // The size constraints are from Box2d
        IME_ASSERT(width >= 0.1f, "The width of the rectangle must be greater than or equal to the minimum value of 0.1f");
        IME_ASSERT(height >= 0.1f, "The height of the rectangle must be greater than or equal to the minimum value of 0.1f");

        size_ = {width, height};
        box_->SetAsBox(utility::pixelsToMetres(width / 2.0f),
            utility::pixelsToMetres(height / 2.0f));

        emitChange(Property{"size", size_});
    }

    void BoxCollider::setSize(Vector2f size) {
        setSize(size.x, size.y);
    }

    Vector2f BoxCollider::getSize() const {
        return size_;
    }

    b2Shape& BoxCollider::getInternalShape() {
        return *box_;
    }

    const b2Shape& BoxCollider::getInternalShape() const {
        return *box_;
    }

    BoxCollider::~BoxCollider() = default;
}

