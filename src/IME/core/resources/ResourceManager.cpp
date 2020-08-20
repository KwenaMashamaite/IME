#include "IME/core/resources/ResourceManager.h"
#include "IME/common/Definitions.h"
#include <algorithm>

using IME::Definitions::FilePath;

namespace IME {
    ResourceHolder<sf::Texture> ResourceManager::textures_{FilePath::TexturesPath};
    ResourceHolder<sf::SoundBuffer> ResourceManager::soundBuffers_{FilePath::SoundEffectsPath};
    ResourceHolder<sf::Font> ResourceManager::fonts_{FilePath::FontsPath};
    ResourceHolder<sf::Image> ResourceManager::images_{FilePath::ImagesPath};
    ResourceHolder<sf::Music> ResourceManager::music_{FilePath::MusicPath};

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
}
