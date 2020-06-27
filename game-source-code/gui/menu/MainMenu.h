/**
 * @brief Represents the main menu of the game
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "IMenu.h"
#include "../layout/Panel.h"
#include <memory>
#include <map>

namespace Gui {
    class MainMenu : public IMenu{
    public:
        /**
         * @brief Construct a new Main Menu object
         * @param renderTarget Render target to draw menu on
         */
        explicit MainMenu(Window &renderTarget);

        /**
         * @brief Draw all GUI elements and layouts of the main menu
         *        on a render target
         * @param renderTarget Target to draw main menu on
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
         * @brief Create the main menu title
         *
         * The title is positioned at the top of the window
         */
        void createTitle();

        /**
         * @brief Create the main menu navigation panel
         *
         * This function creates buttons that are stacked vertically and
         * positioned at the left edge of the window. This buttons may be
         * used to navigate the main menu
         */
        void createNavigationButtons();

        /**
         * @brief Initialize the main menu buttons
         *
         * This function defines how the navigation buttons responds to
         * the mouse cursor. That is, what the buttons do when they are
         * clicked or when the mouse cursor enters/leaves them
         */
        void initNavigationButtonActions();

        /**
         * @brief Create "onNavigationButton" click information panel
         *
         * This panel will display information associated with a certain
         * navigation button when it is clicked
         */
        void createInfoPanel();

        /**
         * @brief Create a button that return back to the main menu
         *
         * This function creates a button whose sole purpose is to return
         * to the main menu after it hs been exited. This button is only
         * visible if the main menu is exited. For example, clicking on
         * the "Controls" button to see how the game is played would
         * exit the main menu
         */
        void createReturnButton();

        /**
        * @brief Set text to be displayed on the info panel
        * @param newInfo Text to be set
         *
         * This function will overwrite any information that was on the info
         * panel prior to calling the function
        */
        void updateInfoPanel(const std::string& newInfo);

    private:
        //Reference to the games render target
        Window& renderTarget_;
        //Container for all main menu panels
        std::map<std::string, std::unique_ptr<Panel>> panels_;

        /**
         * @brief States the menu can be in
         */
        enum class State{
            Main,
            Info
        };
        //Current State of the main menu
        State state_;
    };
}


#endif
