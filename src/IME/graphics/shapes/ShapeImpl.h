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

#ifndef IME_SHAPEIMPL_H
#define IME_SHAPEIMPL_H

#include "IME/common/ITransformable.h"
#include "IME/graphics/Colour.h"
#include "IME/utility/Helpers.h"
#include "IME/graphics/WindowImpl.h"
#include "IME/graphics/Window.h"
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
        class IShapeImpl : public ITransformable {
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
            virtual void draw(Window &renderTarget) const = 0;
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

            void setPosition(Vector2f position) override {
                setPosition(position.x, position.y);
            }

            Vector2f getPosition() const override {
                return {shape_->getPosition().x, shape_->getPosition().y};
            }

            void setRotation(float angle) override {
                shape_->setRotation(angle);
            }

            void rotate(float angle) override {
                setRotation(getRotation() + angle);
            }

            float getRotation() const override {
                return shape_->getRotation();
            }

            void setScale(float factorX, float factorY) override {
                shape_->setScale(factorX, factorY);
            }

            void setScale(Vector2f scale) override {
                setScale(scale.x, scale.y);
            }

            void scale(float factorX, float factorY) override {
                setScale(getScale().x * factorX, getScale().y * factorY);
            }

            void scale(Vector2f offset) override {
                scale(offset.x, offset.y);
            }

            Vector2f getScale() const override {
                return {shape_->getScale().x, shape_->getScale().y};
            }

            void setOrigin(float x, float y) override {
                shape_->setOrigin(x, y);
            }

            void setOrigin(Vector2f origin) override {
                setOrigin(origin.x, origin.y);
            }

            Vector2f getOrigin() const override {
                return {shape_->getOrigin().x, shape_->getOrigin().y};
            }

            void move(float offsetX, float offsetY) override {
                shape_->move(offsetX, offsetY);
            }

            void move(Vector2f offset) override {
                shape_->move({offset.x, offset.y});
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

            void draw(Window &renderTarget) const override {
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
