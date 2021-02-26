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

#include "IME/graphics/shapes/ConvexShape.h"
#include "IME/graphics/Window.h"
#include "../../utility/Helpers.h"
#include "../WindowImpl.h"
#include <SFML/Graphics/ConvexShape.hpp>

namespace ime {
    struct ConvexShape::Impl {
        Impl(std::size_t pointCount) :
            polygon_{pointCount}
        {}

        ///////////////////////////////////////////////////////////////////////
        // Member data
        ///////////////////////////////////////////////////////////////////////

        sf::ConvexShape polygon_;
    };
    
    ConvexShape::ConvexShape(std::size_t pointCount) :
        Shape(Type::Convex),
        impl_{std::make_unique<Impl>(pointCount)}
    {}

    ConvexShape::ConvexShape(const ConvexShape & other) :
        Shape(other.getShapeType()),
        impl_{std::make_unique<Impl>(*other.impl_)}
    {}

    ConvexShape &ConvexShape::operator=(const ConvexShape& other) {
        if (this != &other) {
            *impl_ = *other.impl_;
        }

        return *this;
    }

    ConvexShape::ConvexShape(ConvexShape &&) noexcept = default;

    ConvexShape &ConvexShape::operator=(ConvexShape &&) noexcept = default;

    ConvexShape::Ptr ConvexShape::create(std::size_t pointCount) {
        return ConvexShape::Ptr(new ConvexShape(pointCount));
    }

    void ConvexShape::setPointCount(std::size_t count) {
        impl_->polygon_.setPointCount(count);
    }

    std::size_t ConvexShape::getPointCount() const {
        return impl_->polygon_.getPointCount();
    }

    void ConvexShape::setPoint(std::size_t index, const Vector2f &point) {
        impl_->polygon_.setPoint(index, {point.x, point.y});
    }

    Vector2f ConvexShape::getPoint(std::size_t index) const {
        auto [x, y] = impl_->polygon_.getPoint(index);
        return {x, y};
    }

    void ConvexShape::setFillColour(const Colour &colour) {
        impl_->polygon_.setFillColor(utility::convertToSFMLColour(colour));
    }

    Colour ConvexShape::getFillColour() const {
        return utility::convertFrom3rdPartyColour(impl_->polygon_.getFillColor());
    }

    void ConvexShape::setOutlineColour(const Colour &colour) {
        impl_->polygon_.setOutlineColor(utility::convertToSFMLColour(colour));
    }

    Colour ConvexShape::getOutlineColour() const {
        return utility::convertFrom3rdPartyColour(impl_->polygon_.getOutlineColor());
    }

    void ConvexShape::setOutlineThickness(float thickness) {
        impl_->polygon_.setOutlineThickness(thickness);
    }

    float ConvexShape::getOutlineThickness() const {
        return impl_->polygon_.getOutlineThickness();
    }

    FloatRect ConvexShape::getLocalBounds() const {
        auto [left, top, width, height] = impl_->polygon_.getLocalBounds();
        return {left, top, width, height};
    }

    FloatRect ConvexShape::getGlobalBounds() const {
        auto [left, top, width, height] = impl_->polygon_.getGlobalBounds();
        return {left, top, width, height};
    }

    void ConvexShape::setPosition(float x, float y) {
        impl_->polygon_.setPosition(x, y);
    }

    void ConvexShape::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    Vector2f ConvexShape::getPosition() const {
        return {impl_->polygon_.getPosition().x, impl_->polygon_.getPosition().y};
    }

    void ConvexShape::setRotation(float angle) {
        impl_->polygon_.setRotation(angle);
    }

    void ConvexShape::rotate(float angle) {
        impl_->polygon_.rotate(angle);
    }

    float ConvexShape::getRotation() const {
        return impl_->polygon_.getRotation();
    }

    void ConvexShape::setScale(float factorX, float factorY) {
        impl_->polygon_.setScale(factorX, factorY);
    }

    void ConvexShape::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void ConvexShape::scale(float factorX, float factorY) {
        impl_->polygon_.scale(factorX, factorY);
    }

    void ConvexShape::scale(Vector2f offset) {
        impl_->polygon_.scale({offset.x, offset.y});
    }

    Vector2f ConvexShape::getScale() const {
        return {impl_->polygon_.getScale().x, impl_->polygon_.getScale().y};
    }

    void ConvexShape::setOrigin(float x, float y) {
        impl_->polygon_.setOrigin(x, y);
    }

    void ConvexShape::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f ConvexShape::getOrigin() const {
        return {impl_->polygon_.getOrigin().x, impl_->polygon_.getOrigin().y};
    }

    void ConvexShape::move(float offsetX, float offsetY) {
        impl_->polygon_.move(offsetX, offsetY);
    }

    void ConvexShape::move(Vector2f offset) {
        impl_->polygon_.move({offset.x, offset.y});
    }

    void ConvexShape::draw(Window &renderTarget) const {
        renderTarget.getImpl()->getSFMLWindow().draw(impl_->polygon_);
    }

    ConvexShape::~ConvexShape() = default;
}
