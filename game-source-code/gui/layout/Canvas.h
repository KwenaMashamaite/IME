/**
 * @brief UI layout that has no restrictions on the placement of UI controls
 */

#ifndef CANVAS_H
#define CANVAS_H

#include "Panel.h"

namespace Gui {
    class Canvas final : public Panel{
    public:
        /**
         * @brief Constructor
         * @param x X coordinate of the panel
         * @param y Y coordinate of the panel
         */
        Canvas(float x, float y);

        /**
         * @brief Add UI element to panel
         * @param guiElement UI element to add
         *
         * If the point of placement lies within the panel, then the UI element
         * will be added to the panel. The panel does not check if the element
         * sticks outside of it or not, as long as the UI elements point of
         * placement lies within the panel
         */
        void addElement(std::shared_ptr<UIElement> guiElement) override;
    };
}

#endif //CANVAS_H
