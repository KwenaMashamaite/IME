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

#include "IME/graphics/shapes/RectangleShape.h"
#include "IME/graphics/shapes/ShapeImpl.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

namespace ime {
    struct RectangleShape::RecShapeImpl {
        explicit RecShapeImpl(const std::shared_ptr<sf::Shape>& shape) :
            rectangle_{std::static_pointer_cast<sf::RectangleShape>(shape)}
        {}

        // Member data
        std::shared_ptr<sf::RectangleShape> rectangle_;
    };

    /*-------------------------------------------------------------------------
     # RectangleShape class
     =-----------------------------------------------------------------------*/

    RectangleShape::RectangleShape(const Vector2f &size) :
        Shape(std::make_unique<priv::ShapeImpl<sf::RectangleShape>>(
            std::make_shared<sf::RectangleShape>(sf::Vector2f({size.x, size.y}))),Type::Rectangle),
        pimpl_{std::make_unique<RecShapeImpl>(std::static_pointer_cast<sf::Shape>(getInternalPtr()))}
    {}

    RectangleShape::RectangleShape(const RectangleShape & other) :
        Shape(other),
        pimpl_{std::make_unique<RecShapeImpl>(*other.pimpl_)}
    {}

    RectangleShape &RectangleShape::operator=(const RectangleShape& other) {
        if (this != &other) {
            *pimpl_ = *other.pimpl_;
        }

        return *this;
    }

    RectangleShape::RectangleShape(RectangleShape &&) noexcept = default;
    RectangleShape &RectangleShape::operator=(RectangleShape &&) noexcept = default;

    RectangleShape::Ptr RectangleShape::create(const Vector2f &size) {
        return std::make_unique<RectangleShape>(size);
    }

    RectangleShape::Ptr RectangleShape::copy() const {
        return RectangleShape::Ptr(static_cast<RectangleShape*>(clone().release()));
    }

    Shape::Ptr RectangleShape::clone() const {
        return std::make_unique<RectangleShape>(*this);
    }

    std::string RectangleShape::getClassName() const {
        return "RectangleShape";
    }

    void RectangleShape::setSize(const Vector2f &size) {
        if (getSize() == size)
            return;

        pimpl_->rectangle_->setSize({size.x, size.y});
        emitChange(Property{"size", size});
    }

    Vector2f RectangleShape::getSize() const {
        const sf::Vector2f& size = pimpl_->rectangle_->getSize();
        return Vector2f{size.x, size.y};
    }

    RectangleShape::~RectangleShape() {
        emit("destruction");
    }
}
