/**
 * @brief UI layout that stacks panel vertically or horizontally
 */

#ifndef STACKPANEL_H
#define STACKPANEL_H

#include "gui/layout/Panel.h"

namespace Gui {
    enum class Orientation{
        Vertical,
        Horizontal
    };

    class StackPanel : public Panel{
    public:
        /**
         * @brief Create a new Panel object
         * @param x X coordinate of the panel
         * @param y Y coordinate of the panel
         * @param orientation Specify how the UI elements are stacked to each other
         */
        StackPanel(float x, float y, Orientation orientation);

        /**
         * @brief Add a UI element to the panel
         * @param guiElement Element to be added
         */
        void addElement(std::shared_ptr<UIElement> guiElement) override;

    private:
        //UI element orientation
        Orientation orientation_;
    };
}

#endif
