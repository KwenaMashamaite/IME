/**
 * @brief Represents the main menu of the game
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "gui/menu/IMenu.h"
#include "gui/control/Button.h"
#include "gui/control/TextBlock.h"
#include "gui/layout/DockPanel.h"
#include "gui/layout/StackPanel.h"

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
         * @brief Create the main menu title panel
         */
        void createTitle();

        /**
         * @brief Create the main menu footer
         */
        void createFooter();

        /**
         * @brief Create the main menu navigation panel
         */
        void createNavigationButtons();

        /**
         * @brief Initialize the main menu buttons
         */
        void initNavigationButtons();

        /**
         * @brief Create a button that return back to the main menu
         */
        void createReturnButton();

        /**
        * @brief Set text to be displayed on the info panel
        * @param newInfo Text to be set
        */
        void updateInfoPanel(const std::string& newInfo);

        /**
         * @brief Create a text block
         * @param text Text to be displayed inside the text block
         * @return Created text block
         */
        std::unique_ptr<TextBlock> createTextBlock(const std::string& text);

        /**
         * @brief Create a button
         * @param buttonText Text to be displayed inside the button
         * @return Created button
         */
        std::unique_ptr<Button> createButton(const std::string &buttonText);

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
        //Temporarily stores the navigation buttons
        std::vector<std::pair<ButtonType, std::unique_ptr<Button>>> navButtons_;
    };
}


#endif
