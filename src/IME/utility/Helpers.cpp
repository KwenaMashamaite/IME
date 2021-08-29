////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/utility/Helpers.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/ui/widgets/WidgetContainer.h"
#include <TGUI/Backends/SFML/BackendFontSFML.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <TGUI/Color.hpp>

namespace ime::utility {
    namespace {
        auto constexpr PIXELS_PER_METRE = 30.0f;
        auto constexpr PI = 3.14159265358979323846f;
    }

    Event convertToOwnEvent(const sf::Event &SFML_Event) {
        auto IME_Event = Event();
        switch (SFML_Event.type) {
            case sf::Event::Closed:
                IME_Event.type = Event::Type::Closed;
                return IME_Event;
            case sf::Event::Resized:
                IME_Event.type = Event::Type::Resized;
                IME_Event.size.width = SFML_Event.size.width;
                IME_Event.size.height = SFML_Event.size.height;
                return IME_Event;
            case sf::Event::LostFocus:
                IME_Event.type = Event::Type::LostFocus;
                return IME_Event;
            case sf::Event::GainedFocus:
                IME_Event.type = Event::Type::GainedFocus;
                return IME_Event;
            case sf::Event::TextEntered:
                IME_Event.type = Event::Type::TextEntered;
                IME_Event.text.unicode = SFML_Event.text.unicode;
                return IME_Event;
            case sf::Event::KeyReleased:
            case sf::Event::KeyPressed:
                if (SFML_Event.type == sf::Event::KeyPressed)
                    IME_Event.type = Event::Type::KeyPressed;
                else
                    IME_Event.type = Event::Type::KeyReleased;

                IME_Event.key.code = static_cast<input::Keyboard::Key>(SFML_Event.key.code);
                IME_Event.key.alt = SFML_Event.key.alt;
                IME_Event.key.control = SFML_Event.key.control;
                IME_Event.key.shift = SFML_Event.key.shift;
                IME_Event.key.system = SFML_Event.key.system;
                return IME_Event;
            case sf::Event::MouseWheelScrolled:
                IME_Event.type = Event::Type::MouseWheelScrolled;
                if (SFML_Event.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel)
                    IME_Event.mouseWheelScroll.wheel = input::Mouse::Wheel::VerticalWheel;
                else
                    IME_Event.mouseWheelScroll.wheel = input::Mouse::Wheel::HorizontalWheel;

                IME_Event.mouseWheelScroll.delta = SFML_Event.mouseWheelScroll.delta;
                IME_Event.mouseWheelScroll.x = SFML_Event.mouseWheelScroll.x;
                IME_Event.mouseWheelScroll.y = SFML_Event.mouseWheelScroll.y;
                return IME_Event;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                if (SFML_Event.type == sf::Event::MouseButtonPressed)
                    IME_Event.type = Event::Type::MouseButtonPressed;
                else
                    IME_Event.type = Event::Type::MouseButtonReleased;

                IME_Event.mouseButton.button = static_cast<input::Mouse::Button>(SFML_Event.mouseButton.button);
                IME_Event.mouseButton.x = SFML_Event.mouseButton.x;
                IME_Event.mouseButton.y = SFML_Event.mouseButton.y;
                return IME_Event;
            case sf::Event::MouseMoved:
                IME_Event.type = Event::Type::MouseMoved;
                IME_Event.mouseMove.x = SFML_Event.mouseMove.x;
                IME_Event.mouseMove.y = SFML_Event.mouseMove.y;
                return IME_Event;
            case sf::Event::MouseEntered:
                IME_Event.type = Event::MouseEntered;
                return IME_Event;
            case sf::Event::MouseLeft:
                IME_Event.type = Event::MouseLeft;
                return IME_Event;
            case sf::Event::JoystickButtonPressed:
                IME_Event.type = Event::JoystickButtonPressed;
                IME_Event.joystickButton.joystickId = SFML_Event.joystickButton.joystickId;
                IME_Event.joystickButton.button = SFML_Event.joystickButton.button;
                return IME_Event;
            case sf::Event::JoystickButtonReleased:
                IME_Event.type = Event::JoystickButtonReleased;
                IME_Event.joystickButton.joystickId = SFML_Event.joystickButton.joystickId;
                IME_Event.joystickButton.button = SFML_Event.joystickButton.button;
                return IME_Event;
            case sf::Event::JoystickMoved:
                IME_Event.type = Event::JoystickMoved;
                IME_Event.joystickMove.joystickId = SFML_Event.joystickMove.joystickId;
                IME_Event.joystickMove.axis = static_cast<input::Joystick::Axis>(SFML_Event.joystickMove.axis);
                IME_Event.joystickMove.position = SFML_Event.joystickMove.position;
                return IME_Event;
            case sf::Event::JoystickConnected:
                IME_Event.type = Event::JoystickConnected;
                IME_Event.joystickConnect.joystickId = SFML_Event.joystickConnect.joystickId;
                return IME_Event;
            case sf::Event::JoystickDisconnected:
                IME_Event.type = Event::JoystickDisconnected;
                IME_Event.joystickConnect.joystickId = SFML_Event.joystickConnect.joystickId;
                return IME_Event;
            default:
            {
                IME_Event.type = Event::Unknown;
                switch (SFML_Event.type) {
                    case sf::Event::TouchBegan:
                    case sf::Event::TouchEnded:
                        if (SFML_Event.touch.finger != 0) // Multi-touch not supported
                            return IME_Event;

                        // Treat touch events as mouse events
                        if (SFML_Event.type == sf::Event::TouchBegan)
                            IME_Event.type = Event::Type::MouseButtonPressed;
                        else
                            IME_Event.type = Event::Type::MouseButtonReleased;

                        IME_Event.mouseButton.button = input::Mouse::Button::Left;
                        IME_Event.mouseButton.x = SFML_Event.touch.x;
                        IME_Event.mouseButton.y = SFML_Event.touch.y;
                        return IME_Event;
                    case sf::Event::TouchMoved:
                        if (SFML_Event.touch.finger != 0) // Multi-touch not supported
                            return IME_Event;

                        // Treat moving touch as moving mouse cursor
                        IME_Event.type = Event::Type::MouseMoved;
                        IME_Event.mouseMove.x = SFML_Event.touch.x;
                        IME_Event.mouseMove.y = SFML_Event.touch.y;
                        return IME_Event;
                    case sf::Event::SensorChanged:
                        IME_PRINT_WARNING(
                            "Sensors are not supported in IME v"
                            + std::to_string(IME_VERSION_MAJOR) + "."
                            + std::to_string(IME_VERSION_MINOR) + + "."
                            + std::to_string(IME_VERSION_PATCH))
                        break;
                    default:
                        break;
                }
                return IME_Event;
            }
        }
    }

    sf::Event convertToSFMLEvent(const Event &IME_Event) {
        auto SFML_Event = sf::Event();
        switch (IME_Event.type) {
            case Event::Closed:
                SFML_Event.type = sf::Event::EventType::Closed;
                return SFML_Event;
            case Event::Resized:
                SFML_Event.type = sf::Event::EventType::Resized;
                SFML_Event.size.width = IME_Event.size.width;
                SFML_Event.size.height = IME_Event.size.height;
                return SFML_Event;
            case Event::LostFocus:
                SFML_Event.type = sf::Event::EventType::LostFocus;
                return SFML_Event;
            case Event::GainedFocus:
                SFML_Event.type = sf::Event::EventType::GainedFocus;
                return SFML_Event;
            case Event::TextEntered:
                SFML_Event.type = sf::Event::EventType::TextEntered;
                SFML_Event.text.unicode = IME_Event.text.unicode;
                return SFML_Event;
            case Event::KeyReleased:
            case Event::KeyPressed:
                if (IME_Event.type == Event::KeyPressed)
                    SFML_Event.type = sf::Event::EventType::KeyPressed;
                else
                    SFML_Event.type = sf::Event::EventType::KeyReleased;

                SFML_Event.key.code = static_cast<sf::Keyboard::Key>(IME_Event.key.code);
                SFML_Event.key.alt = IME_Event.key.alt;
                SFML_Event.key.control = IME_Event.key.control;
                SFML_Event.key.shift = IME_Event.key.shift;
                SFML_Event.key.system = IME_Event.key.system;
                return SFML_Event;
            case Event::MouseWheelScrolled:
                SFML_Event.type = sf::Event::EventType::MouseWheelScrolled;
                if (IME_Event.mouseWheelScroll.wheel == input::Mouse::Wheel::VerticalWheel)
                    SFML_Event.mouseWheelScroll.wheel = sf::Mouse::Wheel::VerticalWheel;
                else
                    SFML_Event.mouseWheelScroll.wheel = sf::Mouse::Wheel::HorizontalWheel;

                SFML_Event.mouseWheelScroll.delta = IME_Event.mouseWheelScroll.delta;
                SFML_Event.mouseWheelScroll.x = IME_Event.mouseWheelScroll.x;
                SFML_Event.mouseWheelScroll.y = IME_Event.mouseWheelScroll.y;
                return SFML_Event;
            case Event::MouseButtonPressed:
            case Event::MouseButtonReleased:
                if (IME_Event.type == Event::MouseButtonPressed)
                    SFML_Event.type = sf::Event::EventType::MouseButtonPressed;
                else
                    SFML_Event.type = sf::Event::EventType::MouseButtonReleased;

                SFML_Event.mouseButton.button = static_cast<sf::Mouse::Button>(IME_Event.mouseButton.button);
                SFML_Event.mouseButton.x = IME_Event.mouseButton.x;
                SFML_Event.mouseButton.y = IME_Event.mouseButton.y;
                return SFML_Event;
            case Event::MouseMoved:
                SFML_Event.type = sf::Event::EventType::MouseMoved;
                SFML_Event.mouseMove.x = IME_Event.mouseMove.x;
                SFML_Event.mouseMove.y = IME_Event.mouseMove.y;
                return SFML_Event;
            case Event::MouseEntered:
                SFML_Event.type = sf::Event::EventType::MouseEntered;
                return SFML_Event;
            case Event::MouseLeft:
                SFML_Event.type = sf::Event::EventType::MouseLeft;
                return SFML_Event;
            case Event::JoystickButtonPressed:
                SFML_Event.type = sf::Event::JoystickButtonPressed;
                SFML_Event.joystickButton.joystickId = IME_Event.joystickButton.joystickId;
                SFML_Event.joystickButton.button = IME_Event.joystickButton.button;
                return SFML_Event;
            case Event::JoystickButtonReleased:
                SFML_Event.type = sf::Event::JoystickButtonReleased;
                SFML_Event.joystickButton.joystickId = IME_Event.joystickButton.joystickId;
                SFML_Event.joystickButton.button = IME_Event.joystickButton.button;
                return SFML_Event;
            case Event::JoystickMoved:
                SFML_Event.type = sf::Event::JoystickMoved;
                SFML_Event.joystickMove.joystickId = IME_Event.joystickMove.joystickId;
                SFML_Event.joystickMove.axis = static_cast<sf::Joystick::Axis>(IME_Event.joystickMove.axis);
                SFML_Event.joystickMove.position = IME_Event.joystickMove.position;
                return SFML_Event;
            case Event::JoystickConnected:
                SFML_Event.type = sf::Event::JoystickConnected;
                SFML_Event.joystickConnect.joystickId = IME_Event.joystickConnect.joystickId;
                return SFML_Event;
            case Event::JoystickDisconnected:
                SFML_Event.type = sf::Event::JoystickDisconnected;
                SFML_Event.joystickConnect.joystickId = IME_Event.joystickConnect.joystickId;
                return SFML_Event;
            default:
                return SFML_Event;
        }
    }

    sf::Color convertToSFMLColour(Colour colour) {
        return {static_cast<sf::Uint8>(colour.red),
                static_cast<sf::Uint8>(colour.green),
                static_cast<sf::Uint8>(colour.blue),
                static_cast<sf::Uint8>(colour.opacity)};
    }

    tgui::Color convertToTGUIColour(Colour color) {
        return {static_cast<std::uint8_t>(color.red),
                static_cast<std::uint8_t>(color.green),
                static_cast<std::uint8_t>(color.blue),
                static_cast<std::uint8_t>(color.opacity)};
    }

    Colour convertFrom3rdPartyColour(sf::Color thirdPartyColour) {
        return {thirdPartyColour.r, thirdPartyColour.g, thirdPartyColour.b, thirdPartyColour.a};
    }

    float pixelsToMetres(float pixels) {
        return pixels / PIXELS_PER_METRE;
    }

    Vector2f pixelsToMetres(Vector2f pixels) {
        return {pixelsToMetres(pixels.x), pixelsToMetres(pixels.y)};
    }

    float metresToPixels(float metres) {
        return metres * PIXELS_PER_METRE;
    }

    Vector2f metresToPixels(Vector2f metres) {
        return {metresToPixels(metres.x), metresToPixels(metres.y)};
    }

    float radToDeg(float rad) {
        return (180.0f * rad) / PI;
    }

    float degToRad(float deg) {
        return (PI * deg) / 180.0f;
    }

    tgui::Font get_TGUI_Font(const std::string &filename) {
        auto tguiBackendFont = std::make_shared<tgui::BackendFontSFML>();
        tguiBackendFont->getInternalFont() = ime::ResourceManager::getInstance()->getFont(filename);
        auto tguiFont = tgui::Font(std::move(tguiBackendFont), filename);
        return tguiFont;
    }

    ui::Widget* findRecursively(const std::unordered_map<std::string,
        std::unique_ptr<ui::Widget>>& widgets, const std::string &widgetName)
    {
        for (const auto& widget : widgets) {
            if (widget.second->isContainer()) {
                auto* container = static_cast<ui::WidgetContainer*>(widget.second.get());
                auto* widgetInContainer = container->getWidget(widgetName);
                if (widgetInContainer)
                    return widgetInContainer;
            }
        }

        return nullptr;
    }

    bool removeRecursively(const std::unordered_map<std::string,
        std::unique_ptr<ui::Widget>>& widgets, const std::string &widgetName)
    {
        for (const auto& widget : widgets) {
            if (widget.second->isContainer()) {
                auto* container = static_cast<ui::WidgetContainer*>(widget.second.get());
                if (container->removeWidget(widgetName))
                    return true;
                else continue;
            }
        }

        return false;
    }
}