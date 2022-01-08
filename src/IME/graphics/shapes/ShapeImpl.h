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

#ifndef IME_SHAPEIMPL_H
#define IME_SHAPEIMPL_H

#include "IME/common/ITransformable.h"
#include "IME/graphics/Colour.h"
#include "IME/utility/Helpers.h"
#include "IME/graphics/RenderTargetImpl.h"
#include "IME/graphics/RenderTarget.h"
#include <SFML/Graphics/Shape.hpp>
#include <memory>

namespace ime {
    namespace priv {
        /**
         * @brief Interface for ShapeImpl class template
         *
         * This interface allows us to store instances of ShapeImpl inside
         * non-template classes. The interface is necessary because you can't
         * have a template variable inside a non-template class unless the
         * variable is static which is not the case in this case because each
         * shape is a different type
         */
        class IShapeImpl {
        public:
            /**
             * @brief Make a copy of the the implementation
             * @return A copy of the implementation
             *
             * We returning std::unique_ptr to make sure each shape has its
             * own implementation
             */
            virtual std::unique_ptr<IShapeImpl> clone() = 0;

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
            virtual void setPosition(float x, float y) = 0;

            /**
             * @brief Get the position of the shape
             * @return Current position of the shape
             */
            virtual Vector2f getPosition() const = 0;

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
            virtual void setRotation(float angle) = 0;

            /**
             * @brief Get the orientation of the shape
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            virtual float getRotation() const = 0;

            /**
             * @brief Set the scale factors of the shape
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            virtual void setScale(float factorX, float factorY) = 0;

            /**
             * @brief Get the current scale of the shape
             * @return Current scale of the shape
             */
            virtual Vector2f getScale() const = 0;

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
            virtual void setOrigin(float x, float y) = 0;

            /**
             * @brief Get the local origin of the shape
             * @return Local origin of the shape
             */
            virtual Vector2f getOrigin() const = 0;

            /**
             * @brief Set the fill colour of the shape
             * @param colour The new colour of the shape
             *
             *  By default, the shape's fill colour is opaque white.
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
             * @internal
             * @brief Get the internal pointer to a third party shape object
             * @return The internal pointer to a third party shape object
             *
             * @warning This function is intended for internal use only and
             * should never be called
             */
            virtual std::shared_ptr<sf::Shape> getInternalPtr() = 0;

            /**
             * @brief Draw the shape on a render target
             * @param renderTarget Target to draw object on
             */
            virtual void draw(priv::RenderTarget &renderTarget) const = 0;

            /**
             * @brief Destructor
             */
            virtual ~IShapeImpl() = default;
        };

        /*---------------------------------------------------------------------
         # class IShapeImpl implementation
         --------------------------------------------------------------------*/

        /**
         * @brief Shape implementation
         *
         * This class aims to reduce code repetition since all shape classes
         * keep an instance of a third party Shape and delegate to it, so most 
         * of the implementation is the same for some common functions
         */
        template <typename T>
        class ShapeImpl : public IShapeImpl {
        public:
            explicit ShapeImpl(std::shared_ptr<T> shape) :
                shape_{std::move(shape)}
            {}

            ShapeImpl(const ShapeImpl& other) :
                shape_{std::make_shared<T>(*other.shape_)}
            {}

            ShapeImpl& operator=(const ShapeImpl& rhs) {
                if (this != &rhs) {
                    shape_ = rhs.shape_;
                }

                return *this;
            }

            ShapeImpl(ShapeImpl&& other) noexcept {
                *this = std::move(other);
            }

            ShapeImpl& operator=(ShapeImpl&& rhs) noexcept {
                if (this != &rhs) {
                    shape_ = std::move(rhs.shape_);
                }

                return *this;
            }

            std::unique_ptr<IShapeImpl> clone() override {
                return std::make_unique<ShapeImpl<T>>(*this);
            }

            void setPosition(float x, float y) override {
                shape_->setPosition(x, y);
            }

            Vector2f getPosition() const override {
                return {shape_->getPosition().x, shape_->getPosition().y};
            }

            void setRotation(float angle) override {
                shape_->setRotation(angle);
            }

            float getRotation() const override {
                return shape_->getRotation();
            }

            void setScale(float factorX, float factorY) override {
                shape_->setScale(factorX, factorY);
            }

            Vector2f getScale() const override {
                return {shape_->getScale().x, shape_->getScale().y};
            }

            void setOrigin(float x, float y) override {
                shape_->setOrigin(x, y);
            }

            Vector2f getOrigin() const override {
                return {shape_->getOrigin().x, shape_->getOrigin().y};
            }

            void setFillColour(const Colour &colour) override {
                shape_->setFillColor(utility::convertToSFMLColour(colour));
            }

            Colour getFillColour() const override {
                return utility::convertFrom3rdPartyColour(shape_->getFillColor());
            }

            void setOutlineColour(const Colour &colour) override {
                shape_->setOutlineColor(utility::convertToSFMLColour(colour));
            }

            Colour getOutlineColour() const override {
                return utility::convertFrom3rdPartyColour(shape_->getOutlineColor());
            }

            void setOutlineThickness(float thickness) override {
                shape_->setOutlineThickness(thickness);
            }

            float getOutlineThickness() const override {
                return shape_->getOutlineThickness();
            }

            FloatRect getLocalBounds() const override {
                auto [left, top, width, height] = shape_->getLocalBounds();
                return {left, top, width, height};
            }

            FloatRect getGlobalBounds() const override {
                auto [left, top, width, height] = shape_->getGlobalBounds();
                return {left, top, width, height};
            }

            void draw(priv::RenderTarget &renderTarget) const override {
                renderTarget.getImpl()->getSFMLWindow().draw(*shape_);
            }

            std::shared_ptr<sf::Shape> getInternalPtr() override {
                return shape_;
            }
            
            ~ShapeImpl() override = default;

        private:
            std::shared_ptr<T> shape_; //!< Pointer to third party shape
        };
    }
}

#endif //IME_SHAPEIMPL_H
