#include "globals/Globals.h"
#include "gui/window/Window.h"
#include "gui/layout/StackPanel.h"
#include "gui/control/Button.h"
#include "event/EventPublisher.h"
#include <ctime>
#include <iostream>

int main(){
    srand(time(nullptr));
    auto window = Gui::Window();
    window.create("test", 600, 600);

    auto greetings = std::vector{"Sanibonani\n (isiZulu)", "Molo\n (isiXhosa)", "Hallo\n (Afrikaans)",
                                 "Thobela\n (Sepedi)", "Dumela\n (Setswana)", "Lumela\n (Sesotho)",
                                 "Abusheni\n (Xitsonga)", "Sanibona\n (SiSwati)", "Avuwani\n (Tshivenda)",
                                 "Salibonani\n (isiNdebele)", "Hello\n (English)"};

    auto fonts = std::vector{"sansation.ttf", "hangedLetters.ttf", "basson.ttf", "philosopher.ttf"};

    auto charSize = 20;
    auto languagesPanel = Gui::StackPanel(0.0f, window.getDimensions().height / 2.0f, Gui::Orientation::Vertical);
    for (const auto& greeting : greetings) {
        languagesPanel.addElement([&]() {
            auto button = std::make_shared<Gui::Button>(greeting);
            button->setTextCharSize(charSize);
            button->setPadding(20.0f);
            button->setMargin(1.0f);

            button->setPosition(window.getDimensions().width / 2.0f - button->getDimensions().width / 2.0f,
                                window.getDimensions().height / 2.0f);

            button->mouseEnterEvent.addListener([button]() {
                button->setTextFillColour({34,56, 231});
                button->setFillColour({10, 67, 90});
            });
            button->mouseLeaveEvent.addListener([button]() {
                button->setTextFillColour({54, 78, 3});
                button->setFillColour({98, 88, 143});
            });
            button->clickEvent.addListener([&, button]() {
                auto randonIndex = rand() % (fonts.size() - 1);
                button->setTextFont(fonts.at(randonIndex));
            });
            return button;
        }());
    }

    Globals::Events::windowClose.addListener([&window](){
        window.close();
    });

    auto emitter = EventPublisher();
    while (window.isOpen()) {
        emitter.update(window);
        window.clear();
        languagesPanel.draw(window);
        window.display();
    }

    return 0;
}