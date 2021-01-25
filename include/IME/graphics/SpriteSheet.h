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

#ifndef IME_SPRITESHEET_H
#define IME_SPRITESHEET_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include "IME/graphics/Sprite.h"
#include "IME/core/tilemap/Index.h"
#include <string>
#include <optional>
#include <unordered_map>

namespace ime {
    /**
     * @brief Construct sprites and animation frames from a spritesheet
     *        image
     *
     * This class only supports images that are contiguous and are the
     * same size
     */
    class IME_API SpriteSheet {
    public:
        using Frame = UIntRect; //!< A frame on the spritesheet

        /**
         * @brief Create the spritesheet
         * @param texture Filename of the image used by this spritesheet
         * @param frameSize The size of each frame in the spritesheet
         * @param spacing The space between frames on the spritesheet texture
         */
        SpriteSheet(const std::string& texture, Vector2u frameSize, Vector2u spacing);

        /**
         * @brief Create the spritesheet
         * @param area Sub-rectangle to construct spritesheet from
         *
         * The @a area can be used to construct the spritesheet from a
         * sub-rectangle of the whole spritesheet image. To construct
         * the spritesheet from the whole image (default), leave the
         * @a area argument unspecified. If the @a area rectangle crosses
         * the bounds of the image, it is adjusted to fit the image size
         */
        void create(UIntRect area = {});

        /**
         * @brief Get the size of each frame in the spritesheet
         * @return The size of each frame in the spritesheet
         */
        Vector2u getFrameSize() const;

        /**
         * @brief Get the number of frames constructed from the spritesheet
         * @return The total number of frames in the spritesheet
         */
        std::size_t getFramesCount() const;

        /**
         * @brief Get the frame at a given index
         * @param index The index to get the frame of
         * @return The frame at the specified index if it is within
         *         bounds otherwise returns no value
         */
        std::optional<Frame> getFrame(Index index) const;

        /**
         * @brief Get the frame by its assigned alias
         * @param alias The alias assigned to a frame
         * @return he frame at the specified index if it is within
         *         bounds otherwise returns no value
         */
        std::optional<Frame> getFrame(const std::string& alias) const;

        /**
         * @brief Get the size of the spritesheet in pixels
         * @return The size of the spritesheet in pixels
         *
         * The x component is width whilst the y component is the height
         * of the spritesheet
         */
        Vector2u getSize() const;

        /**
         * @brief Get the width of the spritesheet in pixels
         * @return The width of the spritesheet in pixels
         */
        unsigned int getWidth() const;

        /**
         * @brief Get the height of the spritesheet in pixels
         * @return The height of the spritesheet in pixels
         */
        unsigned int getHeight() const;

        /**
         * @brief Get the size of the spritesheet in frames
         * @return The size of the spritesheet in frames
         *
         * @warning The x component is the number of columns and the y
         * component is the number of rows
         */
        Vector2u getSizeInFrames() const;

        /**
         * @brief Get the number of rows in the spritesheet
         * @return The number of rows in the spritesheet
         */
        unsigned int getNumberOfRows() const;

        /**
         * @brief Get the number of columns in the spritesheet
         * @return The number of columns in the spritesheet
         */
        unsigned int getNumberOfColumns() const;

        /**
         * @brief Get the filename of the image used by the spritesheet
         * @return The filename of the images used by the spritesheet
         */
        const std::string& getTextureFilename() const;

        /**
         * @brief Get a sprite from an index
         * @param index Index to get the sprite from
         * @return The sprite at the given index, or an empty sprite if
         *         the index is out of bounds
         */
        Sprite getSprite(Index index);

        /**
         * @brief Get a sprite from the index with a given alias
         * @param alias The name given to a frame in the spritesheet
         * @return The sprite at the aliased index or an empty sprite if
         *         there is no frame with the specified alias
         *
         * @see assignAlias
         */
        Sprite getSprite(const std::string& alias);

        /**
         * @brief Check if an index has a frame or not
         * @param index Index to be checked
         * @return True if there is a frame at the specified index of false
         *         if the index is invalid
         */
        bool hasFrame(Index index) const;

        /**
         * @brief Check if there is a frame with a specified alias
         * @param alias Name of the alias given to a frame
         * @return True if a frame with the specified alias exist or false
         *         if there is no frame with the given alias
         *
         * @see assignAlias
         */
        bool hasFrame(const std::string& alias) const;

        /**
         * @brief Assign an alias to a frame
         * @param index Index of the frame to assign an alias
         * @param alias The alias to be assigned to the frame
         * @return True if the frame was assigned an alias
         *
         * This function allows a frame to be accessed by its name
         * instead of its index
         *
         * @code
         * spritesheet.assignAlias("blank_frame", Index{4, 0});
         * spritesheet.getFrame("blank_frame"); //Returns frame at index 4, 0
         * spritesheet.getFrame(Index{4, 0});   //Returns frame at index 4, 0
         * @endcode
         *
         * @see getFrame(const std::string&)
         */
        bool assignAlias(Index index, const std::string& alias);

    private:
        /**
         * @brief Calculate the dimensions of interest from spritesheet image
         * @param area Sub-rectangle to load
         *
         * This function loads the spritesheet image and  calculates the
         * size of the spritesheet, the number of rows and columns based
         * on the given frame size
         */
        void computeDimensions(UIntRect area);

    private:
        std::string filename_;  //!< Filename of the texture the spritesheet uses
        Vector2u frameSize_;    //!< The size of each frame in the spritesheet
        Vector2u spacing_;      //!< The space between frames on the spritesheet
        Vector2u sizeInPixels_; //!< The size of the spritesheet in pixels
        Vector2u sizeInFrames_; //!< The size of the spritesheet in frames
        Vector2u offset_;       //!< Offset of the sub-rectangle from the top-left of the original spritesheet image

        std::unordered_map<Index, Frame> frames_;        //!< Stores the frames
        std::unordered_map<std::string, Index> aliases_; //!< Saves the index of frames with aliases
    };
}

#endif //IME_SPRITESHEET_H
