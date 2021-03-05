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

#ifndef IME_WIDGETCONTAINER_H
#define IME_WIDGETCONTAINER_H

#include "IME/Config.h"
#include "IME/ui/widgets/Widget.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Abstract base class for widgets that can store other
         *        widgets in them
         */
        class IME_API WidgetContainer : public Widget {
        public:
            using Ptr = std::shared_ptr<WidgetContainer>; //!< Shared IContainer pointer

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
             * @return True if the widget was added to the container or false
             *         if the container already has a widget with the same name
             *         as the specified widget name
             *
             * The name of the widget must not contain whitespaces
             */
            bool addWidget(Widget::Ptr widget, const std::string& name);
            
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
            Widget::Ptr getWidget(const std::string& name) const;

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
            std::shared_ptr<T> getWidget(const std::string& name) const {
                return std::dynamic_pointer_cast<T>(getWidget(name));
            }

            /**
             * @brief Get a widget at a given position
             * @param pos The position of the widget relative to the container
             *          view
             * @return Pointer to the widget at the specified position or a
             *         nullptr if there is no widget at that position
             */
            Widget::Ptr getWidgetAtPosition(Vector2f pos) const;

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
            void moveWidgetToFront(Widget::Ptr widget);

            /**
             * @brief Place a widget behind all other widgets, to the back
             *        of the z-order
             * @param widget The widget that should be moved to the front
             */
            void moveWidgetToBack(Widget::Ptr widget);

            /**
             * @brief Place a widget one step forward in the z-order
             * @param widget The widget that should be moved one step forward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            std::size_t moveWidgetForward(Widget::Ptr widget);

            /**
             * @brief Place a widget one step backwards in the z-order
             * @param widget The widget that should be moved one step backward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            std::size_t moveWidgetBackward(Widget::Ptr widget);

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
             * @brief Destructor
             */
            ~WidgetContainer();

        private:
            class WidgetContainerImpl;
            std::unique_ptr<WidgetContainerImpl> pimpl_;
        };
    }
}

#endif // IME_WIDGETCONTAINER_H
