/**
 * @brief GUI layout panel for GUI layout panels
 *
 * This class helps organise layout panels
 */

#ifndef DOCKPANEL_H
#define DOCKPANEL_H

#include "Panel.h"
#include <memory>
#include <unordered_map>

namespace Gui {
    class DockPanel : public Panel {
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
         * @brief Constructor
         * @param x X coordinate of the panel
         * @param y Y coordinate of the panel
         */
        DockPanel(float x, float y);

        /**
         * @brief Add a panel
         * @param dockPosition Side on which the panel should be docked
         * @param panel Panel to be docked
         *
         * @note If a panel was already docked at the specidfied position it
         * will be replaced. The order in which panels are docked is important
         * as each time a panel is docked, the overall space of the dock panel
         * decreases. The last panel (One docked after all the other three edges
         * have been docked) to be docked will take the remaining space
         */
        void dock(DockPosition dockPosition, std::shared_ptr<Panel> panel);

        /**
         * @brief Add a GUI element to the last docked panel
         * @param guiElement GUI element to be added
         *
         * The "last docked panel" refers to the panel that was added during the
         * last call to the "dock" method
         */
        void addElement(std::shared_ptr<UIElement> guiElement) override;

        /**
         * @brief Render GUI elements of the panel on a render target
         * @param renderTarget Render target to draw GUI elements on
         */
        void draw(Window &renderTarget) override;

    private:
        //Panels container
        std::unordered_map<DockPosition, std::shared_ptr<Panel>> panels_;
        //Panel docked on the top egde of the dock panel
        std::shared_ptr<Panel> topEdgeDock_;
        //Panel docked on the bottom egde of the dock panel
        std::shared_ptr<Panel> bottomEdgeDock_;
        //Panel docked on the left side of the screen
        std::shared_ptr<Panel> leftEdgeDock_;
        //Panel docked on the right egde of the dock panel
        std::shared_ptr<Panel> rightEdgeDock_;
        //Pointer to the last docked panel
        std::shared_ptr<Panel> lastDocked_;

        void dock(DockPosition dockPosition, std::shared_ptr<Panel> &dockPanel, std::shared_ptr<Panel> panel, Position defaultPos);
    };
}

#endif //DOCKPANEL_H
