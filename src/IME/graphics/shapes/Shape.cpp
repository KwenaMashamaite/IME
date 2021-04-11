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

#include "IME/graphics/shapes/Shape.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/physics/World.h"
#include "IME/graphics/shapes/ShapeImpl.h"

namespace ime {
    Shape::Shape(std::unique_ptr<priv::IShapeImpl> impl, Type type) :
        pimpl_{std::move(impl)},
        type_{type},
        postStepId_{-1}
    {}

    Shape::Shape(const Shape& other) :
        Drawable(other),
        pimpl_{other.pimpl_->clone()},
        type_{other.type_},
        body_{},
        postStepId_{-1}
    {
        if (other.body_)
            body_ = other.body_->copy();
    }

    Shape &Shape::operator=(const Shape& rhs) {
        // Can't use copy-swap idiom (class is abstract)
        if (this != &rhs) {
            Drawable::operator=(rhs);
            pimpl_ = rhs.pimpl_->clone();
            type_ = rhs.type_;
            postStepId_ = -1;

            if (rhs.body_)
                body_ = rhs.body_->copy();
        }

        return *this;
    }

    Shape::Shape(Shape &&) noexcept = default;
    Shape &Shape::operator=(Shape &&) noexcept = default;

    std::string Shape::getClassType() const {
        return "Shape";
    }

    Shape::Type Shape::getShapeType() const {
        return type_;
    }

    void Shape::attachRigidBody(Body::Ptr body) {
        IME_ASSERT(body, "Invalid rigid body, cannot attach a nullptr to a shape")
        IME_ASSERT(!body_, "Shape already has a rigid body attached, remove it first before attaching another one")
        body_ = std::move(body);
        setOrigin(getLocalBounds().width / 2.0f, getLocalBounds().height / 2.0f);
        body_->setPosition(getPosition());
        body_->setRotation(getRotation());

        // Synchronize the shape with its rigid body
        if (postStepId_ == -1) {
            postStepId_ = body_->getWorld()->getScene().on_("postStep", Callback<Time>([this](Time) {
                if (body_) {
                    setPosition(body_->getPosition());
                    setRotation(body_->getRotation());
                }
            }));
        }
    }

    void Shape::removeRigidBody() {
        if (body_) {
            body_->getWorld()->destroyBody(body_);
            body_.reset();
        }
    }

    Body::Ptr Shape::getRigidBody() {
        return body_;
    }

    Body::Ptr Shape::getRigidBody() const {
        return body_;
    }

    bool Shape::hasRigidBody() const {
        return body_ != nullptr;
    }

    void Shape::setFillColour(const Colour &colour) {
        pimpl_->setFillColour(colour);
        emitChange(Property{"fillColour", colour});
    }

    Colour Shape::getFillColour() const {
        return pimpl_->getFillColour();
    }

    void Shape::setOutlineColour(const Colour &colour) {
        pimpl_->setOutlineColour(colour);
        emitChange(Property{"outlineColour", colour});
    }

    Colour Shape::getOutlineColour() const {
        return pimpl_->getOutlineColour();
    }

    void Shape::setOutlineThickness(float thickness) {
        pimpl_->setOutlineThickness(thickness);
        emitChange(Property{"outlineThickness", thickness});
    }

    float Shape::getOutlineThickness() const {
        return pimpl_->getOutlineThickness();
    }

    FloatRect Shape::getLocalBounds() const {
        return pimpl_->getLocalBounds();
    }

    FloatRect Shape::getGlobalBounds() const {
        return pimpl_->getGlobalBounds();
    }

    void Shape::setPosition(float x, float y) {
        pimpl_->setPosition(x, y);
        emitChange({"position", getPosition()});
    }

    void Shape::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    Vector2f Shape::getPosition() const {
        return pimpl_->getPosition();
    }

    void Shape::setRotation(float angle) {
        pimpl_->setRotation(angle);
        emitChange(Property{"rotation", angle});
    }

    void Shape::rotate(float angle) {
        setRotation(getRotation() + angle);
    }

    float Shape::getRotation() const {
        return pimpl_->getRotation();
    }

    void Shape::setScale(float factorX, float factorY) {
        pimpl_->setScale(factorX, factorY);
        emitChange(Property{"scale", getScale()});
    }

    void Shape::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void Shape::scale(float factorX, float factorY) {
        setScale(getScale().x * factorX, getScale().y * factorY);
    }

    void Shape::scale(Vector2f factor) {
        scale(factor.x, factor.y);
    }

    Vector2f Shape::getScale() const {
        return pimpl_->getScale();
    }

    void Shape::setOrigin(float x, float y) {
        pimpl_->setOrigin(x, y);
        emitChange(Property{"origin", getOrigin()});
    }

    void Shape::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f Shape::getOrigin() const {
        return pimpl_->getOrigin();
    }

    void Shape::move(float offsetX, float offsetY) {
        setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    }

    void Shape::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void Shape::draw(Window &renderTarget) const {
        pimpl_->draw(renderTarget);
    }

    std::shared_ptr<void> Shape::getInternalPtr() const {
        return pimpl_->getInternalPtr();
    }

    Shape::~Shape() {
        if (postStepId_ != -1 && body_)
            body_->getWorld()->getScene().unsubscribe_("postStep", postStepId_);
    }
}
