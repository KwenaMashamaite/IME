/**
 * @brief Menu displayed when the game is paused
 */

#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "IMenu.h"
#include "../layout/StackPanel.h"

namespace Gui {
    class PauseMenu : public IMenu{
    public:
        /**
         * @brief Create a new Pause Menu object
         * @param renderTarget Target to draw menu on
         */
        explicit PauseMenu(Window &renderTarget);

        /**
         * @brief Draw all GUI elements and layouts of the menu
         *        on a render target
         * @param renderTarget Target to draw pause menu on
         */
        void draw(Window &renderTarget) override;

    private:
        /**
         * @brief Create pause menu buttons
         */
        void createButtons();

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
