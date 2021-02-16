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

#include "IME/graphics/shapes/RectangleShape.h"
#include "IME/graphics/Window.h"
#include "../../utility/Helpers.h"
#include "../WindowImpl.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace ime {
    struct RectangleShape::Impl {
        Impl(Vector2f size) :
            rectangle_{sf::Vector2f{size.x, size.y}}
        {}

        ///////////////////////////////////////////////////////////////////////
        // Member data
        ///////////////////////////////////////////////////////////////////////

        sf::RectangleShape rectangle_;
    };

    RectangleShape::RectangleShape(const Vector2f &size) :
        Shape( Type::Rectangle),
        impl_{std::make_unique<Impl>(size)}
    {}

    RectangleShape::RectangleShape(const RectangleShape & other) :
        Shape(other.getShapeType()),
        impl_{std::make_unique<Impl>(*other.impl_)}
    {}

    RectangleShape &RectangleShape::operator=(const RectangleShape& other) {
        if (this != &other) {
            *impl_ = *other.impl_;
        }

        return *this;
    }

    RectangleShape::RectangleShape(RectangleShape &&) noexcept = default;

    RectangleShape &RectangleShape::operator=(RectangleShape &&) noexcept = default;

    RectangleShape::sharedPtr RectangleShape::create(const Vector2f &size) {
        return sharedPtr(new RectangleShape(size));
    }

    void RectangleShape::setSize(const Vector2f &size) {
        impl_->rectangle_.setSize({size.x, size.y});
    }

    Vector2f RectangleShape::getSize() const {
        auto [x, y] = impl_->rectangle_.getSize();
        return {x, y};
    }

    void RectangleShape::setFillColour(const Colour &colour) {
        impl_->rectangle_.setFillColor(utility::convertToSFMLColour(colour));
    }

    Colour RectangleShape::getFillColour() const {
        return utility::convertFrom3rdPartyColour(impl_->rectangle_.getFillColor());
    }

    void RectangleShape::setOutlineColour(const Colour &colour) {
        impl_->rectangle_.setOutlineColor(utility::convertToSFMLColour(colour));
    }

    Colour RectangleShape::getOutlineColour() const {
        return utility::convertFrom3rdPartyColour(impl_->rectangle_.getOutlineColor());
    }

    void RectangleShape::setOutlineThickness(float thickness) {
        impl_->rectangle_.setOutlineThickness(thickness);
    }

    float RectangleShape::getOutlineThickness() const {
        return impl_->rectangle_.getOutlineThickness();
    }

    FloatRect RectangleShape::getLocalBounds() const {
        auto [left, top, width, height] = impl_->rectangle_.getLocalBounds();
        return {left, top, width, height};
    }

    FloatRect RectangleShape::getGlobalBounds() const {
        auto [left, top, width, height] = impl_->rectangle_.getGlobalBounds();
        return {left, top, width, height};
    }

    void RectangleShape::setPosition(float x, float y) {
        impl_->rectangle_.setPosition(x, y);
    }

    void RectangleShape::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    Vector2f RectangleShape::getPosition() const {
        return {impl_->rectangle_.getPosition().x, impl_->rectangle_.getPosition().y};
    }

    void RectangleShape::setRotation(float angle) {
        impl_->rectangle_.setRotation(angle);
    }

    void RectangleShape::rotate(float angle) {
        impl_->rectangle_.rotate(angle);
    }

    float RectangleShape::getRotation() const {
        return impl_->rectangle_.getRotation();
    }

    void RectangleShape::setScale(float factorX, float factorY) {
        impl_->rectangle_.setScale(factorX, factorY);
    }

    void RectangleShape::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void RectangleShape::scale(float factorX, float factorY) {
        impl_->rectangle_.scale(factorX, factorY);
    }

    void RectangleShape::scale(Vector2f offset) {
        impl_->rectangle_.scale({offset.x, offset.y});
    }

    Vector2f RectangleShape::getScale() const {
        return {impl_->rectangle_.getScale().x, impl_->rectangle_.getScale().y};
    }

    void RectangleShape::setOrigin(float x, float y) {
        impl_->rectangle_.setOrigin(x, y);
    }

    void RectangleShape::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f RectangleShape::getOrigin() const {
        return {impl_->rectangle_.getOrigin().x, impl_->rectangle_.getOrigin().y};
    }

    void RectangleShape::move(float offsetX, float offsetY) {
        impl_->rectangle_.move(offsetX, offsetY);
    }

    void RectangleShape::move(Vector2f offset) {
        impl_->rectangle_.move({offset.x, offset.y});
    }

    void RectangleShape::draw(Window &renderTarget) const {
        renderTarget.getImpl()->getSFMLWindow().draw(impl_->rectangle_);
    }

    RectangleShape::~RectangleShape() = default;
}
