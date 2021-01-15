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
#include "IClickableWidget.h"
#include "IME/ui/renderers/PictureRenderer.h"
#include "IME/common/Rect.h"
#include <TGUI/Widgets/Picture.hpp>

namespace ime {
    namespace ui {
        /**
         * @brief A widget which displays images
         */
        class IME_API Picture : public IClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<Picture>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const Picture>; //!< const shared widget pointer
            
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

            /**
             * @brief Create an empty picture widget
             * @return The new picture widget
             */
            static sharedPtr create();

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
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

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
            static sharedPtr create(const std::string& filename, bool transparentTexture = false);

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
            static sharedPtr create(const std::string& filename, UIntRect frame, bool transparentTexture = true);

            /**
             * @brief Set the pictures renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the picture is displayed.
             *
             * @note The picture has a default renderer
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<PictureRenderer> renderer);

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
            std::shared_ptr<PictureRenderer> getRenderer();

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
             * @brief Set the character size of the text
             * @param charSize New character size
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Set the size of the picture
             * @param width The width of the picture
             * @param height The height of the picture
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the picture relative to the size of
             *        its parent
             * @param width The new width of the picture
             * @param height The new height of the picture
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * picture->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the picture
             * @return Current size of the picture
             *
             * This function only returns the size of the picture (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the picture
             * @return The absolute size of the picture
             *
             * The absolute size includes the size of the picture, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the picture
             * @param width New width of the picture
             *
             * This function sets the width while keeping the height
             * the same
             *
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the picture relative to its parent
             * @param width New width
             *
             * The relative width is given in percentages as shown:
             *
             * @code
             * picture->setWidth("10%");
             * @endcode
             *
             * This function sets the width of the picture while keeping the
             * height the same
             *
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the picture
             * @param height New height of the picture
             *
             * This function sets the height while keeping the width
             * the same
             *
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the picture relative to its parent
             * @param height New height
             *
             * The relative height is given in percentages as shown:
             *
             * @code
             * picture->setHeight("10%");
             * @endcode
             *
             * This function sets the height of the picture while keeping the
             * width the same
             *
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Set the mouse cursor that is displayed when the mouse
             *        is on top of the picture
             * @param cursor The cursor to be shown
             *
             * By default, the arrow cursor is shown
             */
            void setMouseCursor(CursorType cursor) override;

            /**
             * @brief Get the mouse cursor that is displayed when the mouse
             *        is on top of the picture
             * @return The cursor shown when hovering above the picture
             */
            CursorType getMouseCursor() const override;

            /**
             * @brief Get the type of the picture
             * @return The type of the picture
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the picture with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the picture currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the picture
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the picture with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the picture currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the picture
             * will be back in the state in which it was when this function
             * was called
             *
             * @see showWithEffect
             * @see isAnimationPlaying
             */
            void hideWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Check whether or not an animation is currently playing
             * @return True if an animation is playing, otherwise false
             *
             * @see showWithEffect
             * @see hideWithEffect
             */
            bool isAnimationPlaying() const override;

            /**
             * @brief Show or hide a picture
             * @param visible True to show or false to hide
             *
             * If the picture is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The picture is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the picture is visible or not
             * @return True if the picture is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the picture
             *
             * This function will hide the picture if its currently
             * visible and vice versa
             * 
             * @see setVisible
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the picture
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the picture, false if
             *         coordinates do not lie inside the picture
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the picture
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the picture is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the picture
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the picture is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the picture relative to the
             *        size of its parent
             * @param x New x coordinate of the picture
             * @param y New y coordinate of the picture
             *
             * The position is specified in percentages as shown below:
             *
             * @code
             * picture->setPosition({"5%", "10%"});
             * @endcode
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the picture is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the picture
             * @return Current position of the picture
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the picture
             * @return The absolute position of the picture
             * 
             * Unlike getPosition, this function returns the absolute 
             * position of the top-left point of the picture instead 
             * of the relative position to its parent
             * 
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

            /**
             * @brief Set the orientation of the picture
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the picture is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the picture
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the picture,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the picture
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the picture
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the picture
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the picture by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the picture,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the picture by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the picture,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the picture
             * @return Current scale of the picture
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the picture
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the picture defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the picture, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the picture is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the picture
             * @param origin New origin
             *
             * The origin of the picture defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the picture, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the picture is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the picture
             * @return Local origin of the picture
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the picture by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the picture,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the picture by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the picture,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Enable or disable the picture
             * @param isEnable Set true to enable the picture, false to
             *        disable the picture
             *
             * The picture is enabled by default
             *
             * @note Disabling the picture cancels all the interaction events
             */
            void setEnabled(bool isEnable) override;

            /**
             * @brief Check if picture is enabled or disabled
             * @return True if picture is enabled, false if picture is disabled
             */
            bool isEnabled() const override;

            /**
             * @brief Disable picture if its currently enabled and vice versa
             */
            void toggleEnabled() override;

            /**
             * @brief Focus or unfocus picture
             * @param isFocused True to focus or false to unfocus picture
             */
            void setFocused(bool isFocused) override;

            /**
             * @brief Check if picture is focused or not
             * @return True if picture is focused. Otherwise, false
             */
            bool isFocused() const override;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget
             * @return The internal pointer to a third party widget
             *
             * @warning This function is intended for internal use only and
             * should never be called under any circumstance
             */
            std::shared_ptr<tgui::Widget> getInternalPtr() override;

        private:
            /**
             * @brief Initialize events
             *
             * These events will notify event listeners about an internal state
             * change of the widget when that state changes
             */
            void initEvents();

        private:
            std::shared_ptr<tgui::Picture> picture_;     //!< Pointer to third party picture
            std::shared_ptr<PictureRenderer> renderer_;  //!< Renderer
        };
    }
}

#endif //IME_PICTURE_H
