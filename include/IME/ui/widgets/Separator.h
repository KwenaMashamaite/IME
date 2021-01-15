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

#ifndef IME_SEPARATOR_H
#define IME_SEPARATOR_H

#include "IME/Config.h"
#include "IClickableWidget.h"
#include "IME/ui/renderers/SeparatorRenderer.h"
#include <TGUI/Widgets/SeparatorLine.hpp>

namespace ime {
    namespace ui {
        /**
         * @brief A rectangle that can be used as a line to visually
         *        separate widgets from each other
         *
         * @note This widget just draws a line. It does not support dragging
         * to e.g enlarge or shrink a panel
         */
        class IME_API Separator : public IClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<Separator>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const Separator>; //!< const shared widget pointer

            /**
             * @brief Constructor
             */
            Separator();

            /**
             * @brief Create a new separator widget
             * @return The new separator separator
             */
            static sharedPtr create();

            /**
             * @brief Create a copy of another separator
             * @param other The separator to copy
             * @param shareRenderer True if the new separator should have the
             *          same renderer as the copied separator
             * @return The new separator widget
             *
             * When the separators share a renderer, changes in a render
             * property of one of the separators automatically reflect on
             * the other separator, otherwise each separator has its own renderer
             * and changes in render properties are isolated to the specific
             * separator.
             *
             * @note when the separators don't share a render, the renderer of
             * the new separator widget will initially have the properties of
             * the copied separator such that the two look the same after this
             * function returns
             *
             * By default, the separators share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Set the separators renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the separator is displayed.
             *
             * @note The separator has a default renderer
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<SeparatorRenderer> renderer);

            /**
             * @brief Get the separators renderer
             * @return The separators renderer
             *
             * The renderer gives access to functions that determine how the
             * separator is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            std::shared_ptr<SeparatorRenderer> getRenderer();

            /**
             * @brief Set the character size of the text
             * @param charSize New character size
             *
             * If the size is 0 then the text will be scaled to fit in
             * the separator
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Set the size of the separator
             * @param width The width of the separator
             * @param height The height of the separator
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the separator relative to the size of
             *        its parent
             * @param width The new width of the separator
             * @param height The new height of the separator
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * separator->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the separator
             * @return Current size of the separator
             *
             * This function only returns the size of the separator (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the separator
             * @return The absolute size of the separator
             *
             * The absolute size includes the size of the separator, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the separator
             * @param width New width of the separator
             *
             * This function sets the width while keeping the height
             * the same
             *
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the separator relative to its parent
             * @param width New width
             *
             * The relative width is given in percentages as shown:
             *
             * @code
             * separator->setWidth("10%");
             * @endcode
             *
             * This function sets the width of the separator while keeping the
             * height the same
             *
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the separator
             * @param height New height of the separator
             *
             * This function sets the height while keeping the width
             * the same
             *
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the separator relative to its parent
             * @param height New height
             *
             * The relative height is given in percentages as shown:
             *
             * @code
             * separator->setHeight("10%");
             * @endcode
             *
             * This function sets the height of the separator while keeping the
             * width the same
             *
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Get the type of the separator
             * @return The type of the separator
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the separator with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the separator currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the separator
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the separator with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the separator currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the separator
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
             * @brief Show or hide a separator
             * @param visible True to show or false to hide
             *
             * If the separator is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The separator is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the separator is visible or not
             * @return True if the separator is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the separator
             *
             * This function will hide the separator if its currently
             * visible and vice versa
             *
             * @see setVisible
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the separator
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the separator, false if
             *         coordinates do not lie inside the separator
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the separator
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the separator is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the separator
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the separator is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the separator relative to the
             *        size of its parent
             * @param x New x coordinate of the separator
             * @param y New y coordinate of the separator
             *
             * The position is specified in percentages as shown below:
             *
             * @code
             * separator->setPosition({"5%", "10%"});
             * @endcode
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the separator is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the separator
             * @return Current position of the separator
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the separator
             * @return The absolute position of the separator
             *
             * Unlike getPosition, this function returns the absolute
             * position of the top-left point of the separator instead
             * of the relative position to its parent
             *
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

            /**
             * @brief Set the orientation of the separator
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the separator is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the separator
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the separator,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the separator
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the separator
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the separator
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the separator by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the separator,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the separator by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the separator,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the separator
             * @return Current scale of the separator
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the separator
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the separator defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the separator, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the separator is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the separator
             * @param origin New origin
             *
             * The origin of the separator defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the separator, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the separator is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the separator
             * @return Local origin of the separator
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the separator by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the separator,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the separator by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the separator,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Enable or disable the separator
             * @param isEnable Set true to enable the separator, false to
             *        disable the separator
             *
             * The separator is enabled by default
             *
             * @note Disabling the separator cancels all the interaction events
             */
            void setEnabled(bool isEnable) override;

            /**
             * @brief Check if separator is enabled or disabled
             * @return True if separator is enabled, false if separator is disabled
             */
            bool isEnabled() const override;

            /**
             * @brief Disable separator if its currently enabled and vice versa
             */
            void toggleEnabled() override;

            /**
             * @brief Focus or unfocus separator
             * @param isFocused True to focus or false to unfocus separator
             */
            void setFocused(bool isFocused) override;

            /**
             * @brief Check if separator is focused or not
             * @return True if separator is focused. Otherwise, false
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
            std::shared_ptr<tgui::SeparatorLine> separator_; //!< Pointer to third party widget
            std::shared_ptr<SeparatorRenderer> renderer_;    //!< Separator renderer
        };
    }
}

#endif //IME_SEPARATOR_H
