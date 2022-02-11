////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/core/input/Keyboard.h"
#include "IME/core/event/Event.h"
#include <doctest.h>

using Keyboard = ime::input::Keyboard;

TEST_CASE("ime::input::Keyboard class")
{
    SUBCASE("Constructors")
    {
        SUBCASE("Default constructor")
        {
            Keyboard keyboard;
            CHECK(keyboard.isEnabled());
        }
    }

    SUBCASE("Setters")
    {
        SUBCASE("setEnable()")
        {
            Keyboard keyboard;

            keyboard.setEnable(false);
            CHECK_FALSE(keyboard.isEnabled());
            keyboard.setEnable(true);
            CHECK(keyboard.isEnabled());
        }
    }

    SUBCASE("Callbacks")
    {
        SUBCASE("onKeyUp()")
        {
            Keyboard keyboard;
            bool isInvoked = false;
            Keyboard::Key upKey = Keyboard::Key::Unknown;

            keyboard.onKeyUp([&isInvoked, &upKey](Keyboard::Key key) {
                isInvoked = true;
                upKey = key;
            });

            ime::Event event;
            event.type = ime::Event::KeyReleased;
            event.key.code = Keyboard::Key::W;

            REQUIRE(keyboard.isEnabled());
            keyboard.handleEvent(event);

            CHECK(isInvoked);
            CHECK_EQ(upKey, Keyboard::Key::W);

            WHEN("A ime::input::Keyboard is disabled")
            {
                keyboard.setEnable(false);
                REQUIRE_FALSE(keyboard.isEnabled());

                THEN("It does not dispatch key up events.")
                {
                    isInvoked = false;
                    keyboard.handleEvent(event);
                    CHECK_FALSE(isInvoked);
                }
            }
        }

        SUBCASE("onKeyDown()")
        {
            Keyboard keyboard;
            bool isInvoked = false;
            Keyboard::Key downKey = Keyboard::Key::Unknown;

            keyboard.onKeyDown([&isInvoked, &downKey](Keyboard::Key key) {
                isInvoked = true;
                downKey = key;
            });

            ime::Event event;
            event.type = ime::Event::KeyPressed;
            event.key.code = Keyboard::Key::V;

            REQUIRE(keyboard.isEnabled());
            keyboard.handleEvent(event);

            CHECK(isInvoked);
            CHECK_EQ(downKey, Keyboard::Key::V);

            WHEN("A ime::input::Keyboard is disabled")
            {
                keyboard.setEnable(false);
                REQUIRE_FALSE(keyboard.isEnabled());

                THEN("It does not dispatch key down events.")
                {
                    isInvoked = false;
                    keyboard.handleEvent(event);
                    CHECK_FALSE(isInvoked);
                }
            }
        }

        SUBCASE("onKeyHeld()")
        {
            Keyboard keyboard;
            bool isInvoked = false;
            Keyboard::Key heldKey = Keyboard::Key::Unknown;

            keyboard.onKeyDown([&isInvoked, &heldKey](Keyboard::Key key) {
                isInvoked = true;
                heldKey = key;
            });

            ime::Event event;
            event.type = ime::Event::KeyPressed;
            event.key.code = Keyboard::Key::K;

            // key press event triggered multiple times in the same frame
            REQUIRE(keyboard.isEnabled());
            keyboard.handleEvent(event);
            keyboard.handleEvent(event);

            CHECK(isInvoked);
            CHECK_EQ(heldKey, Keyboard::Key::K);

            SUBCASE("A disabled ime::input::Keyboard does not dispatch key held events")
            {
                keyboard.setEnable(false);
                REQUIRE_FALSE(keyboard.isEnabled());
                isInvoked = false;

                // key press event triggered multiple times in the same frame
                keyboard.handleEvent(event);
                keyboard.handleEvent(event);

                CHECK_FALSE(isInvoked);
            }
        }
    }

    SUBCASE("unsubscribe()")
    {
        SUBCASE("Removing a non-existent event listener returns false")
        {
            CHECK_FALSE(Keyboard().unsubscribe(ime::KeyboardEvent::KeyUp, -1));
            CHECK_FALSE(Keyboard().unsubscribe(ime::KeyboardEvent::KeyDown, -1));
            CHECK_FALSE(Keyboard().unsubscribe(ime::KeyboardEvent::KeyHeld, -1));
        }

        SUBCASE("Removing an existing event listener returns true")
        {
            Keyboard keyboard;

            int keyUpListener = keyboard.onKeyUp([](Keyboard::Key) {});
            int keyDownListener = keyboard.onKeyDown([](Keyboard::Key) {});
            int keyHeldListener = keyboard.onKeyHeld([](Keyboard::Key) {});

            CHECK(keyboard.unsubscribe(ime::KeyboardEvent::KeyUp, keyUpListener));
            CHECK(keyboard.unsubscribe(ime::KeyboardEvent::KeyDown, keyDownListener));
            CHECK(keyboard.unsubscribe(ime::KeyboardEvent::KeyHeld, keyHeldListener));
        }

        SUBCASE("Removing an existing event listener from an event its not listening for returns false")
        {
            Keyboard keyboard;
            int keyUpListener = keyboard.onKeyUp([](Keyboard::Key) {});

            CHECK_FALSE(keyboard.unsubscribe(ime::KeyboardEvent::KeyDown, keyUpListener));
            CHECK_FALSE(keyboard.unsubscribe(ime::KeyboardEvent::KeyHeld, keyUpListener));
        }
    }

    SUBCASE("String-enum conversions")
    {
        SUBCASE("keyToString()")
        {
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::A), "A");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::B), "B");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::C), "C");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::D), "D");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::E), "E");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F), "F");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::G), "G");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::H), "H");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::I), "I");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::J), "J");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::K), "K");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::L), "L");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::M), "M");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::N), "N");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::O), "O");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::P), "P");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Q), "Q");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::R), "R");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::S), "S");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::T), "T");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::U), "U");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::V), "V");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::W), "W");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::X), "X");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Y), "Y");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Z), "Z");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num0), "Num0");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num1), "Num1");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num2), "Num2");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num3), "Num3");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num4), "Num4");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num5), "Num5");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num6), "Num6");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num7), "Num7");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num8), "Num8");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Num9), "Num9");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Escape), "Escape");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::LControl), "LControl");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::LShift), "LShift");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::LAlt), "LAlt");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::LSystem), "LSystem");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::RControl), "RControl");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::RShift), "RShift");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::RAlt), "RAlt");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::RSystem), "RSystem");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Menu), "Menu");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::LBracket), "LBracket");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::RBracket), "RBracket");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Semicolon), "Semicolon");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Comma), "Comma");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Period), "Period");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Quote), "Quote");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Slash), "Slash");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Backslash), "Backslash");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Tilde), "Tilde");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Equal), "Equal");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Hyphen), "Hyphen");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Space), "Space");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Enter), "Enter");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Backspace), "Backspace");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Tab), "Tab");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::PageUp), "PageUp");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::PageDown), "PageDown");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::End), "End");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Home), "Home");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Insert), "Insert");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Delete), "Delete");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Add), "Add");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Subtract), "Subtract");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Multiply), "Multiply");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Divide), "Divide");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Left), "Left");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Right), "Right");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Up), "Up");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Down), "Down");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad0), "Numpad0");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad1), "Numpad1");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad2), "Numpad2");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad3), "Numpad3");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad4), "Numpad4");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad5), "Numpad5");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad6), "Numpad6");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad7), "Numpad7");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad8), "Numpad8");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Numpad9), "Numpad9");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F1), "F1");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F2), "F2");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F3), "F3");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F4), "F4");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F5), "F5");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F6), "F6");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F7), "F7");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F8), "F8");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F9), "F9");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F10), "F10");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F11), "F11");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F12), "F12");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F13), "F13");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F14), "F14");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::F15), "F15");
            CHECK_EQ(Keyboard::keyToString(Keyboard::Key::Pause), "Pause");
        }

        SUBCASE("stringToKey()")
        {
            CHECK_EQ(Keyboard::stringToKey("A"), Keyboard::Key::A);
            CHECK_EQ(Keyboard::stringToKey("B"), Keyboard::Key::B);
            CHECK_EQ(Keyboard::stringToKey("C"), Keyboard::Key::C);
            CHECK_EQ(Keyboard::stringToKey("D"), Keyboard::Key::D);
            CHECK_EQ(Keyboard::stringToKey("E"), Keyboard::Key::E);
            CHECK_EQ(Keyboard::stringToKey("F"), Keyboard::Key::F);
            CHECK_EQ(Keyboard::stringToKey("G"), Keyboard::Key::G);
            CHECK_EQ(Keyboard::stringToKey("H"), Keyboard::Key::H);
            CHECK_EQ(Keyboard::stringToKey("I"), Keyboard::Key::I);
            CHECK_EQ(Keyboard::stringToKey("J"), Keyboard::Key::J);
            CHECK_EQ(Keyboard::stringToKey("K"), Keyboard::Key::K);
            CHECK_EQ(Keyboard::stringToKey("L"), Keyboard::Key::L);
            CHECK_EQ(Keyboard::stringToKey("M"), Keyboard::Key::M);
            CHECK_EQ(Keyboard::stringToKey("N"), Keyboard::Key::N);
            CHECK_EQ(Keyboard::stringToKey("O"), Keyboard::Key::O);
            CHECK_EQ(Keyboard::stringToKey("P"), Keyboard::Key::P);
            CHECK_EQ(Keyboard::stringToKey("Q"), Keyboard::Key::Q);
            CHECK_EQ(Keyboard::stringToKey("R"), Keyboard::Key::R);
            CHECK_EQ(Keyboard::stringToKey("S"), Keyboard::Key::S);
            CHECK_EQ(Keyboard::stringToKey("T"), Keyboard::Key::T);
            CHECK_EQ(Keyboard::stringToKey("U"), Keyboard::Key::U);
            CHECK_EQ(Keyboard::stringToKey("V"), Keyboard::Key::V);
            CHECK_EQ(Keyboard::stringToKey("W"), Keyboard::Key::W);
            CHECK_EQ(Keyboard::stringToKey("X"), Keyboard::Key::X);
            CHECK_EQ(Keyboard::stringToKey("Y"), Keyboard::Key::Y);
            CHECK_EQ(Keyboard::stringToKey("Z"), Keyboard::Key::Z);
            CHECK_EQ(Keyboard::stringToKey("Num0"), Keyboard::Key::Num0);
            CHECK_EQ(Keyboard::stringToKey("Num1"), Keyboard::Key::Num1);
            CHECK_EQ(Keyboard::stringToKey("Num2"), Keyboard::Key::Num2);
            CHECK_EQ(Keyboard::stringToKey("Num3"), Keyboard::Key::Num3);
            CHECK_EQ(Keyboard::stringToKey("Num4"), Keyboard::Key::Num4);
            CHECK_EQ(Keyboard::stringToKey("Num5"), Keyboard::Key::Num5);
            CHECK_EQ(Keyboard::stringToKey("Num6"), Keyboard::Key::Num6);
            CHECK_EQ(Keyboard::stringToKey("Num7"), Keyboard::Key::Num7);
            CHECK_EQ(Keyboard::stringToKey("Num8"), Keyboard::Key::Num8);
            CHECK_EQ(Keyboard::stringToKey("Num9"), Keyboard::Key::Num9);
            CHECK_EQ(Keyboard::stringToKey("Escape"), Keyboard::Key::Escape);
            CHECK_EQ(Keyboard::stringToKey("LControl"), Keyboard::Key::LControl);
            CHECK_EQ(Keyboard::stringToKey("LShift"), Keyboard::Key::LShift);
            CHECK_EQ(Keyboard::stringToKey("LAlt"), Keyboard::Key::LAlt);
            CHECK_EQ(Keyboard::stringToKey("LSystem"), Keyboard::Key::LSystem);
            CHECK_EQ(Keyboard::stringToKey("RControl"), Keyboard::Key::RControl);
            CHECK_EQ(Keyboard::stringToKey("RShift"), Keyboard::Key::RShift);
            CHECK_EQ(Keyboard::stringToKey("RAlt"), Keyboard::Key::RAlt);
            CHECK_EQ(Keyboard::stringToKey("RSystem"), Keyboard::Key::RSystem);
            CHECK_EQ(Keyboard::stringToKey("Menu"), Keyboard::Key::Menu);
            CHECK_EQ(Keyboard::stringToKey("LBracket"), Keyboard::Key::LBracket);
            CHECK_EQ(Keyboard::stringToKey("RBracket"), Keyboard::Key::RBracket);
            CHECK_EQ(Keyboard::stringToKey("Semicolon"), Keyboard::Key::Semicolon);
            CHECK_EQ(Keyboard::stringToKey("Comma"), Keyboard::Key::Comma);
            CHECK_EQ(Keyboard::stringToKey("Period"), Keyboard::Key::Period);
            CHECK_EQ(Keyboard::stringToKey("Quote"), Keyboard::Key::Quote);
            CHECK_EQ(Keyboard::stringToKey("Slash"), Keyboard::Key::Slash);
            CHECK_EQ(Keyboard::stringToKey("Backslash"), Keyboard::Key::Backslash);
            CHECK_EQ(Keyboard::stringToKey("Tilde"), Keyboard::Key::Tilde);
            CHECK_EQ(Keyboard::stringToKey("Equal"), Keyboard::Key::Equal);
            CHECK_EQ(Keyboard::stringToKey("Hyphen"), Keyboard::Key::Hyphen);
            CHECK_EQ(Keyboard::stringToKey("Space"), Keyboard::Key::Space);
            CHECK_EQ(Keyboard::stringToKey("Enter"), Keyboard::Key::Enter);
            CHECK_EQ(Keyboard::stringToKey("Tab"), Keyboard::Key::Tab);
            CHECK_EQ(Keyboard::stringToKey("PageUp"), Keyboard::Key::PageUp);
            CHECK_EQ(Keyboard::stringToKey("PageDown"), Keyboard::Key::PageDown);
            CHECK_EQ(Keyboard::stringToKey("End"), Keyboard::Key::End);
            CHECK_EQ(Keyboard::stringToKey("Home"), Keyboard::Key::Home);
            CHECK_EQ(Keyboard::stringToKey("Insert"), Keyboard::Key::Insert);
            CHECK_EQ(Keyboard::stringToKey("Delete"), Keyboard::Key::Delete);
            CHECK_EQ(Keyboard::stringToKey("Add"), Keyboard::Key::Add);
            CHECK_EQ(Keyboard::stringToKey("Subtract"), Keyboard::Key::Subtract);
            CHECK_EQ(Keyboard::stringToKey("Multiply"), Keyboard::Key::Multiply);
            CHECK_EQ(Keyboard::stringToKey("Divide"), Keyboard::Key::Divide);
            CHECK_EQ(Keyboard::stringToKey("Left"), Keyboard::Key::Left);
            CHECK_EQ(Keyboard::stringToKey("Right"), Keyboard::Key::Right);
            CHECK_EQ(Keyboard::stringToKey("Up"), Keyboard::Key::Up);
            CHECK_EQ(Keyboard::stringToKey("Down"), Keyboard::Key::Down);
            CHECK_EQ(Keyboard::stringToKey("Numpad0"), Keyboard::Key::Numpad0);
            CHECK_EQ(Keyboard::stringToKey("Numpad1"), Keyboard::Key::Numpad1);
            CHECK_EQ(Keyboard::stringToKey("Numpad2"), Keyboard::Key::Numpad2);
            CHECK_EQ(Keyboard::stringToKey("Numpad3"), Keyboard::Key::Numpad3);
            CHECK_EQ(Keyboard::stringToKey("Numpad4"), Keyboard::Key::Numpad4);
            CHECK_EQ(Keyboard::stringToKey("Numpad5"), Keyboard::Key::Numpad5);
            CHECK_EQ(Keyboard::stringToKey("Numpad6"), Keyboard::Key::Numpad6);
            CHECK_EQ(Keyboard::stringToKey("Numpad7"), Keyboard::Key::Numpad7);
            CHECK_EQ(Keyboard::stringToKey("Numpad8"), Keyboard::Key::Numpad8);
            CHECK_EQ(Keyboard::stringToKey("Numpad9"), Keyboard::Key::Numpad9);
            CHECK_EQ(Keyboard::stringToKey("F1"), Keyboard::Key::F1);
            CHECK_EQ(Keyboard::stringToKey("F2"), Keyboard::Key::F2);
            CHECK_EQ(Keyboard::stringToKey("F3"), Keyboard::Key::F3);
            CHECK_EQ(Keyboard::stringToKey("F4"), Keyboard::Key::F4);
            CHECK_EQ(Keyboard::stringToKey("F5"), Keyboard::Key::F5);
            CHECK_EQ(Keyboard::stringToKey("F6"), Keyboard::Key::F6);
            CHECK_EQ(Keyboard::stringToKey("F7"), Keyboard::Key::F7);
            CHECK_EQ(Keyboard::stringToKey("F8"), Keyboard::Key::F8);
            CHECK_EQ(Keyboard::stringToKey("F9"), Keyboard::Key::F9);
            CHECK_EQ(Keyboard::stringToKey("F10"), Keyboard::Key::F10);
            CHECK_EQ(Keyboard::stringToKey("F11"), Keyboard::Key::F11);
            CHECK_EQ(Keyboard::stringToKey("F12"), Keyboard::Key::F12);
            CHECK_EQ(Keyboard::stringToKey("F13"), Keyboard::Key::F13);
            CHECK_EQ(Keyboard::stringToKey("F14"), Keyboard::Key::F14);
            CHECK_EQ(Keyboard::stringToKey("F15"), Keyboard::Key::F15);
            CHECK_EQ(Keyboard::stringToKey("Pause"), Keyboard::Key::Pause);
        }
    }
}