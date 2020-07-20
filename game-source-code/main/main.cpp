#include "gui/window/Window.h"
#include "core/states/MainMenuState.h"
#include "core/states/QuitingState.h"
#include "core/Engine.h"

using IME::Callback;

class TestEngine : public IME::Engine{

};

int main(){
    auto gameEngine = TestEngine();
    gameEngine.init();
    gameEngine.addState("mainMenu", std::make_shared<IME::MainMenuState>(gameEngine));
    gameEngine.addState("quit", std::make_shared<IME::QuitingState>(gameEngine));
    gameEngine.changeState("mainMenu");

    gameEngine.getRenderTarget().addEventListener("closed", Callback<>([&gameEngine] {
        gameEngine.changeState("quit");
    }));

    gameEngine.run();

    return 0;
}
