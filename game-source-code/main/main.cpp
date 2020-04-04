#include "gui/window/Window.h"
#include "event/SystemEventEmitter.h"
#include "gui/menu/MainMenu.h"
#include "gui/menu/PauseMenu.h"
#include "gui/layout/DockPanel.h"

int main(){
    auto window = Gui::Window();
    window.create("test", 600, 600);

    auto systemEventEmitter = SystemEventEmitter(window);
    systemEventEmitter.addListener("Closed", Callback<>([&window]() {
        window.close();
    }));

    auto mainMenu = Gui::MainMenu(window, systemEventEmitter);

    while (window.isOpen()) {
        systemEventEmitter.processEvents();
        window.clear();
        mainMenu.draw();
        window.display();
    }

    return 0;
}
