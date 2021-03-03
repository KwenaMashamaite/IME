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
#include "IME/common/Rect.h"
#include "IME/common/ITransformable.h"
#include "IME/common/Object.h"
#include "IME/core/time/Time.h"
#include "IME/graphics/IDrawable.h"
#include "IME/graphics/Colour.h"
#include "IME/graphics/Texture.h"
#include "IME/core/animation/Animator.h"
#include <string>
#include <memory>

namespace ime {
    /**
     * @brief Drawable representation of a texture
     *
     * The sprite can be static (display a single non changing texture)
     * or animated via its animator (see the getAnimator function)
     */
    class IME_API Sprite : public ITransformable, public IDrawable {
    public:
        using Ptr = std::shared_ptr<Sprite>; //!< Shared sprite pointer

        /**
         * @brief Construct an empty sprite
         *
         * @see setTexture and setTextureRect
         */
        Sprite();

        /**
         * @brief Construct a sprite from a texture
         * @param texture Filename of the texture to construct the sprite from
         *
         * @see setTextureRect
         */
        Sprite(const std::string& texture);

        /**
         * @brief Construct a sprite from a texture
         * @param texture Texture to construct sprite from
         *
         * @see setTextureRect
         */
        Sprite(const Texture& texture);

        /**
         * @brief Construct the sprite from a sub-rectangle of a source texture
         * @param texture The source texture
         * @param rectangle Sub-rectangle of the texture to assign to the sprite
         *
         * This function is a shortcut for:
         *
         * @code
         * auto sprite = Sprite();
         * sprite.setTexture(texture);
         * sprite.setTextureRect(rectangle);
         * @endcode
         *
         * @see setTexture and setTextureRect
         */
        Sprite(const Texture& texture, const UIntRect& rectangle);

        /**
         * @brief Copy constructor
         */
        Sprite(const Sprite&);

        /**
         * @brief Copy assignment operator
         */
        Sprite& operator=(const Sprite&);

        /**
         * @brief Move constructor
         */
        Sprite(Sprite&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        Sprite& operator=(Sprite&&) noexcept;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Set the texture of the object
         * @param filename Filename of the texture to set
         * @throws FileNotFound if the specified texture cannot be found
         *         in the images path
         *
         * This function will set the texture to the whole image
         */
        void setTexture(const std::string &filename);

        /**
         * @brief Set the texture of the sprite from a source texture
         * @param texture The source texture
         *
         * The @a texture argument refers to a texture that must exist as
         * long as the sprite uses it. Indeed, the sprite doesn't store its
         * own copy of the texture, but rather keeps a pointer to the one
         * that you passed to this function. If the source texture is destroyed
         * and the sprite tries to use it, the behavior is undefined
         */
        void setTexture(const Texture& texture);

        /**
         * @brief Get the name of the texture used by the sprite
         * @return Name of the texture used by the sprite
         */
        const Texture& getTexture() const;

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
        void setTextureRect(unsigned int left, unsigned int top, unsigned int width,
            unsigned int height);

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
        void setTextureRect(const UIntRect& rect);

        /**
         * @brief Get the sub-rectangle of the texture displayed
         *        by the sprite
         * @return The sub-rectangle of the texture displayed by the
         *         sprite
         */
        UIntRect getTextureRect() const;

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
         * @brief Show or hide the sprite
         * @param visible True to show or false to hide
         *
         * When hidden the sprite will not be shown on the render target
         *
         * By default, the sprite is visible
         */
        void setVisible(bool visible);

        /**
         * @brief Check whether or not the sprite is visible
         * @return True if visible, otherwise false
         */
        bool isVisible() const;

        /**
         * @brief Toggle the visibility of the sprite
         *
         * This function will hide the sprite if its currently
         * visible or show it if it is currently hidden
         */
        void toggleVisibility();

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
         * @brief Get the sprites animator
         * @return The sprites animator
         *
         * This function enables the sprite to be animated
         *
         * checkout the Animator class
         */
        Animator& getAnimator();

        /**
         * @brief Update the current animation
         * @param deltaTime Time passed since last animation update
         *
         * This function need only be called if the sprite is animatable
         * and not just displaying a single static image
         */
        void updateAnimation(Time deltaTime);

        /**
         * @brief Swap this sprite with another sprite
         * @param other The sprite to be swapped with this sprite
         */
        void swap(Sprite& other);

        /**
         * @brief Destructor
         */
        ~Sprite();

    private:
        struct SpriteImpl;
        std::unique_ptr<SpriteImpl> pImpl_;
    };
}

#endif // IME_SPRITE_H
