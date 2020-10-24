/**
 * @brief Helper functions
 */

#ifndef UTILITY_H
#define UTILITY_H

#include "IME/graphics/Colour.h"
#include <SFML/Graphics/Color.hpp>
#include <TGUI/Color.hpp>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <SFML/Window/Keyboard.hpp>
#include <TGUI/Event.hpp>
#include <SFML/Window/Event.hpp>

namespace IME::Utility {
    /**
     * @brief Convert own Colour object to SFML colour object
     * @param colour Colour to be converted to SFML colour object
     * @return SFML colour object
     *
     * This function only converts the object and not the actual
     * colour. This means that the colour after the conversion is
     * the same as the one before the conversion
     */
    static sf::Color convertToSFMLColour(Graphics::Colour color) {
        return {static_cast<sf::Uint8>(color.red),
                static_cast<sf::Uint8>(color.green),
                static_cast<sf::Uint8>(color.blue),
                static_cast<sf::Uint8>(color.opacity)};
    }

    static tgui::Color convertToTGUIColour(Graphics::Colour color) {
        return {static_cast<std::uint8_t>(color.red),
                static_cast<std::uint8_t>(color.green),
                static_cast<std::uint8_t>(color.blue),
                static_cast<std::uint8_t>(color.opacity)};
    }

    /**
     * @brief Convert graphics library colour object to own colour object
     * @param thirdPartyColour Colour to be converted to own colour object
     * @return Own colour object
     *
     * This function only converts the object and not the actual
     * colour. This means that the colour after the conversion is
     * the same as the one before the conversion
     */
    static Graphics::Colour convertFrom3rdPartyColour(sf::Color thirdPartyColour) {
        return {thirdPartyColour.r, thirdPartyColour.g, thirdPartyColour.b, thirdPartyColour.a};
    }

    /**
     * @brief Check if an item exists or not in an unordered map
     * @param unorderedMap Map to search for item in
     * @param item Item to search for
     * @return True if item exists in the unordered map, otherwise false
     */
    template <typename T, typename U, typename V>
    bool findIn(const std::unordered_map<T, U>& unorderedMap, const V& item) {
        return unorderedMap.find(item) != unorderedMap.end();
    }

    /**
     * @brief Find an item in vector
     * @param vector Vector to search item in
     * @param item Item to search for
     * @return A pair, of which the first element is a bool that is true if
     *         the specified item exists in the vector ,otherwise false and
     *         the second is an int which is the index of the found item in
     *         the vector
     */
    template <typename T, typename U>
    std::pair<bool, int> findIn(const std::vector<T> vector, const U& item) {
        if (auto found = std::find(vector.begin(), vector.end(), item); found != vector.end())
            return {true, std::distance(vector.begin(), found)};
        return {false, -1};
    }

    /**
     * @brief Erase an element from a vector
     * @param vector Vector to remove element from
     * @param element Element to be removed
     * @return True if element was removed or false if element doesn't exist
     *         in the vector
     */
    template <typename T, typename U>
    bool eraseIn(std::vector<T>& vector, const U& element) {
        if (auto [found, index] = findIn(vector, element); found) {
            vector.erase(vector.begin() + index);
            return true;
        }
        return false;
    }

    /**
     * @brief Generate a random number in a range
     * @param min The start of the range
     * @param max The end of the range
     * @return A random number in the given range
     */
    static int generateRandomNum(int min, int max) {
        return min + (rand() % (max - min + 1));
    }

    /**
     * @brief Create a callable that generates random numbers in a range
     * @param min The start of the range
     * @param max The end of the range
     * @return A callable object, when called returns a random number in the
     *         specified range
     */
    static auto createRandomNumGenerator(int min, int max) {
        return [distribution = std::uniform_int_distribution(min, max),
            randomEngine = std::mt19937{std::random_device{}()}]() mutable {
                return distribution(randomEngine);
        };
    }

    /**
     * @brief Create a random colour
     * @return A random colour
     */
    static Graphics::Colour generateRandomColour() {
        return {static_cast<unsigned int>(generateRandomNum(0, 255)),
                static_cast<unsigned int>(generateRandomNum(0, 255)),
                static_cast<unsigned int>(generateRandomNum(0, 255)),255};
    }

    /**
     * @internal
     * @brief Convert an sf::Event object to a tgui::Event object
     * @param sfmlEvent Event to be converted
     * @return tgui::Event object
     */
    static tgui::Event convert_SFML_event_to_TGUI_event(const sf::Event& sfmlEvent) {
        static auto convertKeyCode = [](sf::Keyboard::Key key) {
            switch (key) {
                case sf::Keyboard::Key::A:          return tgui::Event::KeyboardKey::A;
                case sf::Keyboard::Key::B:          return tgui::Event::KeyboardKey::B;
                case sf::Keyboard::Key::C:          return tgui::Event::KeyboardKey::C;
                case sf::Keyboard::Key::D:          return tgui::Event::KeyboardKey::D;
                case sf::Keyboard::Key::E:          return tgui::Event::KeyboardKey::E;
                case sf::Keyboard::Key::F:          return tgui::Event::KeyboardKey::F;
                case sf::Keyboard::Key::G:          return tgui::Event::KeyboardKey::G;
                case sf::Keyboard::Key::H:          return tgui::Event::KeyboardKey::H;
                case sf::Keyboard::Key::I:          return tgui::Event::KeyboardKey::I;
                case sf::Keyboard::Key::J:          return tgui::Event::KeyboardKey::J;
                case sf::Keyboard::Key::K:          return tgui::Event::KeyboardKey::K;
                case sf::Keyboard::Key::L:          return tgui::Event::KeyboardKey::L;
                case sf::Keyboard::Key::M:          return tgui::Event::KeyboardKey::M;
                case sf::Keyboard::Key::N:          return tgui::Event::KeyboardKey::N;
                case sf::Keyboard::Key::O:          return tgui::Event::KeyboardKey::O;
                case sf::Keyboard::Key::P:          return tgui::Event::KeyboardKey::P;
                case sf::Keyboard::Key::Q:          return tgui::Event::KeyboardKey::Q;
                case sf::Keyboard::Key::R:          return tgui::Event::KeyboardKey::R;
                case sf::Keyboard::Key::S:          return tgui::Event::KeyboardKey::S;
                case sf::Keyboard::Key::T:          return tgui::Event::KeyboardKey::T;
                case sf::Keyboard::Key::U:          return tgui::Event::KeyboardKey::U;
                case sf::Keyboard::Key::V:          return tgui::Event::KeyboardKey::V;
                case sf::Keyboard::Key::W:          return tgui::Event::KeyboardKey::W;
                case sf::Keyboard::Key::X:          return tgui::Event::KeyboardKey::X;
                case sf::Keyboard::Key::Y:          return tgui::Event::KeyboardKey::Y;
                case sf::Keyboard::Key::Z:          return tgui::Event::KeyboardKey::Z;
                case sf::Keyboard::Key::Num0:       return tgui::Event::KeyboardKey::Num0;
                case sf::Keyboard::Key::Num1:       return tgui::Event::KeyboardKey::Num1;
                case sf::Keyboard::Key::Num2:       return tgui::Event::KeyboardKey::Num2;
                case sf::Keyboard::Key::Num3:       return tgui::Event::KeyboardKey::Num3;
                case sf::Keyboard::Key::Num4:       return tgui::Event::KeyboardKey::Num4;
                case sf::Keyboard::Key::Num5:       return tgui::Event::KeyboardKey::Num5;
                case sf::Keyboard::Key::Num6:       return tgui::Event::KeyboardKey::Num6;
                case sf::Keyboard::Key::Num7:       return tgui::Event::KeyboardKey::Num7;
                case sf::Keyboard::Key::Num8:       return tgui::Event::KeyboardKey::Num8;
                case sf::Keyboard::Key::Num9:       return tgui::Event::KeyboardKey::Num9;
                case sf::Keyboard::Key::Escape:     return tgui::Event::KeyboardKey::Escape;
                case sf::Keyboard::Key::LControl:   return tgui::Event::KeyboardKey::LControl;
                case sf::Keyboard::Key::LShift:     return tgui::Event::KeyboardKey::LShift;
                case sf::Keyboard::Key::LAlt:       return tgui::Event::KeyboardKey::LAlt;
                case sf::Keyboard::Key::LSystem:    return tgui::Event::KeyboardKey::LSystem;
                case sf::Keyboard::Key::RControl:   return tgui::Event::KeyboardKey::RControl;
                case sf::Keyboard::Key::RShift:     return tgui::Event::KeyboardKey::RShift;
                case sf::Keyboard::Key::RAlt:       return tgui::Event::KeyboardKey::RAlt;
                case sf::Keyboard::Key::RSystem:    return tgui::Event::KeyboardKey::RSystem;
                case sf::Keyboard::Key::Menu:       return tgui::Event::KeyboardKey::Menu;
                case sf::Keyboard::Key::LBracket:   return tgui::Event::KeyboardKey::LBracket;
                case sf::Keyboard::Key::RBracket:   return tgui::Event::KeyboardKey::RBracket;
                case sf::Keyboard::Key::Semicolon:  return tgui::Event::KeyboardKey::Semicolon;
                case sf::Keyboard::Key::Comma:      return tgui::Event::KeyboardKey::Comma;
                case sf::Keyboard::Key::Period:     return tgui::Event::KeyboardKey::Period;
                case sf::Keyboard::Key::Quote:      return tgui::Event::KeyboardKey::Quote;
                case sf::Keyboard::Key::Slash:      return tgui::Event::KeyboardKey::Slash;
                case sf::Keyboard::Key::Backslash:  return tgui::Event::KeyboardKey::Backslash;
                case sf::Keyboard::Key::Equal:      return tgui::Event::KeyboardKey::Equal;
                case sf::Keyboard::Key::Hyphen:     return tgui::Event::KeyboardKey::Minus;
                case sf::Keyboard::Key::Space:      return tgui::Event::KeyboardKey::Space;
                case sf::Keyboard::Key::Enter:      return tgui::Event::KeyboardKey::Enter;
                case sf::Keyboard::Key::Backspace:  return tgui::Event::KeyboardKey::Backspace;
                case sf::Keyboard::Key::Tab:        return tgui::Event::KeyboardKey::Tab;
                case sf::Keyboard::Key::PageUp:     return tgui::Event::KeyboardKey::PageUp;
                case sf::Keyboard::Key::PageDown:   return tgui::Event::KeyboardKey::PageDown;
                case sf::Keyboard::Key::End:        return tgui::Event::KeyboardKey::End;
                case sf::Keyboard::Key::Home:       return tgui::Event::KeyboardKey::Home;
                case sf::Keyboard::Key::Insert:     return tgui::Event::KeyboardKey::Insert;
                case sf::Keyboard::Key::Delete:     return tgui::Event::KeyboardKey::Delete;
                case sf::Keyboard::Key::Add:        return tgui::Event::KeyboardKey::Add;
                case sf::Keyboard::Key::Subtract:   return tgui::Event::KeyboardKey::Subtract;
                case sf::Keyboard::Key::Multiply:   return tgui::Event::KeyboardKey::Multiply;
                case sf::Keyboard::Key::Divide:     return tgui::Event::KeyboardKey::Divide;
                case sf::Keyboard::Key::Left:       return tgui::Event::KeyboardKey::Left;
                case sf::Keyboard::Key::Right:      return tgui::Event::KeyboardKey::Right;
                case sf::Keyboard::Key::Up:         return tgui::Event::KeyboardKey::Up;
                case sf::Keyboard::Key::Down:       return tgui::Event::KeyboardKey::Down;
                case sf::Keyboard::Key::Numpad0:    return tgui::Event::KeyboardKey::Numpad0;
                case sf::Keyboard::Key::Numpad1:    return tgui::Event::KeyboardKey::Numpad1;
                case sf::Keyboard::Key::Numpad2:    return tgui::Event::KeyboardKey::Numpad2;
                case sf::Keyboard::Key::Numpad3:    return tgui::Event::KeyboardKey::Numpad3;
                case sf::Keyboard::Key::Numpad4:    return tgui::Event::KeyboardKey::Numpad4;
                case sf::Keyboard::Key::Numpad5:    return tgui::Event::KeyboardKey::Numpad5;
                case sf::Keyboard::Key::Numpad6:    return tgui::Event::KeyboardKey::Numpad6;
                case sf::Keyboard::Key::Numpad7:    return tgui::Event::KeyboardKey::Numpad7;
                case sf::Keyboard::Key::Numpad8:    return tgui::Event::KeyboardKey::Numpad8;
                case sf::Keyboard::Key::Numpad9:    return tgui::Event::KeyboardKey::Numpad9;
                case sf::Keyboard::Key::F1:         return tgui::Event::KeyboardKey::F1;
                case sf::Keyboard::Key::F2:         return tgui::Event::KeyboardKey::F2;
                case sf::Keyboard::Key::F3:         return tgui::Event::KeyboardKey::F3;
                case sf::Keyboard::Key::F4:         return tgui::Event::KeyboardKey::F4;
                case sf::Keyboard::Key::F5:         return tgui::Event::KeyboardKey::F5;
                case sf::Keyboard::Key::F6:         return tgui::Event::KeyboardKey::F6;
                case sf::Keyboard::Key::F7:         return tgui::Event::KeyboardKey::F7;
                case sf::Keyboard::Key::F8:         return tgui::Event::KeyboardKey::F8;
                case sf::Keyboard::Key::F9:         return tgui::Event::KeyboardKey::F9;
                case sf::Keyboard::Key::F10:        return tgui::Event::KeyboardKey::F10;
                case sf::Keyboard::Key::F11:        return tgui::Event::KeyboardKey::F11;
                case sf::Keyboard::Key::F12:        return tgui::Event::KeyboardKey::F12;
                case sf::Keyboard::Key::F13:        return tgui::Event::KeyboardKey::F13;
                case sf::Keyboard::Key::F14:        return tgui::Event::KeyboardKey::F14;
                case sf::Keyboard::Key::F15:        return tgui::Event::KeyboardKey::F15;
                case sf::Keyboard::Key::Pause:      return tgui::Event::KeyboardKey::Pause;
                default: // We don't process the other keys
                    return tgui::Event::KeyboardKey::Unknown;
            }
        };

        tgui::Event tguiEvent;
        switch (sfmlEvent.type) {
            case sf::Event::LostFocus:
                tguiEvent.type = tgui::Event::Type::LostFocus;
            case sf::Event::GainedFocus:
                tguiEvent.type = tgui::Event::Type::GainedFocus;
            case sf::Event::Resized: {
                tguiEvent.type = tgui::Event::Type::Resized;
                tguiEvent.size.width = sfmlEvent.size.width;
                tguiEvent.size.height = sfmlEvent.size.height;
            } case sf::Event::TextEntered: {
                tguiEvent.type = tgui::Event::Type::TextEntered;
                tguiEvent.text.unicode = sfmlEvent.text.unicode;
            } case sf::Event::KeyPressed: {
                const tgui::Event::KeyboardKey code = convertKeyCode(sfmlEvent.key.code);
                if (code == tgui::Event::KeyboardKey::Unknown)
                    return tgui::Event();

                tguiEvent.type = tgui::Event::Type::KeyPressed;
                tguiEvent.key.code = code;
                tguiEvent.key.alt = sfmlEvent.key.alt;
                tguiEvent.key.control = sfmlEvent.key.control;
                tguiEvent.key.shift = sfmlEvent.key.shift;
                tguiEvent.key.system = sfmlEvent.key.system;
            } case sf::Event::MouseWheelScrolled: {
                if (sfmlEvent.mouseWheelScroll.wheel != sf::Mouse::Wheel::VerticalWheel)
                    return tgui::Event(); // TGUI only handles the vertical mouse wheel

                tguiEvent.type = tgui::Event::Type::MouseWheelScrolled;
                tguiEvent.mouseWheel.delta = sfmlEvent.mouseWheelScroll.delta;
                tguiEvent.mouseWheel.x = sfmlEvent.mouseWheelScroll.x;
                tguiEvent.mouseWheel.y = sfmlEvent.mouseWheelScroll.y;
            }
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased: {
                switch (sfmlEvent.mouseButton.button) {
                    case sf::Mouse::Button::Left:
                        tguiEvent.mouseButton.button = tgui::Event::MouseButton::Left;
                        break;
                    case sf::Mouse::Button::Middle:
                        tguiEvent.mouseButton.button = tgui::Event::MouseButton::Middle;
                        break;
                    case sf::Mouse::Button::Right:
                        tguiEvent.mouseButton.button = tgui::Event::MouseButton::Right;
                        break;
                    default: // This mouse button isn't handled by TGUI
                        return tgui::Event();
                }

                if (sfmlEvent.type == sf::Event::MouseButtonPressed)
                    tguiEvent.type = tgui::Event::Type::MouseButtonPressed;
                else
                    tguiEvent.type = tgui::Event::Type::MouseButtonReleased;

                tguiEvent.mouseButton.x = sfmlEvent.mouseButton.x;
                tguiEvent.mouseButton.y = sfmlEvent.mouseButton.y;
            } case sf::Event::MouseMoved: {
                tguiEvent.type = tgui::Event::Type::MouseMoved;
                tguiEvent.mouseMove.x = sfmlEvent.mouseMove.x;
                tguiEvent.mouseMove.y = sfmlEvent.mouseMove.y;
            } default: // This event is not handled by TGUI
                return tgui::Event();
        }
        return tguiEvent;
    }
}

#endif
