/**
 * @brief
 */

#ifndef SLIDER_H
#define SLIDER_H

#include "IWidget.h"
#include <TGUI/Widgets/Slider.hpp>

namespace IME {
    namespace Graphics::UI {
        class Slider : public IWidget {
        public:
            /**
             * @brief Construct a slider
             * @param minValue The minimum slider value
             * @param maxValue The maximum slider value
             */
            Slider(float minValue = 0, float maxValue = 10);

            /**
             * @brief Set a minimum value for the slider
             * @param minValue The value to set
             *
             * If the specified value is larger than the maximum value @see
             * setMaximum() then it will be changed to this value and the
             * previous maximum will be the new minimum. The default minimum
             * value is 0
             */
            void setMinimumValue(float minValue);

            /**
             * @brief Get the minimum value
             * @return The minimum value
             */
            float getMinimumValue() const;

            /**
             * @brief Set the maximum value for the slider
             * @param maxValue The value to be set
             *
             * The default maximum value is 10
             */
            void setMaximumValue(float maxValue);

            /**
             * @brief Get the maximum value for the slider
             * @return The maximum value
             */
            float getMaximumValue() const;

            /**
             * @brief Set the current value
             * @param value The value to be set
             *
             * The value must not be smaller than the minimum value  bigger than
             * the maximum value
             */
            void setValue(float value);

            /**
             * @brief Get the current value
             * @return The current value
             */
            float getValue() const;

            /**
             * @brief Change the number of positions the thumb advances with
             *        each move
             * @param step The new step size
             *
             *
             * The default step size is 1, which means the slider will only use
             * integer values between minimum and maximum. When set to 0, the
             * slider will be able to use any floating point value between
             * minimum and maximum values
             */
            void setStep(float step);

            /**
             * @brief Get the number of positions the thumb advances with each
             *        move
             * @return The current step size
             */
            float getStep() const;

            /**
             * @brief Set the orientation of the slider
             * @param isVertical Set true to place the slider vertically or false
             *                 to set the orientation horizontal
             *
             * The default orientation is horizontal
             */
            void setVerticalScroll(bool isVertical);

            /**
             * @b Check if the slider lies vertically or horizontally
             * @return True if the slider lies vertically or false if the slider
             *          lies horizontally
             */
            bool isVerticalScroll() const;


            /**
             * @brief Invert the minimum and maximum positions
             * @param isInverted True to invert the direction, otherwise
             *         false
             *
             * By default the minimum is on the left for horizontal sliders and
             * on the bottom for vertical sliders. The slider is not inverted
             * by default
             */
            void invert(bool isInverted);

            /**
             * @brief Check if the slider is inverted or not
             * @return True if the slider is inverted, otherwise false
             *
             * @see setInvertedDirection()
             */
            bool isInverted() const;

            /**
             * @brief Set whether the mouse wheel can be used to change the
             *        value of the slider
             * @param changeValueOnScroll True to change the value with the
             *        mouse wheel, otherwise false
             *
             * The value is changeable by the mouse wheel by default
             */
            void setChangeValueOnScroll(bool changeValueOnScroll);

            /**
             * @brief Check if the value is changed with the mouse wheel or not
             * @return True if the value is changed with the mouse wheel,
             *         otherwise false
             */
            bool isValueChangedOnScroll() const;

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
            std::shared_ptr<tgui::Slider> slider_;
            static const int fadeAnimDuration_ = 100;
        };
    }
}

#endif