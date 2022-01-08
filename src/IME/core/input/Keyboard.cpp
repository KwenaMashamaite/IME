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
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

namespace ime::input {
    namespace {
        // Convert a key to string representation
        std::string keyToString(Keyboard::Key key);
    }

    Keyboard::Keyboard() {
        for (auto i = 0; i < static_cast<int>(Key::KeyCount) - 1; ++i) {
            wasDown_[i] = false;
            stringKeyPairs_.insert({keyToString(static_cast<Key>(i)), static_cast<Key>(i)});
        }
    }

    std::string Keyboard::keyToString(Key key) {
        return ime::input::keyToString(key);
    }

    Key Keyboard::stringToKey(const std::string &key) {
        if (stringKeyPairs_.find(key) == stringKeyPairs_.end()) {
            std::cerr << "Error: " << key << " is not a valid key" << std::endl;
            exit(-1);
        }

        return stringKeyPairs_[key];
    }

    bool Keyboard::isKeyPressed(Key keyId) {
        return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyId));
    }

    int Keyboard::onKeyUp(Callback<Key> callback) {
        return eventEmitter_.on("keyUp", std::move(callback));
    }

    int Keyboard::onKeyDown(Callback<Keyboard::Key> callback) {
        return eventEmitter_.on("keyDown", std::move(callback));
    }

    int Keyboard::onKeyHeld(Callback<Keyboard::Key> callback) {
        return eventEmitter_.on("keyHeld", std::move(callback));
    }

    bool Keyboard::unsubscribe(KeyboardEvent event, int id) {
        switch (event) {
            case KeyboardEvent::KeyDown:
                return eventEmitter_.removeEventListener("keyDown", id);
            case KeyboardEvent::KeyUp:
                return eventEmitter_.removeEventListener("keyUp", id);
            case KeyboardEvent::KeyHeld:
                return eventEmitter_.removeEventListener("keyHeld", id);
            default:
                return false;
        }
    }

    void Keyboard::handleEvent(Event event) {
        switch (event.type) {
            case Event::KeyPressed:
                if (wasDown_[static_cast<int>(event.key.code)])
                    eventEmitter_.emit("keyHeld", event.key.code);
                else {
                    wasDown_[static_cast<int>(event.key.code)] = true;
                    eventEmitter_.emit("keyDown", event.key.code);
                }
                break;
            case Event::KeyReleased:
                wasDown_[static_cast<int>(event.key.code)] = false;
                eventEmitter_.emit("keyUp", event.key.code);
                break;
            default:
                break;
        }
    }

    namespace {
        std::string keyToString(Keyboard::Key key) {
            switch (key) {
                case Key::A:            return "A";
                case Key::B:            return "B";
                case Key::C:            return "C";
                case Key::D:            return "D";
                case Key::E:            return "E";
                case Key::F:            return "F";
                case Key::G:            return "G";
                case Key::H:            return "H";
                case Key::I:            return "I";
                case Key::J:            return "J";
                case Key::K:            return "K";
                case Key::L:            return "L";
                case Key::M:            return "M";
                case Key::N:            return "N";
                case Key::O:            return "O";
                case Key::P:            return "P";
                case Key::Q:            return "Q";
                case Key::R:            return "R";
                case Key::S:            return "S";
                case Key::T:            return "T";
                case Key::U:            return "U";
                case Key::V:            return "V";
                case Key::W:            return "W";
                case Key::X:            return "X";
                case Key::Y:            return "Y";
                case Key::Z:            return "Z";
                case Key::Num0:         return "Num0";
                case Key::Num1:         return "Num1";
                case Key::Num2:         return "Num2";
                case Key::Num3:         return "Num3";
                case Key::Num4:         return "Num4";
                case Key::Num5:         return "Num5";
                case Key::Num6:         return "Num6";
                case Key::Num7:         return "Num7";
                case Key::Num8:         return "Num8";
                case Key::Num9:         return "Num9";
                case Key::Escape:       return "Escape";
                case Key::LControl:     return "LControl";
                case Key::LShift:       return "LShift";
                case Key::LAlt:         return "LAlt";
                case Key::LSystem:      return "LSystem";
                case Key::RControl:     return "RControl";
                case Key::RShift:       return "RShift";
                case Key::RAlt:         return "RAlt";
                case Key::RSystem:      return "RSystem";
                case Key::Menu:         return "Menu";
                case Key::LBracket:     return "LBracket";
                case Key::RBracket:     return "RBracket";
                case Key::Semicolon:    return "Semicolon";
                case Key::Comma:        return "Comma";
                case Key::Period:       return "Period";
                case Key::Quote:        return "Quote";
                case Key::Slash:        return "Slash";
                case Key::Backslash:    return "Backslash";
                case Key::Tilde:        return "Tilde";
                case Key::Equal:        return "Equal";
                case Key::Hyphen:       return "Hyphen";
                case Key::Space:        return "Space";
                case Key::Enter:        return "Enter";
                case Key::Backspace:    return "Backspace";
                case Key::Tab:          return "Tab";
                case Key::PageUp:       return "PageUp";
                case Key::PageDown:     return "PageDown";
                case Key::End:          return "End";
                case Key::Home:         return "Home";
                case Key::Insert:       return "Insert";
                case Key::Delete:       return "Delete";
                case Key::Add:          return "Add";
                case Key::Subtract:     return "Subtract";
                case Key::Multiply:     return "Multiply";
                case Key::Divide:       return "Divide";
                case Key::Left:         return "Left";
                case Key::Right:        return "Right";
                case Key::Up:           return "Up";
                case Key::Down:         return "Down";
                case Key::Numpad0:      return "Numpad0";
                case Key::Numpad1:      return "Numpad1";
                case Key::Numpad2:      return "Numpad2";
                case Key::Numpad3:      return "Numpad3";
                case Key::Numpad4:      return "Numpad4";
                case Key::Numpad5:      return "Numpad5";
                case Key::Numpad6:      return "Numpad6";
                case Key::Numpad7:      return "Numpad7";
                case Key::Numpad8:      return "Numpad8";
                case Key::Numpad9:      return "Numpad9";
                case Key::F1:           return "F1";
                case Key::F2:           return "F2";
                case Key::F3:           return "F3";
                case Key::F4:           return "F4";
                case Key::F5:           return "F5";
                case Key::F6:           return "F6";
                case Key::F7:           return "F7";
                case Key::F8:           return "F8";
                case Key::F9:           return "F9";
                case Key::F10:          return "F10";
                case Key::F11:          return "F11";
                case Key::F12:          return "F12";
                case Key::F13:          return "F13";
                case Key::F14:          return "F14";
                case Key::F15:          return "F15";
                case Key::Pause:        return "Pause";
                default:
                    return "Unknown";
            }
        }
    }
}
