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

#ifndef IME_RADIOBUTTON_H
#define IME_RADIOBUTTON_H

#include "IME/Config.h"
#include "IClickableWidget.h"
#include "IME/ui/renderers/RadioButtonRenderer.h"
#include <TGUI/Widgets/RadioButton.hpp>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Widget that can toggle between on and off states
         */
        class IME_API RadioButton : public IClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<RadioButton>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const RadioButton>; //!< const shared widget pointer

            /**
             * @brief Create a button
             * @param buttonText Text to be displayed next to the button
             */
            explicit RadioButton(const std::string &buttonText = "");

            /**
             * @brief Create a new radio button widget
             * @param text Text to be displayed next to the button
             * @return The new radio button
             */
            static sharedPtr create(const std::string& text = "");

            /**
             * @brief Create a copy of another button
             * @param other The button to copy
             * @param shareRenderer True if the new button should have the
             *          same renderer as the copied button
             * @return The new button widget
             *
             * When the buttons share a renderer, changes in a render
             * property of one of the buttons automatically reflect on
             * the other button, otherwise each button has its own renderer
             * and changes in render properties are isolated to the specific
             * button.
             *
             * @note when the buttons don't share a render, the renderer of
             * the new button widget will initially have the properties of
             * the copied button such that the two look the same after this
             * function returns
             *
             * By default, the buttons share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Set the buttons renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the button is displayed.
             *
             * @note The button has a default renderer
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<RadioButtonRenderer> renderer);

            /**
             * @brief Get the buttons renderer
             * @return The buttons renderer
             *
             * The renderer gives access to functions that determine how the
             * button is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             */
            std::shared_ptr<RadioButtonRenderer> getRenderer();

            /**
             * @brief Allow or disallow the button to be checked by clicking
             *        on the text next to it
             * @param acceptTextClick True to allow, or false to disallow
             */
            void setTextClickable(bool acceptTextClick);

            /**
             * @brief Check if the the button can be checked by clicking
             *         on the text next to it
             * @return True if the button is clickable by clicking on the
             *         text next to it, otherwise false
             */
            bool isTextClickable() const;

            /**
             * @brief Check or uncheck the button
             * @param isChecked True to check the button, otherwise false
             */
            void setChecked(bool isChecked);

            /**
             * @brief Check whether the button is checked or not
             * @return True if it is checked, otherwise false
             */
            bool isChecked() const;

            /**
             * @brief Set the text displayed next to the button
             * @param text The text to display
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &text);

            /**
             * @brief Get the text displayed next to the button
             * @return The buttons text content
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
             * @brief Set the size of the button
             * @param width The width of the button
             * @param height The height of the button
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the button relative to the size of
             *        its parent
             * @param width The new width of the button
             * @param height The new height of the button
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * button->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the button
             * @return Current size of the button
             *
             * This function only returns the size of the button (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the button
             * @return The absolute size of the button
             *
             * The absolute size includes the size of the button, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the button
             * @param width New width of the button
             *
             * This function sets the width while keeping the height
             * the same
             *
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the button relative to its parent
             * @param width New width
             *
             * The relative width is given in percentages as shown:
             *
             * @code
             * button->setWidth("10%");
             * @endcode
             *
             * This function sets the width of the button while keeping the
             * height the same
             *
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the button
             * @param height New height of the button
             *
             * This function sets the height while keeping the width
             * the same
             *
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the button relative to its parent
             * @param height New height
             *
             * The relative height is given in percentages as shown:
             *
             * @code
             * button->setHeight("10%");
             * @endcode
             *
             * This function sets the height of the button while keeping the
             * width the same
             *
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Set the mouse cursor that is displayed when the mouse
             *        is on top of the button
             * @param cursor The cursor to be shown
             *
             * By default, the arrow cursor is shown
             */
            void setMouseCursor(CursorType cursor) override;

            /**
             * @brief Get the mouse cursor that is displayed when the mouse
             *        is on top of the button
             * @return The cursor shown when hovering above the button
             */
            CursorType getMouseCursor() const override;

            /**
             * @brief Get the type of the button
             * @return The type of the button
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the button with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the button currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the button
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the button with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the button currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the button
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
             * @brief Show or hide a button
             * @param visible True to show or false to hide
             *
             * If the button is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The button is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the button is visible or not
             * @return True if the button is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the button
             *
             * This function will hide the button if its currently
             * visible and vice versa
             *
             * @see setVisible
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the button
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the button, false if
             *         coordinates do not lie inside the button
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the button
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the button is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the button
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the button is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the button relative to the
             *        size of its parent
             * @param x New x coordinate of the button
             * @param y New y coordinate of the button
             *
             * The position is specified in percentages as shown below:
             *
             * @code
             * button->setPosition({"5%", "10%"});
             * @endcode
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the button is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the button
             * @return Current position of the button
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the button
             * @return The absolute position of the button
             *
             * Unlike getPosition, this function returns the absolute
             * position of the top-left point of the button instead
             * of the relative position to its parent
             *
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

            /**
             * @brief Set the orientation of the button
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the button is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the button
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the button,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the button
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the button
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the button
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the button by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the button,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the button by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the button,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the button
             * @return Current scale of the button
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the button
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the button defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the button, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the button is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the button
             * @param origin New origin
             *
             * The origin of the button defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the button, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the button is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the button
             * @return Local origin of the button
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the button by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the button,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the button by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the button,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Enable or disable the button
             * @param isEnable Set true to enable the button, false to
             *        disable the button
             *
             * The button is enabled by default
             *
             * @note Disabling the button cancels all the interaction events
             */
            void setEnabled(bool isEnable) override;

            /**
             * @brief Check if button is enabled or disabled
             * @return True if button is enabled, false if button is disabled
             */
            bool isEnabled() const override;

            /**
             * @brief Disable button if its currently enabled and vice versa
             */
            void toggleEnabled() override;

            /**
             * @brief Focus or unfocus button
             * @param isFocused True to focus or false to unfocus button
             */
            void setFocused(bool isFocused) override;

            /**
             * @brief Check if button is focused or not
             * @return True if button is focused. Otherwise, false
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
            std::shared_ptr<tgui::RadioButton> button_;     //!< Pointer to third party button
            std::shared_ptr<RadioButtonRenderer> renderer_; //!< Renderer
        };
    }
}

#endif //IME_RADIOBUTTON_H
