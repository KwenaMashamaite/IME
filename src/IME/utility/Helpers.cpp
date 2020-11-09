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