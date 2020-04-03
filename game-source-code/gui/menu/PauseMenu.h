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
        /**
         * @brief Create a new Pause Menu object
         * @param renderTarget Target to draw menu on
         * @param systemEventEmitter System events emitter
         */
        PauseMenu(Window &renderTarget, SystemEventEmitter& systemEventEmitter);

        /**
         * @brief Draw all GUI elements and layouts of the menu
         *        on a render target
         */
        void draw() override;

        /**
         * @brief Remove all Gui elements and layouts of the menu from a
         *        render target
         */
        void clear() override;

    private:
        //Games render target
        Window& renderTarget_;
        //Layout panel for the menus UI elements
        std::unique_ptr<StackPanel> pauseMenuButtonsPanel_;
        //Menu clear state
        bool isCleared_;
    };
}

#endif
