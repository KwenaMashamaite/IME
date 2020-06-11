/**
 * @brief Menu displayed when the game is lost
 */

#ifndef GAMELOSEMENU_H
#define GAMELOSEMENU_H

#include "IMenu.h"
#include "gui/control/TextBlock.h"

namespace Gui {
    class GameLoseMenu : public IMenu{
    public:
        /**
         * @brief Default constructor
         */
        GameLoseMenu();

        /**
         * @brief Render the game over mnu on a render target
         * @param renderTarget Target to draw menu on
         */
        void draw(Window &renderTarget) override;

    private:
        std::unique_ptr<TextBlock> message_;
    };
}

#endif
