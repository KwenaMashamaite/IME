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

namespace ime {
    /**
     * @brief Drawable representation of a texture
     */
    class IME_API Sprite : public ITransformable, public IDrawable {
    public:
        /**
         * @brief Default constructor
         */
        Sprite();

        /**
         * @brief Set the texture of the object
         * @param filename Filename of the texture to set
         * @throws FileNotFound if the specified texture cannot be found
         *         in the images path
         */
        void setTexture(const std::string &filename);

        /**
         * @brief Get the name of the texture used by the sprite
         * @return Name of the texture used by the sprite
         */
        const std::string& getTexture() const;

        /**
         * @brief Set the sub-rectangle of the texture that the sprite
         *        will  display
         * @param left horizontal starting position
         * @param top Vertical starting position
         * @param width Width of the sub-rectangle
         * @param height Height of the sub-rectangle
         *
         * This function will set the texture that the sprite displays
         * to a portion of the entire texture. The displaying will start
         * at the specified starting position
         *
         * By default, the sprite displays the entire texture
         */
        void setTextureRect(int left, int top, int width, int height);

        /**
         * @brief Set the sub-rectangle of the texture that the
         *        sprite will display
         * @param rect The rectangle to set
         *
         * This function will set the texture that the sprite displays to a
         * portion of the entire texture.
         *
         * By default, the sprite displays the entire texture
         */
        void setTextureRect(IntRect rect);

        /**
         * @brief Get the sub-rectangle of the texture displayed
         *        by the sprite
         * @return The sub-rectangle of the texture displayed by the
         *         sprite
         */
        IntRect getTextureRect() const;

        /**
         * @brief Set the colour of the sprite
         * @param colour New colour opf the sprite
         */
        void setColour(Colour colour);

        /**
         * @brief Get the colour of the sprite
         * @return The colour of the sprite
         */
        Colour getColour() const;

        /**
         * @brief Get the local bounding rectangle of the sprite
         * @return Local bounding rectangle of the sprite
         *
         * The returned rectangle is in local coordinates, which means
         * that it ignores the transformations (translation, rotation,
         * scale, ...) that are applied to the sprite. In other words,
         * this function returns the bounds of the sprite in the sprite's
         * coordinate system
         */
        FloatRect getLocalBounds() const;

        /**
         * @brief Get the global bounding rectangle of the sprite
         * @return Global bounding rectangle of the sprite
         *
         * The returned rectangle is in global coordinates, which means
         * that it takes into account the transformations (translation,
         * rotation, scale, ...) that are applied to the sprite. In other
         * words, this function returns the bounds of the sprite in the
         * global 2D world's coordinate system
         */
        FloatRect getGlobalBounds() const;

        /**
         * @brief Set the position of the sprite
         * @param x X coordinate of the new position
         * @param y Y coordinate of the new position
         *
         * This function completely overwrites the previous position.
         * use move function to apply an offset based on the previous
         * position instead
         *
         * The default position of a the sprite is (0, 0)
         *
         * @see move
         */
        void setPosition(float x, float y) override;

        /**
         * @brief Set the position of the sprite
         * @param position New position
         *
         * This function completely overwrites the previous position.
         * Use the move function to apply an offset based on the previous
         * position instead.
         *
         * The default position of the sprite is (0, 0)
         *
         * @see move
         */
        void setPosition(Vector2f position) override;

        /**
         * @brief Get the position of the sprite
         * @return Current position of the sprite
         */
        Vector2f getPosition() const override;

        /**
         * @brief Set the orientation of the sprite
         * @param angle New rotation, in degrees
         *
         * This function completely overwrites the previous rotation.
         * See the rotate function to add an angle based on the previous
         * rotation instead.
         *
         * The default rotation of the sprite is 0
         *
         * @see rotate
         */
        void setRotation(float angle) override;

        /**
         * @brief Rotate the sprite
         * @param angle Angle of rotation, in degrees
         *
         * This function adds to the current rotation of the sprite,
         * unlike setRotation which overwrites it
         *
         * @see setRotation
         */
        void rotate(float angle) override;

        /**
         * @brief Get the orientation of the sprite
         * @return Current rotation, in degrees
         *
         * The rotation is always in the range [0, 360]
         */
        float getRotation() const override;

        /**
         * @brief Set the scale factors of the sprite
         * @param factorX New horizontal scale factor
         * @param factorY New vertical scale factor
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(float factorX, float factorY) override;

        /**
         * @brief Set the scale factor of the sprite
         * @param scale New scale
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(Vector2f scale) override;

        /**
         * @brief Scale the sprite by an offset
         * @param factorX Horizontal scale factor
         * @param factorY Vertical scale factor
         *
         * This function multiplies the current scale of the sprite,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(float factorX, float factorY) override;

        /**
         * @brief Scale the sprite by an offset
         * @param offset Offset to apply
         *
         * This function multiplies the current scale of the sprite,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(Vector2f offset) override;

        /**
         * @brief Get the current scale of the sprite
         * @return Current scale of the sprite
         */
        Vector2f getScale() const override;

        /**
         * @brief Set the local origin of the sprite
         * @param x X coordinate of the new origin
         * @param y Y coordinate of the new origin
         *
         * The origin of the sprite defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the sprite, and ignore all
         * transformations (position, scale, rotation).
         *
         * The default origin of the sprite is (0, 0)
         */
        void setOrigin(float x, float y) override;

        /**
         * @brief Set the local origin of the sprite
         * @param origin New origin
         *
         * The origin of the sprite defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the sprite, and ignore all
         * transformations (position, scale, rotation).
         *
         * The default origin of the sprite is (0, 0)
         */
        void setOrigin(Vector2f origin) override;

        /**
         * @brief Get the local origin of the sprite
         * @return Local origin of the sprite
         */
        Vector2f getOrigin() const override;

        /**
         * @brief Move the sprite by a given offset
         * @param offsetX Horizontal offset
         * @param offsetY Vertical offset
         *
         * This function adds to the current position of the sprite,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(float offsetX, float offsetY) override;

        /**
         * @brief Move the sprite by a given offset
         * @param offset Offset to apply
         *
         * This function adds to the current position of the sprite,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(Vector2f offset) override;

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
        sf::Sprite sprite_;           //!< Third party sprite
        std::string textureFileName_; //!< Filename of the texture used by the object
        bool isHidden_;               //!< Hidden state
        Colour prevSpriteColour;      //!< Sprite colour before it was hidden
    };
}

#endif // IME_SPRITE_H
