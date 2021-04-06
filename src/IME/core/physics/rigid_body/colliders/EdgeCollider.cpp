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

#include "IME/core/physics/rigid_body/colliders/EdgeCollider.h"
#include "../../../../utility/Helpers.h"
#include <box2d/b2_edge_shape.h>

namespace ime {
    EdgeCollider::EdgeCollider() :
        Collider(Type::Edge),
        edgeShape_{std::make_unique<b2EdgeShape>()}
    {}

    EdgeCollider::EdgeCollider(const EdgeCollider& other) :
        Collider(other),
        edgeShape_{std::make_unique<b2EdgeShape>(*other.edgeShape_)}
    {}

    EdgeCollider &EdgeCollider::operator=(const EdgeCollider& rhs) {
        if (this != &rhs) {
            auto temp{rhs};
            edgeShape_ = std::move(temp.edgeShape_);
        }

        return *this;
    }

    EdgeCollider::EdgeCollider(EdgeCollider &&) noexcept = default;
    EdgeCollider &EdgeCollider::operator=(EdgeCollider &&) noexcept = default;

    EdgeCollider::Ptr EdgeCollider::copy() const {
        return std::static_pointer_cast<EdgeCollider>(clone());
    }

    Collider::Ptr EdgeCollider::clone() const {
        return EdgeCollider::Ptr(new EdgeCollider(*this));
    }

    EdgeCollider::Ptr EdgeCollider::create() {
        return std::make_shared<EdgeCollider>();
    }

    std::string EdgeCollider::getClassName() const {
        return "EdgeCollider";
    }

    void EdgeCollider::setOneSided(Vector2f v0, Vector2f v1, Vector2f v2, Vector2f v3)
    {
        edgeShape_->SetOneSided(
            {utility::pixelsToMetres(v0.x), utility::pixelsToMetres(v0.y)},
            {utility::pixelsToMetres(v1.x), utility::pixelsToMetres(v1.y)},
            {utility::pixelsToMetres(v2.x), utility::pixelsToMetres(v2.y)},
            {utility::pixelsToMetres(v3.x), utility::pixelsToMetres(v3.y)});
    }

    void EdgeCollider::setTwoSided(Vector2f v1, Vector2f v2) {
        edgeShape_->SetTwoSided({utility::pixelsToMetres(v1.x), utility::pixelsToMetres(v1.y)},
            {utility::pixelsToMetres(v2.x), utility::pixelsToMetres(v2.y)});
    }

    std::pair<Vector2f, Vector2f> EdgeCollider::getEdgeVertices() const {
        return {getFirstVertex(), getSecondVertex()};
    }

    Vector2f EdgeCollider::getFirstVertex() const {
        return utility::metresToPixels({edgeShape_->m_vertex1.x, edgeShape_->m_vertex1.y});
    }

    Vector2f EdgeCollider::getSecondVertex() const {
        return utility::metresToPixels({edgeShape_->m_vertex2.x, edgeShape_->m_vertex2.y});
    }

    std::pair<Vector2f, Vector2f> EdgeCollider::getGhostVertices() const {
        return {{utility::metresToPixels(edgeShape_->m_vertex0.x), utility::metresToPixels(edgeShape_->m_vertex0.y)},
                {utility::metresToPixels(edgeShape_->m_vertex3.x), utility::metresToPixels(edgeShape_->m_vertex3.y)}};
    }

    bool EdgeCollider::isOneSided() const {
        return edgeShape_->m_oneSided;
    }

    b2Shape& EdgeCollider::getInternalShape() {
        return *edgeShape_;
    }

    const b2Shape& EdgeCollider::getInternalShape() const {
        return *edgeShape_;
    }

    EdgeCollider::~EdgeCollider() = default;
}
