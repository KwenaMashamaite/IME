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

#ifndef IME_SHAPE_H
#define IME_SHAPE_H

#include "IME/common/ITransformable.h"
#include "IME/graphics/IDrawable.h"
#include "IME/graphics/Colour.h"
#include "IME/common/Rect.h"
#include "IME/core/physics/rigid_body/Body.h"
#include <memory>

namespace ime {
    /**
     * @brief Abstract base class for geometric figures
     *
     * Some common geometric figures are squares, rectangles and triangles
     */
    class IME_API Shape : public IDrawable, public ITransformable {
    public:
        using Ptr = std::shared_ptr<Shape>; //!< Shared shape pointer

        /**
         * @brief The types of shapes
         */
        enum class Type {
            Rectangle, //!< Rectangle shape
            Circle,    //!< Circle shape
            Convex     //!< Convex polygon shape
        };

        /**
         * @brief Constructor
         * @param type The type of this shape
         */
        explicit Shape(Type type);

        /**
         * @brief Copy constructor
         */
        Shape(const Shape&) = default;

        /**
         * @brief Copy assignment operator
         */
        Shape& operator=(const Shape&) = default;

        /**
         * @brief Move constructor
         */
        Shape(Shape&&) noexcept = default;

        /**
         * @brief Move assignment operator
         */
        Shape& operator=(Shape&&) noexcept = default;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         *
         * Note that this function is only implemented by child classes
         * of Object which also serve as a base class for other classes
         *
         * @see Object::getClassType and Object::getClassName
         */
        std::string getClassType() const override;

        /**
         * @brief Get the type of this shape
         * @return The type of the shape
         */
        Type getShapeType() const;

        /**
         * @brief Attach a rigid body to a shape
         * @param body The body to be attached
         *
         * Attaching a rigid Body to a shape enables physics for that shape.
         * This means that you should refrain from calling functions that
         * MODIFY the shapes transform (position, rotation and origin).
         * Note that the physics simulation does not account for scaling,
         * that should be handles by you
         *
         * @note Attaching a rigid body will alter the origin of the shape to
         * match the centre of mass of the body
         *
         * @warning The pointer must not be a nullptr. Also, you cannot attach
         * a rigid body to a shape that already has a rigid body attached, the
         * previous body must be removed first
         *
         * @see removeRigidBody
         */
        void attachRigidBody(Body::Ptr body);

        /**
         * @brief Remove a rigid body from the shape
         *
         * Removing a rigid Body from a shape disables all physics applied to
         * the shape. This means that the shape will not respond to forces
         * ans must be moved and rotated manually if need be
         */
        void removeRigidBody();

        /**
         * @brief Get the rigid body attached to the shape
         * @return The rigid body attached to the shape or a nullptr if the
         *         shape does not have a rigid body attached to it
         */
        Body::Ptr getRigidBody();
        const Body::Ptr getRigidBody() const;

        /**
         * @brief Check if the the shape has a rigid body attached to it or not
         * @return True if the shape has a rigid body attached to it, otherwise
         *         false
         */
        bool hasRigidBody() const;

        /**
         * @brief Set the fill colour of the shape
         * @param colour The new colour of the shape
         *
         * By default, the shape's fill colour is opaque white.
         */
        virtual void setFillColour(const Colour& colour) = 0;

        /**
         * @brief Get the fill colour of the shape
         * @return The fill colour of the shape
         */
        virtual Colour getFillColour() const = 0;

        /**
         * @brief Set the outline colour of the shape
         * @param colour The new outline colour
         *
         * By default, the shape's outline colour is opaque white.
         */
        virtual void setOutlineColour(const Colour& colour) = 0;

        /**
         * @brief Get the outline colour of the shape
         * @return The outline colour of the shape
         */
        virtual Colour getOutlineColour() const = 0;

        /**
         * @brief Set the thickness of the shape's outline
         * @param thickness The new outline thickness
         *
         * Note that negative values are allowed (so that the outline
         * expands towards the center of the shape), and using zero
         * disables the outline.
         *
         * By default, the outline thickness is 0.
         */
        virtual void setOutlineThickness(float thickness) = 0;

        /**
         * @brief Get the outline thickness of the shape
         * @return The outline thickness of the shape
         */
        virtual float getOutlineThickness() const = 0;

        /**
         * @brief Get the local bounding rectangle of the shape
         * @return The local bounding rectangle of the shape
         *
         * The returned rectangle is in local coordinates, which means
         * that it ignores the transformations (translation, rotation,
         * scale, ...) that are applied to the entity
         */
        virtual FloatRect getLocalBounds() const = 0;

        /**
         * @brief Get the global bounding rectangle of the shape
         * @return The global bounding rectangle of the shape
         *
         * The returned rectangle is in global coordinates, which means
         * that it takes into account the transformations (translation,
         * rotation, scale, ...) that are applied to the entity.
         * In other words, this function returns the bounds of the
         * shape in the global 2D world's coordinate system.
         */
        virtual FloatRect getGlobalBounds() const = 0;

        /**
         * @brief Destructor
         */
        virtual ~Shape();

    private:
        Type type_;            //!< The type of this shape
        Body::Ptr body_; //!< The shapes rigid body
        int postStepId_;       //!< Scene post step handler id
    };
}

#endif //IME_SHAPE_H
