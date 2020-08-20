#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "IME/core/engine/State.h"
#include "IME/gui/layout/Panel.h"
#include "IME/core/audio/MusicPlayer.h"

namespace SI {
    class MainMenuState : public IME::State {
    public:
        /**
         *
         * @param engine
         */
        MainMenuState(IME::Engine &engine);

        /**
         *
         */
        void initialize() override;

        /**
         * @brief Update state
         */
        void update() override;

        /**
         * @brief Update menu animations
         * @param deltaTime Time passed since animations were last updated
         */
        void fixedUpdate(float deltaTime) override;

        /**
         * @brief
         * @param renderTarget
         */
        void render(IME::Gui::Window &renderTarget) override;

        /**
         * @brief Handle an event
         * @param event Event to handle
         */
        void handleEvent(sf::Event event) override;

        /**
         *
         */
        void pause() override;

        /**
         *
         */
        void resume() override;

        /**
         *
         * @return
         */
        bool isInitialized() const override;

        /**
         *
         */
        void reset() override;

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
        void updateInfoPanel(const std::string &newInfo);

    private:
        //Initialization state
        bool isInitialized_;
        //Container for all main menu panels
        std::map<std::string, std::unique_ptr<IME::Gui::Panel>> panels_;
        //Main menu music player
        IME::Audio::MusicPlayer musicPlayer_;

        /**
         * @brief States the menu can be in
         */
        enum class View {
            None,
            Main,
            Info
        };
        //Current View of the main menu
        View currentView_;

        /**
         * @brief Change the current view of the main menu
         * @param view View to change to
         */
        void changeView(View view);
    };
}

#endif
