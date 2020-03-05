#include "gui/window/Window.h"
#include "gui/layout/StackPanel.h"
#include "gui/control/Button.h"
#include "event/SystemEventEmitter.h"
#include "input/Keyboard.h"
#include "gui/layout/DockPanel.h"
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

    auto charSize = 15;
    auto languagesPanel = std::make_shared<Gui::StackPanel>(0.0f, window.getDimensions().height / 2.0f,
            Gui::Orientation::Vertical);
    languagesPanel->setFillColour(Gui::Colour{175, 205, 36});

    auto genButton = [&](std::shared_ptr<Gui::StackPanel>& panel) {
        for (const auto &greeting : greetings) {
            panel->addElement([&]() {
                auto button = std::make_shared<Gui::Button>(greeting);
                button->setTextCharSize(charSize);
                button->setPadding(5.0f);
                button->setMargin(1.0f);

                button->setPosition(window.getDimensions().width / 2.0f - button->getDimensions().width / 2.0f,
                                    window.getDimensions().height / 2.0f);

                button->on("mouseEnter", Callback<>([button]() {
                    button->setTextFillColour({34, 56, 231});
                    button->setFillColour({10, 67, 90});
                }));
                button->on("mouseLeave", Callback<>([button]() {
                    button->setTextFillColour({54, 78, 3});
                    button->setFillColour({98, 88, 143});
                }));
                button->on("click", Callback<>([&, button]() {
                    auto randonIndex = rand() % (fonts.size() - 1);
                    button->setTextFont(fonts.at(randonIndex));
                }));

                button->on("mouseEnter", Callback<>([]() {
                    std::cout << "mouse entered button" << std::endl;
                }));

                button->on("mouseLeave", Callback<>([]() {
                    std::cout << "mouse left button" << std::endl;
                }));

                return button;
            }());
        }
    };

    genButton(languagesPanel);
    auto languagesPanel2 = std::make_shared<Gui::StackPanel>(320.0f, window.getDimensions().height / 2.0f,
                                                            Gui::Orientation::Vertical);
    languagesPanel2->setFillColour(Gui::Colour{1, 205, 136});
    languagesPanel2->setOutlineColour(Gui::Colour{45, 78, 45});
    genButton(languagesPanel2);

    auto languagesPanel3 = std::make_shared<Gui::StackPanel>(0.0f, 0.0f,Gui::Orientation::Horizontal);
    languagesPanel3->setFillColour(Gui::Colour{100, 50, 13});
    genButton(languagesPanel3);
    languagesPanel3->setOutlineColour(Gui::Colour{45, 78, 124});

    auto languagesPanel4 = std::make_shared<Gui::StackPanel>(0.0f, 0.0f,Gui::Orientation::Horizontal);
    languagesPanel4->setFillColour(Gui::Colour{80, 150, 133});
    languagesPanel4->setOutlineColour(Gui::Colour{145, 178, 224});
    genButton(languagesPanel4);
    auto dockPanel = Gui::DockPanel();
    dockPanel.dock(Gui::DockPanel::Dock::Left, languagesPanel);
    dockPanel.dock(Gui::DockPanel::Dock::Right, languagesPanel2);
    dockPanel.dock(Gui::DockPanel::Dock::Top, languagesPanel3);
    dockPanel.dock(Gui::DockPanel::Dock::Bottom, languagesPanel4);

    auto systemEventEmitter = SystemEventEmitter(window);
    systemEventEmitter.addListener("Closed", Callback<>([&window]() {
        window.close();
    }));

    while (window.isOpen()) {
        systemEventEmitter.process();
        window.clear();
        dockPanel.draw(window);
        window.display();
    }

    return 0;
}