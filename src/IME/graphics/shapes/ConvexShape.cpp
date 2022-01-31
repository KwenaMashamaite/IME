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

#include "IME/graphics/shapes/ConvexShape.h"
#include "IME/graphics/shapes/ShapeImpl.h"
#include <SFML/Graphics/ConvexShape.hpp>
#include <memory>

namespace ime {
    struct ConvexShape::ConvexShapeImpl {
        explicit ConvexShapeImpl(const std::shared_ptr<sf::Shape>& shape) :
            polygon_{std::static_pointer_cast<sf::ConvexShape>(shape)}
        {}

        // Member data
        std::shared_ptr<sf::ConvexShape> polygon_;
    };

    /*-------------------------------------------------------------------------
    # ConvexShape class
    =-----------------------------------------------------------------------*/

    ConvexShape::ConvexShape(std::size_t pointCount) :
        Shape(std::make_unique<priv::ShapeImpl<sf::ConvexShape>>(
            std::make_shared<sf::ConvexShape>(pointCount)), Type::Convex),
        pimpl_{std::make_unique<ConvexShapeImpl>(std::static_pointer_cast<sf::Shape>(getInternalPtr()))}
    {}

    ConvexShape::ConvexShape(const ConvexShape & other) :
        Shape(other),
        pimpl_{std::make_unique<ConvexShapeImpl>(*other.pimpl_)}
    {}

    ConvexShape &ConvexShape::operator=(const ConvexShape& other) {
        if (this != &other) {
            *pimpl_ = *other.pimpl_;
        }

        return *this;
    }

    ConvexShape::ConvexShape(ConvexShape &&) noexcept = default;
    ConvexShape &ConvexShape::operator=(ConvexShape &&) noexcept = default;

    ConvexShape::Ptr ConvexShape::create(std::size_t pointCount) {
        return std::make_unique<ConvexShape>(pointCount);
    }

    ConvexShape::Ptr ConvexShape::copy() const {
        return ConvexShape::Ptr(static_cast<ConvexShape*>(clone().release()));
    }

    Shape::Ptr ConvexShape::clone() const {
        return std::make_unique<ConvexShape>(*this);
    }

    std::string ConvexShape::getClassName() const {
        return "ConvexShape";
    }

    void ConvexShape::setPointCount(std::size_t count) {
        if (getPointCount() == count)
            return;

        pimpl_->polygon_->setPointCount(count);
        emitChange(Property{"pointCount", count});
    }

    std::size_t ConvexShape::getPointCount() const {
        return pimpl_->polygon_->getPointCount();
    }

    void ConvexShape::setPoint(std::size_t index, const Vector2f &point) {
        if (getPoint(index) == point)
            return;

        IME_ASSERT(index <= getPointCount() - 1, "Index out of bounds")
        pimpl_->polygon_->setPoint(index, {point.x, point.y});
        emitChange(Property{"point", index});
    }

    Vector2f ConvexShape::getPoint(std::size_t index) const {
        IME_ASSERT(index <= getPointCount() - 1, "Index out of bounds")
        sf::Vector2f point = pimpl_->polygon_->getPoint(index);
        return Vector2f{point.x, point.y};
    }

    ConvexShape::~ConvexShape() = default;
}
