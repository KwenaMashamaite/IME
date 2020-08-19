#include "IME/core/engine/Engine.h"
#include "IME/utility/DiskFileReader.h"
#include "IME/core/exceptions/Exceptions.h"
#include "IME/utility/Clock.h"
#include "IME/utility/Helpers.h"

namespace IME {
    std::shared_ptr<const GuiFactory> IME::Engine::guiFactory_(std::make_shared<GuiFactory>());

    Engine::Engine(const std::string &gameName, const std::string &settingsFilename)
        : isRunning_{false},
          appName_{gameName},
          settingFile_{settingsFilename}
    {}

    void Engine::init() {
        loadSettings();
        initRenderTarget();
        window_.setFramerateLimit(60);
        window_.setIcon("icon.png");
    }

    void Engine::loadSettings() {
        auto settings = std::stringstream();
        Utility::DiskFileReader().readFileInto(settingFile_, settings);
        auto setting = std::string("");
        while (std::getline(settings, setting)) {
            static auto errorMessage = [&](const std::string& errorMessage){
                return R"(The entry ')" + setting + R"(')" + " in " + settingFile_
                    + " is invalid because " + errorMessage;
            };

            ////Skip lines that are empty or begin with a comment or whitespaces
            if (setting.empty() || setting[0] == '#' || setting[0] == ' ')
                continue;

            if (auto separatorPos = setting.find_first_of('='); separatorPos != std::string::npos) {
                auto key = setting.substr(0, separatorPos);
                if (key.find_first_of(' ') != std::string::npos)
                    throw InvalidArgument(errorMessage("key contains whitespaces"));
                auto value = setting.substr(separatorPos + 1);
                settings_.insert(std::pair(key, value));
            } else
                throw InvalidArgument(errorMessage(R"("it's missing a separator '=')"));
        }
        verifySettings();
    }

    void Engine::verifySettings() const {
        auto mandatorySettings = {"title", "width", "height", "fullscreen"};
        std::for_each(mandatorySettings.begin(), mandatorySettings.end(),
            [this](const std::string setting){
                if (settings_.find(setting) == settings_.end())
                    throw InvalidArgument(R"(Missing mandatory setting ')"
                        + setting + R"(' in )" + settingFile_);
            }
        );
    }

    void Engine::initRenderTarget() {
        auto desktopWidth = sf::VideoMode::getDesktopMode().width;
        auto desktopHeight = sf::VideoMode::getDesktopMode().height;
        auto width = std::stof(settings_["width"]);
        auto height = std::stof(settings_["height"]);
        auto isFullscreen = static_cast<bool>(std::stoi(settings_["fullscreen"]));
        if (isFullscreen || (width >= desktopWidth && height >= desktopHeight)){
            window_.create(settings_["title"], desktopWidth, desktopHeight, Gui::Window::Style::Fullscreen);
        } else {
            if (width > desktopWidth)
                width = desktopWidth;
            if (height > desktopHeight)
                height = desktopHeight;
            window_.create(settings_["title"], width, height, Gui::Window::Style::Close);
        }
    }

    void Engine::run() {
        if (!isRunning_ && !statesManager_.isEmpty()) {
            isRunning_ = true;
            auto const frameTime = 1.0f / 60.0f;
            auto clock = Utility::Clock();
            auto deltaTime = clock.restart();
            while (window_.isOpen() && isRunning_ && !statesManager_.isEmpty()) {
                window_.processEvents();
                if (deltaTime >= frameTime) { //Fixed time step update
                    if (auto currentState = statesManager_.getCurrentState(); currentState)
                        currentState->fixedUpdate(deltaTime);
                    deltaTime = 0.0;
                }
                update();
                render();
                window_.display();
                deltaTime += clock.restart();
            }
        }
    }

    void Engine::stop() {
        isRunning_ = false;
    }

    const std::shared_ptr<const GuiFactory> & IME::Engine::getGuiFactory() const {
        return guiFactory_;
    }

    void Engine::update() {
        if (!isRunning_)
            window_.close();
        else
            statesManager_.getCurrentState()->update();
    }

    void Engine::render() {
        if (isRunning_)
            statesManager_.getCurrentState()->render(window_);
    }

    bool Engine::isRunning() const {
        return isRunning_;
    }

    const Gui::Window &Engine::getRenderTarget() const {
        return window_;
    }

    StateManager &Engine::getStateManager() {
        return statesManager_;
    }

    const std::string &Engine::getAppName() const {
        return appName_;
    }

    Engine::~Engine() = default;
}
