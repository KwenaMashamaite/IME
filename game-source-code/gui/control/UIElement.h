/**
 * @brief Abstract base class for static Graphical User Interface (GUI) elements
 */

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "../window/Window.h"
#include "event/EventEmitter.h"
#include "gui/IDrawable.h"
#include "common/Common.h"
#include <string>
#include <SFML/Graphics.hpp>

using Common::Position;
using Common::Dimensions;

namespace Gui {
    /**
     * @brief Represents the whitespace around the borders
     *        of the GUI element
     */
    struct Margin{
        float left = 0.0f;
        float right = 0.0f;
        float top = 0.0f;
        float bottom = 0.0f;
    };

    /**
     * @brief Represents the spacing between the
     *        text and the border of the GUI element
     */
    struct Padding{
        float left = 0.0f;
        float right = 0.0f;
        float top = 0.0f;
        float bottom = 0.0f;
    };

    /**
     * @brief Represents RGB combination colour
     */
    struct Colour{
        unsigned int red = 0;
        unsigned int green = 0;
        unsigned int blue = 0;
        unsigned int opacity = 255;
    };

    /**
     * @brief Position of the text within the elements border
     */
    enum class TextAlignment{
        Left,
        Right,
        Center
    };

    class UIElement : public EventEmitter, public IDrawable{
    public:
        /**
         * @brief Create a UI element
         *
         * The UI element is created with an empty text content
         * @note A UI element with no text content cannot be seen when
         * rendered. It will remain invisible until its text content,
         * outline thickness, padding or margin is set
         */
        UIElement();

        /**
         * @brief Create a UI element
         * @param textContent Text to be displayed inside the element
         *
         * The UI element will have the dimensions of the text content
         */
        explicit UIElement(const std::string &textContent);

        /**
         * @brief Set the same padding on all sides
         * @param padding Padding to set
         *
         * This function controls the distance between the elements text
         * content and the border. When the padding is 0, the border and
         * the elements text will have the same dimensions, When the padding
         * is set to a non-zero value, the border will move away from the
         * text content by the specified amount on all four sides. The
         * padding is 0 by default
         */
        void setPadding(float padding);

        /**
         * @brief Set the padding of the element individually
         * @param padding Padding to set
         *
         * This function controls the distance between the elements text
         * content and the border. When the padding is 0, the border and
         * the elements text will have the same dimensions. The "left"
         * and "right" values of the argument adjust the width while the
         * "top" and "bottom" values adjust the height. The default padding
         * is {0, 0, 0, 0}
         */
        void setPadding(const Padding& padding);

        /**
         * @brief Set the same margin on all sides
         * @param margin Margin to set
         *
         * The margin controls the distance between the element and
         * whatever its placed next to. For instance, when the element
         * is placed next to another UI element and the margin is zero,
         * The elements will physically touch each other. However, when
         * the margin is non-zero, the elements will automatically be
         * separated by the set margin. The default margin is 0 on all
         * sides
         */
        void setMargin(float margin);

        /**
         * @brief Set the margin (individually)
         * @param margin Margin to set
         *
         * The margin controls the distance between the element and
         * whatever its placed next to. For instance, when the element
         * is placed next to another UI element and the margin is zero,
         * The elements will physically touch each other. However, when
         * the margin is non-zero, the elements will automatically be
         * separated by the set margin. The default margin is {0, 0, 0, 0}
         */
        void setMargin(const Margin &margin);

        /**
         * @brief Set the position of the element
         * @param x New x coordinate of the element
         * @param y New y coordinate of the element
         */
        void setPosition(float x, float y);

        /**
         * @brief Set the position of the element
         * @param position New position of the element
         */
        void setPosition(Position position);

        /**
         * @brief Set the element's text font
         * @param textFont New font
         *
         * This function will overwrite the default text font
         */
        void setTextFont(const std::string &textFont);

        /**
         * @brief Set the character size of the element's text
         * @param charSize New character size
         *
         * The default character size is 30
         */
        void setTextCharSize(unsigned int charSize);

        /**
         * @brief Set the text content of the element
         * @param content New text content
         *
         * This function will overwrite any text that was previously
         * set
         */
        void setText(const std::string &content);

        /**
         * @brief Set the outline thickness of the element
         * @param outlineThickness New outline thickness to set
         *
         * The default outline thickness is 0
         */
        void setOutlineThickness(float outlineThickness);

        /**
        * @brief Set the fill colour of the element
        * @param fillColour New fill colour of the element
        *
        * The default fill colour is gainsboro
        */
        void setFillColour(Colour fillColour);

        /**
         * @brief Set the fill colour of the element's text
         * @param textFillColour New text fill colour
         *
         * The default text fill colour is black
         */
        void setTextFillColour(Colour textFillColour);

        /**
         * @brief Set the outline colour of the element
         * @param outlineColour New outline colour
         *
         * The default outline colour is grey
         */
        void setOutlineColour(Colour outlineColour);

        /**
         * @brief Set text alignment
         * @param textAlignment Text alignment to set
         */
        void setTextAlignment(TextAlignment textAlignment);

        /**
         * @brief Get the padding set on the element
         * @return Padding set on th element
         */
        Padding getPadding() const;

        /**
         * @brief Get the margin set on the element
         * @return Margin set on the element
         */
        Margin getMargin() const;

        /**
         * @brief Get the position of the element
         * @return Current position of the element
         */
        Position getPosition() const;

        /**
         * @brief Get the dimensions of the element
         * @return Current Dimensions of the element
         *
         * The dimensions of the element include the applied
         * margin, padding and outline thickness
         */
        Dimensions getDimensions() const;

        /**
         * @brief Get the fill colour of the element
         * @return Fill colour of the element
         */
        Colour getFillColour() const;

        /**
         * @brief Get the fill colour of the element's text
         * @return Fill colour of the element's text
         */
        Colour getTextFillColour() const;

        /**
         * @brief Get the outline colour of the element
         * @return Outline colour of the element
         */
        Colour getOutlineColour() const;

        /**
         * @brief Get the text alignment
         * @return Text alignment
         */
        TextAlignment getTextAlignment() const;

        /**
         * @brief Toggle the visibility of the element
         *
         * This function will make the element invisible if its currently
         * visible and vice versa. The visibility is not automatically
         * reflected on the render target. A call to draw() must be made
         * after calling this function
         */
        void toggleVisibility();

        /**
         * @brief Check if UI element is hidden on a render target or not
         * @return True if UI element is hidden, false if it is not hidden
         */
        bool isHidden() const override;

        /**
        * @brief Check if coordinates lie inside the element
        * @param x X coordinate to be checked
        * @param y Y coordinate to be checked
        * @return true if coordinates lie inside the element, false if
        *         coordinates do not lie inside the element
        */
        bool contains(float x, float y) const;

        /**
         * @brief Draw element on a render target
         * @param renderTarget Render target to draw element on
         */
        void draw(Window &renderTarget) override;

        /**
         * @brief Remove the element from a render target
         *
         * The UI element is only hidden graphically. That is, after
         * calling this function the element will remain where it is
         * and any operations on it (Such as changing the text font)
         * will be carried out behind the scene. Calling draw() on a
         * hidden element has no effect. That is, the element will
         * not appear on the render target
         */
        void hide() override;

        /**
         * @brief Make a hidden element reappear on a render target
         *
         * revealing a hidden UI element does not automatically show
         * it on the render target, a call to draw() must be made
         */
        void show() override ;

        /**
         * @brief Abstract Destructor
         *
         * The destructor is made abstract so that the class cannot be
         * instantiated directly. Derived classes will NOT be abstract
         * by default (The class implements the destructor), Only if they
         * themselves introduce abstract methods
         */
        virtual ~UIElement() = 0;

    protected:
        /**
         * @brief Restrict the publication of UI element events to
         *        class level
         *
         * This ensures that the publishing of events is exclusively
         * controlled by the class. For instance, if the method is
         * public, a click event can be raised on a button through
         * an instance, even thought the said button is not clicked.
         * This may cause bugs in the program
         */
        using EventEmitter::emit;

    private:
        /**
         * @brief Initialize element
         */
        void initialize();

        /**
         * @brief Create events and attach listeners
         */
        void initEvents();

        /**
        * @brief Update the element when text dimensions change
         *
         * This function will update the element when the text font,
         * text content, text character size etc.. changes
        */
        void updateDimensions();

    private:
        //White space around element
        Margin margin_;
        //Space between the border and elements text content
        Padding padding_;
        //Elements text content
        sf::Text text_;
        //Defines the perimeter of the entire element (includes margin and padding)
        sf::RectangleShape parentRectangle_;
        //Defines the perimeter of the elements border
        sf::RectangleShape border_;
        //Text position within the border
        TextAlignment textAlignment_;
        //Display state of element
        bool isHidden_;
    };
}

#endif
