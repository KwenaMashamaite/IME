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

        void dock(Dock dockPosition, std::unique_ptr<Panel> panel);

        void addElement(std::unique_ptr<UIElement> guiElement) override;

        void draw(Window &renderTarget) override;

    private:
        std::unordered_map<Dock, std::unique_ptr<Panel>> panels_;
    
        std::unique_ptr<Panel> topDock_;
        std::unique_ptr<Panel> bottomDock_;
        std::unique_ptr<Panel> leftDock_;
        std::unique_ptr<Panel> rightDock_;
        std::unique_ptr<Panel> lastDocked_;

        void dock(Dock dockPosition, const std::unique_ptr<Panel> &dockPanel,
                const std::unique_ptr<Panel>& panel,
                Position defaultPos);
    };
}

#endif //DOCKPANEL_H
