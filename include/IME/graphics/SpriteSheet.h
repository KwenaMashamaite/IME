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
         * @param texture Filename of the texture used by this spritesheet
         * @param frameSize The size of each frame in the spritesheet
         * @param spacing The space between frames on the spritesheet texture
         */
        SpriteSheet(const std::string& texture, Vector2u frameSize, Vector2u spacing);

        /**
         * @brief Create the spritesheet
         */
        void create();

        /**
         * @brief Get the size of each frame in the spritesheet
         * @return The size of each frame
         */
        Vector2u getFrameSize() const;

        /**
         * @brief Get the number of frames constructed from the spritesheet
         * @return The total number of frames in the spritesheet
         */
        std::size_t getNumberOfFrames() const;

        /**
         * @brief Get the frame at a given index
         * @param index The index to get the frame of
         * @return The frame at the specified index if it is within
         *         bounds otherwise an invalid frame
         *
         * An invalid frame has the width and height properties set to 0
         */
        Frame getFrame(Index index) const;

        /**
         * @brief Get the frame by its assigned alias
         * @param alias The alias assigned to a frame
         * @return The frame with the given alias if found otherwise
         *         an invalid frame
         *
         * An invalid frame has the width and height properties set to 0
         */
        Frame getFrame(const std::string& alias) const;

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
         * @brief Get the number of rows
         * @return The number of rows
         */
        unsigned int getNumberOfRows() const;

        /**
         * @brief Get the number of columns
         * @return The number of columns
         */
        unsigned int getNumberOfColumns() const;

        /**
         * @brief Get the filename of the texture this spritesheet uses
         * @return The filename of the texture this spritesheet uses
         */
        const std::string& getTextureFilename() const;

        /**
         * @brief Create a sprite from a frame in the spritesheet
         * @param index Index of the frame to construct a sprite from
         * @return The created sprite or an empty sprite if the index
         *         is not within bounds
         */
        Sprite getSprite(Index index);

        /**
         * @brief Create a sprite from a frame with the specified alias
         * @param alias The name given to a frame in the spritesheet
         * @return The created sprite or an empty sprite if there is no
         *          frame with the given alias
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
         */
        bool hasFrame(const std::string& alias) const;

        /**
         * @brief Assign an alias to a frame
         * @param index Index of the frame to assign an alias
         * @param alias The alias to be assigned to the frame
         * @return True if the frame was assigned an alias
         *
         * This function allows a frame to be accessed by name instead of
         * its index
         *
         * @see getFrame(const std::string&)
         */
        bool assignAlias(Index index, const std::string& alias);

    private:
        /**
         * @brief Calculate the size of the spritesheet, the number of
         *        rows and the number of columns
         */
        void computeDimensions();

    private:
        std::string filename_;      //!< Filename of the texture the spritesheet uses
        Vector2u frameSize_;        //!< The size of each frame in the spritesheet
        Vector2u spacing_;          //!< The space between frames on the spritesheet
        Vector2u sizeInPixels_;     //!< The size of the spritesheet in pixels
        Vector2u sizeInFrames_;     //!< The size of the spritesheet in frames
        const Frame invalidFrame_;  //!< A frame that doesn't exist in the spritesheet

        std::unordered_map<Index, Frame> frames_;        //!< Stores the frames
        std::unordered_map<std::string, Index> aliases_; //!< Saves the index of frames with aliases
    };
}

#endif //IME_SPRITESHEET_H
