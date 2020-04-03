/**
 * @brief Abstract base class for static Graphical User Interface (GUI) elements
 */

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "gui/window/Window.h"
#include "event/EventEmitter.h"
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

    class UIElement {
    public:
        /**
         * @brief Create a UI element
         * @param content Text to be displayed inside the element
         * @param font Font to be used for the text
         * @param textCharSize Character size of the text
         *
         * The UI element has a character size of 30, a white background
         * and a black foreground by default
         */
        explicit UIElement(const std::string &content,
                           const std::string &font = "basson.ttf",
                           unsigned int textCharSize = 30u);

        /**
         * @brief Set the position of the element
         * @param x New x coordinate of the element
         * @param y New y coordinate of the element
         */
        void setPosition(float x, float y);

        /**
         * @brief Set the same margin on all sides
         * @param margin Margin to set
         */
        void setMargin(float margin);

        /**
         * @brief Set the same padding on all sides
         * @param padding Padding to set
         */
        void setPadding(float padding);

        /**
         * @brief Set the margin individually
         * @param margin Margin to set
         */
        void setMargin(const Margin &margin);

        /**
         * @brief Set the padding individually
         * @param padding Padding to set
         */
        void setPadding(const Padding& padding);

        /**
        * @brief Set the fill colour of the element
        * @param fillColour New fill colour of the element
        */
        void setFillColour(Colour fillColour);

        /**
         * @brief Set the UI element's text font
         * @param textFont New font
         */
        void setTextFont(const std::string &textFont);

        /**
         * @brief Set the character size of the element's text
         * @param charSize New character size
         */
        void setTextCharSize(unsigned int charSize);

        /**
         * @brief Set the text content of the element
         * @param content New text content
         *
         * This function will overwrite the text that
         * was previously set
         */
        void setText(const std::string &content);

        /**
         * @brief Set the fill colour of the element's text
         * @param textFillColour New text fill colour
         */
        void setTextFillColour(Colour textFillColour);

        /**
         * @brief Get the fill colour of the element's text
         * @return Fill colour of the element's text
         */
        Colour getTextFillColour() const;

        /**
         * @brief Get the fill colour of the element
         * @return Fill colour of the element
         */
        Colour getFillColour() const;

        /**
         * @brief Get the position of the element
         * @return Position of the element
         */
        Position getPosition() const;

        /**
         * @brief Get the dimensions of the element
         * @return Dimensions of the element
         */
        Dimensions getDimensions() const;

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
         * @brief Make UI element disappear from a render target
         */
        void hide();

        /**
         * @brief Make UI element reappear on a render target
         */
        void unHide();

        /**
         * @brief Check if UI element is hidden on a render target or not
         * @return True if UI element is hidden, false if it is not hidden
         */
        bool isHidden() const;

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
        virtual void draw(Window &renderTarget);

        /**
         * @brief Abstract Destructor
         *
         * The destructor is made abstract so that the class cannot be
         * instantiated directly. Derived classes will NOT be abstract
         * by default!, Only if they themselves introduce abstract methods
         */
        virtual ~UIElement() = 0;

    private:
        /**
        * @brief helper function for resizing the element
        */
        void resize();

        /**
         * @brief setup events
         */
        void initEvents();

    private:
        //White space around element
        Margin margin_;
        //Space between border and content
        Padding padding_;
        //Elements text content
        sf::Text text_;
        //Number of lines present in the content string
        unsigned int numOfLinesInText_;
        //Defines the perimeter of the entire element (includes margin and padding)
        sf::RectangleShape outline_;
        //Defines the perimeter of the element border
        sf::RectangleShape border_;
        //Event Emitter
        EventEmitter eventEmitter_;
        //
        bool isHidden_;
    };
}

#endif