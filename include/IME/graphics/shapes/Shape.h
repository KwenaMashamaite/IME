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
#include "IME/graphics/Drawable.h"
#include "IME/graphics/Colour.h"
#include "IME/common/Rect.h"
#include "IME/core/physics/rigid_body/RigidBody.h"
#include <memory>

namespace ime {

    /// @internal
    namespace priv {
        class IShapeImpl;
    }

    /**
     * @brief Abstract base class for geometric figures
     *
     * Some common geometric figures are squares, rectangles and triangles
     */
    class IME_API Shape : public Drawable, public ITransformable {
    public:
        using Ptr = std::unique_ptr<Shape>; //!< Shared shape pointer

        /**
         * @brief The types of shapes
         */
        enum class Type {
            Rectangle, //!< Rectangle shape
            Circle,    //!< Circle shape
            Convex     //!< Convex polygon shape
        };

        /**
         * @internal
         * @brief Constructor
         * @param impl The widgets implementation
         * @param type The type of this shape
         */
        Shape(std::unique_ptr<priv::IShapeImpl> impl, Type type);

        /**
         * @brief Copy constructor
         */
        Shape(const Shape&);

        /**
         * @brief Copy assignment operator
         */
        Shape& operator=(const Shape&);

        /**
         * @brief Move constructor
         */
        Shape(Shape&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        Shape& operator=(Shape&&) noexcept;

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
        void attachRigidBody(RigidBody::Ptr body);

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
        const RigidBody::Ptr& getRigidBody();
        const RigidBody::Ptr& getRigidBody() const;

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
        void setFillColour(const Colour& colour);

        /**
         * @brief Get the fill colour of the shape
         * @return The fill colour of the shape
         */
        Colour getFillColour() const;

        /**
         * @brief Set the outline colour of the shape
         * @param colour The new outline colour
         *
         * By default, the shape's outline colour is opaque white.
         */
        void setOutlineColour(const Colour& colour);

        /**
         * @brief Get the outline colour of the shape
         * @return The outline colour of the shape
         */
        Colour getOutlineColour() const;

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
        void setOutlineThickness(float thickness);

        /**
         * @brief Get the outline thickness of the shape
         * @return The outline thickness of the shape
         */
        float getOutlineThickness() const;

        /**
         * @brief Get the local bounding rectangle of the shape
         * @return The local bounding rectangle of the shape
         *
         * The returned rectangle is in local coordinates, which means
         * that it ignores the transformations (translation, rotation,
         * scale, ...) that are applied to the entity
         */
        FloatRect getLocalBounds() const;

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
        FloatRect getGlobalBounds() const;

        /**
         * @brief Set the position of the shape
         * @param x X coordinate of the new position
         * @param y Y coordinate of the new position
         *
         * This function completely overwrites the previous position.
         * use move function to apply an offset based on the previous
         * position instead
         *
         * The default position of a the shape is (0, 0)
         *
         * @see move
         */
        void setPosition(float x, float y) override;

        /**
         * @brief Set the position of the shape
         * @param position New position
         *
         * This function completely overwrites the previous position.
         * Use the move function to apply an offset based on the previous
         * position instead.
         *
         * The default position of the shape is (0, 0)
         *
         * @see move
         */
        void setPosition(Vector2f position) override;

        /**
         * @brief Get the position of the shape
         * @return Current position of the shape
         */
        Vector2f getPosition() const override;

        /**
         * @brief Set the orientation of the shape
         * @param angle New rotation, in degrees
         *
         * This function completely overwrites the previous rotation.
         * See the rotate function to add an angle based on the previous
         * rotation instead.
         *
         * The default rotation of the shape is 0
         *
         * @see rotate
         */
        void setRotation(float angle) override;

        /**
         * @brief Rotate the shape
         * @param angle Angle of rotation, in degrees
         *
         * This function adds to the current rotation of the shape,
         * unlike setRotation which overwrites it
         *
         * @see setRotation
         */
        void rotate(float angle) override;

        /**
         * @brief Get the orientation of the shape
         * @return Current rotation, in degrees
         *
         * The rotation is always in the range [0, 360]
         */
        float getRotation() const override;

        /**
         * @brief Set the scale factors of the shape
         * @param factorX New horizontal scale factor
         * @param factorY New vertical scale factor
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(float factorX, float factorY) override;

        /**
         * @brief Set the scale factor of the shape
         * @param scale New scale
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(Vector2f scale) override;

        /**
         * @brief Scale the shape by an offset
         * @param factorX Horizontal scale factor
         * @param factorY Vertical scale factor
         *
         * This function multiplies the current scale of the shape,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(float factorX, float factorY) override;

        /**
         * @brief Scale the shape by an offset
         * @param factor Offset to apply
         *
         * This function multiplies the current scale of the shape,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(Vector2f factor) override;

        /**
         * @brief Get the current scale of the shape
         * @return Current scale of the shape
         */
        Vector2f getScale() const override;

        /**
         * @brief Set the local origin of the shape
         * @param x X coordinate of the new origin
         * @param y Y coordinate of the new origin
         *
         * The origin of the shape defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the shape, and ignore all
         * transformations (position, scale, rotation).
         *
         * The default origin of the shape is (0, 0)
         */
        void setOrigin(float x, float y) override;

        /**
         * @brief Set the local origin of the shape
         * @param origin New origin
         *
         * The origin of the shape defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the shape, and ignore all
         * transformations (position, scale, rotation).
         *
         * The default origin of the shape is (0, 0)
         */
        void setOrigin(Vector2f origin) override;

        /**
         * @brief Get the local origin of the shape
         * @return Local origin of the shape
         */
        Vector2f getOrigin() const override;

        /**
         * @brief Move the shape by a given offset
         * @param offsetX Horizontal offset
         * @param offsetY Vertical offset
         *
         * This function adds to the current position of the shape,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(float offsetX, float offsetY) override;

        /**
         * @brief Move the shape by a given offset
         * @param offset Offset to apply
         *
         * This function adds to the current position of the shape,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(Vector2f offset) override;

        /**
         * @brief Make a copy of the shape
         * @return A copy of the shape
         *
         * You should use this function if you don't care about the type
         * of the shape, otherwise use the shapes copy function for
         * copying purposes
         */
        virtual Shape::Ptr clone() const = 0;

        /**
         * @internal
         * @brief Draw the shape on a render target
         * @param renderTarget Target to draw object on
         *
         * @note This function is intended for internal use only
         */
        void draw(priv::Window &renderTarget) const override;

        /**
         * @brief Destructor
         */
        ~Shape() override;

    protected:
        /**
         * @internal
         * @brief Get the internal shape
         * @return The internal shape
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        std::shared_ptr<void> getInternalPtr() const;

    private:
        std::unique_ptr<priv::IShapeImpl> pimpl_;
        Type type_;              //!< The type of this shape
        RigidBody::Ptr body_;    //!< The shapes rigid body
        int postStepId_;         //!< Scene post step handler id
        int destructionId_;      //!< Scene destruction listener id
        int propertyChangeId_;   //!< Object property change handler id
    };
}

#endif //IME_SHAPE_H
