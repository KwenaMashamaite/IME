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

#include "IME/Config.h"
#include "IClickableWidget.h"
#include "IME/ui/renderers/CheckBoxRenderer.h"
#include <TGUI/Widgets/CheckBox.hpp>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Checkbox widget
         */
        class IME_API CheckBox : public IClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<CheckBox>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const CheckBox>; //!< const shared widget pointer

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
             * @brief Create a copy of another checkbox
             * @param other The checkbox to copy
             * @param shareRenderer True if the new checkbox should have the
             *          same renderer as the copied checkbox
             * @return The new checkbox widget
             *
             * When the checkboxes share a renderer, changes in a render
             * property of one of the checkboxes automatically reflect on
             * the other checkbox, otherwise each checkbox has its own renderer
             * and changes in render properties are isolated to the specific
             * checkbox.
             *
             * @note when the checkboxes don't share a render, the renderer of
             * the new checkbox widget will initially have the properties of
             * the copied checkbox such that the two look the same after this
             * function returns
             *
             * By default, the checkboxes share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Set the checkboxes renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the checkbox is displayed. The 
             *
             * @note The checkbox has a default renderer
             *
             * @see getRenderer
             */
            void setRenderer(CheckBoxRenderer::sharedPtr renderer);

            /**
             * @brief Get the checkboxes renderer
             * @return The checkboxes renderer
             *
             * The renderer gives access to functions that determine how the
             * checkbox is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             *
             * @see setRenderer
             */
            CheckBoxRenderer::sharedPtr getRenderer();

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
             * @brief Set the text to display next to the checkbox
             * @param text Text to display
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &text);

            /**
             * @brief Get the text displayed next to the checkbox
             * @return The text displayed next to the checkbox
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
             * @brief Set the size of the check box
             * @param width The width of the check box
             * @param height The height of the check box
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the checkbox relative to the size of
             *        its parent
             * @param width The new width of the checkbox
             * @param height The new height of the checkbox
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * checkbox->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

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
             * @brief Set the width of the checkbox
             * @param width New width of the checkbox
             *
             * This function sets the width while keeping the height
             * the same
             *
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the checkbox relative to its parent
             * @param width New width
             *
             * The relative width is given in percentages as shown:
             *
             * @code
             * checkbox->setWidth("10%");
             * @endcode
             *
             * This function sets the width of the checkbox while keeping the
             * height the same
             *
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the checkbox
             * @param height New height of the checkbox
             *
             * This function sets the height while keeping the width
             * the same
             *
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the checkbox relative to its parent
             * @param height New height
             *
             * The relative height is given in percentages as shown:
             *
             * @code
             * checkbox->setHeight("10%");
             * @endcode
             *
             * This function sets the height of the checkbox while keeping the
             * width the same
             *
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Set the mouse cursor that is displayed when the mouse
             *        is on top of the checkbox
             * @param cursor The cursor to be shown
             *
             * By default, the arrow cursor is shown
             */
            void setMouseCursor(CursorType cursor) override;

            /**
             * @brief Get the mouse cursor that is displayed when the mouse
             *        is on top of the checkbox
             * @return The cursor shown when hovering above the checkbox
             */
            CursorType getMouseCursor() const override;

            /**
             * @brief Get the type of the check box
             * @return The type of the check box
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the checkbox with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the checkbox currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the checkbox
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the checkbox with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the checkbox currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the checkbox
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
             * @brief Show or hide a checkbox
             * @param visible True to show or false to hide
             *
             * If the checkbox is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The checkbox is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the checkbox is visible or not
             * @return True if the checkbox is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the checkbox
             *
             * This function will hide the checkbox if its currently
             * visible and vice versa
             *
             * @see setVisible
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
             * @brief Set the position of the checkbox relative to the
             *        size of its parent
             * @param x New x coordinate of the checkbox
             * @param y New y coordinate of the checkbox
             * 
             * The position is specified in percentages as shown below:
             * 
             * @code
             * checkbox->setPosition({"5%", "10%"});
             * @endcode
             * 
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the checkbox is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the checkbox
             * @return Current position of the checkbox
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the checkbox
             * @return The absolute position of the checkbox
             *
             * Unlike getPosition, this function returns the absolute
             * position of the top-left point of the checkbox instead
             * of the relative position to its parent
             *
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

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
            std::shared_ptr<tgui::CheckBox> checkBox_; //!< Pointer to third party library
            CheckBoxRenderer::sharedPtr renderer_;     //!< Renderer for this checkbox
        };
    }
}

#endif // IME_CHECKBOX_H
