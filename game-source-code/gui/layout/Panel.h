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

        /**
         * @brief Get the position of the panel
         * @return Position of the panel
         */
        Position getPosition() const;

        /**
         * @brief Set the position of the panel
         * @param position New position of the panel
         */
        void setPosition(const Position &position);

        /**
         * @brief Get the dimensions of the panel
         * @return Dimensions of the panel
         */
        Dimensions getDimensions() const;

        /**
         * @brief Set the dimensions of the panel
         * @param dimensions New dimensions of the panel
         */
        void setDimensions(const Dimensions &dimensions);

    private:
        //Representation
        sf::RectangleShape panel_;
    };
}

#endif