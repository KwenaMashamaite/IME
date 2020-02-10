/**
 * @brief UI element that can be interacted with (e.g clicked)
 */

#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "gui/control/UIElement.h"
#include "event/Event.h"
#include <string>

namespace Gui {
    class Button : public UIElement {
    public:
        /**
         * @brief Construct a new Button object
         * @param buttonText Text to be displayed on the button
         *
         * The button is placed at (0, 0) and the button text
         * has a character size of 30 by default
         */
        explicit Button(const std::string &buttonText);

        /**
         * @brief Create a button
         * @param content Text to be displayed on the button
         * @param font  Font used for the text
         * @param textCharSize Character size of the text
         *
         * The button has the dimensions of the button content and
         * a position of (0, 0) by default
         */
        Button(const std::string &content, const std::string &font, unsigned int textCharSize);

        /**
         * @brief Activate or deactivate a button
         * @param isActive Set to true to activate or false to deactivate
         *
         * The button is activated by default. When deactivated, the button
         * becomes a static UI element. That is, Hovering the mouse over the
         * button or clicking it will have no effect
         */
        void setActive(bool isActive);

        /**
         * @brief Destructor
         */
        ~Button();

    private:
        /**
         * @brief Subscribe to mouse click and mouse move events
         */
        void subscribeToEvents();

    public:
        /**
         * @brief Subscribe to get notified when the button is clicked
         */
        Event<> clickEvent;

        /**
         * @brief Subscribe to get notified when the mouse enters the button
         */
        Event<> mouseEnterEvent;

        /**
         * @brief Subscribe to get notified when the mouse leaves the button
         */
        Event<> mouseLeaveEvent;

    private:
        //Selection state
        bool isSelected_;
        inline static auto numOfInstantiations_ = 0u;
        std::string instantiationNum_;
    };
}

#endif