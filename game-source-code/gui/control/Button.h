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
         * @brief Register a callback function to an event
         * @tparam Args Template parameter pack name
         * @param eventName Name of the event to register callback on
         * @param callbackFunc Callback function to be registered
         *
         * This function registers callbacks to the following events:
         * 1. "click" - Fires when the button is clicked
         * 2. "mouseEnter" - Fires when the mouse enters the button
         * 3. "mouseLeave" - Fires when the mouse leaves the button
         *
         * If the name of the event is none of the above events, the
         * operation is ignored
         */
        void on(std::string&& eventName, Callback<> callbackFunc);

        /**
         * @brief Destructor
         */
        ~Button();

    private:
        /**
         * @brief Subscribe to mouse click and mouse move events
         */
        void subscribeToEvents();

    private:
        //Selection state
        bool isSelected_;
        //Stores the number of times the class is instantiated
        inline static auto numOfInstantiations_ = 0u;
        //Stores the instantiation number of a specific class object
        std::string instantiationNum_;
        //Button clicked event
        Event<> clickEvent;
        //Mouse cursor entered button event
        Event<> mouseEnterEvent;
        //Mouse cursor left button event
        Event<> mouseLeaveEvent;
    };
}

#endif
