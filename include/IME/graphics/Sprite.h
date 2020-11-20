////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Drawable representation of a texture
 */

#ifndef IME_SPRITE_H
#define IME_SPRITE_H

#include "IME/common/Vector2.h"
#include "IME/common/ITransformable.h"
#include "IDrawable.h"
#include "Colour.h"
#include "IME/core/animation/Animation.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <memory>

namespace IME {
    namespace Graphics {
        class IME_API Sprite : public ITransformable, public IDrawable {
        public:
            /**
             * @brief Default constructor
             */
            Sprite();

            /**
             * @brief Set the position of the object
             * @param X coordinate of the new position
             * @param Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * See the move function to apply an offset based on the previous
             * position instead. The default position of a transformable object
             * is (0, 0).
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the object
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * See the move function to apply an offset based on the previous
             * position instead. The default position of a transformable object
             * is (0, 0).
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the orientation of the object
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead. The default rotation of a transformable object
             * is 0.
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Set the scale factors of the object
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factors of the object
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief set the local origin of the object
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of an object defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the object, and ignore all
             * transformations (position, scale, rotation).
             * The default origin of a transformable object is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief set the local origin of the object
             * @param origin New origin
             *
             * The origin of an object defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the object, and ignore all
             * transformations (position, scale, rotation).
             * The default origin of a transformable object is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the position of the object
             * @return Current position of the object
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the local origin of the object
             * @return get the local origin of the object
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Get the orientation of the object
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360].
             */
            float getRotation() const override;

            /**
             * @brief Move the object by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the object,
             * unlike @see setPosition which overwrites it
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the object by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the object,
             * unlike @see setPosition which overwrites it
             */
            void move(Vector2f offset) override;

            /**
             * @brief Rotate the object
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the object,
             * unlike @see setRotation which overwrites it
             */
            void rotate(float angle) override;

            /**
             * @brief Scale the object by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the object,
             * unlike @see setScale which overwrites it
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the object by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the object,
             * unlike @see setScale which overwrites it
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Set the texture of the object
             * @param filename Filename of the texture to set
             * @throws FileNotFound if the specified texture cannot be found
             *         in the images path
             */
            void setTexture(const std::string &filename);

            /**
             * @brief Set the sub-rectangle of the texture that the sprite will display
             * @param left horizontal starting position
             * @param top Vertical starting position
             * @param width Width of the sub-rectangle
             * @param height Height of the sub-rectangle
             * @param size The width and height of the sub-rectangle
             *
             * This function will set the texture that the sprite displays to a
             * portion of the entire texture. The displaying will start at the
             * specified starting position. By default, the sprite displays the
             * entire texture
             */
            void setTextureRect(int left, int top, int width, int height);

            /**
             * @brief Set the sub-rectangle of the texture that the sprite will display
             * @param rect The rectangle to set
             *
             * This function will set the texture that the sprite displays to a
             * portion of the entire texture. The displaying will start at the
             * position of the @param rect. By default, the sprite displays the
             * entire texture
             */
            void setTextureRect(IntRect rect);

            /**
             * @brief Set the colour of the sprite
             * @param colour New colour opf the sprite
             */
            void setColour(Colour colour);

            /**
             * @brief Get the name of the texture used by the sprite
             * @return Name of the texture used by the sprite
             */
            const std::string& getTexture() const;

            /**
             * @brief Get the size of the object
             * @return The size of the object
             */
            Vector2f getSize() const;

            /**
             * @brief Get the colour of the sprite
             * @return The colour of the sprite
             */
            Colour getColour() const;

            /**
             * @brief Draw object on a render target
             * @param renderTarget Target to draw object on
             */
            void draw(Window &renderTarget) const override;

            /**
             * @brief Hide object
             */
            void hide() override;

            /**
             * @brief Reveal object
             */
            void show() override;

            /**
             * @brief Check if object is hidden or not
             * @return True if object is hidden, otherwise false
             */
            bool isHidden() const override;

        private:
            //Internal sprite
            sf::Sprite sprite_;
            //Filename of the texture used by the object
            std::string textureFileName_;
            //Hidden state
            bool isHidden_;
            // Sprite colour
            Colour prevSpriteColour;
        };
    }
}

#endif