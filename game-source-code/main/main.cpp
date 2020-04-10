#include "gui/window/Window.h"
#include "gui/menu/MainMenu.h"
#include "gui/menu/PauseMenu.h"

int main(){
    auto window = Gui::Window();
    window.create("test", 600, 600);

    auto mainMenu = Gui::MainMenu(window);

    while (window.isOpen()) {
        window.processEvents();
        window.clear();
        mainMenu.draw();
        window.display();
    }

    return 0;
}
