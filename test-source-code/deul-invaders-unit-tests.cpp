#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../game-source-code/gui/window/Window.h"
#include "../game-source-code/exceptions/Exceptions.h"
#include "../game-source-code/event/Event.h"
#include "../game-source-code/input/InputManager.h"
#include "../game-source-code/globals/Globals.h"

using Globals::Events;
using Gui::Window;

//////////////////////////////////////////////////////////////////
/// Window class tests
/////////////////////////////////////////////////////////////////

TEST_CASE("Uncreated window is not open"){
    auto window = Window();
    CHECK_FALSE(window.isOpen());
}

TEST_CASE("A created window is open by default"){
    auto window = Window();
    window.create("duel invaders", 600u, 600u);
    CHECK(window.isOpen());
}

TEST_CASE("An open window can be closed"){
    auto window = Window();
    window.create("duel invaders", 600u, 600u);
    window.close();
    CHECK_FALSE(window.isOpen());
}

TEST_CASE("Window is created with specified dimensions"){
    auto window = Window();
    window.create("duel invaders", 600u, 500u);
    CHECK_EQ(window.getDimensions().width, 600u);
    CHECK_EQ(window.getDimensions().height, 500u);
}

/////////////////////////////////////////////////////////////////
/// Event class tests
/////////////////////////////////////////////////////////////////

TEST_CASE("A Callback function can be registered to an event"){
    auto clickEvent = Event<>();
    auto clickEventHandlerId = clickEvent.addListener([](){});
    CHECK(clickEventHandlerId == 1u);
}

TEST_CASE("Event handlers can be notified when an event is raised"){
    struct Mouse {
        Event<int, int> clickEvent;
        void click(int x, int y) { clickEvent.notifyListeners(x, y);}
    };
    auto mousePosition = std::pair<int, int>(0u, 0u);
    auto mouse = Mouse{};
    mouse.clickEvent.addListener([&mousePosition](int xMouseCoord, int yMouseCoord){
        mousePosition.first = xMouseCoord;
        mousePosition.second = yMouseCoord;
    });
    mouse.click(50, 40);
    CHECK((mousePosition.first == 50 && mousePosition.second == 40));
}

TEST_CASE("A callback function can be removed from an event"){
    auto event = Event<>();
    auto counter = 0u;
    auto counterHandlerId = event.addListener([&counter](){++counter;});
    event.notifyListeners();
    CHECK(counter == 1);
    event.notifyListeners();
    CHECK(counter == 2);
    CHECK(event.removeListener(counterHandlerId));
    event.notifyListeners();
    CHECK_FALSE(counter == 3);
}

TEST_CASE("A non existent event handler cannot be removed from event handler list"){
    auto event = Event<>();
    auto nonExistentHandlerId = 10;
    CHECK_FALSE(event.removeListener(nonExistentHandlerId));
}

TEST_CASE("An event can have multiple handlers registered to it"){
    auto event = Event<>();
    event.addListener([](){});
    auto secondHandlerId = event.addListener(([](){}));
    auto thirdHandlerId = event.addListener([](){});
    CHECK(thirdHandlerId == secondHandlerId + 1);
}

TEST_CASE("The same callback function is treated as a unique handler when subscribing to an event"){
    auto clickEvent = Event<int, int>();
    auto print = [](int x, int y){/*Code that prints the mouse coordinates to the console*/};
    auto handlerOneId = clickEvent.addListener(print);
    auto handlerTwoId = clickEvent.addListener(print);
    CHECK_NE(handlerTwoId, -1); //handler registration successful
    CHECK_NE(handlerOneId, handlerTwoId);
}

/////////////////////////////////////////////////////////////////
/// Input manager class tests
/////////////////////////////////////////////////////////////////

TEST_CASE("A key is released by default"){
    auto inputManager = InputManager();
    CHECK_FALSE(inputManager.isKeyPressed(InputManager::Key::A));
    CHECK_FALSE(inputManager.isKeyHeld(InputManager::Key::A));
}

TEST_CASE("A mouse button is released by default"){
    auto inputManager = InputManager();
    CHECK_FALSE(inputManager.isMouseButtonPressed(InputManager::MouseButton::RMouseButton));
}

TEST_CASE("A key that is pressed and was previously released is pressed"){
    auto inputManager = InputManager();
    Events::keyPressed.notifyListeners(InputManager::Key::B);
    CHECK(inputManager.isKeyPressed(InputManager::Key::B));
}

TEST_CASE("A mouse button that is pressed and was previously released is pressed"){
    auto inputManager = InputManager();
    Events::mouseButtonPressed.notifyListeners(InputManager::MouseButton::LMouseButton, 0, 0);
    CHECK(inputManager.isMouseButtonPressed(InputManager::MouseButton::LMouseButton));
}

TEST_CASE("A key that is not pressed/held is not pressed/held"){
    auto inputManager = InputManager();
    Events::keyPressed.notifyListeners(InputManager::Key::K);
    CHECK_FALSE(inputManager.isKeyPressed(InputManager::Key::H));
    //CHECK_FALSE(inputManager.isKeyHeld(InputManager::Key::H));
}

TEST_CASE("A mouse button that is not pressed is not pressed"){
    auto inputManager = InputManager();
    Events::mouseButtonPressed.notifyListeners(InputManager::MouseButton::LMouseButton, 0, 0);
    CHECK_FALSE(inputManager.isMouseButtonPressed(InputManager::MouseButton::RMouseButton));
}

/*
TEST_CASE("A key that is pressed and was previously pressed is held and not pressed"){
    auto inputManager = InputManager();
    Events::keyPressed.notifyListeners(InputManager::Key::Q);
    inputManager.update();
    //Key still pressed after call to update (that is, no call to release has been made)
    CHECK(inputManager.isKeyDown(InputManager::Key::Q));
    CHECK_FALSE(inputManager.isKeyPressed(InputManager::Key::Q));
}

TEST_CASE("A key that is released and was previously held/pressed is released"){
    auto inputManager = InputManager();
    Events::keyPressed.notifyListeners(InputManager::Key::Escape);
    inputManager.update();
    Events::keyReleased.notifyListeners(InputManager::Key::Escape);
    CHECK_FALSE(inputManager.isKeyHeld(InputManager::Key::Escape));
    CHECK_FALSE(inputManager.isKeyPressed(InputManager::Key::Escape));
}*/