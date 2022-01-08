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

#ifndef IME_TEXTURECONTAINER_H
#define IME_TEXTURECONTAINER_H

#include "IME/Config.h"
#include "IME/common/Object.h"
#include "IME/graphics/Texture.h"
#include "IME/core/tilemap/Index.h"
#include "IME/common/Vector2.h"
#include <string>

namespace ime {
    /**
     * @brief Abstract base class for image containers
     *
     * A sprite image is a collection of smaller images packed together into
     * a single image. The sub-images may be of the same size or of varying
     * dimensions. In addition, the sub-images may be arranged in grid
     * formation or tightly packed next to each other in the sprite image. A
     * sprite image simplifies file management and increases performance as we
     * only have to deal with a single texture instead of multiple textures.
     * For example, imagine a character which has a walking and running animation
     * in all four directions (Up, right. down and left) and each animation has
     * 15 frames. This would require 120 individual images files!. With a sprite
     * image all that information can be stored in a single image file and accessed
     * later using coordinates or indexes
     */
    class IME_API SpriteImage : public Object {
    public:
        using Ptr = std::shared_ptr<SpriteImage>; //!< A shared sprite pointer

        /**
         * @brief Default constructor
         *
         * @warning This constructor creates an empty sprite image. You must
         * call create() before using the class, not doing so leads to undefined
         * behavior
         *
         * @see create
         */
        SpriteImage();
        
        /**
         * @brief Constructor
         * @param sourceTexture The filename of the sprite image on the disk
         * @param area Sub-rectangle to construct sprite image from
         * @throws FileNotFound If the image could not be found on the disk
         * 
         * The @a area can be used to construct the sprite image from a
         * sub-rectangle of the @a sourceTexture. To construct the sprite 
         * image from the whole @a sourceTexture (default), leave the @a area 
         * argument unspecified. If the @a area rectangle crosses the bounds 
         * of the @a sourceTexture, it is adjusted to fit the @a sourceTexture 
         * size
         */
        explicit SpriteImage(const std::string& sourceTexture, UIntRect area = {});

        /**
         * @brief Create the sprite image
         * @param sourceTexture The filename of the sprite image on the disk
         * @param area Sub-rectangle to construct sprite image from
         * @throws FileNotFound If the image could not be found on the disk
         *
         * The @a area can be used to construct the sprite image from a
         * sub-rectangle of the @a sourceTexture. To construct the sprite
         * image from the whole @a sourceTexture (default), leave the @a area
         * argument unspecified. If the @a area rectangle crosses the bounds
         * of the @a sourceTexture, it is adjusted to fit the @a sourceTexture
         * size
         *
         * @note Only use this function if you've previously created an empty
         * sprite image
         *
         * @see SpriteImage()
         */
        void create(const std::string& sourceTexture, UIntRect area = {});

        /**
         * @brief Copy constructor
         */
        SpriteImage(const SpriteImage&) = default;

        /**
         * @brief Copy assignment operator
         */
        SpriteImage& operator=(const SpriteImage&) = default;

        /**
         * @brief Move constructor
         */
        SpriteImage(SpriteImage&&) noexcept = default;

        /**
         * @brief Move assignment operator
         */
        SpriteImage& operator=(SpriteImage&&) noexcept = default;

        /**
         * @brief Get the size of the sprite image in pixels
         * @return The size of the sprite image in pixels
         *
         * The x component is width whilst the y component is the height
         * of the sprite image
         */
        Vector2u getSize() const;

        /**
         * @brief Get the width of the sprite image in pixels
         * @return The width of the sprite image in pixels
         */
        unsigned int getWidth() const;

        /**
         * @brief Get the height of the sprite image in pixels
         * @return The height of the sprite image in pixels
         */
        unsigned int getHeight() const;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         *
         * Note that this function is only overridden by child classes
         * of Object which also serve as a base class for other classes
         *
         * @see Object::getClassType and Object::getClassName
         */
        std::string getClassType() const override;

        /**
         * @brief Get the source texture of the sprite image
         * @return The source texture of the sprite image
         *
         * @warning Don't call this function when the sprite image is not yet
         * created. Also, the texture is destroyed when the sprite image is
         * destroyed, exercise caution when there are Sprite objects referencing
         * the sprite image texture
         *
         * @see create
         */
        const Texture& getTexture() const;

        /**
         * @brief Get the top-left position of the sprite image relative to
         *        the sprite image source texture
         * @return The relative top-left position
         *
         * If the sprite image was created from the whole source texture, this
         * function returns {0, 0}
         *
         * @see SpriteImage
         */
        Vector2u getRelativePosition() const;

        /**
         * @brief Destructor
         */
        ~SpriteImage() override;

    protected:
        /**
         * @brief Check if the sprite image contains a point or not
         * @param point The point to be checked
         * @return True if the sprite image contains the @a point otherwise false
         */
        bool contains(Vector2u point) const;

    private:
        Texture::Ptr texture_; //!< The source texture
        Vector2u relativePos_; //!< The top-left position of the sprite image relative to the top-left position source texture
    };
}

#endif //IME_TEXTURECONTAINER_H
