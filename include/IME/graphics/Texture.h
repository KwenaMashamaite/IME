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

#ifndef IME_TEXTURE_H
#define IME_TEXTURE_H

#include "IME/Config.h"
#include "IME/common/Rect.h"
#include <memory>
#include <string>

/// @internal
namespace sf {
    class Texture;
}

namespace ime {
    /// @internal
    namespace priv {
        class RenderTarget;
    }

    /**
     * @brief Image living on the graphics card that can be used for drawing
     */
    class IME_API Texture {
    public:
        using Ptr = std::shared_ptr<Texture>; //!< shared texture pointer

        /**
         * @brief Constructor
         *
         * Creates an empty texture of size {0, 0}
         *
         * @see loadFromFile
         */
        Texture();

        /**
         * @brief Construct the texture
         * @param filename Filename of the image file to load
         * @param area Area of the image to load
         * @throws FileNotFound if the @a filename cannot be found on the disk
         *
         * The @a area can be used to construct the texture from a
         * sub-rectangle of the whole image. To construct the texture from
         * the whole image (default), leave the @a area argument unspecified.
         * If the @a area rectangle crosses the bounds of the image, it is
         * adjusted to fit the image size
         */
        explicit Texture(const std::string& filename, const UIntRect& area = UIntRect());

        /**
         * @brief Copy constructor
         */
        Texture(const Texture&);

        /**
         * @brief Copy assignment operator
         */
        Texture& operator=(const Texture&);

        /**
         * @brief Move constructor
         */
        Texture(Texture&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        Texture& operator=(Texture&&) noexcept;

        /**
         * @brief Create an empty texture
         * @param width The width of the texture
         * @param height The height of the texture
         * @return True if the texture was created successfully, or false
         *         if the creation failed
         *
         * You can use this function if you want the texture to have a
         * size but intend to load the image file at a later time.
         *
         * This function fails if the specified size is invalid. The size
         * must be greater than zero but less than the maximum allowed
         * size of the texture (see getMaximumSize()). If this function
         * fails, the texture is left unchanged
         *
         * @see loadFromFile
         */
        bool create(unsigned int width, unsigned int height);

        /**
         * @brief Create an empty texture
         * @param size The size of the texture
         * @return True if the texture was created successfully, or false
         *         if the creation failed
         *
         * You can use this function if you want the texture to have a
         * size but intend to load the image file at a later time.
         *
         * This function fails if the specified size is invalid. The size
         * must be greater than zero but less than the maximum allowed
         * size of the texture (see getMaximumSize()). If this function
         * fails, the texture is left unchanged
         *
         * @see loadFromFile
         */
        bool create(const Vector2u& size);

        /**
         * @brief Load the texture from an image on the disk
         * @param filename Filename of the image file to load
         * @param area Area of the image to load
         * @throws FileNotFound if the @a filename cannot be found on the disk
         *
         * The @a area can be used to construct the texture from a sub-rectangle
         * of the whole image. To construct the texture from the whole image
         * (default), leave the @a area argument unspecified. If the @a area
         * rectangle crosses the bounds of the image, it is adjusted to fit
         * the image size
         */
        void loadFromFile(const std::string& filename, const UIntRect& area = UIntRect());

        /**
         * @brief Save the texture to file on disk
         * @param filename Path of the file to save
         * @return True if the texture was saved successfully, or false if
         *         the texture is empty
         *
         * The format of the image is automatically deduced from the file
         * extension. The supported image formats are bmp, png, tga and jpg.
         * The destination file is overwritten if it already exists
         *
         * @note This function performs a slow operation
         */
        bool saveToFile(const std::string& filename);

        /**
         * @brief Get the size of the texture
         * @return The size of the texture in pixels
         */
        Vector2u getSize() const;

        /**
         * @brief Enable or disable the smooth filter
         * @param smooth True to enable smoothing or false to disable it
         *
         * When the filter is activated, the texture appears smoother so
         * that pixels are less noticeable. However if you want the texture
         * to look exactly the same as its source file, you should leave it
         * disabled
         *
         * The smooth filter is disabled by default
         */
        void setSmooth(bool smooth);

        /**
         * @brief Check whether the smooth filter is enabled or not
         * @return True if smoothing is enabled, false if it is disabled
         *
         * @see setSmooth
         */
        bool isSmooth() const;

        /**
         * @brief Enable or disable repeating
         * @param repeated True to repeat the texture, false to disable repeating
         *
         * Repeating is involved when using texture coordinates  outside
         * the texture rectangle [0, 0, width, height]. In this case, if
         * repeat mode is enabled, the whole texture will be repeated as
         * many times as needed to reach the coordinate (for example, if
         * the X texture coordinate is 3 * width, the texture will be
         * repeated 3 times). If repeat mode is disabled, the "extra space"
         * will instead be filled with border pixels.
         *
         * Repeating is disabled by default.
         *
         * @warning On very old graphics cards, white pixels may appear when
         * the texture is repeated. With such cards, repeat mode  can be used
         * reliably only if the texture has power-of-two dimensions
         * (such as 256x128).
         */
        void setRepeated(bool repeated);

        /**
         * @brief Check whether the texture is repeated or not
         * @return True if repeat mode is enabled, false if it is disabled
         *
         * @see setRepeated
         */
        bool isRepeated() const;

        /**
         * @brief Get the maximum texture size allowed
         * @return The maximum size allowed for textures, in pixels
         *
         * This maximum size is defined by the graphics driver.
         * You can expect a value of 512 pixels for low-end graphics
         * card, and up to 8192 pixels or more for newer hardware.
         */
        static unsigned int getMaximumSize();

        /**
         * @brief Get the filename of the image the texture was loaded from
         * @return The filename of the image the texture was created from
         */
        const std::string& getFilename() const;

        /**
         * @internal
         * @brief Update the texture from sub-area of the render target
         * @param x X X offset in the texture where to copy the source window
         * @param y Y Y offset in the texture where to copy the source window
         *
         * Note that the size of @a renderTarget must be less than or equal
         * to the size of the texture. Passing a render target bigger than
         * the texture will lead to an undefined behavior. In addition, note
         * that this function does nothing if either the texture or the
         * @a renderTarget  was not previously created.
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         *
         * @see create
         */
        void update(const priv::RenderTarget& renderTarget, unsigned int x, unsigned int y);

        /**
         * @brief Check if this texture is not the same as another texture
         * @param other The texture to compare against this texture
         * @return True if the two textures are not the same, otherwise false
         */
        bool operator!=(const Texture& other) const;

        /**
         * @internal
         * @brief Get the internal texture
         * @return The internal texture
         *
         * This function is intended for internal use and must not be
         * called outside of IME
         */
        const sf::Texture& getInternalTexture() const;

        /**
         * @brief Destructor
         */
        ~Texture();

    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl_;
    };
}

#endif //IME_TEXTURE_H
