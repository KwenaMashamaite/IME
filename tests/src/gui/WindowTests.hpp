#include "doctest.h"
#include "IME/graphics/Window.h"

using IME::Graphics::Window;

TEST_CASE("A window that is not created is not open"){
    auto window = Window();
    CHECK_FALSE(window.isOpen());
}

TEST_CASE("Creating a window opens it"){
    auto window = Window();
    window.create("testWindow", 600u, 600u, Window::Style::None);
    CHECK(window.isOpen());
}

TEST_CASE("An open window can be closed"){
    auto window = Window();
    window.create("testWindow", 600u, 600u, Window::Style::None);
    window.close();
    CHECK_FALSE(window.isOpen());
}

TEST_CASE("Window is created with the specified dimensions"){
    auto window = Window();
    window.create("duel invaders", 600u, 500u, Window::Style::None);
    CHECK_EQ(window.getDimensions().width, 600u);
    CHECK_EQ(window.getDimensions().height, 500u);
}
