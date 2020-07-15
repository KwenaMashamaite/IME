#ifndef CLICKABLEUIELEMENT_H
#define CLICKABLEUIELEMENT_H

#include "UIElement.h"
#include <string>

namespace Gui {
    class ClickableUIElement : public UIElement {
    public:
        /**
         * @brief Create a new UI element
         */
        ClickableUIElement();

        /**
         * @brief Create a new UI element
         * @param text Text to be displayed inside the element
         */
        explicit ClickableUIElement(const std::string& text);

       /**
         * @brief Enable or disable the element
         * @param isEnable Set true to enable the element, false to
         *        disable the element
         *
         * The element is enabled by default
         *
         * @note Disabling the element cancels all the interaction events.
         *       That is, the "mouseEnter", "mouseLeave", "click", "mouseUp"
         *       and "mouseDown" events will not fire while the element is
         *       disabled
         */
        void setEnabled(bool isEnable);

        /**
          * @brief Select/deselect element
          * @param isSelected Set true to select element, false to deselect element
          *
          * The element is not selected by default
          */
        void setSelected(bool isSelected);

        /**
          * @brief Check if element is enabled or disabled
          * @return True if element is enabled, false if element is disabled
          *
          * @note A disabled element cannot be interacted with using the mouse.
          * @see setEnabled(bool). Also, Hiding an element disables it, @see hide()
          * in @class UIElement
          */
        bool isEnabled() const;

        /**
         * @brief Disable element if its currently enabled and vice versa
         */
        void toggleEnabled();

        /**
         * @brief Check if element is selected or not
         * @return True if element is selected, false if element is not selected
         */
        bool isSelected() const;

        /**
         * @brief Destructor
         */
        virtual ~ClickableUIElement() = 0;

    private:
        /**
         * @brief Initialize events
         */
        void initEvents();

    private:
        //Selected state
        bool isSelected_;
        //Enabled state
        bool isEnabled_;
    };
}

#endif
