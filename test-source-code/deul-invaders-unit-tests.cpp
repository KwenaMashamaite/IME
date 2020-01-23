#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../game-source-code/gui/window/Window.h"

using Gui::Window;

//////////////////////////////////////////////////////////////////
//  Window class tests
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