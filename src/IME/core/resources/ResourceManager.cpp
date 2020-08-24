#include "IME/core/resources/ResourceManager.h"
#include <algorithm>

namespace IME {
    ResourceManager::ResourceManager()
        : fonts_(""), textures_(""), images_(""), soundBuffers_(""), music_("")
    {}

    void ResourceManager::loadFromFile(ResourceType type, const std::string &filename){
        switch (type) {
            case ResourceType::Texture:
                textures_.loadFromFile(filename);
                break;
            case ResourceType::SoundBuffer:
                soundBuffers_.loadFromFile(filename);
                break;
            case ResourceType::Image:
                images_.loadFromFile(filename);
                break;
            case ResourceType::Font:
                fonts_.loadFromFile(filename);
                break;
            case ResourceType::Music:
                music_.loadFromFile(filename);
                break;
        }
    }

    void ResourceManager::loadFromFile(ResourceType type,
           const std::initializer_list<std::string>& filenames)
    {
        std::for_each(filenames.begin(), filenames.end(),
            [=](const std::string& filename) {
                loadFromFile(type, filename);
        });
    }

    const sf::Font &ResourceManager::getFont(const std::string &fileName) {
        return *(fonts_.get(fileName));
    }

    const sf::Texture &ResourceManager::getTexture(const std::string &fileName) {
        return *(textures_.get(fileName));
    }

    const sf::Image &ResourceManager::getImage(const std::string &fileName) {
        return *(images_.get(fileName));
    }

    const sf::SoundBuffer &ResourceManager::getSoundBuffer(const std::string &fileName) {
        return *(soundBuffers_.get(fileName));
    }

    std::shared_ptr<sf::Music> ResourceManager::getMusic(const std::string& filename) {
        return music_.get(filename);
    }

    bool ResourceManager::unload(ResourceType type, const std::string &filename) {
        switch (type) {
            case ResourceType::Texture:
                return textures_.unload(filename);
            case ResourceType::Font:
                return fonts_.unload(filename);
            case ResourceType::Image:
                return images_.unload(filename);
            case ResourceType::SoundBuffer:
                return soundBuffers_.unload(filename);
            case ResourceType::Music:
                return music_.unload(filename);
        }
    }

    int ResourceManager::getUseCount(ResourceType type, const std::string &filename) {
        switch (type) {
            case ResourceType::Texture:
                return textures_.getUseCountFor(filename);
            case ResourceType::Font:
                return fonts_.getUseCountFor(filename);
            case ResourceType::Image:
                return images_.getUseCountFor(filename);
            case ResourceType::SoundBuffer:
                return soundBuffers_.getUseCountFor(filename);
            case ResourceType::Music:
                return music_.getUseCountFor(filename);
        }
    }

    void ResourceManager::setPath(ResourceType type, const std::string& path) {
        switch (type) {
            case ResourceType::Texture:
                textures_.setPath(path);
                break;
            case ResourceType::Font:
                fonts_.setPath(path);
                break;
            case ResourceType::Image:
                images_.setPath(path);
                break;
            case ResourceType::SoundBuffer:
                soundBuffers_.setPath(path);
                break;
            case ResourceType::Music:
                music_.setPath(path);
                break;
        }
    }

    std::shared_ptr<ResourceManager> ResourceManager::getInstance() {
        static std::weak_ptr<ResourceManager> instance_;
        if (const auto result = instance_.lock())
            return result;
        return (instance_ = std::shared_ptr<ResourceManager>(new ResourceManager())).lock();
    }
}
