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

#include "IWidget.h"
#include <TGUI/Widgets/Label.hpp>
#include "IME/graphics/ui/renderers/LabelRenderer.h"
#include <string>
#include <memory>

namespace IME {
    namespace UI {
        /**
         * @brief Widget that displays a single or multiple lines of text
         */
        class IME_API Label : public IWidget {
        public:
            using sharedPtr = std::shared_ptr<Label>; //!< Shared widget pointer

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
             * @brief Set the labels renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the label is displayed.
             *
             * @note The label has a default renderer
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<LabelRenderer> renderer);

            /**
             * @brief Get the labels renderer
             * @return The labels renderer
             *
             * The renderer gives access to functions that determine how the
             * label is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             */
            std::shared_ptr<LabelRenderer> getRenderer();

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
             * @brief Set the text content of the label
             * @param text New text content
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &text) override;

            /**
             * @brief Get the labels text content
             * @return The labels text content
             */
            std::string getText() const override;

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
             * @brief Get the type of the label
             * @return The type of the label
             */
            std::string getType() const override;

            /**
             * @brief Show a hidden label
             *
             * This function will reveal the label that was hidden prior to
             * function call. Calling this function on a label that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Hide label
             */
            void hide() override;

            /**
             * @brief Check if the label is hidden or not
             * @return True if the label is hidden, otherwise false
             */
            bool isHidden() const override;

            /**
             * @brief Toggle the visibility of the label
             *
             * This function will hide the label if its currently
             * visible and vice versa
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
             * @brief Get the position of the label
             * @return Current position of the label
             */
            Vector2f getPosition() const override;

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
            std::shared_ptr<tgui::Label> label_;      //!< Pointer to third party library
            std::shared_ptr<LabelRenderer> renderer_; //!< Renderer for this label
        };
    }
} 

#endif // IME_LABEL_H
