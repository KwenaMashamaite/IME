/**
 * @brief Represennts the main menu of the game
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include "gui/menu/Menu.h"
#include "gui/control/Button.h"
#include "gui/control/TextBlock.h"

namespace Gui {
    class MainMenu : public Menu{
    public:
        /**
         * @brief Construct a new Main Menu object
         * @param renderTarget Render target to draw menu on
         */
        MainMenu(Window &renderTarget, SystemEventEmitter &sysEventEmitter);

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
        enum class State{
            MAIN,
            INSTRUCTIONS,
            HIGHSCORES,
            CONTROLS
        };
        //Current State of the main menu
        State state_;
        //
        SystemEventEmitter systemEventEmitter_;

    private:
        /**
         * @brief Create main menu navigation buttons
         */
        void createNavigationButtons();

        /**
         * @brief Set up the content that is displayed when a
         *        navigation button is clicked
         */
        void initNavigationButtonsContent();

        /**
         * @brief Get the actions to be performed when navigation
         *        buttons are clicked
         * @return Actions to be performed when navigation buttons are clicked
         */
        std::vector<Callback<>> getOnClickCallbacks();

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

        void renderPanels(const std::initializer_list<std::string> &panelNames);
    };
}


#endif
