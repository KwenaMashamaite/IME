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

        /**
         * @brief Set the fill colour of the panel
         * @param fillColour Fill colour to set
         *
         * The panel has a transparent fill colour by default
         */
        void setFillColour(Colour fillColour);

        /**
         * @brief Get the number of elements in the panel
         * @return Number of elements in the panel
         */
        unsigned int size() const;

        /**
         * @brief Add a UI element to the panel
         * @param guiElement Element to add to panel
         */
        virtual void addElement(std::shared_ptr<UIElement> guiElement) = 0;

        /**
         * @brief Render the elements of a panel on a render target
         * @param renderTarget Render target to draw UI elements on
         */
        virtual void draw(Window &renderTarget);

    protected:
        /**
         * @brief Add gui element to underlying data structure
         * @param guiElement Element to be added
         * @return True if element was successfully added. false otherwise
         */
        bool add(std::shared_ptr<UIElement> guiElement);

        /**
         * @brief Get the last element that was added to the panel
         * @return A shared pointer to the last element that was added to the panel
         */
        std::shared_ptr<UIElement> lastInsertedElement() const;

    private:
        //Elements contained by the panel
        std::set<std::shared_ptr<UIElement>> guiElementList_;
        //Pointer to the last inserted element. (Can't use back(), Elements are sorted after insertion)
        std::shared_ptr<UIElement> lastInsertedElement_;
        //Representation
        sf::RectangleShape panel_;
    };
}

#endif