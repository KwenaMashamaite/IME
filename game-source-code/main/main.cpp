#include "globals/Globals.h"
#include "gui/window/Window.h"
#include "gui/layout/StackPanel.h"
#include "gui/control/Button.h"
#include "event/EventEmitter.h"
#include <ctime>
#include <iostream>

void processOSevents(Gui::Window& window, EventEmitter& eventEmitter){
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type){
            case sf::Event::Closed:
                eventEmitter.emit("Closed");
                break;
            case sf::Event::KeyPressed:
                eventEmitter.emit("keyPressed",
                    static_cast<Keyboard::Key>(static_cast<unsigned int>(event.key.code))
                );
                break;
            case sf::Event::KeyReleased:
                eventEmitter.emit("keyReleased", 
                    static_cast<Keyboard::Key>(static_cast<unsigned int>(event.key.code))
                );
                break;
            case sf::Event::MouseMoved:
                eventEmitter.emit("mouseMoved", event.mouseMove.x, event.mouseMove.y);
                break;
            case sf::Event::MouseButtonPressed:
                eventEmitter.emit("mouseButtonPressed",
                    static_cast<Mouse::Button>(static_cast<unsigned int>(event.mouseButton.button))
                );
                break;
            case sf::Event::MouseButtonReleased:
                eventEmitter.emit("mouseButtonReleased",
                    static_cast<Mouse::Button>(static_cast<unsigned int>(event.mouseButton.button))
                );
                break;
            default:
                break;
        }
    }
}

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

    auto eventEmitter = EventEmitter();

    for (const auto& greeting : greetings) {
        languagesPanel.addElement([&]() {
            auto button = std::make_shared<Gui::Button>(greeting);
            button->setTextCharSize(charSize);
            button->setPadding(20.0f);
            button->setMargin(1.0f);

            button->setPosition(window.getDimensions().width / 2.0f - button->getDimensions().width / 2.0f,
                                window.getDimensions().height / 2.0f);

            button->on("mouseEnter", Callback<>([button]() {
                button->setTextFillColour({34,56, 231});
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

            button->on("mouseEnter", Callback<>([](){
                std::cout << "mouse entered button" << std::endl;
            }));

            button->on("mouseLeave", Callback<>([]() {
                std::cout << "mouse left button" << std::endl;
            }));

            eventEmitter.addEventListener("mouseMoved", Callback<int, int>([button](int x, int y){
                //button->emit("mouseMoved", x, y);
            }));

            eventEmitter.addEventListener("mouseButtonReleased", Callback<Mouse::Button>({
                [button](Mouse::Button releasedButton){
                    //button->emit("mouseButtonReleased", releasedButton);
                }
            }));

            return button;
        }());
    }

    eventEmitter.addEventListener("Closed", Callback<>([&window](){
        window.close();
    }));


    while (window.isOpen()) {
        processOSevents(window, eventEmitter);
        window.clear();
        languagesPanel.draw(window);
        window.display();
    }

    return 0;
}