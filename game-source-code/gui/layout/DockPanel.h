/**
 * @brief GUI layout panel for other GUI layout panels
 */

#ifndef DOCKPANEL_H
#define DOCKPANEL_H

#include "Panel.h"
#include <memory>
#include <unordered_map>

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
         * @brief Add a GUI element to the panel that was previously
         *        docked
         * @param alias Name that can be used to refer to element
         * @param guiElement GUI element to be added
         *
         * This function will add a UI element to the panel that was
         * last docked, that is, the panel that was added to the Dock
         * panel during the last call to the dock method. If no panel
         * was previously docked, the UI element will be ignored
         */
        void addElement(const std::string &alias,
                std::unique_ptr<UIElement> guiElement) override;

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
        //Panel docked on the top edge of the dock panel
        std::unique_ptr<Panel> topEdgeDock_;
        //Panel docked on the bottom edge of the dock panel
        std::unique_ptr<Panel> bottomEdgeDock_;
        //Panel docked on the left edge of the dock panel
        std::unique_ptr<Panel> leftEdgeDock_;
        //Panel docked on the right edge of the dock panel
        std::unique_ptr<Panel> rightEdgeDock_;
        //Position of the panel added during the last call to dock
        int lastDockedPosition_;

        /**
         * @brief Helper function for docking panels
         * @param dockPosition Is the position where the panel should
         *        be docked
         * @param panel Panel to be docked
         * @param defaultPos Position of the panel if currently there's
         *        no panel docked
         *
         * This function will dock the provided panel at the default
         * position if there are no panels already docked to other
         * edges of the dock panel. The dimensions and position of the
         * panel to be docked will be adjusted accordingly if there are
         * panels already docked on other edges of the dock panel. The
         * last panel to be docked will occupy the remaining space
         */
        void dock(DockPosition dockPosition, const std::unique_ptr<Panel>& panel,
                Position defaultPos);

        /**
         * @brief  Check if a docking area is the last to be occupied
         * @param  dockPosition Position to be checked
         * @return True if docking area is the last to be occupied,
         *         otherwise false
         */
        bool isLastToBeDocked(DockPosition dockPosition) const;
    };
}

#endif
