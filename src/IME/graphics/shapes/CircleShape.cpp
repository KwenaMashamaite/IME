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

#include "IME/graphics/shapes/CircleShape.h"
#include "IME/utility/Helpers.h"
#include "IME/graphics/Window.h"
#include <SFML/Graphics/CircleShape.hpp>

namespace ime {
    struct CircleShape::Impl {
        Impl(float radius) :
            circle_{radius}
        {}

        ///////////////////////////////////////////////////////////////////////
        // Member data
        ///////////////////////////////////////////////////////////////////////

        sf::CircleShape circle_;
    };

    CircleShape::CircleShape(float radius) : 
        Shape(Type::Circle),
        impl_{std::make_unique<Impl>(radius)}
    {}

    CircleShape::CircleShape(const CircleShape & other) :
        Shape(other.getShapeType()),
        impl_{std::make_unique<Impl>(*other.impl_)}
    {}

    CircleShape &CircleShape::operator=(const CircleShape& other) {
        if (this != &other) {
            auto temp{other};
            std::swap(impl_, temp.impl_);
        }

        return *this;
    }

    CircleShape::sharedPtr CircleShape::create(float radius) {
        return CircleShape::sharedPtr(new CircleShape(radius));
    }

    void CircleShape::setRadius(float radius) {
        impl_->circle_.setRadius(radius);
    }

    float CircleShape::getRadius() const {
        return impl_->circle_.getRadius();
    }

    void CircleShape::setFillColour(const Colour &colour) {
        impl_->circle_.setFillColor(utility::convertToSFMLColour(colour));
    }

    Colour CircleShape::getFillColour() const {
        return utility::convertFrom3rdPartyColour(impl_->circle_.getFillColor());
    }

    void CircleShape::setOutlineColour(const Colour &colour) {
        impl_->circle_.setOutlineColor(utility::convertToSFMLColour(colour));
    }

    Colour CircleShape::getOutlineColour() const {
        return utility::convertFrom3rdPartyColour(impl_->circle_.getOutlineColor());
    }

    void CircleShape::setOutlineThickness(float thickness) {
        impl_->circle_.setOutlineThickness(thickness);
    }

    float CircleShape::getOutlineThickness() const {
        return impl_->circle_.getOutlineThickness();
    }

    FloatRect CircleShape::getLocalBounds() const {
        auto [left, top, width, height] = impl_->circle_.getLocalBounds();
        return {left, top, width, height};
    }

    FloatRect CircleShape::getGlobalBounds() const {
        auto [left, top, width, height] = impl_->circle_.getGlobalBounds();
        return {left, top, width, height};
    }

    void CircleShape::setPosition(float x, float y) {
        impl_->circle_.setPosition(x, y);
    }

    void CircleShape::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    Vector2f CircleShape::getPosition() const {
        return {impl_->circle_.getPosition().x, impl_->circle_.getPosition().y};
    }

    void CircleShape::setRotation(float angle) {
        impl_->circle_.setRotation(angle);
    }

    void CircleShape::rotate(float angle) {
        impl_->circle_.rotate(angle);
    }

    float CircleShape::getRotation() const {
        return impl_->circle_.getRotation();
    }

    void CircleShape::setScale(float factorX, float factorY) {
        impl_->circle_.setScale(factorX, factorY);
    }

    void CircleShape::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void CircleShape::scale(float factorX, float factorY) {
        impl_->circle_.scale(factorX, factorY);
    }

    void CircleShape::scale(Vector2f offset) {
        impl_->circle_.scale({offset.x, offset.y});
    }

    Vector2f CircleShape::getScale() const {
        return {impl_->circle_.getScale().x, impl_->circle_.getScale().y};
    }

    void CircleShape::setOrigin(float x, float y) {
        impl_->circle_.setOrigin(x, y);
    }

    void CircleShape::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f CircleShape::getOrigin() const {
        return {impl_->circle_.getOrigin().x, impl_->circle_.getOrigin().y};
    }

    void CircleShape::move(float offsetX, float offsetY) {
        impl_->circle_.move(offsetX, offsetY);
    }

    void CircleShape::move(Vector2f offset) {
        impl_->circle_.move({offset.x, offset.y});
    }

    void CircleShape::draw(Window &renderTarget) const {
        renderTarget.draw(impl_->circle_);
    }

    CircleShape::~CircleShape() = default;
}
