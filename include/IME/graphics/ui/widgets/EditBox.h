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

#ifndef IME_EDITBOX_H
#define IME_EDITBOX_H

#include "IClickableWidget.h"
#include "IME/graphics/ui/renderers/EditBoxRenderer.h"
#include <TGUI/Widgets/EditBox.hpp>
#include <memory>

namespace IME {
    namespace UI {
        /**
         * @brief A single line input field
         */
        class IME_API EditBox : public IClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<EditBox>; //!< Shared widget pointer

            /**
             * @brief Construct an edit box
             */
            EditBox();

            /**
             * @brief Create a new edit box widget
             * @return The new edit box
             */
            static sharedPtr create();

            /**
             * @brief Set the edit boxes renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the edit box is displayed. The edit
             * box has a default renderer which can be manipulated using the
             * getRenderer function
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<EditBoxRenderer> renderer);

            /**
             * @brief Get the labels renderer
             * @return The labels renderer
             *
             * The renderer gives access to functions that determine how the
             * widget is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             */
            std::shared_ptr<EditBoxRenderer> getRenderer();

            /**
             * @brief Set the default text of the editbox
             * @param text The text to set
             *
             * The default text is displayed when the edit box is empty
             */
            void setDefaultText(const std::string& text);

            /**
             * @brief Get the default text
             * @return The default text
             */
            std::string getDefaultText() const;

            /**
             * @brief Set the character limit
             * @param maxChars The character limit
             *
             * The characters are not limited by default
             */
            void setMaximumCharacters(unsigned int maxChars);

            /**
             * @brief Get the character limit
             * @return The character limit or 0 if n limit is set
             */
            unsigned int getMaximumCharacters() const;

            /**
             * @brief Limit the text field width
             * @param limitWidth True to limit the text width otherwise false
             *
             * When the text width is limited, you wont be able to enter more
             * text when the text field is full. The text field width is not
             * limited by default
             */
            void limitTextWidth(bool limitWidth = true);

            /**
             * @brief Check if the text field width is limited or not
             * @return True if the text field is limited otherwise false
             */
            bool isTextWidthLimited() const;

            /**
             * @brief Make the edit box read-only or make it writable again
             * @param readOnly True to set the edit box as reda-only, otherwise
             *        false
             *
             * When the edit box is read-only, you can no longer delete
             * characters and type text. However, selecting text, copying text
             * and even calling the setText() function will still work
             */
            void setReadOnly(bool readOnly = true);

            /**
             * @brief Check if the edit box read-only or writable
             * @return True if the edit box is read-only or false if it is
             *         writable
             */
            bool isReadOnly() const;

            /**
             * @brief Place the caret after a specific character
             * @param charactersBeforeCaret The new position of the caret
             */
            void setCaretPosition(std::size_t charactersBeforeCaret);

            /**
             * @brief Get the position of the caret
             * @return The position of the caret
             */
            std::size_t getCaretPosition() const;

            /**
             * @brief Place a suffix at the right side of the edit box
             * @param suffix Text to show on right side of edit box
             *
             * Setting a suffix can be useful for inputting numbers where you
             * want to unit to be displayed inside the edit box
             */
            void setSuffix(const std::string& suffix);

            /**
             * @brief Get suffix currently displayed on the right side of the
             *        edit box
             * @return Text shown on right side of edit box
             */
            std::string getSuffix() const;

            /**
             * @brief Set the text inside the edit box
             * @param text Text inside the edit box
             *
             * The last characters of the text might be removed if:
             * - There is a set a character limit and this text contains
             *   too much characters.
             * - The text width is limited and the text does not fit inside
             *   the EditBox.
             *
             * @see setMaximumCharacters
             * @see limitTextWidth
             */
            void setText(const std::string &text);

            /**
             * @brief Get the text inside the edit box
             * @return The text inside the edit box
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
             * @brief Set the size of the edit box
             * @param width The width of the edit box
             * @param height The height of the edit box
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the edit box relative to the size of
             *        its parent
             * @param width The new width of the edit box
             * @param height The new height of the edit box
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * editbox->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the edit box
             * @return Current size of the edit box
             *
             * This function only returns the size of the edit box (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the edit box
             * @return The absolute size of the edit box
             *
             * The absolute size includes the size of the edit box, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the edit box
             * @param width New width of the edit box
             * 
             * This function sets the width while keeping the height
             * the same
             * 
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the edit box relative to its parent
             * @param width New width
             * 
             * The relative width is given in percentages as shown:
             * 
             * @code
             * edit box->setWidth("10%");
             * @endcode
             * 
             * This function sets the width of the edit box while keeping the
             * height the same
             * 
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the edit box
             * @param height New height of the edit box
             * 
             * This function sets the height while keeping the width 
             * the same
             * 
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the edit box relative to its parent
             * @param height New height
             * 
             * The relative height is given in percentages as shown:
             * 
             * @code
             * edit box->setHeight("10%");
             * @endcode
             * 
             * This function sets the height of the edit box while keeping the
             * width the same
             * 
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Get the type of the edit box
             * @return The type of the edit box
             */
            std::string getType() const override;

            /**
             * @brief Show a hidden edit box
             *
             * This function will reveal the edit box that was hidden prior to
             * function call. Calling this function on a edit box that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Hide edit box
             */
            void hide() override;

            /**
             * @brief Check if the edit box is hidden or not
             * @return True if the edit box is hidden, otherwise false
             */
            bool isHidden() const override;

            /**
             * @brief Toggle the visibility of the edit box
             *
             * This function will hide the edit box if its currently
             * visible and vice versa
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the edit box
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the edit box, false if
             *         coordinates do not lie inside the edit box
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the edit box
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the edit box is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the edit box
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead. 
             * 
             * The default position of the edit box is (0, 0)
             * 
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the edit box relative to the
             *        size of its parent
             * @param x New x coordinate of the edit box
             * @param y New y coordinate of the edit box
             * 
             * The position is specified in percentages as shown below:
             * 
             * @code
             * editbox->setPosition({"5%", "10%"});
             * @endcode
             * 
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the edit box is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the edit box
             * @return Current position of the edit box
             */
            Vector2f getPosition() const override;

            /**
             * @brief Set the orientation of the edit box
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead. 
             * 
             * The default rotation of the edit box is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the edit box
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the edit box,
             * unlike setRotation which overwrites it
             * 
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the edit box
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the edit box
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the edit box
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the edit box by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the edit box,
             * unlike setScale which overwrites it
             * 
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the edit box by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the edit box,
             * unlike setScale which overwrites it
             * 
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the edit box
             * @return Current scale of the edit box
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the edit box
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the edit box defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the edit box, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the edit box is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the edit box
             * @param origin New origin
             *
             * The origin of the edit box defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the edit box, and ignore all
             * transformations (position, scale, rotation).
             * 
             * The default origin of the edit box is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the edit box
             * @return Local origin of the edit box
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the edit box by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the edit box,
             * unlike setPosition which overwrites it
             * 
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the edit box by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the edit box,
             * unlike setPosition which overwrites it
             * 
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Enable or disable the edit box
             * @param isEnable Set true to enable the edit box, false to
             *        disable the edit box
             *
             * The edit box is enabled by default
             *
             * @note Disabling the edit box cancels all the interaction events
             */
            void setEnabled(bool isEnable) override;

            /**
              * @brief Check if edit box is enabled or disabled
              * @return True if edit box is enabled, false if edit box is disabled
              */
            bool isEnabled() const override;

            /**
             * @brief Disable edit box if its currently enabled and vice versa
             */
            void toggleEnabled() override;

            /**
             * @brief Focus or unfocus edit box
             * @param isFocused True to focus or false to unfocus edit box
             */
            void setFocused(bool isFocused) override;

            /**
             * @brief Check if edit box is focused or not
             * @return True if edit box is focused. Otherwise, false
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
             * change of the object when that state changes
             */
            void initEvents();

        private:
            std::shared_ptr<tgui::EditBox> editBox_;    //!< Pointer to third party library
            std::shared_ptr<EditBoxRenderer> renderer_; //!< Renderer for this edit box
        };
    }
}

#endif // IME_EDITBOX_H
