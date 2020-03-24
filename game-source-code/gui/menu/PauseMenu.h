/**
 * @brief Menu displayed when the game is paused
 */

#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "gui/menu/IMenu.h"
#include "gui/layout/StackPanel.h"
#include "event/SystemEventEmitter.h"

namespace Gui {
    class PauseMenu : public IMenu{
    public:
        explicit PauseMenu(Window &renderTarget, SystemEventEmitter& systemEventEmitter);

        void draw() override;

        void clear() override;

    private:
        Window& renderTarget_;
        std::unique_ptr<StackPanel> pauseMenuButtonsPanel_;
        bool isCleared_;
    };
}

#endif //SFML_2_5_0_GAME_DEV_TEMPLATE_PAUSEMENU_H
