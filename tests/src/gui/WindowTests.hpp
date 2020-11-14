////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

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
    CHECK_EQ(window.getSize().x, 600u);
    CHECK_EQ(window.getSize().y, 500u);
}
