/**
 * @brief Abstract base class for UI element layouts
 */

#ifndef PANEL_H
#define PANEL_H

#include "gui/control/UIElement.h"
#include "event/EventEmitter.h"
#include <SFML/Graphics.hpp>
#include <vector>
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
         * @brief Set the outline colour of the panel
         * @param outlineColour New outline colour of the panel
         */
        void setOutlineColour(Colour outlineColour);

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
        using UIElementContainer = std::vector<std::shared_ptr<UIElement>>;
        using constIterator = UIElementContainer::const_iterator;

        /**
         * @brief Add gui element to underlying data structure
         * @param guiElement Element to be added
         */
        void add(std::shared_ptr<UIElement> guiElement);

        /**
         * @brief Add listener to event
         * @param event Event to add listener to
         * @param callback Function to execute when event is raised
         */
        template <typename...Args>
        void on(std::string&& event, Callback<Args...> callback){
            eventEmitter_.addListener(std::forward<std::string&&>(event),std::move(callback));
        }

        /**
         * @brief Get a constant iterator that points to the first element in the
	     *        the panel
         * @return A constant iterator that points to the first element in the
	     *         the panel
         */
        constIterator cBegin() const;

        /**
         * @brief Get a constant iterator that points one past the last element in the
	     *        panel
         * @return A constant iterator that points one past the last element in the
	     *         panel
         */
        constIterator cEnd() const;

    private:
        //Elements contained by the panel
        UIElementContainer uiElements_;
        //Representation
        sf::RectangleShape panel_;
        //Event Emitter
        EventEmitter eventEmitter_;
    };
}

#endif