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

#include "IME/core/physics/rigid_body/AABB.h"
#include "../../../utility/Helpers.h"
#include <box2d/b2_collision.h>

namespace ime {
    AABB::AABB() :
        aabb_{new b2AABB()}
    {}

    void AABB::create(Vector2f lowerBounds, Vector2f upperBounds) {
        aabb_->lowerBound = {utility::pixelsToMetres(lowerBounds.x),
                             utility::pixelsToMetres(lowerBounds.y)};

        aabb_->upperBound = {utility::pixelsToMetres(upperBounds.x),
                             utility::pixelsToMetres(upperBounds.y)};
    }

    std::string AABB::getClassName() const {
        return "AABB";
    }

    std::pair<Vector2f, Vector2f> AABB::getBounds() const {
        return {getLowerBounds(), getUpperBounds()};
    }

    Vector2f AABB::getLowerBounds() const {
        return {utility::metresToPixels(aabb_->lowerBound.x),
                utility::metresToPixels(aabb_->lowerBound.y)};
    }

    Vector2f AABB::getUpperBounds() const {
        return {utility::metresToPixels(aabb_->upperBound.x),
                utility::metresToPixels(aabb_->upperBound.y)};
    }

    float AABB::getPerimeter() const {
        return aabb_->GetPerimeter();
    }

    Vector2f AABB::getCenter() const {
        return {utility::metresToPixels(aabb_->GetCenter().x),
                utility::metresToPixels(aabb_->GetCenter().y)};
    }

    void AABB::combine(const AABB &aabb) {
        aabb_->Combine(*(aabb.aabb_));
    }

    void AABB::combine(const AABB &aabb1, const AABB &aabb2) {
        aabb_->Combine(*(aabb1.aabb_), *(aabb2.aabb_));
    }

    bool AABB::contains(const AABB &aabb) const {
        return aabb_->Contains(*(aabb.aabb_));
    }

    const b2AABB *AABB::getInternalAABB() const {
        return aabb_;
    }

    AABB::~AABB() {
        delete aabb_;
        aabb_ = nullptr;
    }
}
