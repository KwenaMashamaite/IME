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

#ifndef IME_TEXTUREATLAS_H
#define IME_TEXTUREATLAS_H

#include "IME/Config.h"
#include "IME/graphics/SpriteImage.h"
#include <optional>

namespace ime {
    class Sprite;

    /**
     * @brief A SpriteImage with no size and arrangement restrictions
     *
     * Unlike a SpriteSheet, a texture atlas may have uniformly-sized images
     * or images of varying dimensions. The images need not be arranged in grid
     * formation or in any order at all. Instead of retrieving images with
     * indexes, we use frames. The frame specifies the top-left position, the
     * width and height of the image to be retrieved. A texture atlas usually
     * stores level textures such as walls, doors, floor, ground etc. In a
     * tile-based game, the complete set is often called a tileset
     */
    class IME_API TextureAtlas : public SpriteImage {
    public:
        using Ptr = std::shared_ptr<TextureAtlas>; //!< Shared texture atlas pointer
        using Frame = UIntRect; //!< A texture atlas image

        /**
         * @brief Default constructor
         *
         * @warning You must call ime::SpriteImage::create (inherited) before
         * using the object, not doing so leads to undefined behaviour
         *
         * @see ime::SpriteImage::create
         */
        TextureAtlas();

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
        explicit TextureAtlas(const std::string& sourceTexture, UIntRect area = {});

        /**
         * @brief Copy constructor
         */
        TextureAtlas(const TextureAtlas&) = default;

        /**
         * @brief Copy assignment operator
         */
        TextureAtlas& operator=(const TextureAtlas&) = default;

        /**
         * @brief Move constructor
         */
        TextureAtlas(TextureAtlas&&) noexcept = default;

        /**
         * @brief Move assignment operator
         */
        TextureAtlas& operator=(TextureAtlas&&) noexcept = default;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Get the sub-image at the specified position as a sprite
         * @param frame The frame of the image to be retrieved
         * @return The sprite corresponding to @a frame or an empty sprite
         *          @a frame does not lie within or extends beyond the texture
         *          atlas
         *
         * @a frame is split as follows: {left, top, width, height}. For example
         * to get a crate texture at the position (100, 45) with the dimensions
         * (32, 16), you would:
         *
         * @code
         * auto crate = textureAtlas.getSprite({100, 45, 32, 16});
         * @endcode
         */
        Sprite getSprite(Frame frame);

        /**
         * @brief Destructor
         */
        ~TextureAtlas() override;
    };
}

#endif //IME_TEXTUREATLAS_H
