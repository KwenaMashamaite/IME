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

#ifndef IME_PICTURE_H
#define IME_PICTURE_H

#include "IME/Config.h"
#include "IME/ui/widgets/ClickableWidget.h"
#include "IME/ui/renderers/PictureRenderer.h"
#include "IME/common/Rect.h"

namespace ime {
    namespace ui {
        /**
         * @brief A widget that displays graphic images
         */
        class IME_API Picture : public ClickableWidget {
        public:
            using Ptr = std::unique_ptr<Picture>; //!< Unique widget pointer
            using ConstPtr = std::unique_ptr<const Picture>; //!< Const unique widget pointer

            /**
             * @brief Copy constructor
             */
            Picture(const Picture&);

            /**
             * @brief Copy assignment operator
             */
            Picture& operator=(const Picture&);

            /**
             * @brief Move constructor
             */
            Picture(Picture&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            Picture& operator=(Picture&&) noexcept;

            /**
             * @brief Create an empty picture widget
             * @return The new picture widget
             */
            static Picture::Ptr create();

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            Picture::Ptr copy() const;

            /**
             * @brief Create a new picture widget
             * @param filename Filename of the image to construct widget from
             * @param transparentTexture True to pass mouse events to the
             *          widget behind the picture on transparent parts of
             *          the picture, otherwise false
             * @throws FileNotFoundException if the image cannot be found on the disk
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
             * @throws FileNotFoundException If the image cannot be found on the disk
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
            PictureRenderer* getRenderer();
            const PictureRenderer* getRenderer() const;

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
             * @brief Make a copy of this widget
             * @return A copy of this widget
             *
             * You should use this function if you don't care about the type
             * of the widget, otherwise use the widgets copy function
             *
             * @see copy
             */
            Widget::Ptr clone() const override;

            /**
             * @brief Get the type of the picture
             * @return The type of the picture
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~Picture() override;

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
             * @throws FileNotFoundException If the image cannot be found on the disk
             *
             * By default, the widget is the same size as the image
             */
            explicit Picture(const std::string& filename, bool transparentTexture = true);

            /**
             * @brief Create a picture from a certain parts of an image
             * @param filename Filename of the image to construct the picture from
             * @param frame Frame to load from source image as picture
             * @param transparentTexture True to pass mouse events to the
             *          widget behind the picture on transparent parts of
             *          the picture, otherwise false
             * @throws FileNotFoundException If the image cannot be found on the disk
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

            /**
             * @brief Initialize events emitted by the widget
             */
            void initEvents();

        private:
            class PictureImpl;
            std::unique_ptr<PictureImpl> pimpl_;
        };
    }
}

/**
 * @class ime::ui::Picture
 * @ingroup ui
 *
 * <table>
 * <caption>Events generated by ime::ui::Picture </caption>
 * <tr><th> Name            <th> Argument Type          <th> Description
 * <tr><td> doubleClick     <td> void or ime::Vector2f  <td> The picture was double clicked. Optional parameter = Coordinates of the mouse cursor
 *                                                           relative to the picture
 * </table>
 *
 * Event usage example:
 * @code
 * picture.on("doubleClick", ime::Callback<ime::Vector2f>([](ime::Vector2f mousePos) {
 *      std::cout << "picture clicked at {" << mousePos.x << ", " << mousePos.y << "}" << "\n";
 * }));
 * @endcode
 */

#endif //IME_PICTURE_H
