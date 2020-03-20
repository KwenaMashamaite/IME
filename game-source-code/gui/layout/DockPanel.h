/**
 * @brief
 */

#ifndef DOCKPANEL_H
#define DOCKPANEL_H

#include "Panel.h"
#include <memory>
#include <unordered_map>

namespace Gui {
    class DockPanel final : public Panel {
    public:
        enum class Dock{
            Left,
            Right,
            Top,
            Bottom
        };

        explicit DockPanel(float x = 0.0f, float y = 0.0f);

        void dock(Dock dock, std::shared_ptr<Panel> panel);

        void addElement(std::shared_ptr<UIElement> guiElement) override;

        void draw(Window &renderTarget) override;

    private:
        std::unordered_map<Dock, std::shared_ptr<Panel>> panels_;
    
        std::shared_ptr<Panel> topDock_;
        std::shared_ptr<Panel> bottomDock_;
        std::shared_ptr<Panel> leftDock_;
        std::shared_ptr<Panel> rightDock_;
        std::shared_ptr<Panel> lastDocked_;

        void dock(Dock dockPosition, std::shared_ptr<Panel> &dockPanel, std::shared_ptr<Panel> panel, Position defaultPos);
    };
}

#endif //DOCKPANEL_H
