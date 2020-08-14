/**
 * @brief GUI layout panel for other GUI layout panels
 */

#ifndef DOCKPANEL_H
#define DOCKPANEL_H

#include "Panel.h"
#include <memory>
#include <map>

namespace IME {
    namespace Gui {
        class DockPanel final : public Panel {
        public:
            /**
             * @brief Dock positions
             */
            enum class DockPosition{
                LeftEdge,
                RightEdge,
                TopEdge,
                BottomEdge
            };

            /**
             * @brief Create a new DockPanel object
             * @param x X coordinate of the panel
             * @param y Y coordinate of the panel
             */
            DockPanel(float x, float y);

            /**
             * @brief Add a GUI layout panel to the Dock panel
             * @param dockPosition Side on which the panel should be
             *        docked
             * @param panel Panel to be docked
             *
             * @note If a panel was already docked at the specified
             * position, it will be replaced. The order in which panels
             * are docked is important as each time a panel is docked,
             * the overall space of the dock panel decreases. The last
             * panel (One docked after all the other three edges have
             * been docked) to be docked will occupy remaining space
             */
            void dock(DockPosition dockPosition, std::unique_ptr<Panel> panel);

            /**
             * @brief Set the position of the default panel for adding
             *        UI elements
             * @param dockPosition The position of the panel to set as
             *        default
             *
             * All UI elements added to the @class DockPanel using the
             * addElement() function will be added to the default panel.
             * Initially, the panel on the left edge is set os the default
             * panel
             */
            void setDefaultPanelPos(DockPosition dockPosition);

            /**
             * @brief Get the position of the default panel
             * @return The position of the default panel
             */
            DockPosition getDefaultPanelPos() const;

            /**
             * @brief Add a GUI element to the default panel
             * @param alias Name that can be used to refer to element
             * @param uiElement UI element to be added
             *
             * This function will add a UI element to the panel that is
             * set as the default. The UI element will not be added If
             * the default panel has not been docked yet
             */
            bool addElement(const std::string &alias,
                    std::unique_ptr<UIElement> uiElement) override;

            /**
             *@brief  Get access to a GUI layout panel at a specific edge
             *        of the Dock panel
             * @param  dockPosition Position of the panel to get access to
             * @return A pointer to the specified panel if it exists,
             *         otherwise a null pointer
             */
            const std::unique_ptr<Panel>& getPanelAt(DockPosition dockPosition);

            /**
             * @brief Render GUI layout panels on a render target
             * @param renderTarget Render target to draw GUI elements on
             *
             * This function will draw all docked GUI panels together with
             * the UI elements they contain on a render target
             */
            void draw(Window &renderTarget) override;

        private:
            //Stores docked panels
            std::map<DockPosition, std::unique_ptr<Panel>> dockedPanels_;
            //Position of the default panel
            DockPosition defaultPanelPos_;
            //null unique pointer
            const std::unique_ptr<Panel> null_ptr;
        };
    } // namespace Gui
} // namespace IME

#endif
