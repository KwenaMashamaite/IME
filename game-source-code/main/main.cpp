#include "gui/window/Window.h"
#include "gui/menu/WindowClosePopUpMenu.h"

int main(){
    auto window = Gui::Window();
    window.create("test", 800, 600);

    //Close the window when the windows close button is clicked
    window.addEventListener("Closed", Callback<>([&window] {
        static auto closeConfirmationMenu = Gui::WindowClosePopUpMenu(window);
        window.draw(closeConfirmationMenu);
    }));

    while (window.isOpen()) {
        window.processEvents();
        window.clear();
        window.display();
    }

    return 0;
}
