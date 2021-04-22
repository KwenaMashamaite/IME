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

#include "IME/core/physics/rigid_body/colliders/PolygonCollider.h"
#include "IME/utility/Helpers.h"
#include <box2d/b2_polygon_shape.h>

namespace ime {
    PolygonCollider::PolygonCollider() :
        Collider{Collider::Type::Polygon},
        polygon_{std::make_unique<b2PolygonShape>()}
    {}

    PolygonCollider::PolygonCollider(const PolygonCollider& other) :
        Collider(other),
        polygon_{std::make_unique<b2PolygonShape>(*other.polygon_)}
    {}

    PolygonCollider &PolygonCollider::operator=(const PolygonCollider& rhs) {
        if (this != &rhs) {
            auto temp{rhs};
            Collider::operator=(temp);
            polygon_ = std::move(temp.polygon_);
        }

        return *this;
    }

    PolygonCollider::PolygonCollider(PolygonCollider&&) noexcept = default;
    PolygonCollider &PolygonCollider::operator=(PolygonCollider&&) noexcept = default;

    PolygonCollider::Ptr PolygonCollider::copy() const {
        return  std::static_pointer_cast<PolygonCollider>(clone());
    }

    Collider::Ptr PolygonCollider::clone() const {
        return PolygonCollider::Ptr(new PolygonCollider(*this));
    }

    PolygonCollider::Ptr PolygonCollider::create() {
        return std::make_shared<PolygonCollider>();
    }

    std::string PolygonCollider::getClassName() const {
        return "PolygonCollider";
    }

    void PolygonCollider::set(const std::vector<Vector2f>& vertices) {
        IME_ASSERT(vertices.size() < 8, "The number of vertices exceed 8, which is the maximum number of vertices allowed")
        b2Vec2 points[8]; // 8 is the maximum allowed and std::vector.size() is not a constexpr
        for (auto i = 0u; i < vertices.size(); i++)
            points[i].Set(utility::pixelsToMetres(vertices[i].x), utility::pixelsToMetres(vertices[i].y));

        polygon_->Set(points, static_cast<int32>(vertices.size()));
    }

    b2Shape& PolygonCollider::getInternalShape() {
        return *polygon_;
    }

    const b2Shape& PolygonCollider::getInternalShape() const {
        return *polygon_;
    }

    PolygonCollider::~PolygonCollider() {
        emit("destruction");
    }
}