#include "gui/window/Window.h"
#include "gui/menu/MainMenu.h"
#include "gui/control/Button.h"
#include "gui/menu/PauseMenu.h"

using Gui::StackPanel;
using Gui::Button;

int main(){
    auto window = Gui::Window();
    window.create("test", 800, 600);
    auto mainMenu = Gui::MainMenu(window);

    //Close the window when the windows close button is clicked
    window.addEventListener("Closed", Callback<>([&window] {
        window.close();
    }));

    while (window.isOpen()) {
        window.processEvents();
        window.clear();
        window.draw(mainMenu);
        window.display();
    }

    return 0;
}
