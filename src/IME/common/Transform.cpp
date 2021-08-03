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

#include "IME/common/Transform.h"
#include <cmath>

namespace ime {
    Transform::Transform() :
        scale_{1.0f, 1.0f},
        rotation_{0.0f}
    {}

    void Transform::setPosition(float x, float y) {
        if (position_.x == x && position_.y == y)
            return;

        position_.x = x;
        position_.y = y;

        if (onPropertyChange_)
            onPropertyChange_(Property{"position", position_});
    }

    void Transform::setPosition(const Vector2f& position) {
        setPosition(position.x, position.y);
    }

    const Vector2f& Transform::getPosition() const {
        return position_;
    }

    void Transform::setRotation(float angle) {
        float newRotation = static_cast<float>(fmod(static_cast<double>(angle), 360));
        if (rotation_ == newRotation)
            return;

        rotation_ = newRotation;
        if (rotation_ < 0)
            rotation_ += 360.f;

        if (onPropertyChange_)
            onPropertyChange_(Property{"rotation", rotation_});
    }

    void Transform::rotate(float angle) {
        setRotation(rotation_ + angle);
    }

    float Transform::getRotation() const {
        return rotation_;
    }

    void Transform::setScale(float factorX, float factorY) {
        if (scale_.x == factorX && scale_.y == factorY)
            return;

        scale_.x = factorX;
        scale_.y = factorY;

        if (onPropertyChange_)
            onPropertyChange_(Property{"scale", scale_});
    }

    void Transform::setScale(const Vector2f& scale) {
        setScale(scale.x, scale.y);
    }

    void Transform::scale(float factorX, float factorY) {
        setScale(scale_.x * factorX, scale_.y * factorY);
    }

    void Transform::scale(const Vector2f& offset) {
        setScale(scale_.x * offset.x, scale_.y * offset.y);
    }

    const Vector2f& Transform::getScale() const {
        return scale_;
    }

    void Transform::setOrigin(float x, float y) {
        if (origin_.x == x && origin_.y == y)
            return;

        origin_.x = x;
        origin_.y = y;

        if (onPropertyChange_)
            onPropertyChange_(Property{"origin", origin_});
    }

    void Transform::setOrigin(const Vector2f& origin) {
        setOrigin(origin.x, origin.y);
    }

    const Vector2f& Transform::getOrigin() const {
        return origin_;
    }

    void Transform::move(float offsetX, float offsetY) {
        setPosition(position_.x + offsetX, position_.y + offsetY);
    }

    void Transform::move(const Vector2f& offset) {
        move(offset.x, offset.y);
    }

    void Transform::onPropertyChange(Callback<const Property&> callback) {
        onPropertyChange_ = std::move(callback);
    }
}
