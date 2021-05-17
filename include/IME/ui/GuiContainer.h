////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef IME_GUICONTAINER_H
#define IME_GUICONTAINER_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include "IME/ui/widgets/Widget.h"
#include "IME/core/event/Event.h"
#include <string>
#include <memory>

namespace ime {

    /// @internal
    namespace priv {
        class Window;
    }

    namespace ui {
        /**
         * @brief Container for Graphical User Interface (GUI) widgets
         *
         * This class is a container for all UI widgets. In order for a
         * widget to receive events, updates and be rendered, it must exist
         * in the gui container either directly (explicit addition) or
         * indirectly (added to a container widget which is then added to
         * the gui container)
         */
        class IME_API GuiContainer {
        public:
            using Ptr = std::shared_ptr<GuiContainer>; //!< Shared gui container pointer
            /**
             * @brief Construct the gui
             *
             * @warning When constructed with this constructor, setTarget
             * must be called before the gui container is used
             *
             * @see setTarget
             */
            GuiContainer();

            /**
             * @brief Construct the gui and set the target on which the gui
             *        should be drawn
             * @param window Render target that will be used by the gui
             *
             * This constructor will set the target therefore there is no need
             * to call setTarget
             *
             * @see setTarget
             */
            explicit GuiContainer(priv::Window& window);

            /**
             * @brief Copy constructor
             */
            GuiContainer(const GuiContainer&) = delete;

            /**
             * @brief Assignment operator
             */
            GuiContainer& operator=(const GuiContainer&) = delete;

            /**
             * @brief Move constructor
             */
            GuiContainer(GuiContainer&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            GuiContainer& operator=(GuiContainer&&) noexcept;

            /**
             * @brief Set the part of the window the gui will render on
             * @param viewport Rect of the window to which the gui should draw
             *
             * Example code to render the gui on only the right side of an
             * 800x600 window:
             *
             * @code
             * gui.setAbsoluteViewport({400, 0, 400, 600});
             * @endcode
             *
             * By default, the gui fills the entire window
             *
             * @see setRelativeViewPort
             */
            void setAbsoluteViewport(const FloatRect& viewport);

            /**
             * @brief Set the part of the window the gui will render on as a
             *        ratio relative to the window size
             * @param viewport Rect of the window to which the gui should draw
             *        relative to the window size
             *
             * Example code to render the gui on only the right side of window:
             * @code
             * gui.setRelativeViewport({0.5f, 0, 0.5f, 1});
             * @endcode
             *
             * The default viewport is (0, 0, 1, 1) so that the gui fills
             * the entire window
             *
             * @see setViewPort
             */
            void setRelativeViewport(const FloatRect& viewport);

            /**
             * @brief Get the part of the window the gui renders
             * @return Rect of the window to which the gui will draw
             *
             * @see setViewPort and setRelativeViewPort
             */
            FloatRect getViewport() const;

            /**
             * @brief Set the part of the gui that will be used to fill the
             *        viewport
             * @param view
             *
             * Example code to use the contents of the gui container from
             * top-left (200,100) to bottom-right (600, 400) and stretch
             * it to fill the viewport (which equals the entire window
             * by default):
             * @code
             * gui.setAbsoluteView({200, 100, 400, 300});
             * @endcode
             */
            void setAbsoluteView(const FloatRect& view);

            /**
             * @brief Set the part of the gui that is used to fill the viewport
             * @param view Rect of the gui that will be stretched to fill the
             *             viewport relative to the viewport size
             *
             * The default view is (0, 0, 1, 1) so that no scaling happens
             * when the viewport is changed
             *
             * Example code to zoom in on the gui and display everything at
             * 2x the size:
             * @code
             * gui.setRelativeView({0, 0, 0.5f, 0.5f});
             * @endcode
             *
             * @see setViewPort
             */
            void setRelativeView(const FloatRect& view);

            /**
             * @brief Get the part of the gui that is used to fill the viewport
             * @return The part of the gui that fills the viewport
             *
             * By default, the view will have the same size as the viewport
             * @see setViewPort and setRelativeViewPort
             */
            FloatRect getView() const;

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

            /**
             * @internal
             * @brief Set the target on which the gui should be drawn
             * @param window Render target that will be used by the gui
             *
             * @warning This function is intended for internal use and should
             * never be called outside of IME
             */
            void setTarget(priv::Window& window);

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
            void handleEvent(Event event);

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
             * @warning The mouse cursor must be restored for every call
             * to this function. If the cursor is not restored then it can
             * no longer be changed by widgets. If this function is called
             * multiple times, the cursors are stacked and restoring the
             * cursors will only pop the last added cursor from the stack
             *
             * @note This function can also be used to prevent widgets from
             * changing the mouse cursor by setting the cursor of choice and
             * restoring it once widgets are allowed to change the cursor
             *
             * @see restoreMouseCursor
             */
            void setMouseCursor(CursorType cursorType);

            /**
             * @brief Restores the mouse cursor to the way it was prior to
             *        setMouseCursor
             *
             * The mouse cursor is changeable only if there are no active
             * mouse cursor changes
             *
             * @see setMouseCursor
             */
            void restoreMouseCursor();

            /**
             * @brief Change the mouse cursor that is shown
             * @param cursorType The cursor to show
             *
             * This function is used by widgets to set the mouse cursor when
             * the mouse enters or leaves a widget. If you want to choose a
             * cursor that doesnt changed when moving the mouse, then use
             * setMouseCursor. If the cursor is already set using the
             * setMouseCursor function then this function wont be able to
             * change the cursor. When the mouse cursor is restored
             * restoreMouseCursor, then the mouse cursor will be changed to
             * what was last requested here
             *
             * @see setMouseCursor and restoreMouseCursor
             */
            void requestMouseCursor(CursorType cursorType);

            /**
             * @brief Add a widget to the gui
             * @param widget The widget to be added
             * @param widgetName Unique name of the widget
             * @return True if the widget was added to the container or false
             *         if the container already has a widget with the same name
             *         as the specified widget name
             *
             * The name of the widget must not contain whitespaces
             */
            bool addWidget(const Widget::Ptr& widget,
                const std::string& widgetName);

            /**
             * @brief Get a pointer to a widget in the gui
             * @param name Name of the widget to retrieve
             * @return Pointer to the specified widget or a nullptr if the gui
             *         does not have a widget with the specified name
             *
             * The gui will first search for widgets that are direct children
             * of it, but when none of the child widgets match the given name,
             * a recursive search will be performed
             */
            Widget::Ptr getWidget(const std::string& name) const;

            /**
             * @brief Get a pointer to a widget in the gui
             * @param name Name of the widget to retrieve
             * @return Pointer to the specified widget or a nullptr if the gui
             *         does not have a widget with the specified name or T is
             *         invalid
             *
             * @note The pointer will already be casted to the desired type (T)
             */
            template <class T>
            std::shared_ptr<T> getWidget(const std::string& name) const {
                return std::dynamic_pointer_cast<T>(getWidget(name));
            }

            /**
             * @brief Remove a widget from the gui
             * @param widget Name of the widget to be removed from the gui
             * @return True if the widget was removed or false if the widget
             *         does not exist in the gui
             */
            bool removeWidget(const std::string &widget);

            /**
             * @brief Remove all widgets from the gui
             */
            void removeAllWidgets();

            /**
             * @brief Get the currently focused widget inside the container
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note Unlike getFocusedWidget which returns a pointer to
             * a container when the focused widget is a child of another
             * container within the container, this function will always return
             * the focused widget regardless of whether its a direct child of
             * the container or not
             *
             * @see getFocusedWidget
             */
            Widget::Ptr getFocusedWidget() const;

            /**
             * @brief Get the currently focused widget inside the container
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note Unlike getFocusedWidget which returns a pointer to
             * a container when the focused widget is a child of another
             * container within the container, this function will always return
             * the focused widget regardless of whether its a direct child of
             * the container or not
             *
             * @see getFocusedWidget
             */
            Widget::Ptr getFocusedLeaf() const;

            /**
             * @brief Get a widget at a given position
             * @param pos The position of the widget relative to the gui view
             * @return Pointer to the widget at the specified position or a
             *         nullptr if there is no widget at that position
             */
            Widget::Ptr getWidgetAtPosition(Vector2f pos) const;

            /**
             * @brief Get the widget below the mouse cursor
             * @param mousePos The position of the mouse cursor in pixel
             *                 coordinates relative to the window
             * @return Widget below the mouse or a nullptr if the mouse isn't
             *         on top of any widgets
             */
            Widget::Ptr getWidgetBelowMouseCursor(Vector2f mousePos) const;

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
             * @brief Unfocus all widgets in the container
             */
            void unfocusAllWidgets();

            /**
             * @brief Place a widget before all other widgets to the front
             * @param widget The widget to be moved to the front
             */
            void moveWidgetToFront(const Widget::Ptr &widget);

            /**
             * @brief Place a widget behind all other widgets
             * @param widget The widget to be moved to the back
             */
            void moveWidgetToBack(const Widget::Ptr &widget);

            /**
             * @brief Place a widget one step forward in the z-order
             * @param widget The widget that should be moved one step forward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t moveWidgetForward(const Widget::Ptr& widget);

            /**
             * @brief Place a widget one step backwards in the z-order
             * @param widget The widget that should be moved one step backward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t moveWidgetBackward(const Widget::Ptr& widget);

            /**
             * @brief Destructor
             */
            ~GuiContainer();

        private:
            class GuiContainerImpl;
            std::unique_ptr<GuiContainerImpl> pimpl_;
        };
    }
}

#endif // IME_GUICONTAINER_H
