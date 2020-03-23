/**
 * @brief Abstract base class for static Graphical User Interface (GUI) elements
 */

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "gui/window/Window.h"
#include "event/EventEmitter.h"
#include "globals/Globals.h"
#include <string>
#include <SFML/Graphics.hpp>

using Globals::Position;
using Globals::Dimensions;

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
         * @brief Creates a UI element that has a width and height of 40 respectively,
         * 		  a transparent fill colour and a position of (0, 0)
         * @param content Content to be displayed inside the element
         * @param font Text content font
         * @param textCharSize Text content character size
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
         * @brief Set the margin on all sides (equal)
         * @param margin Margin o set
         */
        void setMargin(float margin);

        /**
         * @brief Set the padding on all sides (equal)
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
         * @brief Set the element's text content font
         * @param contentFont New font
         */
        void setTextFont(const std::string &contentFont);

        /**
         * @brief Set the character size of the element's text content
         * @param charSize New character size
         */
        void setTextCharSize(unsigned int charSize);

        /**
         * @brief Set the text content of the element. Overrides existing content.
         * @param content New text content
         */
        void setText(const std::string &content);

        /**
         * @brief Set the fill colour of the element's text content
         * @param textFillColour New text content fill colour
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
        * @brief Check if coordinates lie inside the element
        * @param x X coordinate to be checked
        * @param y Y coordinate to be checked
        * @return true if coordinates lie inside the element, false if
        *         coordinates do not lie inside the element
        */
        bool contains(float x, float y) const;

        /**
         * @brief Renders element on a render target
         * @param renderTarget Render target to draw element on
         */
        virtual void draw(Window &renderTarget);

        /**
         * @brief Default destructor
         */
        virtual ~UIElement() = 0;

    private:
        /**
        * @brief helper function for resizing element
        */
        void resize();

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
        sf::RectangleShape parentRectangle_;
        //Defines the perimeter of the element border
        sf::RectangleShape border_;
        //Defines the perimeter of the content area
        sf::RectangleShape textRectangle_;
        //Event Emitter
        EventEmitter eventEmitter_;

        /**
         * @brief Convert own Colour object to SFML colour object
         * @param color Colour to be converted to SFML colour object
         * @return SFML colour object
         */
        static sf::Color convertOwnColourToSFMLColour(Colour color);

        /**
         * @brief Convert SFML colour object to own colour object
         * @param SFMLColour Colour to be converted to own colour object
         * @return Own colour object
         */
        static Colour convertSFMLColourToOwnColour(sf::Color SFMLColour);
    };
}

#endif