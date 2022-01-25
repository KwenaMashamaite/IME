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

#include "IME/graphics/shapes/Shape.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/physics/rigid_body/PhysicsEngine.h"
#include "IME/graphics/shapes/ShapeImpl.h"

namespace ime {
    Shape::Shape(std::unique_ptr<priv::IShapeImpl> impl, Type type) :
        pimpl_{std::move(impl)},
        type_{type},
        postStepId_{-1},
        destructionId_{-1},
        propertyChangeId_{-1}
    {}

    Shape::Shape(const Shape& other) :
        Drawable(other),
        pimpl_{other.pimpl_->clone()},
        type_{other.type_},
        body_{},
        postStepId_{-1},
        destructionId_{-1},
        propertyChangeId_{-1}
    {
        if (other.body_)
            attachRigidBody(other.body_->copy());
    }

    Shape &Shape::operator=(const Shape& rhs) {
        if (this != &rhs) {
            Drawable::operator=(rhs);
            pimpl_ = rhs.pimpl_->clone();
            type_ = rhs.type_;

            if (!body_) {
                if (rhs.body_)
                    attachRigidBody(rhs.body_->copy());
                else {
                    postStepId_ = -1;
                    destructionId_ = -1;
                    propertyChangeId_ = -1;
                }
            }
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

    void Shape::attachRigidBody(RigidBody::Ptr body) {
        IME_ASSERT(body, "Invalid rigid body, cannot attach a nullptr to a shape")
        IME_ASSERT(!body_, "Shape already has a rigid body attached, remove it first before attaching another one")
        body_ = std::move(body);
        setOrigin(getLocalBounds().width / 2.0f, getLocalBounds().height / 2.0f);
        body_->setPosition(getPosition());
        body_->setRotation(getRotation());

        // Synchronize the shape's transform with that of its rigid body
        if (body_->getType() == RigidBody::Type::Dynamic) {
            postStepId_ = body_->getWorld()->getScene().on_("postStep", Callback<Time>([this](Time) {
                setPosition(body_->getPosition());
                setRotation(body_->getRotation());
            }));

            destructionId_ = body_->getWorld()->getScene().onDestruction([this] {
                postStepId_ = destructionId_ = -1;
            });

            onDestruction([this] {
                if (destructionId_ != -1 && body_) {
                    body_->getWorld()->getScene().removeDestructionListener(destructionId_);
                    destructionId_ = -1;
                }
            });
        } else {
            propertyChangeId_ = onPropertyChange([this](const Property& property) {
                if (body_) {
                    if (property.getName() == "position")
                        body_->setPosition(property.getValue<Vector2f>());
                    else if (property.getName() == "rotation")
                        body_->setRotation(property.getValue<float>());
                }
            });
        }
    }

    void Shape::removeRigidBody() {
        if (body_) {
            if (body_->getType() == RigidBody::Type::Dynamic) {
                body_->getWorld()->getScene().unsubscribe_("postStep", postStepId_);
                postStepId_ = -1;
            } else {
                unsubscribe("propertyChange", propertyChangeId_);
                propertyChangeId_ = -1;
            }

            body_.reset();
        }
    }

    const RigidBody::Ptr& Shape::getRigidBody() {
        return body_;
    }

    const RigidBody::Ptr& Shape::getRigidBody() const {
        return body_;
    }

    bool Shape::hasRigidBody() const {
        return body_ != nullptr;
    }

    void Shape::setFillColour(const Colour &colour) {
        if (getFillColour() == colour)
            return;

        pimpl_->setFillColour(colour);
        emitChange(Property{"fillColour", colour});
    }

    Colour Shape::getFillColour() const {
        return pimpl_->getFillColour();
    }

    void Shape::setOutlineColour(const Colour &colour) {
        if (getOutlineColour() == colour)
            return;

        pimpl_->setOutlineColour(colour);
        emitChange(Property{"outlineColour", colour});
    }

    Colour Shape::getOutlineColour() const {
        return pimpl_->getOutlineColour();
    }

    void Shape::setOutlineThickness(float thickness) {
        if(getOutlineThickness() == thickness)
            return;

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
        Vector2f pos = getPosition();

        if (pos.x == x && pos.y == y)
            return;

        pimpl_->setPosition(x, y);
        emitChange(Property{"position", getPosition()});
    }

    void Shape::setPosition(const Vector2f& position) {
        setPosition(position.x, position.y);
    }

    Vector2f Shape::getPosition() const {
        return pimpl_->getPosition();
    }

    void Shape::setRotation(float angle) {
        if (getRotation() == angle)
            return;

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
        Vector2f scale = getScale();
        if (scale.x == factorX && scale.y == factorY)
            return;

        pimpl_->setScale(factorX, factorY);
        emitChange(Property{"scale", getScale()});
    }

    void Shape::setScale(const Vector2f& scale) {
        setScale(scale.x, scale.y);
    }

    void Shape::scale(float factorX, float factorY) {
        setScale(getScale().x * factorX, getScale().y * factorY);
    }

    void Shape::scale(const Vector2f& factor) {
        scale(factor.x, factor.y);
    }

    Vector2f Shape::getScale() const {
        return pimpl_->getScale();
    }

    void Shape::setOrigin(float x, float y) {
        Vector2f origin = getOrigin();

        if (origin.x == x && origin.y == y)
            return;

        pimpl_->setOrigin(x, y);
        emitChange(Property{"origin", getOrigin()});
    }

    void Shape::setOrigin(const Vector2f& origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f Shape::getOrigin() const {
        return pimpl_->getOrigin();
    }

    void Shape::move(float offsetX, float offsetY) {
        setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    }

    void Shape::move(const Vector2f& offset) {
        move(offset.x, offset.y);
    }

    void Shape::draw(priv::RenderTarget &renderTarget) const {
        pimpl_->draw(renderTarget);
    }

    std::shared_ptr<void> Shape::getInternalPtr() const {
        return pimpl_->getInternalPtr();
    }

    Shape::~Shape() {
        if (postStepId_ != -1)
            body_->getWorld()->getScene().unsubscribe_("postStep", postStepId_);

        if (destructionId_ != -1)
            body_->getWorld()->getScene().removeDestructionListener(destructionId_);
    }
}
