#include "gui/window/Window.h"
#include "gui/layout/StackPanel.h"
#include "gui/control/Button.h"
#include "event/SystemEventEmitter.h"
#include "input/Keyboard.h"
#include "gui/layout/DockPanel.h"
#include <ctime>

int main(){
    srand(time(nullptr));
    auto window = Gui::Window();
    window.create("test", 600, 600);

    auto greetings = std::vector{"Sanibonani\n (isiZulu)", "Molo\n (isiXhosa)", "Hallo\n (Afrikaans)",
                                 "Thobela\n (Sepedi)", "Dumela\n (Setswana)", "Lumela\n (Sesotho)",
                                 "Abusheni\n (Xitsonga)", "Sanibona\n (SiSwati)", "Avuwani\n (Tshivenda)",
                                 "Salibonani\n (isiNdebele)", "Hello\n (English)"};

    auto charSizes = std::vector{5, 10, 15, 30, 40};

    auto systemEventEmitter = SystemEventEmitter(window);
    systemEventEmitter.addListener("Closed", Callback<>([&window]() {
        window.close();
    }));

    auto charSize = 15;
    auto languagesPanel = std::make_unique<Gui::StackPanel>(0.0f, window.getDimensions().height / 2.0f,
            Gui::Orientation::Vertical);
    languagesPanel->setFillColour(Gui::Colour{175, 205, 36});

    auto genButton = [&](std::unique_ptr<Gui::StackPanel>& panel) {
        for (const auto &greeting : greetings) {
            panel->addElement([&]() {
                auto button = std::make_unique<Gui::Button>(greeting);
                button->initialize(systemEventEmitter);
                button->setTextCharSize(charSize);
                button->setPadding(5.0f);
                button->setMargin(1.0f);

                button->setPosition(window.getDimensions().width / 2.0f - button->getDimensions().width / 2.0f,
                                    window.getDimensions().height / 2.0f);
                auto& buttonPointee = (*(button.get()));
                button->on("mouseEnter", Callback<>([&]() {
                    buttonPointee.setTextFillColour({34, 56, 231});
                    buttonPointee.setFillColour({10, 67, 90});
                }));
                button->on("mouseLeave", Callback<>([&]() {
                    buttonPointee.setTextFillColour({54, 78, 3});
                    buttonPointee.setFillColour({98, 88, 143});
                }));
                button->on("click", Callback<>([&]() {
                    auto randonIndex = rand() % (charSizes.size() - 1);
                    buttonPointee.setTextCharSize(charSizes.at(randonIndex));
                }));

                return button;
            }());
        }
    };

    genButton(languagesPanel);
    auto languagesPanel2 = std::make_unique<Gui::StackPanel>(320.0f, window.getDimensions().height / 2.0f,
                                                            Gui::Orientation::Vertical);
    languagesPanel2->setFillColour(Gui::Colour{1, 205, 136});
    languagesPanel2->setOutlineColour(Gui::Colour{45, 78, 45});
    genButton(languagesPanel2);

    auto languagesPanel3 = std::make_unique<Gui::StackPanel>(0.0f, 0.0f,Gui::Orientation::Horizontal);
    languagesPanel3->setFillColour(Gui::Colour{100, 50, 13});
    genButton(languagesPanel3);
    languagesPanel3->setOutlineColour(Gui::Colour{45, 78, 124});

    auto languagesPanel4 = std::make_unique<Gui::StackPanel>(0.0f, 0.0f,Gui::Orientation::Horizontal);
    languagesPanel4->setFillColour(Gui::Colour{80, 150, 133});
    languagesPanel4->setOutlineColour(Gui::Colour{145, 178, 224});
    genButton(languagesPanel4);
    auto dockPanel = Gui::DockPanel();
    dockPanel.dock(Gui::DockPanel::Dock::Left, std::move(languagesPanel));
    dockPanel.dock(Gui::DockPanel::Dock::Right, std::move(languagesPanel2));
    dockPanel.dock(Gui::DockPanel::Dock::Top, std::move(languagesPanel3));
    dockPanel.dock(Gui::DockPanel::Dock::Bottom, std::move(languagesPanel4));

    while (window.isOpen()) {
        systemEventEmitter.process();
        window.clear();
        dockPanel.draw(window);
        window.display();
    }

    return 0;
}
