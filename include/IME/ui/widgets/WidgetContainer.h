////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_WIDGETCONTAINER_H
#define IME_WIDGETCONTAINER_H

#include "IME/Config.h"
#include "IME/ui/widgets/Widget.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief An Abstract Base Class for widgets that can store other
         *        widgets in them
         */
        class IME_API WidgetContainer : public Widget {
        public:
            using Ptr = std::unique_ptr<WidgetContainer>; //!< Unique IContainer pointer

            /**
             * @internal
             * @brief Constructor
             * @param widgetImpl Widget implementation
             */
            explicit WidgetContainer(std::unique_ptr<priv::IWidgetImpl> widgetImpl);

            /**
             * @brief Copy constructor
             */
            WidgetContainer(const WidgetContainer&);

            /**
             * @brief Copy assignment operator
             */
            WidgetContainer& operator=(const WidgetContainer&);

            /**
             * @brief Move constructor
             */
            WidgetContainer(WidgetContainer&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            WidgetContainer& operator=(WidgetContainer&&) noexcept;
            
            /**
             * @brief Add a widget to the container
             * @param widget Widget to be added
             * @param name Unique Name of the widget
             * @return Pointer to the widget if it was added to the container
             *         or nullptr if the container already has a widget with
             *         the same name as the specified widget name
             *
             * The @a name parameter is kept for compatibility with v2.2.x and
             * prior. Starting with v2.3.0, use ime::ui::Widget::setName
             *
             * @warning The name of the widget must not contain whitespaces
             */
            Widget* addWidget(Widget::Ptr widget, const std::string& name = "");
            
            /**
             * @brief Get access to a widget in the container
             * @param name Name of the widget to get access to
             * @return Pointer to the specified widget or nullptr if the
             *         container does not have a widget with the given
             *         name
             *
             * The container will first search for widgets that are direct 
             * children of it, but when none of the child widgets match the 
             * given name, a recursive search will be performed.
             */
            Widget* getWidget(const std::string& name) const;

            /**
             * @brief Add a widget to the gui
             * @param widget The widget to be added
             * @param name Unique name of the widget
             * @return Pointer to the widget if it was added to the container
             *         or a premature program exit if a widget with the same
             *         name as @a name already exist in the container
             *
             * The @a name parameter is kept for compatibility with v2.2.x and
             * prior. Starting with v2.3.0, use ime::ui::Widget::setName
             *
             * This function that will return the widget pointer already casted
             * to the desired type:
             *
             * @code
             * using ime::ui;
             * // Here the type of lblGreeting is deduced to Widget*
             * auto* lblGreeting = gui.addWidget(Label::create("Hi there"), "lblGreeting");
             *
             * // Here the type of lblGreeting is deduced to Label*
             * auto* lblGreeting = gui.addWidget<Label>(Label::create("Hi there"), "lblGreeting");
             * @endcode
             *
             * @warning This function will return a nullptr if the argument
             * @a widget is not convertible to T. In addition @a name
             * must be unique
             */
            template<typename T>
            T* addWidget(Widget::Ptr widget, const std::string& name = "") {
                return dynamic_cast<T*>(addWidget(std::move(widget), name));
            }

            /**
             * @brief Get access to a widget in the container
             * @param name Name of the widget to get access to
             * @return Pointer to the specified widget or nullptr if the
             *         container does not have a widget with the given
             *         name
             *
             * The container will first search for widgets that are direct
             * children of it, but when none of the child widgets match the
             * given name, a recursive search will be performed.
             *
             * If the widget is found, it will be casted to the desired type
             *
             * @warning This function will return nullptr if the widget
             * cannot be casted to the desired type
             */
            template<class T>
            T* getWidget(const std::string& name) const {
                return dynamic_cast<T*>(getWidget(name));
            }

            /**
             * @brief Get a widget at a given position
             * @param pos The position of the widget relative to the container
             *          view
             * @return Pointer to the widget at the specified position or a
             *         nullptr if there is no widget at that position
             */
            Widget* getWidgetAtPosition(Vector2f pos) const;

            /**
             * @brief Remove a widget from the container
             * @param name Name of the widget to be removed from the container
             * @return True if the widget was removed or false if the widget
             *         does not exist in the container
             */
            bool removeWidget(const std::string &name);

            /**
             * @brief Remove all widgets from the container
             */
            void removeAllWidgets();

            /**
             * @brief Place a widget before all other widgets, to the front
             *        of the z-order
             * @param widget The widget that should be moved to the front
             */
            void moveWidgetToFront(const Widget* widget);

            /**
             * @brief Place a widget behind all other widgets, to the back
             *        of the z-order
             * @param widget The widget that should be moved to the front
             */
            void moveWidgetToBack(const Widget* widget);

            /**
             * @brief Place a widget one step forward in the z-order
             * @param widget The widget that should be moved one step forward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            std::size_t moveWidgetForward(const Widget* widget);

            /**
             * @brief Place a widget one step backwards in the z-order
             * @param widget The widget that should be moved one step backward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            std::size_t moveWidgetBackward(const Widget* widget);

            /**
             * @brief Place a widget before all other widgets to the front
             * @param widget The widget to be moved to the front
             */
            void moveWidgetToFront(const std::string& widget);

            /**
             * @brief Place a widget behind all other widgets
             * @param widget The widget to be moved to the back
             */
            void moveWidgetToBack(const std::string& widget);

            /**
             * @brief Place a widget one step forward in the z-order
             * @param widget The widget that should be moved one step forward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t moveWidgetForward(const std::string& widget);

            /**
             * @brief Place a widget one step backwards in the z-order
             * @param widget The widget that should be moved one step backward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t moveWidgetBackward(const std::string& widget);

            /**
             * @brief Get the currently focused widget inside the container
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note If the focused widget is a container, then a pointer to
             * the container is returned rather than a pointer to the focused
             * widget inside that container
             *
             * @see getFocusedLeaf
             */
            Widget* getFocusedWidget() const;

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
            Widget* getFocusedLeaf() const;

            /**
             * @brief Focus the next widget in the container
             * @param recursive Set true to focus next widget when the currently
             *        focused widget is a container or false to focus the sibling
             *        of that container
             * @return True if the next widget was focused, otherwise false
             */
            bool focusNextWidget(bool recursive = true);

            /**
             * @brief Focus the previous widget in the container
             * @param recursive Set true to focus next widget when the currently
             *        focused widget is a container or false to focus the sibling
             *        of that container
             * @return True if the next widget was focused, otherwise false
             */
            bool focusPreviousWidget(bool recursive = true);

            /**
             * @brief Get the number of widgets in the container
             * @return The number of widgets in the container
             *
             * Note that child widgets that are also containers are only
             * counted as one
             */
            std::size_t getCount() const;

            /**
             * @brief Apply a callback to each widget in the container
             * @param callback The function to be applied
             */
            void forEach(const Callback<Widget*>& callback) const;

            /**
             * @brief Destructor
             */
            ~WidgetContainer() override;

        private:
            class WidgetContainerImpl;
            std::unique_ptr<WidgetContainerImpl> pimpl_;
        };
    }
}

#endif // IME_WIDGETCONTAINER_H
