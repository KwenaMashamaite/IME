/**
 * @brief Intemediate Abstract Base Class for menus
 *
 * The menus are made up of layout panels that contain GUI elements
 * such as buttons and text labels
 *
 * @note This class does not implement the Menu Interface, it only
 * implements methods which are common to all menus to avoid code
 * duplication. All Menu classes must implement the Menu Interface
 * through this intermediate class.
 */

#ifndef MENU_H
#define MENU_H

#include "gui/menu/IMenu.h"
#include "gui/window/Window.h"
#include "gui/layout/Panel.h"
#include <unordered_map>
#include <memory>


namespace Gui {
    class Menu : public IMenu {
    public:
        /**
         * @brief Constructor
         * @param renderTarget render target to draw menu on
         */
        explicit Menu(Window& renderTarget);

    protected:
        /**
         * @brief Get a refernce to a render target
         * @return Reference to a render target
         */
        Window& getRenderTarget();

        /**
         * @brief Add a panel to the menu
         * @param panelName Name of the panel
         * @param panel Panel to be added
         */
        void addPanel(const std::string &panelName, std::shared_ptr<Panel> panel);

        /**
         * @brief Get access to a panel
         * @param panel Name of the panel to acess
         * @return Panel to access
         *
         * If the requested panel cannot be found, a null shared
         * pointer will be returned
         */
        std::shared_ptr<Panel> getPanel(const std::string& panel) const;

        /**
         * @brief Remove a panel from the menu
         * @param panel Name of the panel to remove
         */
        void removePanel(const std::string& panel);

    private:
        //Render target
        Window& renderTarget_;
        //Stores a list of GUI control element containers
        std::unordered_map<std::string, std::shared_ptr<Panel>> panels_;
    };
}

#endif
