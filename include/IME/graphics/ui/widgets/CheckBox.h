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

#ifndef IME_CHECKBOX_H
#define IME_CHECKBOX_H

#include "IClickableWidget.h"
#include "IME/graphics/ui/renderers/CheckBoxRenderer.h"
#include <TGUI/Widgets/CheckBox.hpp>
#include <memory>

namespace IME {
    namespace UI {
        /**
         * @brief Checkbox widget
         */
        class IME_API CheckBox : public IClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<CheckBox>; //!< Shared widget pointer

            /**
             * @brief Create the checkbox
             * @param text Text to display next to the checkbox
             */
            explicit CheckBox(const std::string &text = "");

            /**
             * @brief Create a new checkbox widget
             * @param text Text to display next to the checkbox
             * @return The new checkbox
             */
            static sharedPtr create(const std::string& text = "");

            /**
             * @brief Set the check boxes renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the checkbox is displayed. The 
             * checkbox has a default renderer which can be manipulated using 
             * the @see getRenderer() function
             */
            void setRenderer(std::shared_ptr<CheckBoxRenderer> renderer);

            /**
             * @brief Get the checkbox's renderer
             * @return The checkbox's renderer
             *
             * The renderer gives access to functions that determine how the
             * checkbox is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             */
            std::shared_ptr<CheckBoxRenderer> getRenderer();

            /**
             * @brief Allow or disallow the checkbox to be checked by clicking
             *        on the text next to it
             * @param acceptTextClick True to allow, or false to disallow
             */
            void setTextClickable(bool acceptTextClick);

            /**
             * @brief Check if the the radio checkbox can be checked by clicking
             *         on the text next to it
             * @return True if the checkbox is clickable by clicking on the
             *         text next to it, otherwise false
             */
            bool isTextClickable() const;

            /**
             * @brief Check or uncheck the checkbox
             * @param isChecked True to check the checkbox, otherwise false
             */
            void setChecked(bool isChecked);

            /**
             * @brief Check whether the checkbox is checked or not
             * @return True if it is checked, otherwise false
             */
            bool isChecked() const;

            /**
             * @brief Set the text content of the check box
             * @param text New text content
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &text) override;

            /**
             * @brief Get the check boxs text content
             * @return The check boxs text content
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
             * @brief Set the size of the check box
             * @param width The width of the check box
             * @param height The height of the check box
             */
            void setSize(float width, float height) override;

            /**
             * @brief Get the size of the check box
             * @return Current size of the check box
             *
             * This function only returns the size of the check box (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the check box
             * @return The absolute size of the check box
             *
             * The absolute size includes the size of the check box, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Get the type of the check box
             * @return The type of the check box
             */
            std::string getType() const override;

            /**
             * @brief Show a hidden check box
             *
             * This function will reveal the check box that was hidden prior to
             * function call. Calling this function on a check box that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Hide check box
             */
            void hide() override;

            /**
             * @brief Check if the check box is hidden or not
             * @return True if the check box is hidden, otherwise false
             */
            bool isHidden() const override;

            /**
             * @brief Toggle the visibility of the check box
             *
             * This function will hide the check box if its currently
             * visible and vice versa
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the check box
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the check box, false if
             *         coordinates do not lie inside the check box
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the checkbox
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the checkbox is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the checkbox
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the checkbox is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Get the position of the checkbox
             * @return Current position of the checkbox
             */
            Vector2f getPosition() const override;

            /**
             * @brief Set the orientation of the checkbox
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the checkbox is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the checkbox
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the checkbox,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the checkbox
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the checkbox
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the checkbox
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the checkbox by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the checkbox,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the checkbox by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the checkbox,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the checkbox
             * @return Current scale of the checkbox
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the checkbox
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the checkbox defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the checkbox, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the checkbox is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the checkbox
             * @param origin New origin
             *
             * The origin of the checkbox defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the checkbox, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the checkbox is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the checkbox
             * @return Local origin of the checkbox
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the checkbox by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the checkbox,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the checkbox by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the checkbox,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Enable or disable the check box
             * @param isEnable Set true to enable the check box, false to
             *        disable the check box
             *
             * The check box is enabled by default
             *
             * @note Disabling the check box cancels all the interaction events
             */
            void setEnabled(bool isEnable) override;

            /**
             * @brief Check if check box is enabled or disabled
             * @return True if check box is enabled, false if check box is disabled
             */
            bool isEnabled() const override;

            /**
             * @brief Disable check box if its currently enabled and vice versa
             */
            void toggleEnabled() override;

            /**
             * @brief Focus or unfocus check box
             * @param isFocused True to focus or false to unfocus check box
             */
            void setFocused(bool isFocused) override;

            /**
             * @brief Check if check box is focused or not
             * @return True if check box is focused, otherwise, false
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
            std::shared_ptr<tgui::CheckBox> checkBox_;   //!< Pointer to third party library
            std::shared_ptr<CheckBoxRenderer> renderer_; //!< Renderer for this checkbox
        };
    }
}

#endif // IME_CHECKBOX_H
