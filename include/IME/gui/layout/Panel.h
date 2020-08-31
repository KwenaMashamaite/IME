/**
 * @brief Abstract base class for UI element layouts
 */

#ifndef PANEL_H
#define PANEL_H

#include "../control/UIElement.h"
#include "IME/common/IDrawable.h"
#include "IME/event/EventEmitter.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

namespace IME {
    namespace Gui {
        class Panel : public EventEmitter, public IDrawable{
        public:
            /**
             * @brief Create a GUI panel
             * @param x X coordinate of the panel
             * @param y Y coordinate of the panel
             */
            Panel(float x, float y);

            /**
             * @brief Set the position of the panel
             * @param position New position of the panel
             */
            void setPosition(const Position &position);

            /**
             * @brief Set the dimensions of the panel
             * @param dimensions New dimensions of the panel
             */
            void setDimensions(const Dimensions &dimensions);

            /**
             * @brief Set the fill colour of the panel
             * @param fillColour New fill colour of the panel
             *
             * The default fill colour is transparent
             */
            void setFillColour(Colour fillColour);

            /**
             * @brief Set the outline colour of the panel
             * @param outlineColour New outline colour of the panel
             *
             * The default outline colour is white
             */
            void setOutlineColour(Colour outlineColour);

            /**
             * @brief Set the outline thickness of the panel
             * @param outlineThickness New outline thickness
             *
             * The default outline thickness is 0
             */
            void setOutlineThickness(float outlineThickness);

            /**
             * @brief Get the position of the panel
             * @return Current position of the panel
             */
            Position getPosition() const;

            /**
             * @brief Get the dimensions of the panel
             * @return Current dimensions of the panel
             */
            Dimensions getDimensions() const;

            /**
             * @brief Get the outline thickness of the panel
             * @return Outline thickness of the panel
             */
            float getOutlineThickness() const;

            /**
             * @brief Get the number of elements in the panel
             * @return Number of elements in the panel
             */
            unsigned int getNumberOfElements() const;

            /**
             * @brief Add a UI element to the panel
             * @param name Name that can be used to refer to element
             * @param uiElement Element to add to panel
             * @return True if element was added or false if an element with the
             *         same name already exists
             */
            virtual bool addElement(const std::string &name,
                std::unique_ptr<UIElement> uiElement) = 0;

            /**
             * @brief Remove a UI element from the panel
             * @param name Name of the element to be removed
             *
             * This function is destructive. This means that the element
             * will be removed completely
             */
            bool removeElement(const std::string& name);

            /**
             * @brief Hide the panel from a render target
             *
             * This function will hide the panel and all it's child elements
             * from a render target. Operations on a hidden panel or on the
             * child elements of a hidden panel can still be performed. The
             * only difference is that the panel and it's child elements will
             * not be shown on the render when after they have been drawn
             */
            void hide() override;

            /**
             * @brief Reveal a hidden panel
             *
             * The panel will not automatically be shown on a render target. It
             * needs to be drawn after being revealed
             */
            void show() override;

            /**
             * @brief Check if panel is hidden or not
             * @return True if panel is hidden, false if panel is not hidden
             */
            bool isHidden() const override;

            /**
             * @brief Get access to an element in the panel
             * @param name Name of the element to get access to
             * @return A pointer to the requested UI element if it exist in the
             *         panel, otherwise a null pointer if the element cannot be
             *         found in the panel
             *
             * @note The pointer is returned by reference. Therefore, it is not
             *       advisable to keep the pointer after it has been accessed as
             *       it can be invalidated by removing the element from the panel
             */
            const std::unique_ptr<UIElement>& getElement(const std::string& name);

            /**
             * @brief Render the panel and it's UI elements on a render target
             * @param renderTarget Render target to draw panel on
             */
            void draw(Window &renderTarget) override;

            /**
             * @brief Handle event for all contained UI elements
             * @param event Event to handle
             *
             * This function will pass the event to all the contained UI elements
             * such that each UI element handles the event
             */
            void handleEvent(sf::Event event);

            /**
             * @brief Subscribe all child elements to an event
             * @tparam Args Template argument name
             * @param event Event to subscribe child elements to
             * @param callback Function to execute when event is fired
             *
             * This function will make all child elements of the panel to
             * listen for an event and execute a callback when that event
             * is fired
             */
            template <typename...Args>
            void subscribeChildrenToEvent(const std::string& event, Callback<Args...> callback){
                std::for_each(uiElements_.begin(), uiElements_.end(),
                    [&](const auto& uiElement){
                        uiElement.second->on(event, callback);
                    });
            }

            /**
             * @brief Subscribe a child element to an event
             * @tparam Args Template argument name
             * @param event Event to subscribe child element to
             * @param callback Function to execute when the event is fired
             * @param childElementName Child element to subscribe to an event
             *
             * This function will attempt to register a child element to an
             * event such that the provided callback function is executed when
             * the event is raised. This operation will be ignored if the child
             * element to subscribe to an event does not exist in the panel
             */
            template <typename...Args>
            void subscribeChildToEvent(const std::string& childElementName, const std::string& event,
               Callback<Args...> callback)
            {
                auto found = findUIElement(childElementName);
                if (found != uiElements_.end()){
                    found->second->on(event, callback);
                }
            }

        protected:
            //Collection alias
            using UIElementContainer = std::vector<std::pair<std::string, std::unique_ptr<UIElement>>>;
            using ConstIterator = UIElementContainer::const_iterator;

            /**
             * @brief Restrict publication of event to class level
             *
             * Only the class knows the conditions under which an event may be
             * fired. Therefore, events must not be raised externally as this
             * may result in events being raised at the wong time, resulting
             * in undesired and incorrect behavior
             */
            using EventEmitter::emit;

            /**
             * @brief Add UI element to underlying data structure
             * @param name Name of the UI element
             * @param uiElement Element to be added
             * @return True if element was added or false if an element with the
             *         same name already exists
             *
             * This function will try to add a UI element to the panel. If the
             * alias for the UI element to be added is already present in the
             * collection, that UI element wil not be added to the panel. In
             * other words, aliases for UI elements must be unique
             */
            bool add(const std::string &name, std::unique_ptr<UIElement> guiElement);

            /**
             * @brief Get access to a UI element inside the collection
             * @param uiElemAlias Name of the UI element to get access to
             * @return An iterator that points to the required element if
             *         it exists in the collection, otherwise an iterator
             *         that points one past the last element in collection
             */
            UIElementContainer::iterator findUIElement(const std::string& uiElemAlias);

            /**
             * @brief  Get a constant iterator that points to the first
             *          element in the the panel
             * @return Constant iterator that points to the first element
             *         in the the panel
             */
            ConstIterator cBegin() const;

            /**
             * @brief  Get a constant iterator that points one past the
             *         last element in the panel
             * @return A constant iterator that points one past the last
             *         element in the panel
             */
            ConstIterator cEnd() const;

        private:
            //UI elements container
            UIElementContainer uiElements_;
            //Graphical representation of the panel
            sf::RectangleShape panel_;
            //Null pointer (Useful when returning unique_ptr by reference)
            const std::unique_ptr<UIElement> null_Ptr;
            //Visibility state of the panel
            bool isHidden_;
        };
    } // namespace Gui
} // namespace IME

#endif
