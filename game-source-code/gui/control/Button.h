/**
 * @brief Dynamic UI element that can perform actions
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "gui/control/UIElement.h"
#include "event/SystemEventEmitter.h"
#include "event/EventEmitter.h"
#include <string>

namespace Gui {
    class Button final : public UIElement {
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
         * @brief Initialize button for event publishing
         * @param systemEventEmitter System event emitter
         *
         * If the button is not initialized, then it will act as a static UI element
         * That is, hovering over it and pressing it will have no effect
         */
        void initialize(SystemEventEmitter &systemEventEmitter);

        /**
         * @brief Register a callback to an event
         * @param eventName Name of the event to register callback on
         * @param callbackFunc Callback to register
         *
         * This function registers callbacks to the following events only:
         * 1. "click" - Fires when the button is clicked
         * 2. "mouseEnter" - Fires when the mouse enters the button
         * 3. "mouseLeave" - Fires when the mouse leaves the button
         *
         * Any event that's none of the above will not be raised
         */
        void on(std::string&& eventName, Callback<> callbackFunc);

        /**
         * @brief Disable the default behaviour of the button's response to the
         *        mouse cursor
         *
         * This function will stop the button from changing colours when the mouse
         * cursor enters or leaves the button. @note After calling this function, the
         * button will stil react to the mouse cursor, however, there won't be any
         * graphical representation to show it. You can define your own behaviour
         * by registering callbacks to "mouseEnter" and "mouseLeave" events. Therefore,
         * calling this functions is useful only if you want to use your own colours or
         * behavior
         */
        void clearDefaultBehavior();

    private:
        //Selection state
        bool isSelected_;
        //Emits button events
        EventEmitter eventEmitter_;
        //Callback id for the default onMouseEnter listener
        int mouseEnterCallbackId_;
        //Callback id for the default onMouseLeave listener
        int mouseLeaveCallbackId_;

        /**
         * @brief Initialize the default hover and hover lost behavior
         *        of the button
         *
         * This function will make the button and the button text change colour
         * when the mouse cursor enters the button. When the mouse cursor leaves
         * the button, the previous colour will be restored. This default behavior
         * may be overwritten through the public interface
         */
        void initDefaultBehavior();
    };
}

#endif
