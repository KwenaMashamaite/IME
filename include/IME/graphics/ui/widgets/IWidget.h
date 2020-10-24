/**
 * @brief Abstract base class Graphical User Interface (GUI) widgets
 */

#ifndef IWIDGET_H
#define IWIDGET_H

#include "IME/graphics/Window.h"
#include "IME/graphics/IDrawable.h"
#include "IME/graphics/Colour.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/common/ITransformable.h"
#include "IME/common/Dimensions.h"
#include <SFML/Window/Event.hpp>
#include <TGUI/Widget.hpp>
#include <string>

namespace IME {
    namespace Graphics::UI {
        /**
         * @brief Represents the whitespace around the borders
         *        of the GUI widget
         */
        struct Margin {
            float left = 0.0f;
            float right = 0.0f;
            float top = 0.0f;
            float bottom = 0.0f;
        };

        /**
         * @brief Represents the spacing between the
         *        text and the border of the GUI widget
         */
        struct Padding {
            float left = 0.0f;
            float right = 0.0f;
            float top = 0.0f;
            float bottom = 0.0f;
        };

        /**
         * @brief Position of the text within the widgets border
         */
        enum class TextAlignment {
            Center,      //!< Center the widget in the cell
            UpperLeft,   //!< Draw the widget in the upper left corner of the cell
            Up,          //!< Draw the widget at the upper side of the cell (horizontally centered)
            UpperRight,  //!< Draw the widget in the upper right corner of the cell
            Right,       //!< Draw the widget at the right side of the cell (vertically centered)
            BottomRight, //!< Draw the widget in the bottom right corner of the cell
            Bottom,      //!< Draw the widget at the bottom of the cell (horizontally centered)
            BottomLeft,  //!< Draw the widget in the bottom left corner of the cell
            Left         //!< Draw the widget at the left side of the cell (vertically centered)
        };

        class IWidget : public ITransformable, public IDrawable, public EventEmitter {
        public:
            /**
             * @brief Set the same padding on all sides
             * @param padding Padding to set
             *
             * This function controls the distance between the widgets text
             * content and the border. When the padding is 0, the border and
             * the widgets text will have the same dimensions, When the padding
             * is set to a non-zero value, the border will move away from the
             * text content by the specified amount on all four sides. The
             * padding is 0 by default
             */
            virtual void setPadding(float padding) = 0;

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
            virtual void setPadding(const Padding& padding) = 0;

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
            virtual void setMargin(float margin) = 0;

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
            virtual void setMargin(const Margin &margin) = 0;

            /**
             * @brief Set the widget's text font
             * @param textFont New font
             * @throws FileNotFound if the specified font cannot be found on the
             *         disk
             *
             * This function will overwrite the current font if set
             */
            virtual void setTextFont(const std::string &textFont) = 0;

            /**
             * @brief Set the character size of the widget's text
             * @param charSize New character size
             *
             * The default character size is 30
             */
            virtual void setTextSize(unsigned int charSize) = 0;

            /**
             * @brief Set the text content of the widget
             * @param content New text content
             *
             * This function will overwrite any text that was previously
             * set
             */
            virtual void setText(const std::string &content) = 0;

            /**
             * @brief Set the outline thickness of the widget
             * @param outlineThickness New outline thickness to set
             *
             * The default outline thickness is 0
             */
            virtual void setOutlineThickness(float outlineThickness) = 0;

            /**
            * @brief Set the background colour of the widget
            * @param backgroundColour New background colour of the widget
            *
            * The default background colour is gainsboro
            */
            virtual void setBackgroundColour(Colour backgroundColour) = 0;

            /**
             * @brief Set the colour of the widget's text
             * @param textColour New text colour
             *
             * The default text colour is black
             */
            virtual void setTextColour(Colour textColour) = 0;

            /**
             * @brief Set the outline colour of the widget
             * @param outlineColour New outline colour
             *
             * The default outline colour is grey
             */
            virtual void setOutlineColour(Colour outlineColour) = 0;

            /**
             * @brief Set text alignment
             * @param textAlignment Text alignment to set
             */
            virtual void setTextAlignment(TextAlignment textAlignment) = 0;

            /**
             * @brief Get the padding set on the widget
             * @return Padding set on the widget
             */
            virtual Padding getPadding() const = 0;

            /**
             * @brief Get the margin set on the widget
             * @return Margin set on the widget
             */
            virtual Margin getMargin() const = 0;

            /**
             * @brief Set the size of the widget
             * @param width The width of the widget
             * @param height The hieght of teh widget
             */
            virtual void setSize(float width, float height) = 0;

            /**
             * @brief Get the size of the widget
             * @return Current size of the widget
             *
             * This function only returns the size of the widget, to get the
             * absolute size (with the margin, outline thickness etc...)
             * @see getAbsoluteSize()
             */
            virtual Dimensions getSize() const = 0;

            /**
             * @brief Get the absolute size of the widget
             * @return The absolute size of the widget
             *
             * The absolute size includes the size of the widget, the padding,
             * margin and outline thickness. To get just the size of the widget
             * use @see getSize()
             */
            virtual Dimensions getAbsoluteSize() = 0;

            /**
             * @brief Get the background colour of the widget
             * @return Background colour of the widget
             */
            virtual Colour getBackgroundColour() const = 0;

            /**
             * @brief Get the text colour of the widget
             * @return Text colour of the widget
             */
            virtual Colour getTextColour() const = 0;

            /**
             * @brief Get the outline colour of the widget
             * @return Outline colour of the widget
             */
            virtual Colour getOutlineColour() const = 0;

            /**
             * @brief Get the widgets text content
             * @return Elements text content
             */
            virtual std::string getText() const = 0;

            /**
             * @brief Get the outline thickness of the widget
             * @return Outline thickness of the widget
             */
            virtual unsigned int getOutlineThickness() const = 0;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            virtual unsigned int getTextSize() const = 0;

            /**
             * @brief Get the text alignment
             * @return Text alignment
             */
            virtual TextAlignment getTextAlignment() const = 0;

            /**
             * @brief Get the name of the current text font
             * @return Name of the current text font
             */
            virtual std::string getFontName() const = 0;

            /**
             * @brief Get the type of the widget
             * @return Type of the widget
             */
            virtual std::string getType() const = 0;

            /**
             * @brief Toggle the visibility of the widget
             *
             * This function will make the widget invisible if its currently
             * visible and vice versa. The visibility is not automatically
             * reflected on the render target. A call to draw() must be made
             * after calling this function
             */
            virtual void toggleVisibility() = 0;

            /**
             * @brief Check if coordinates lie inside the widget
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the widget, false if
             *         coordinates do not lie inside the widget
             */
            virtual bool contains(float x, float y) const = 0;

            /**
             * @brief Handle an event
             * @param event Event to handle
             *
             * @note If overridden, this function must be called in the body of
             * the overriding function so that the base class can also handle
             * its events. Failure to do so may result in inconsistent and
             * incorrect behavior
             */
            virtual void handleEvent(sf::Event event) = 0;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget object
             * @return The internal pointer to a third party widget object
             *
             * @warning This function is intended for internal use only and
             * should never be called
             */
            virtual std::shared_ptr<tgui::Widget> getInternalPtr() = 0;

            /**
             * @brief Default destructor
             */
            virtual ~IWidget() = default;

        protected:
            /**
             * @brief Restrict the publication of widget events to
             *        class level
             *
             * This ensures that the publishing of events is exclusively
             * controlled by the class. For instance, if the method is
             * public, a click event can be raised on a button through
             * an instance, even thought the said button is not clicked.
             * This may cause bugs in the program
             */
            using EventEmitter::emit;
        };
    }
}

#endif
