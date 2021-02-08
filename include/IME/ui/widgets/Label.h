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

#ifndef IME_LABEL_H
#define IME_LABEL_H

#include "IME/Config.h"
#include "IWidget.h"
#include <TGUI/Widgets/Label.hpp>
#include "IME/ui/renderers/LabelRenderer.h"
#include <string>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Widget that displays a single or multiple lines of text
         */
        class IME_API Label : public IWidget {
        public:
            using sharedPtr = std::shared_ptr<Label>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const Label>; //!< const shared widget pointer

            /**
             * @brief The horizontal text alignment
             */
            enum class HorizontalAlignment {
                Left,   //!< Put the text on the left side (default)
                Center, //!< Center the text horizontally
                Right   //!< Put the text on the right side (e.g. for numbers)
            };

            /**
             * @brief The vertical text alignment
             */
            enum class VerticalAlignment {
                Top ,   //!< Put the text at the top (default)
                Center, //!< Center the text vertically
                Bottom  //!< Put the text at the bottom
            };

            /**
             * @brief Create a label
             * @param text Text to be displayed on the label
             */
            explicit Label(const std::string &text = "");

            /**
             * @brief Create a new label widget
             * @param text Text to be displayed on the label
             * @return The new label
             */
            static sharedPtr create(const std::string& text = "");

            /**
             * @brief Create a copy of another label
             * @param other The label to copy
             * @param shareRenderer True if the new label should have the
             *          same renderer as the copied label
             * @return The new label widget
             *
             * When the labels share a renderer, changes in a render
             * property of one of the labels automatically reflect on
             * the other label, otherwise each label has its own renderer
             * and changes in render properties are isolated to the specific
             * label.
             *
             * @note when the labels don't share a render, the renderer of
             * the new label widget will initially have the properties of
             * the copied label such that the two look the same after this
             * function returns
             *
             * By default, the labels share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Set the labels renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the label is displayed.
             *
             * @note The label has a default renderer
             *
             * @see getRenderer
             */
            void setRenderer(LabelRenderer::sharedPtr renderer);

            /**
             * @brief Get the labels renderer
             * @return The labels renderer
             *
             * The renderer gives access to functions that determine how the
             * label is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             *
             * @see setRenderer
             */
            LabelRenderer::sharedPtr getRenderer();

            /**
             * @brief Set the horizontal text alignment
             * @param alignment The new horizontal alignment
             *
             * By default the alignment is to the left
             */
            void setHorizontalAlignment(HorizontalAlignment alignment);

            /**
             * @brief Get the current horizontal alignment
             * @return The current horizontal alignment
             */
            HorizontalAlignment getHorizontalAlignment() const;

            /**
             * @brief Set the vertical text alignment
             * @param alignment The new vertical text alignment
             *
             * By default the text is aligned to the top
             */
            void setVerticalAlignment(VerticalAlignment alignment);

            /**
             * @brief Get the current vertical text alignment
             * @return Vertical text alignment
             */
            VerticalAlignment getVerticalAlignment() const;

            /**
             * @brief Set whether ot not the label is auto-sized
             * @param autoSize True to enable auto-size of false to disable
             *
             * When the label is in auto-size mode, the width and height of
             * the label will be changed to fit the text. Otherwise, only
             * the part defined by the size will be visible
             *
             * The label is auto-sized by default
             */
            void setAutoSize(bool autoSize);

            /**
             * @brief Check if the label is auto-sized or not
             * @return True if the size of the label is changed when the text
             *         change, otherwise false
             */
            bool getAutoSize() const;

            /**
             * @brief Set the maximum width that the text will have when
             *        auto-sizing
             * @param maximumWidth The new maximum text width
             *
             * When the label is auto-sizing the text will be split over
             * several lines when its width would exceed the value passed
             * to this function.
             *
             * @note This property is ignored when an exact size has been
             * given. Pass 0 to this function to disable the maximum
             *
             * @see setAutoSize
             */
            void setMaximumTextWidth(float maximumWidth);

            /**
             * @brief Get the maximum width that the text will have when
             *        auto-sizing
             * @return The maximum width of the text
             *
             * This function will return:
             * - The width of the label minus the padding when a specific
             *   size was set.
             * - The maximum text width when auto-sizing and a maximum was set.
             * - 0 when auto-sizing but there is no maximum width.
             */
            float getMaximumTextWidth() const;

            /**
             * @brief Set the text displayed on the label
             * @param text New text content
             *
             * When the text is auto-sized (default), then the size of the
             * label will be changed to fit the whole text
             *
             * @see setAutoSize
             */
            void setText(const std::string &text);

            /**
             * @brief Get the labels text content
             * @return The labels text content
             */
            std::string getText() const;

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
             * @brief Set the size of the label
             * @param width The width of the label
             * @param height The height of the label
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the label relative to the size of
             *        its parent
             * @param width The new width of the label
             * @param height The new height of the label
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * label->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the label
             * @return Current size of the label
             *
             * This function only returns the size of the label (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the label
             * @return The absolute size of the label
             *
             * The absolute size includes the size of the label, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the label
             * @param width New width of the label
             * 
             * This function sets the width while keeping the height
             * the same
             * 
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the label relative to its parent
             * @param width New width
             * 
             * The relative width is given in percentages as shown:
             * 
             * @code
             * label->setWidth("10%");
             * @endcode
             * 
             * This function sets the width of the label while keeping the
             * height the same
             * 
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the label
             * @param height New height of the label
             * 
             * This function sets the height while keeping the width 
             * the same
             * 
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the label relative to its parent
             * @param height New height
             * 
             * The relative height is given in percentages as shown:
             * 
             * @code
             * label->setHeight("10%");
             * @endcode
             * 
             * This function sets the height of the label while keeping the
             * width the same
             * 
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Set the mouse cursor that is displayed when the mouse
             *        is on top of the label
             * @param cursor The cursor to be shown
             *
             * By default, the arrow cursor is shown
             */
            void setMouseCursor(CursorType cursor) override;

            /**
             * @brief Get the mouse cursor that is displayed when the mouse
             *        is on top of the label
             * @return The cursor shown when hovering above the label
             */
            CursorType getMouseCursor() const override;

            /**
             * @brief Get the type of the label
             * @return The type of the label
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the label with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the label currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the label
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the label with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the label currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the label
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
             * @brief Show or hide a label
             * @param visible True to show or false to hide
             *
             * If the label is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The label is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the label is visible or not
             * @return True if the label is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the label
             *
             * This function will hide the label if its currently
             * visible and vice versa
             * 
             * @see setVisible
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the label
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the label, false if
             *         coordinates do not lie inside the label
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the label
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the label is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the label
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead. 
             * 
             * The default position of the label is (0, 0)
             * 
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the label relative to the
             *        size of its parent
             * @param x New x coordinate of the label
             * @param y New y coordinate of the label
             *
             * The position is specified using percentages as shown below:
             *
             * @code
             * label->setPosition({"5%", "10%"});
             * @endcode
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the label is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the label
             * @return Current position of the label
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the label
             * @return The absolute position of the label
             * 
             * Unlike getPosition, this function returns the absolute 
             * position of the top-left point of the label instead 
             * of the relative position to its parent
             * 
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

            /**
             * @brief Set the orientation of the label
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead. 
             * 
             * The default rotation of the label is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the label
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the label,
             * unlike setRotation which overwrites it
             * 
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the label
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the label
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the label
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the label by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the label,
             * unlike setScale which overwrites it
             * 
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the label by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the label,
             * unlike setScale which overwrites it
             * 
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the label
             * @return Current scale of the label
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the label
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the label defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the label, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the label is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the label
             * @param origin New origin
             *
             * The origin of the label defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the label, and ignore all
             * transformations (position, scale, rotation).
             * 
             * The default origin of the label is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the label
             * @return Local origin of the label
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the label by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the label,
             * unlike setPosition which overwrites it
             * 
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the label by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the label,
             * unlike setPosition which overwrites it
             * 
             * @see setPosition
             */
            void move(Vector2f offset) override;

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
            std::shared_ptr<tgui::Label> label_; //!< Pointer to third party library
            LabelRenderer::sharedPtr renderer_;  //!< Renderer for this label
        };
    }
} 

#endif // IME_LABEL_H
