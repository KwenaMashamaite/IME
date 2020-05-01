/**
 * @brief UI layout that stacks panel vertically or horizontally
 */

#ifndef STACKPANEL_H
#define STACKPANEL_H

#include "Panel.h"

namespace Gui {
    enum class Orientation{
        Vertical,
        Horizontal
    };

    class StackPanel final : public Panel{
    public:
        /**
         * @brief Create a new Stack Panel object
         * @param x X coordinate of the panel
         * @param y Y coordinate of the panel
         * @param orientation Specify how the UI elements
         *        are stacked to each other
         */
        StackPanel(float x, float y, Orientation orientation);

        /**
         * @brief Add a UI element to the panel
         * @param alias Name that can be used to refer to element
         * @param guiElement Element to be added
         */
        void addElement(const std::string &alias,
                std::unique_ptr<UIElement> guiElement) override;

    private:
        //Panel orientation state
        bool isOrientationVertical_;

        /**
         * @brief Set the position of a UI element relative to
         *        another UI element
         * @param uiElem UI element to position relative to another
         * @param refUIElem Reference UI element
         *
         * The element whose position is changed will have the
         * same orientation (vertical or horizontal) as the
         * element which is used as reference.
         */
        void setElemPosRelativeTo(const std::unique_ptr<UIElement> &uiElem,
                                  const std::unique_ptr<UIElement> &refUIElem);

        /**
         * @brief Adjust the dimensions of the panel based on
         *        the dimensions of a UI element
         * @param uiElement UI Element to accommodate
         *
         * This function will adjust the width or height of the
         * panel depending
         * on the dimensions of the UI element. The dimensions of
         * the panel will be adjusted such that all the edges of
         * the UI element lie within the edges of the panel
         */
        void adjustPanelDimensions(const std::unique_ptr<UIElement> &uiElement);
    };
}

#endif
