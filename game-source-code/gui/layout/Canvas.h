/**
 * @brief UI layout that has no restrictions on the placement of UI control elements
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
         * This function will try to add a UI element to the panel.
         * The element can be placed anywhere within the panel. There
         * are no restrictions on how and where the UI element should
         * be placed. @note A UI element that extends outside the edges
         * of the panel will NOT be added to the panel
         */
        void addElement(const std::string &alias, std::unique_ptr<UIElement> guiElement) override;
    };
}

#endif //CANVAS_H
