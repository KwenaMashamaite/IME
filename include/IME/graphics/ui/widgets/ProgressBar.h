#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "IClickableWidget.h"
#include <TGUI/Widgets/ProgressBar.hpp>

namespace IME {
    namespace Graphics::UI {
        class ProgressBar : public IClickableWidget {
        public:
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
             */
            ProgressBar();

            /**
             * @brief Set a minimum value
             * @param minValue The value to set
             *
             * If the specified value is larger than the maximum value @see
             * setMaximum() then it will be changed to this value and the
             * previous maximum will be the new minimum. The default minimum
             * value is 0
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
             * The value must not be smaller than the minimum value  bigger than
             * the maximum value
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
             * The value will never exceed the maximum value
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
             * @brief Set the position of the widget
             * @param X coordinate of the new position
             * @param Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * See the move function to apply an offset based on the previous
             * position instead. The default position of a transformable widget
             * is (0, 0).
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the widget
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * See the move function to apply an offset based on the previous
             * position instead. The default position of a transformable widget
             * is (0, 0).
             */
            void setPosition(Position position) override;

            /**
             * @brief Set the orientation of the widget
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead. The default rotation of a transformable widget
             * is 0.
             */
            void setRotation(float angle) override;

            /**
             * @brief Set the scale factors of the widget
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale.
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the local origin of the widget
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of an widget defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the widget, and ignore all
             * transformations (position, scale, rotation).
             * The default origin of a transformable widget is (0, 0).
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Get the position of the widget
             * @return Current position of the widget
             */
            Position getPosition() const override;

            /**
             * @brief Get the local origin of the widget
             * @return get the local origin of the widget
             */
            Position getOrigin() const override;

            /**
             * @brief Get the orientation of the widget
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360].
             */
            float getRotation() const override;

            /**
             * @brief Move the widget by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the widget,
             * unlike setPosition which overwrites it.
             */
            void move(float xOffset, float yOffset) override;

            /**
             * @brief Rotate the widget
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the widget,
             * unlike setRotation() which overwrites it
             */
            void rotate(float offset) override;

            /**
             * @brief Scale the widget
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the widget,
             * unlike setScale() which overwrites it.
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Draw the widget on a render target
             * @param renderTarget Target to draw widget on
             *
             * @warning Do not call this function, the widget will be drawn
             * by its container
             */
            void draw(Window &renderTarget) override;

            /**
            * @brief Hide widget from a render target
            *
            * A hidden widget will not be drawn on a render target when calling
            * draw()
            */
            void hide() override;

            /**
             * @brief Show a hidden widget
             *
             * This function will reveal an widget that was hidden prior to
             * function call. Calling this function on an widget that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Check if widget is hidden or not
             * @return True if widget is hidden, false if widget is not hidden
             */
            bool isHidden() const override;

            /**
             * @brief Enable or disable the widget
             * @param isEnable Set true to enable the widget, false to
             *        disable the widget
             *
             * The widget is enabled by default
             *
             * @note Disabling the widget cancels all the interaction events.
             *       That is, the "mouseEnter", "mouseLeave", "click", "mouseUp"
             *       and "mouseDown" events will not fire while the widget is
             *       disabled
             */
            void setEnabled(bool isEnable) override;

            /**
              * @brief Check if widget is enabled or disabled
              * @return True if widget is enabled, false if widget is disabled
              *
              * @note A disabled widget cannot be interacted with using the mouse.
              * @see setEnabled(bool). Also, Hiding an widget disables it, @see hide()
              * in @class IWidget
              */
            bool isEnabled() const override;

            /**
             * @brief Disable widget if its currently enabled and vice versa
             */
            void toggleEnabled() override;

            /**
             * @brief Check if mouse cursor is currently over the widget or not
             * @return True if mouse cursor is over the widget, false otherwise
             */
            bool isMouseOverElement() const override;

            /**
             * @brief Set the same margin on all sides
             * @param margin Margin to set
             *
             * The margin controls the distance between the widget and
             * whatever its placed next to. For instance, when the widget
             * is placed next to another widget and the margin is zero,
             * The widgets will physically touch each other. However, when
             * the margin is non-zero, the widgets will automatically be
             * separated by the set margin. The default margin is 0 on all
             * sides
             */
            void setPadding(float padding) override;

            /**
             * @brief Set the padding of the widget individually
             * @param padding Padding to set
             *
             * This function controls the distance between the widgets text
             * content and the border. When the padding is 0, the border and
             * the widgets text will have the same dimensions. The "left"
             * and "right" values of the argument adjust the width while the
             * "top" and "bottom" values adjust the height. The default padding
             * is {0, 0, 0, 0}
             */
            void setPadding(const Padding &padding) override;

            /**
             * @brief Set the same margin on all sides
             * @param margin Margin to set
             *
             * The margin controls the distance between the widget and
             * whatever its placed next to. For instance, when the widget
             * is placed next to another widget and the margin is zero,
             * The widgets will physically touch each other. However, when
             * the margin is non-zero, the widgets will automatically be
             * separated by the set margin. The default margin is 0 on all
             * sides
             */
            void setMargin(float margin) override;

            /**
             * @brief Set the margin (individually)
             * @param margin Margin to set
             *
             * The margin controls the distance between the widget and
             * whatever its placed next to. For instance, when the widget
             * is placed next to another widget and the margin is zero,
             * The widgets will physically touch each other. However, when
             * the margin is non-zero, the widgets will automatically be
             * separated by the set margin. The default margin is {0, 0, 0, 0}
             */
            void setMargin(const Margin &margin) override;

            /**
             * @brief Set the text colour of the button when the mouse cursor
             *        enters it
             * @param textColour Button text colour to set
             *
             * The buttons text colour changes to dark grey by default
             * on "mouseEnter". The colour changes back to the way it
             * was prior to "mouseEnter" on "mouseLeave"
             */
            void setHoverTextColour(Colour textColour) override;

            /**
             * @brief Set the background colour of the button when the mouse
             *        cursor enters it
             * @param backgroundColour Background colour to set
             *
             * The button colour changes to dim grey by default on mouse
             * enter. The colour changes back to the way it was
             * prior to "mouseEnter" on "mouseLeave"
             */
            void setHoverBackgroundColour(Colour backgroundColour) override;

            /**
             * @brief Set the outline colour of the button when the
             *        mouse cursor enters the button
             * @param outlineColour Outline colour to set
             *
             * The buttons outline colour changes to light sky blue
             * by default on "mouseEnter". The colour changes back
             * to the way it was prior to "mouseEnter" on "mouseLeave"
             */
            void setHoverOutlineColour(Colour outlineColour) override;

            /**
             * @brief Set the widget's text font
             * @param textFont New font
             * @throws FileNotFound if the specified font cannot be found on the
             *         disk
             *
             * This function will overwrite the current font if set
             */
            void setTextFont(const std::string &textFont) override;

            /**
             * @brief Set the character size of the widget's text
             * @param charSize New character size
             *
             * The default character size is 30
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Set the text content of the widget
             * @param content New text content
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &content) override;

            /**
             * @brief Set the outline thickness of the widget
             * @param outlineThickness New outline thickness to set
             *
             * The default outline thickness is 0
             */
            void setOutlineThickness(float outlineThickness) override;

            /**
            * @brief Set the background colour of the widget
            * @param backgroundColour New background colour of the widget
            *
            * The default background colour is gainsboro
            */
            void setBackgroundColour(Colour backgroundColour) override;

            /**
             * @brief Set the colour of the widget's text
             * @param textColour New text colour
             *
             * The default text colour is black
             */
            void setTextColour(Colour textColour) override;

            /**
             * @brief Set the outline colour of the widget
             * @param outlineColour New outline colour
             *
             * The default outline colour is grey
             */
            void setOutlineColour(Colour outlineColour) override;

            /**
             * @brief Set text alignment
             * @param textAlignment Text alignment to set
             */
            void setTextAlignment(TextAlignment textAlignment) override;

            /**
             * @brief Get the padding set on the widget
             * @return Padding set on the widget
             */
            Padding getPadding() const override;

            /**
             * @brief Get the margin set on the widget
             * @return Margin set on the widget
             */
            Margin getMargin() const override;

            /**
             * @brief Set the size of the widget
             * @param width The width of the widget
             * @param height The height of the widget
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the image that is shown on the widget
             * @param filename Name of the image file
             * @throws FileNotFound if the image cannot be found on the disk
             *
             * @note When this image is set, the background color property will
             *       be ignored
             */
            void setTexture(const std::string& filename) override;

            /**
             * @brief Set the image that is displayed when the widget is focused
             *        but not hovered
             * @param filename Filename of the image to be displayed
             * @throws FileNotFound if the image cannot be found on the disk
             */
            void setOnFocusedImage(const std::string& filename) override;

            /**
             * @brief Set the image that is displayed when the widget is disabled
             * @param filename Filename of the image to be displayed
             * @throws FileNotFound if the image cannot be found on the disk
             */
            void setOnDisabledImage(const std::string& filename) override;

            /**
             * @brief Set the image that is displayed when the mouse is held
             *        down on the widget
             * @param filename Filename of the image to be displayed
             * @throws FileNotFound if the image cannot be found on the disk
             *
             * No image is displayed by default
             */
            void setOnMouseDownImage(const std::string& filename) override;

            /**
             * @brief Set the image that is displayed when the mouse enters the
             *        widget
             * @param filename Filename of the image to be displayed
             * @throws FileNotFound if the image cannot be found on the disk
             *
             * No image is displayed by default
             */
            void setOnHoverImage(const std::string& filename) override;

            /**
             * @brief Get the size of the widget
             * @return Current size of the widget
             *
             * This function only returns the size of the widget, to get the
             * absolute size (with the margin, outline thickness etc...)
             * @see getAbsoluteSize()
             */
            Dimensions getSize() const override;

            /**
             * @brief Get the absolute size of the widget
             * @return The absolute size of the widget
             *
             * The absolute size includes the size of the widget, the padding,
             * margin and outline thickness. To get just the size of the widget
             * use @see getSize()
             */
            Dimensions getAbsoluteSize() override;

            /**
             * @brief Get the background colour of the widget
             * @return Background colour of the widget
             */
            Colour getBackgroundColour() const override;

            /**
             * @brief Get the text colour of the widget
             * @return Text colour of the widget
             */
            Colour getTextColour() const override;

            /**
             * @brief Get the outline colour of the widget
             * @return Outline colour of the widget
             */
            Colour getOutlineColour() const override;

            /**
             * @brief Get the widgets text content
             * @return Widgets text content
             */
            std::string getText() const override;

            /**
             * @brief Get the outline thickness of the widget
             * @return Outline thickness of the widget
             */
            unsigned int getOutlineThickness() const override;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Get the text alignment
             * @return Text alignment
             */
            TextAlignment getTextAlignment() const override;

            /**
             * @brief Focus or unfocus widget
             * @param isFocused Set to true to focus or false to unfocus widget
             */
            void setFocused(bool isFocused) override;

            /**
             * @brief Check if widget is focused or not
             * @return True if widget is focused. Otherwise, false
             */
            bool isFocused() const override;

            /**
             * @brief Get the name of the current text font
             * @return Name of the current text font
             */
            std::string getFontName() const override;

            /**
             * @brief Get the type of the widget
             * @return Type of the widget
             */
            std::string getType() const override;

            /**
             * @brief Toggle the visibility of the widget
             *
             * This function will make the widget invisible if its currently
             * visible and vice versa. The visibility is not automatically
             * reflected on the render target. A call to draw() must be made
             * after calling this function
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the widget
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the widget, false if
             *         coordinates do not lie inside the widget
             */
            bool contains(float x, float y) const override;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget widget
             * @return The internal pointer to a third party widget widget
             *
             * @warning This function is intended for internal use only and
             * should never be called under any circumstance
             */
            std::shared_ptr<tgui::Widget> getInternalPtr() override;

            /**
             * @brief Handle an event
             * @param event Event to handle
             *
             * @note If overridden, this function must be called in the body of
             * the overriding function so that the base class can also handle
             * its events. Failure to do so may result in inconsistent and
             * incorrect behavior
             *
             * @warning Don't call this function, the widgets container will
             * pass the event to it
             */
            void handleEvent(sf::Event event) override;

        private:
            std::shared_ptr<tgui::ProgressBar> progressBar_;
            static const int fadeAnimDuration_ = 100;
        };
    }
}

#endif
