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

#include "IME/core/physics/CircleShape.h"
#include "IME/utility/Helpers.h"
#include <box2d/b2_circle_shape.h>

namespace ime {
    CircleShape::CircleShape() :
        Shape(Shape::Type::Circle),
        circle_{new b2CircleShape()}
    {}

    void CircleShape::setPosition(Vector2f position) {
        circle_->m_p.x = utility::pixelsToMetres(position.x);
        circle_->m_p.y = utility::pixelsToMetres(position.y);
    }

    Vector2f CircleShape::getPosition() const {
        return {utility::metresToPixels(circle_->m_p.x), utility::metresToPixels(circle_->m_p.y)};
    }

    void CircleShape::setRadius(float radius) {
        circle_->m_radius = utility::degToRad(radius);
    }

    float CircleShape::getRadius() const {
        return utility::radToDeg(circle_->m_radius);
    }

    b2Shape *CircleShape::getInternalShape() {
        return circle_;
    }

    const b2Shape *CircleShape::getInternalShape() const {
        return circle_;
    }

    CircleShape::~CircleShape() {
        delete circle_;
        circle_ = nullptr;
    }
}

