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
         */
        PauseMenu();

        /**
         * @brief Draw pause menu on render target
         * @param renderTarget Target to draw pause menu on
         */
        void draw(Window &renderTarget) override;

        /**
         * @brief Hide menu from a render target
         *
         * A hidden menu will not be drawn on a render target when calling the
         * function draw(Window). Also, A hidden menu cannot be interacted with
         * graphically. That is, interaction with the mouse cursor is disabled
         * while the menu is hidden. However, some states of the menu may be
         * changed while it is hidden but they will not be reflected graphically
         */
        void hide() override;

        /**
         * @brief Reveal a hidden menu
         *
         * @note This function does not show the menu on a render target, it only
         * allows the menu to be drawn when calling draw(Window). @see hide()
         */
        void show() override;

        /**
         * @brief Check if menu is hidden or not
         * @return True if menu is hidden, otherwise false
         */
        bool isHidden() const override;

    private:
        /**
         * @brief Create pause menu buttons
         */
        void createButtons();

    private:
        //Layout panel for the menus UI elements
        std::unique_ptr<Panel> pauseMenuButtonsPanel_;
    };
}

#endif
