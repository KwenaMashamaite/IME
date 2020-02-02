/**
 * @brief Abstract base class for UI element layouts
 */

#ifndef PANEL_H
#define PANEL_H

#include "gui/control/UIElement.h"
#include <SFML/Graphics.hpp>
#include <set>
#include <memory>

namespace Gui {
    class Panel {
    public:
        /**
         * @brief Create a GUI panel
         * @param x X coordinate of the panel
         * @param y Y coordinate of the panel
         */
        Panel(float x, float y);

    private:
        //Representation
        sf::RectangleShape panel_;
    };
}

#endif