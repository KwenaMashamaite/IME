/**
 * @brief Abstract base class for clickable UI elements.
 */

#ifndef CLICKABLEUIELEMENT_H
#define CLICKABLEUIELEMENT_H

#include "gui/control/UIElement.h"
#include "event/Event.h"

namespace Gui {
    class ClickableUIElement : public UIElement {
    public:
        /**
         * @brief Construct a new Clickable Element object
         */
        explicit ClickableUIElement(const std::string &content);

        /**
         * @brief Construct a new Clickable Element object
         * @param content Text displayed inside element
         * @param font Font to be used for the text
         * @param textCharSize Character size of the text content
         */
        ClickableUIElement(const std::string &content, const std::string &font, unsigned int textCharSize);

        /**
         * @brief Destructor. Made pure virtual to make class abstract
         */
        virtual ~ClickableUIElement() = 0;

    public:
        /**
         * @brief Subscribe to get notified when the element is clicked
         */
        Event<> clickEvent;

        /**
         * @brief Subscribe to get notified when the mouse enters the element area
         */
        Event<> mouseEnterEvent;

        /**
         * @brief Subscribe to get notified when the mouse leaves the element area
         */
        Event<> mouseLeaveEvent;

    private:
        /**
        * @brief Notify event listeners when the mouse enters the element
        */
        void onHover();

        /**
         * @brief Notify event listeners when the element is clicked
         */
        void onClick();

        /**
         * @brief Notify event listeners when the mouse leaves the element
         */
        void onHoverLost();

        /**
         * @brief Subscribe to mouse click and mouse move events
         */
        void subscribeToEvents();

    private:
        //Selection state
        bool isSelected_;
    };
}

#endif