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

#include "IME/utility/Helpers.h"
#include "IME/core/managers/ResourceManager.h"
#include <TGUI/Backends/SFML/BackendFontSFML.hpp>

namespace IME::Utility {
    sf::Color convertToSFMLColour(Graphics::Colour colour) {
        return {static_cast<sf::Uint8>(colour.red),
                static_cast<sf::Uint8>(colour.green),
                static_cast<sf::Uint8>(colour.blue),
                static_cast<sf::Uint8>(colour.opacity)};
    }

    tgui::Color convertToTGUIColour(Graphics::Colour color) {
        return {static_cast<std::uint8_t>(color.red),
                static_cast<std::uint8_t>(color.green),
                static_cast<std::uint8_t>(color.blue),
                static_cast<std::uint8_t>(color.opacity)};
    }

    Graphics::Colour convertFrom3rdPartyColour(sf::Color thirdPartyColour) {
        return {thirdPartyColour.r, thirdPartyColour.g, thirdPartyColour.b, thirdPartyColour.a};
    }

    int generateRandomNum(int min, int max) {
        return min + (rand() % (max - min + 1));
    }

    Graphics::Colour generateRandomColour() {
        return {static_cast<unsigned int>(generateRandomNum(0, 255)),
                static_cast<unsigned int>(generateRandomNum(0, 255)),
                static_cast<unsigned int>(generateRandomNum(0, 255)),255};
    }

    tgui::Font get_TGUI_Font(const std::string &filename) {
        auto tguiBackendFont = std::make_shared<tgui::BackendFontSFML>();
        tguiBackendFont->getInternalFont() = IME::ResourceManager::getInstance()->getFont(filename);
        auto tguiFont = tgui::Font(std::move(tguiBackendFont), filename);
        return tguiFont;
    }
}