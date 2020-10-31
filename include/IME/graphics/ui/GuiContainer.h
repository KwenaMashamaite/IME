/**
 * @brief Container for Graphical User Interface (GUI) objects
 */

#ifndef GUI_H
#define GUI_H

#include <TGUI/Backends/SFML/GuiSFML.hpp>
#include "IME/common/Position.h"
#include "IME/graphics/CursorTypes.h"
#include "IME/graphics/ui/layout/IContainer.h"
#include <unordered_map>

namespace IME {
    namespace Graphics::UI {
        namespace Graphics {
            class Window;
        }

        class IWidget;

        class GuiContainer {
        public:
            /**
             * @brief Construct the gui
             *
             * @warning When constructed with this constructor, @see setTarget()
             * must be called before the gui is used
             */
            GuiContainer() = default;

            /**
             * @brief Construct the gui and set the target on which the gui
             *        should be drawn
             * @param target Render target that will be used by the gui
             *
             * This constructor will set the target therefore there is no need
             * to call @see setTarget()
             */
            explicit GuiContainer(Window& target);

            /**
             * @brief Copy constructor
             */
            GuiContainer(const GuiContainer&) = delete;

            /**
             * @brief Assignment operator
             */
            GuiContainer& operator=(const GuiContainer&) = delete;

            /**
             * @brief Set the target on which the gui should be drawn
             * @param target Render target that will be used by the gui
             */
            void setTarget(Window& target);

            /**
             * @brief Check if the target on which the gui should be drawn is
             *        set or not
             * @return True if the target is set, otherwise false
             */
            bool isTargetSet() const;

            /**
             * @brief Handle event for all contained widgets
             * @param event Event to handle
             *
             * This function will pass the event to all the contained widgets
             * such that each widget is given a chance to handle the event
             */
            void handleEvent(sf::Event event);

            /**
             * @brief Enable tab usage
             * @param enabled True to enable tab usage or false to disable it
             *
             * When the tab key usage is enabled, pressing tab will focus
             * another widget
             */
            void setTabKeyUsageEnabled(bool enabled);

            /**
             * @brief Check if tab key usage is enabled or not
             * @return True if it is enabled, otherwise false
             */
            bool isTabKeyUsageEnabled() const;

            /**
             * @brief Draw all the widgets that were added to the gui
             */
            void draw();

            /**
             * @brief Change the global font
             * @param filename Filename of the new global font
             * @throws FileNotFound if the font cannot be found on the disk
             */
            void setFont(const std::string& filename);

            /**
             * @brief Unfocus all widgets
             */
            void unfocusAllWidgets();

            /**
             * @brief Set the opacity of all widgets
             * @param opacity The new opacity of the widgets in the range [0, 1]
             *
             * O means completely transparent whilst 1 means fully opaque.
             * The default opacity for all widgets is 1
             */
            void setOpacity(float opacity);

            /**
             * @brief Get the opacity of all the widgets
             * @return The opacity of all the widgets in the range [0, 1]
             */
            float getOpacity() const;

            /**
             * @brief Change the mouse cursor that gets shown
             * @param cursorType The mouse cursor to show
             *
             * @warning The mouse cursor must be restored for every call to this
             * function @see restoreMouseCursor(). If the cursor is not restored
             * then it can no longer be changed by widgets. If this function is
             * called multiple times, the cursors are stacked and restoring the
             * cursors will only pop the last added cursor from the stack
             *
             * @note This function can also be used to prevent widgets from
             * changing the mouse cursor by setting the cursor of choice and
             * restoring it once widgets are allowed to change the cursor
             */
            void setMouseCursor(CursorType cursorType);

            /**
             * @brief Restores the mouse cursor to the way it was prior to
             *        @see setMouseCursor()
             *
             * @note The mouse cursor is changeable only if there are no active
             * mouse cursor changes @see setMouseCursor()
             */
            void restoreMouseCursor();

            /**
             * @brief Change the mouse cursor that is shown
             * @param cursorType The cursor to show
             *
             * This function is used by widgets to set the mouse cursor when
             * the mouse enters or leaves a widget. If you want to choose a
             * cursor that doesnt changed when moving the mouse, then use
             * @see setMouseCursor(). If the cursor is already set using the
             * setMouseCursor() function then this function wont be able to
             * change the cursor. When the mouse cursor is restored @see
             * restoreMouseCursor(), then the mouse cursor will be changed to
             * what was last requested here
             */
            void requestMouseCursor(CursorType cursorType);

            /**
             * @brief Get a list of all widgets in the gui
             * @return A vector of all widgets in the gui
             */
            const std::vector<IWidget>& getWidgets() const;

            /**
             * @brief Add a widget to the gui
             * @param widget The widget to be added
             * @param widgetName Name of the widget
             *
             * The widget name must be set if the widget is to be retrieved at
             * a later time. In addition, the name must not contain whitespaces
             */
            void addWidget(std::shared_ptr<IWidget> widget,
                const std::string& widgetName = "");

            /**
             * @brief Get a pointer to a widget in the gui
             * @param widgetName Name of the widget to retrieve
             * @return Pointer to the specified widget or a nullptr if the gui
             *         does not have a widget with the specified name
             *
             * The gui will first search for widgets that are direct children
             * of it, but when none of the child widgets match the given name,
             * a recursive search will be performed.
             */
            std::shared_ptr<IWidget> getWidget(const std::string& widgetName) const;

            /**
             * @brief Remove a widget from the gui
             * @param widget Widget to be removed from the gui
             * @return True if the widget was removed or false if the widget
             *         does not exist in the gui
             */
            bool removeWidget(std::shared_ptr<IWidget> widget);

            /**
             * @brief Remove all widgets from the gui
             */
            void removeAllWidgets();

            /**
             * @brief Get the currently focused widget inside the gui
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note If the focused widget is a container, then a pointer to
             * the container is returned rather than a pointer to the focused
             * widget inside that container. @see getFocusedLeaf() should be
             * used to get the widget that is focused inside a container
             */
            std::shared_ptr<IWidget> getFocusedWidget() const;

            /**
             * @brief Get the currently focused widget inside the gui
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note Unlike @see getFocusedWidget() which returns a pointer to
             * a container when the focused widget is a child of another
             * container within the gui, this function will always return the
             * focused widget regardless of whether its a direct child of the
             * gui or not
             */
            std::shared_ptr<IWidget> getFocusedLeaf() const;

            /**
             * @brief Get a widget at a given position
             * @param pos The position of the widget relative to the gui view
             * @return Pointer to the widget at the specified position or a
             *         nullptr if there is no widget at that position
             */
            std::shared_ptr<IWidget> getWidgetAtPosition(Position pos) const;

            /**
             * @brief Get the widget below the mouse cursor
             * @param mousePos The position of the mouse cursor in pixel
             *                 coordinates relative to the window
             * @return Widget below the mouse or a nullptr if the mouse isn't
             *         on top of any widgets
             */
            std::shared_ptr<IWidget> getWidgetBelowMouseCursor(Position mousePos) const;

            /**
             * @brief Focus the next widget in the gui
             * @param recursive Set true to focus next widget when the currently
             *        focused widget is a container or false to focus the sibling
             *        of that container
             * @return True if the next widget was focused, otherwise false
             */
            bool focusNextWidget(bool recursive = true);

            /**
             * @brief Focus the previous widget in the gui
             * @param recursive Set true to focus next widget when the currently
             *        focused widget is a container or false to focus the sibling
             *        of that container
             * @return True if the next widget was focused, otherwise false
             */
            bool focusPreviousWidget(bool recursive = true);

            /**
             * @brief Place a widget before all other widgets to the front
             * @param widget The widget to be moved to the front
             */
            void moveWidgetToFront(const std::shared_ptr<IWidget> &widget);

            /**
             * @brief Place a widget behind all other widgets
             * @param widget The widget to be moved to the back
             */
            void moveWidgetToBack(const std::shared_ptr<IWidget> &widget);

            /**
             * @brief Place a widget one step forward in the z-order
             * @param widget The widget that should be moved one step forward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t
            moveWidgetForward(std::shared_ptr<IWidget> widget);

            /**
             * @brief Place a widget one step backwards in the z-order
             * @param widget The widget that should be moved one step backward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t
            moveWidgetBackward(std::shared_ptr<IWidget> widget);

            /**
             * @brief Set the character size of all existing and future child
             *        widgets
             * @param size The new character size
             */
            void setTextSize(unsigned int size);

            /**
             * @brief Get the text size of all existing and future child widgets
             * @return The text size of all existing and future child widgets
             */
            unsigned int getTextSize() const;

        private:
            //Gui controller and renderer
            tgui::GuiSFML sfmlGui_;
            //Widgets container
            std::unordered_map<std::string, std::shared_ptr<IWidget>> widgets_;
        };
    }
}

#endif
