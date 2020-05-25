/**
 * @brief Represents the main menu of the game
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "IMenu.h"
#include "../control/Button.h"
#include "../control/TextBlock.h"
#include "../layout/DockPanel.h"
#include "../layout/StackPanel.h"

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
         */
        void draw() override;

        /**
         * @brief Clear the main menu
         */
        void clear() override;

    private:
        /**
         * @brief Initialize information to be displayed when a main menu
         *        button is clicked
         */
        void initOnClickInfo();

        /**
         * @brief Create the main menu title
         *
         * The title is positioned at the top of the window
         */
        void createTitle();

        /**
         * @brief Create the main menu footer
         *
         * The footer is positioned at the bottom of the
         * window
         */
        void createFooter();

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
         * @brief Create a button that return back to the main menu
         *
         * This function creates a button whose sole purpose is to return
         * to the main menu after it hs been exited. This button is only
         * visible if the main menu is exited. For example, clicking on
         * the "Controls" button to see how the game is played would usually
         * exit the main menu
         */
        void createReturnButton();

        /**
         * @brief Create a panel to display information when a navigation
         *        button is hovered over
         *
         * This function creates a panel that displays information associated
         * with a certain navigation button when the mouse cursor enters it.
         * This information is not cleared when the mouse cursor leaves the
         * button. However, the information will be cleared if after leaving
         * the button, the mouse cursor enters another navigation button.
         */
        void createOnHoverInfoPanel();

        /**
        * @brief Set text to be displayed on the info panel
        * @param newInfo Text to be set
         *
         * This function will overwrite any information that was on the info
         * panel, prior to calling the function
        */
        void updateInfoPanel(const std::string& newInfo);

    private:
        //Reference to the games render target
        Window& renderTarget_;
        //Container for all main menu panels
        std::unique_ptr<DockPanel> mainLayoutPanel_;
        //Panel displayed when any of the menu buttons are pressed
        std::unique_ptr<StackPanel> onClickInfoPanel_;

        /**
         * @brief States the menu can be in
         */
        enum class State{
            Main,
            Info
        };
        //Current State of the main menu
        State state_;

        //Main menu buttons
        enum class ButtonType{Play, Instructions, Controls, Highscores, Exit};
        //Stores the information that is displayed when a certain button is clicked
        std::unordered_map<ButtonType, std::string> onClickButtonInfo_;
    };
}


#endif
