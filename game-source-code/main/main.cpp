#include "gui/window/Window.h"
#include "event/SystemEventEmitter.h"
#include "gui/menu/MainMenu.h"
#include "gui/layout/DockPanel.h"

int main(){
    auto window = Gui::Window();
    window.create("test", 600, 600);

    auto systemEventEmitter = SystemEventEmitter(window);
    systemEventEmitter.addListener("Closed", Callback<>([&window]() {
        window.close();
    }));

    std::unique_ptr<Gui::IMenu> mainMenu = std::make_unique<Gui::MainMenu>(window, systemEventEmitter);

    while (window.isOpen()) {
        systemEventEmitter.process();
        window.clear();
        mainMenu->draw();
        window.display();
    }

    return 0;
}
