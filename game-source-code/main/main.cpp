#include "gui/window/Window.h"
#include "core/states/MainMenuState.h"
#include "core/states/QuitingState.h"
#include "core/Engine.h"

int main(){
    auto window = Gui::Window();
    window.create("test", 800, 600);

    auto gameEngine = Engine(window);
    gameEngine.addState("mainMenu", std::make_shared<MainMenuState>());
    gameEngine.addState("quit", std::make_shared<QuitingState>());
    gameEngine.changeState("mainMenu");

    window.addEventListener("closed", Callback<>([&gameEngine] {
        gameEngine.changeState("quit");
    }));

    gameEngine.run();

    return 0;
}
