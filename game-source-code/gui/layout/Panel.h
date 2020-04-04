/**
 * @brief Abstract base class for UI element layouts
 */

#ifndef PANEL_H
#define PANEL_H

#include "gui/control/UIElement.h"
#include "event/EventEmitter.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
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
         * @brief Set the outline thickness of the panel
         * @param outlineThickness New outline thickness
         *
         * The outline thickness is zero by default
         */
        void setOutlineThickness(float outlineThickness);

        /**
         * @brief Get the outline thickness
         * @return Outline thickness
         */
        float getOutlineThickness() const;

        /**
         * @brief Add a UI element to the panel
         * @param alias Name that can be used to refer to element
         * @param guiElement Element to add to panel
         */
        virtual void addElement(const std::string &alias, std::unique_ptr<UIElement> guiElement) = 0;

        /**
         * @brief Remove a UI element from the panel
         * @param uiElement Name of the element to be removed
         *
         * This function is destructive. This means that the element will
         * be removed completely
         */
        void remove(const std::string& uiElement);

        /**
         * @brief Hide panel
         *
         * This function will hide a panel and all it's child elements
         * from a render target. Operations on a hidden panel or on the
         * child elements of a hidden panel can still be performed. The
         * only difference is that the panel and it's child elements will
         * not be shown on the render when a call to display is made
         */
        void hide();

        /**
         * @brief Reveal a hidden panel
         */
        void reveal();

        /**
         * @brief Get access to an element
         * @param uiElement Name of the element to get access to
         * @return Pointer to a UI element if found, otherwise
         *         null pointer
         */
        const std::unique_ptr<UIElement>& getElement(const std::string& uiElement);

        /**
         * @brief Render panel and it's UI elements on a render target
         * @param renderTarget Render target to draw UI elements on
         */
        virtual void draw(Window &renderTarget);

    protected:
        //Collection alias
        using UIElementContainer = std::vector<std::pair<std::string, std::unique_ptr<UIElement>>>;
        using ConstIterator = UIElementContainer::const_iterator;

        /**
         * @brief Add gui element to underlying data structure
         * @param alias Name of the UI element
         * @param guiElement Element to be added
         *
         * This function will try to add a UI element to the panel. If the alias for
         * the UI element to be added is already present in the collection, that UI element
         * wil not be added to the panel. In other words, aliases for UI elements must be
         * unique
         */
        void add(const std::string &alias, std::unique_ptr<UIElement> guiElement);

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
        ConstIterator cBegin() const;

        /**
         * @brief Get a constant iterator that points one past the last element in the
	     *        panel
         * @return A constant iterator that points one past the last element in the
	     *         panel
         */
        ConstIterator cEnd() const;

    private:
        /**
         * @brief Get access to a UI element inside the collection
         * @param uiElemAlias Name of the UI element to get access to
         * @return An iterator that points to the required element if it exists
         *         in the collection, otherwise an iterator that points one past the
         *         last element in collection
         */
        auto findUIElement(const std::string& uiElemAlias){
            return std::find_if(uiElements_.begin(), uiElements_.end(),
                [this, &uiElemAlias](const auto& uiElement){
                    return uiElement.first == uiElemAlias;
                });
        }

    private:
        //Elements contained by the panel
        UIElementContainer uiElements_;
        //Representation
        sf::RectangleShape panel_;
        //Event Emitter
        EventEmitter eventEmitter_;
        //Dummy variable
        const std::unique_ptr<UIElement> null_Ptr;
    };
}

#endif