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

#ifndef IME_PROGRESSBAR_H
#define IME_PROGRESSBAR_H

#include "IME/Config.h"
#include "IClickableWidget.h"
#include "IME/ui/renderers/ProgressBarRenderer.h"
#include <TGUI/Widgets/ProgressBar.hpp>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Widget for displaying progress
         */
        class IME_API ProgressBar : public IClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<ProgressBar>; //!< Shared widget pointer

            /**
             * @brief Determines in which direction the progress bar is filled
             *        when value goes from minimum to maximum
             */
            enum class FillDirection {
                LeftToRight,  //!< Start filling at the left side and go to the right
                RightToLeft,  //!< Start filling at the right side and go to the left
                TopToBottom,  //!< Start filling at the top an go downward
                BottomToTop   //!< Start filling at the bottom and go upward
            };

            /**
             * @brief Construct a progress bar
             * @param text Text displayed on the progress bar
             */
            explicit ProgressBar(const std::string& text = "");

            /**
             * @brief Create a new progress bar widget
             * @param text Text displayed on the progress bar
             * @return The new progress bar
             */
            static sharedPtr create(const std::string& text = "");

            /**
             * @brief Set the progress bars renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the label is displayed. The progress
             * bar has a default renderer which can be manipulated using the
             * getRenderer function
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<ProgressBarRenderer> renderer);

            /**
             * @brief Get the progress bars renderer
             * @return The progress bars renderer
             *
             * The renderer gives access to functions that determine how the
             * widget is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             *
             * @see setRenderer
             */
            std::shared_ptr<ProgressBarRenderer> getRenderer();

            /**
             * @brief Set a minimum value
             * @param minValue The value to set
             *
             * If the specified value is larger than the maximum value then
             * it will be changed to this value and the previous maximum will
             * be the new minimum. The default minimum value is 0
             *
             * @see setMaximum
             */
            void setMinimumValue(unsigned int minValue);

            /**
             * @brief Get the minimum value
             * @return The minimum value
             */
            unsigned int getMinimumValue() const;

            /**
             * @brief Set the maximum value
             * @param maxValue The value to be set
             *
             * The default maximum value is 10
             *
             * @see setMinimumValue
             */
            void setMaximumValue(unsigned int maxValue);

            /**
             * @brief Get the maximum value
             * @return The maximum value
             */
            unsigned int getMaximumValue() const;

            /**
             * @brief Set the current value
             * @param value The value to be set
             *
             * The value must not be smaller than the minimum value or
             * bigger than the maximum value
             */
            void setValue(unsigned int value);

            /**
             * @brief Get the current value
             * @return The current value
             */
            unsigned int getValue() const;

            /**
             * @brief Increment the value
             * @return The new value
             *
             * The value is increased by 1 and will never exceed the maximum
             * value
             */
            unsigned int incrementValue();

            /**
             * @brief Set the fill direction of the progress bar
             * @param direction The fill direction to be set
             *
             * The fill direction defines how the progress bar is filled when
             * the value goes from minimum to maximum. By default the progress
             * bar is filled from left to right
             */
            void setFillDirection(FillDirection direction);

            /**
             * @brief Get the fill direction of the progress bar
             * @return The current fill direction
             */
            FillDirection getFillDirection() const;

            /**
             * @brief Set the text displayed on the progress bar
             * @param text New text content
             *
             * This text is centered by default
             */
            void setText(const std::string &text);

            /**
             * @brief Get the progress bars text content
             * @return The progress bars text content
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
             * @brief Set the size of the progress bar
             * @param width The width of the progress bar
             * @param height The height of the progress bar
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the progress bar relative to the size of
             *        its parent
             * @param width The new width of the progress bar
             * @param height The new height of the progress bar
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * progressBar->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the progress bar
             * @return Current size of the progress bar
             *
             * This function only returns the size of the progress bar (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the progress bar
             * @return The absolute size of the progress bar
             *
             * The absolute size includes the size of the progress bar, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the progress bar
             * @param width New width of the progress bar
             * 
             * This function sets the width while keeping the height
             * the same
             * 
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the progress bar relative to its parent
             * @param width New width
             * 
             * The relative width is given in percentages as shown:
             * 
             * @code
             * progress bar->setWidth("10%");
             * @endcode
             * 
             * This function sets the width of the progress bar while keeping the
             * height the same
             * 
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the progress bar
             * @param height New height of the progress bar
             * 
             * This function sets the height while keeping the width 
             * the same
             * 
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the progress bar relative to its parent
             * @param height New height
             * 
             * The relative height is given in percentages as shown:
             * 
             * @code
             * progress bar->setHeight("10%");
             * @endcode
             * 
             * This function sets the height of the progress bar while keeping the
             * width the same
             * 
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Get the type of the progress bar
             * @return The type of the progress bar
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the progressbar with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the progressbar currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the progressbar
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the progressbar with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the progressbar currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the progressbar
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
             * @brief Show or hide a progressbar
             * @param visible True to show or false to hide
             *
             * If the progressbar is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The progressbar is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the progressbar is visible or not
             * @return True if the progressbar is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the progressbar
             *
             * This function will hide the progressbar if its currently
             * visible and vice versa
             * 
             * @see setVisible
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the progress bar
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the progress bar, false if
             *         coordinates do not lie inside the progress bar
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the progress bar
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the progress bar is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the progress bar
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the progress bar is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the progress bar relative to the
             *        size of its parent
             * @param x New x coordinate of the progress bar
             * @param y New y coordinate of the progress bar
             * 
             * The position is specified in percentages as shown below:
             * 
             * @code
             * progressBar->setPosition({"5%", "10%"});
             * @endcode
             * 
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the progress bar is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the progress bar
             * @return Current position of the progress bar
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the progress bar
             * @return The absolute position of the progress bar
             * 
             * Unlike getPosition, this function returns the absolute 
             * position of the top-left point of the progress bar instead 
             * of the relative position to its parent
             * 
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

            /**
             * @brief Set the orientation of the progress bar
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the progress bar is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the progress bar
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the progress bar,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the progress bar
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the progress bar
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the progress bar
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the progress bar by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the progress bar,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the progress bar by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the progress bar,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the progress bar
             * @return Current scale of the progress bar
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the progress bar
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the progress bar defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the progress bar, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the progress bar is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the progress bar
             * @param origin New origin
             *
             * The origin of the progress bar defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the progress bar, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the progress bar is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the progress bar
             * @return Local origin of the progress bar
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the progress bar by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the progress bar,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the progress bar by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the progress bar,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Enable or disable the progress bar
             * @param isEnable Set true to enable the progress bar, false to
             *        disable the progress bar
             *
             * The progress bar is enabled by default
             *
             * @note Disabling the progress bar cancels all the interaction events
             */
            void setEnabled(bool isEnable) override;

            /**
              * @brief Check if progress bar is enabled or disabled
              * @return True if progress bar is enabled, false if progress bar is disabled
              */
            bool isEnabled() const override;

            /**
             * @brief Disable progress bar if its currently enabled and vice versa
             */
            void toggleEnabled() override;

            /**
             * @brief Focus or unfocus progress bar
             * @param isFocused True to focus or false to unfocus progress bar
             */
            void setFocused(bool isFocused) override;

            /**
             * @brief Check if progress bar is focused or not
             * @return True if progress bar is focused. Otherwise, false
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
            std::shared_ptr<tgui::ProgressBar> progressBar_; //!< Pointer to third party library
            std::shared_ptr<ProgressBarRenderer> renderer_;  //!< Renderer for this progress bar
        };
    }
}

#endif // IME_PROGRESSBAR_H
