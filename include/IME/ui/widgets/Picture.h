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

#ifndef IME_PICTURE_H
#define IME_PICTURE_H

#include "IME/Config.h"
#include "IME/ui/widgets/ClickableWidget.h"
#include "IME/ui/renderers/PictureRenderer.h"
#include "IME/common/Rect.h"

namespace ime {
    namespace ui {
        /**
         * @brief A widget which displays images
         */
        class IME_API Picture : public ClickableWidget {
        public:
            using Ptr = std::shared_ptr<Picture>; //!< Shared widget pointer
            using ConstPtr = std::shared_ptr<const Picture>; //!< const shared widget pointer

            /**
             * @brief Move constructor
             */
            Picture(Picture&&);

            /**
             * @brief Move assignment operator
             */
            Picture& operator=(Picture&&);

            /**
             * @brief Create an empty picture widget
             * @return The new picture widget
             */
            static Picture::Ptr create();

            /**
             * @brief Create a copy of another picture
             * @param other The picture to copy
             * @param shareRenderer True if the new picture should have the
             *          same renderer as the copied picture
             * @return The new picture widget
             *
             * When the pictures share a renderer, changes in a render
             * property of one of the pictures automatically reflect on
             * the other picture, otherwise each picture has its own renderer
             * and changes in render properties are isolated to the specific
             * picture.
             *
             * @note when the pictures don't share a render, the renderer of
             * the new picture widget will initially have the properties of
             * the copied picture such that the two look the same after this
             * function returns
             *
             * By default, the pictures share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static Picture::Ptr copy(Picture::ConstPtr other, bool shareRenderer = true);

            /**
             * @brief Create a new picture widget
             * @param filename Filename of the image to construct widget from
             * @param transparentTexture True to pass mouse events to the
             *          widget behind the picture on transparent parts of
             *          the picture, otherwise false
             * @throws FileNotFound if the image cannot be found on the disk
             * @return The new picture widget
             *
             * By default, the widget is the same size as the image
             */
            static Picture::Ptr create(const std::string& filename,
                bool transparentTexture = false);

            /**
             * @brief Create a picture from a certain parts of an image
             * @param filename Filename of the image to construct the picture from
             * @param frame Frame to load from source image as picture
             * @param transparentTexture True to pass mouse events to the
             *          widget behind the picture on transparent parts of
             *          the picture, otherwise false
             * @throws FileNotFound If the image cannot be found on the disk
             * @return The new picture widget
             *
             * The @a frame is in the form {top, left, width, height}
             *
             * By default, the picture is the same size as the last arguments
             * of the @a frame
             *
             * @code
             * Picture("image.png", {20, 15, 60, 40}}); // Load part of the image from (20,15) to (80,55)
             * @endcode
             */
            static Picture::Ptr create(const std::string& filename, UIntRect frame,
                bool transparentTexture = true);

            /**
             * @brief Get the pictures renderer
             * @return The pictures renderer
             *
             * The renderer gives access to functions that determine how the
             * picture is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             *
             * @see getRenderer
             */
            PictureRenderer::Ptr getRenderer();
            const PictureRenderer::Ptr getRenderer() const;

            /**
             * @brief Set whether or not the picture ignores mouse events
             * @param ignore True to ignore mouse events otherwise false
             *
             * When mouse events are ignored, they will be passed to the
             * widget behind the picture if theres any
             *
             * Mouse events are NOT ignored by default
             */
            void ignoreMouseEvents(bool ignore = true);

            /**
             * @brief Check if mouse events are ignored or not
             * @return True if mouse events are ignore, otherwise false
             *
             * @see ignoreMouseEvents
             */
            bool isMouseEventsIgnored() const;

            /**
             * @brief Get the type of the picture
             * @return The type of the picture
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~Picture();

        private:
            /**
             * @brief Create an empty picture
             */
            Picture();

            /**
             * @brief Constructor
             * @param filename Filename of the image to construct widget from
             * @param transparentTexture True to pass mouse events to the
             *          widget behind the picture on transparent parts of
             *          the picture, otherwise false
             * @throws FileNotFound If the image cannot be found on the disk
             *
             * By default, the widget is the same size as the image
             */
            Picture(const std::string& filename, bool transparentTexture = true);

            /**
             * @brief Create a picture from a certain parts of an image
             * @param filename Filename of the image to construct the picture from
             * @param frame Frame to load from source image as picture
             * @param transparentTexture True to pass mouse events to the
             *          widget behind the picture on transparent parts of
             *          the picture, otherwise false
             * @throws FileNotFound If the image cannot be found on the disk
             *
             * The @a frame is in the form {top, left, width, height}
             *
             * By default, the picture is the same size as the last arguments
             * of the @a frame
             *
             * @code
             * Picture("image.png", {20, 15, 60, 40}}); // Load part of the image from (20,15) to (80,55)
             * @endcode
             */
            Picture(const std::string& filename, UIntRect frame, bool transparentTexture = true);

        private:
            class PictureImpl;
            std::unique_ptr<PictureImpl> pimpl_;
        };
    }
}

#endif //IME_PICTURE_H
