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

#ifndef IME_MENUBAR_H
#define IME_MENUBAR_H

#include "IME/Config.h"
#include "IME/ui/widgets/Widget.h"
#include "IME/ui/renderers/MenuBarRenderer.h"
#include <initializer_list>
#include <string>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A widget which contains navigational drop-down menus
         */
        class IME_API MenuBar : public Widget {
        public:
            using Ptr = std::shared_ptr<MenuBar>; //!< Shared widget pointer
            using ConstPtr = std::shared_ptr<const MenuBar>; //!< Shared constant widget pointer

            /**
             * @brief Copy constructor
             */
            MenuBar(const MenuBar&);

            /**
             * @brief Copy assignment operator
             */
            MenuBar& operator=(const MenuBar&);

            /**
             * @brief Move constructor
             */
            MenuBar(MenuBar&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            MenuBar& operator=(MenuBar&&) noexcept;
            
            /**
             * @brief Create a new menu bar widget
             * @return The new menu bar
             */
            static MenuBar::Ptr create();

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            MenuBar::Ptr copy() const;

            /**
             * @brief Make a copy of this widget
             * @return A copy of this widget
             *
             * You should use this function if you don't care about the type
             * of the widget, otherwise use the widgets copy function
             *
             * @see copy
             */
            Widget::Ptr clone() const override;

            /**
             * @brief Get the menu bars renderer
             * @return The menu bars renderer
             *
             * The renderer gives access to functions that determine how the
             * menu bar is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            MenuBarRenderer::Ptr getRenderer();
            const MenuBarRenderer::Ptr getRenderer() const;

            /**
             * @brief Add a new menu
             * @param text The text to be displayed on the menu
             */
            void addMenu(const std::string& text);

            /**
             * @brief Add new menus
             * @param text The menus to be added
             *
             * The menus are created in the given order
             *
             * @code
             * menuBar.addMenus({"File", "Edit", "View", "Help"});
             * @endcode
             */
            void addMenus(const std::initializer_list<std::string>& menus);

            /**
             * @brief Add a new menu item to the last added menu
             * @param text The text to be displayed on the menu item
             * @return True if the menu item was added or false if the menu bar
             *         does not contain any menus yet
             *
             * @code
             * menuBar->addMenu("File");
             * menuBar->addMenuItem("Load");
             * menuBar->addMenuItem("-"); // Adds a line separator between "Load" and "Save"
             * menuBar->addMenuItem("Save");
             * menuBar->addMenu("Edit");
             * menuBar->addMenuItem("Undo");
             * @endcode
             *
             * You can add a separator between menu items by adding "-" as a
             * menu item between the items you want to visually separate
             */
            bool addMenuItem(const std::string& text);

            /**
             * @brief Add a new menu item to an existing menu
             * @param menu The name of the menu to add the item to
             * @param text The text to de displayed on the item
             * @return True if the menu item was added or false if the given
             *         menu could not be found
             *
             * @code
             * menuBar->addMenu("File");
             * menuBar->addMenu("Edit");
             * menuBar->addMenuItem("File", "Load");
             * menuBar->addMenuItem("File", "-"); // Adds a line separator between "Load" and "Save"
             * menuBar->addMenuItem("File", "Save");
             * menuBar->addMenuItem("Edit", "Undo");
             * @endcode
             *
             * You can add a separator between menu items by adding "-" as a
             * menu item between the items you want to visually separate
             */
            bool addMenuItem(const std::string& menu, const std::string& text);

            /**
             * @brief Add a new menu or a sub menu item
             * @param hierarchy Hierarchy of the menu item, starting with the
             *                  parent menu and ending with menu item to be added
             *
             * Note that the hierarchy must contain at least two items. The
             * first item is the name of the parent menu and the second item
             * is the sub-menu of the parent menu. Items three and beyond are
             * cascades of the second item. If the parent menu does not exist
             * it will be created
             *
             * @code
             * menuBar->addMenuItem({"File", "Save"});
             * menuBar->addMenuItem({"File", "Open recent", "SaveGame01"});
             * menuBar->addMenuItem({"File", "Open recent", "SaveGame02"});
             * menuBar->addMenuItem({"Window", "Editor tabs", "Split", "Left"});
             * @endcode
             */
            void addMenuItem(const std::initializer_list<std::string>& hierarchy);

            /**
             * @brief Remove all menus from the menu bar
             */
            void removeAllMenus();

            /**
             * @brief Remove a menu
             * @param menu The name of the menu to be removed
             * @return True if the menu was removed or false if the menu bar
             *         does not contain a menu with the given name
             *
             * Note that all menu items that belonged to the menu will also
             * be removed
             */
            bool removeMenu(const std::string& menu);

            /**
             * @brief Remove a menu item from a menu
             * @param menu The name of the menu to remove an item from
             * @param menuItem The name of the item to be removed
             * @return True if the item was removed or false if either the menu
             *         or menu item does not exist
             */
            bool removeMenuItem(const std::string& menu, const std::string& menuItem);

            /**
             * @brief Remove a menu or a sub menu item
             * @param hierarchy Hierarchy of the menu item, starting with the
             *                  parent menu and ending with the menu item to be
             *                  deleted
             * @param removeParentsWhenEmpty True to delete the parent of the
             *                  deleted menu item if it has no other children
             * @return True if the menu item was found and removed or false if
             *         the given hierarchy is incorrect
             *
             * @code
             * menuBar->removeMenuItem({"File", "Save"});
             * menuBar->removeMenuItem({"File", "Open recent", "SaveGame02"});
             * @endcode
             */
            bool removeMenuItem(const std::initializer_list<std::string>& hierarchy,
                bool removeParentsWhenEmpty = true);

            /**
             * @brief Remove all menu items of a menu
             * @param menu The name of the menu to remove all items from
             * @return True if the menu items were removed or false if the menu
             *         could not be found or the menu does not have any items
             */
            bool removeMenuItems(const std::string& menu);

            /**
             * @brief Remove menu items below a menu or sub menu
             * @param hierarchy Hierarchy of the menu item, starting with the
             *                  parent menu and ending with the sub menu containing
             *                  the items to be removed
             * @return True if the menu item existed and its children were removed
             *         or false if the given hierarchy is incorrect
             *
             * @code
             * menuBar->removeSubMenuItems({"File", "Recent files"});
             * @endcode
             */
            bool removeSubMenuItems(const std::initializer_list<std::string>& hierarchy);

            /**
             * @brief Enable or disable a menu
             * @param menu The name of the menu to enable or disable
             * @param enabled True to enable the menu of false to disable it
             */
            void setMenuEnable(const std::string& menu, bool enabled);

            /**
             * @brief Check if a menu is enabled or disabled
             * @param menu The name of the menu to be checked
             * @return True if the menu is enabled or false if the menu is
             *         disabled or it could not be found
             */
            bool isMenuEnabled(const std::string& menu) const;

            /**
             * @brief Enable or disable a menu item
             * @param menu The name of the menu in which the menu item is located
             * @param menuItem The name of the menu item to enable or disable
             * @param enabled True to enable the menu item of false to disable it
             */
            void setMenuItemEnable(const std::string& menu,const std::string& menuItem,
                bool enabled);

            /**
             * @brief Enable or disable a menu item
             * @param hierarchy Hierarchy of the menu item, starting with the
             *                  parent menu and ending with the menu item to
             *                  be enabled or disabled
             * @param enabled True to enable or false to disable
             *
             * @code
             * menuBar->setMenuItemEnable({"Edit", "Find", "Replace"});
             * @endcode
             */
            void setMenuItemEnable(const std::initializer_list<std::string>& hierarchy, bool enabled);

            /**
             * @brief Check if a menu item is enabled or disabled
             * @param menu The name of the menu in which the menu item is located
             * @param menuItem The name of the menu item to be checked
             * @return True if the menu item is enabled or false if the menu
             *         item is disabled or it could not be found
             *
             * @see setMenuItemEnable
             */
            bool isMenuItemEnabled(const std::string& menu, const std::string& menuItem) const;

            /**
             * @brief Check if a menu item is enabled or disabled
             * @param hierarchy Hierarchy of menu item, starting with the parent
             *                  menu and ending with the menu item to be checked
             * @return True if the menu item is enabled or false if it is disabled
             *         or the given hierarchy is incorrect
             *
             * @code
             * menuBar->isMenuItemEnabled({"Edit", "Find", "Replace"});
             * @endcode
             *
             * @see setMenuItemEnable
             */
            bool isMenuItemEnabled(const std::initializer_list<std::string>& hierarchy) const;

            /**
             * @brief Set the minimum width of the submenus
             * @param minimumWidth The new minimum width
             *
             * When a submenu is displayed, the width will either be
             * @a minimumWidth or the width of the longest text in the
             * submenu
             *
             * The default minimum width is 125 pixels
             */
            void setMinimumSubMenuWidth(float minimumWidth);

            /**
             * @brief Get the distance between the text and the side of the menu item
             * @return The minimum width of the submenus
             *
             * @see setMinimumSubMenuWidth
             */
            float getMinimumSubMenuWidth() const;

            /**
             * @brief Set whether the menus open above or below the menu bar
             * @param invert True to open the menus above the menu bar or false
             *               to open them below the menu bar
             *
             * By default the menus open below the menu bar
             */
            void invertMenuDirection(bool invert);

            /**
             * @brief Check if the menu bar direction is inverted or not
             * @return True if inverted, otherwise false
             *
             * @see invertMenuDirection
             */
            bool isMenuDirectionInverted() const;

            /**
             * @brief Close an open menu
             */
            void closeMenu();

            /**
             * @brief Get the type of the spin control
             * @return The type of the spin control
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~MenuBar() override;

        private:
            /**
             * @brief Constructor
             */
            MenuBar();

        private:
            class MenuBarImpl;
            std::unique_ptr<MenuBarImpl> pimpl_;
        };
    }
}

#endif //IME_MENUBAR_H
