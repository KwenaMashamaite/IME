#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../State.h"
#include "audio/MusicPlayer.h"
#include "gui/menu/MainMenu.h"
#include "gui/drawer/Drawer.h"

class MainMenuState : public State{
public:
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
    void render(Gui::Window &renderTarget) override;

private:
    Gui::MainMenu mainMenu_;
};

#endif
