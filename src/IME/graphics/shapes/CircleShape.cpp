////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/graphics/shapes/CircleShape.h"
#include "IME/graphics/shapes/ShapeImpl.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <memory>

namespace ime {
    struct CircleShape::CircleShapeImpl {
        explicit CircleShapeImpl(const std::shared_ptr<sf::Shape>& shape) :
            circle_{std::static_pointer_cast<sf::CircleShape>(shape)}
        {}

        //Member data
        std::shared_ptr<sf::CircleShape> circle_;
    };

    /*-------------------------------------------------------------------------
     # CircleShape class
     =-----------------------------------------------------------------------*/

    CircleShape::CircleShape(float radius) :
        Shape(std::make_unique<priv::ShapeImpl<sf::CircleShape>>(
            std::make_shared<sf::CircleShape>(radius)),Type::Circle),
        pimpl_{std::make_unique<CircleShapeImpl>(std::static_pointer_cast<sf::Shape>(getInternalPtr()))}
    {}

    CircleShape::CircleShape(const CircleShape & other) :
        Shape(other),
        pimpl_{std::make_unique<CircleShapeImpl>(*other.pimpl_)}
    {}

    CircleShape &CircleShape::operator=(const CircleShape& other) {
        if (this != &other) {
            Shape::operator=(other);
            *pimpl_ = *other.pimpl_;
        }

        return *this;
    }

    CircleShape::CircleShape(CircleShape &&) noexcept = default;
    CircleShape &CircleShape::operator=(CircleShape &&) noexcept = default;

    CircleShape::Ptr CircleShape::create(float radius) {
        return std::make_unique<CircleShape>(radius);
    }

    CircleShape::Ptr CircleShape::copy() const {
        return CircleShape::Ptr(static_cast<CircleShape*>(clone().release()));
    }

    Shape::Ptr CircleShape::clone() const {
        return std::make_unique<CircleShape>(*this);
    }

    std::string CircleShape::getClassName() const {
        return "CircleShape";
    }

    void CircleShape::setRadius(float radius) {
        if (getRadius() == radius)
            return;

        pimpl_->circle_->setRadius(radius);
        emitChange(Property{"radius", radius});
    }

    float CircleShape::getRadius() const {
        return pimpl_->circle_->getRadius();
    }

    CircleShape::~CircleShape() = default;
}
