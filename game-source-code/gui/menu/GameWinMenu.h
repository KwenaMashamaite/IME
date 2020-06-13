/**
 * @brief Menu displayed when the game is won
 */

#ifndef GAMEWINMENU_H
#define GAMEWINMENU_H

#include "IMenu.h"

namespace Gui {
    class GameWinMenu : public IMenu {
    public:
        /**
         * @brief Render the game over mnu on a render target
         * @param renderTarget Target to draw menu on
         */
        void draw(Window &renderTarget) override;
    };
}


#endif
