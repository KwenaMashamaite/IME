#include "gui/window/Window.h"
#include "core/states/MainMenuState.h"
#include "core/states/QuitingState.h"
#include "core/Engine.h"

using IME::Callback;

int main(){
    auto window = IME::Gui::Window();
    window.create("test", 800, 600);

    auto gameEngine = IME::Engine(window);
    gameEngine.addState("mainMenu", std::make_shared<IME::MainMenuState>(gameEngine));
    gameEngine.addState("quit", std::make_shared<IME::QuitingState>(gameEngine));
    gameEngine.changeState("mainMenu");

    window.addEventListener("closed", Callback<>([&gameEngine] {
        gameEngine.changeState("quit");
    }));

    gameEngine.run();

    return 0;
}
