#include "IME/core/resources/ResourceManager.h"
#include "IME/common/Common.h"
#include <algorithm>

namespace IME{
    using Common::FilePath;

    ResourceHolder<sf::Texture> ResourceManager::texturesHolder_{FilePath::TEXTURES_PATH, {}};
    ResourceHolder<sf::SoundBuffer> ResourceManager::soundBuffersHolder_{FilePath::SOUNDS_PATH, {}};
    ResourceHolder<sf::Font> ResourceManager::fontsHolder_{FilePath::FONTS_PATH, {}};
    ResourceHolder<sf::Image> ResourceManager::imagesHolder_{FilePath::TEXTURES_PATH, {}};
    ResourceHolder<sf::Music> ResourceManager::musicHolder_{FilePath::MUSIC_PATH, {}};

    void ResourceManager::loadFromFile(ResourceType type, const std::string &filename){
        switch (type){
            case ResourceType::Texture:
                texturesHolder_.loadFromFile(filename);
                break;
            case ResourceType::SoundBuffer:
                soundBuffersHolder_.loadFromFile(filename);
                break;
            case ResourceType::Image:
                imagesHolder_.loadFromFile(filename);
                break;
            case ResourceType::Font:
                fontsHolder_.loadFromFile(filename);
                break;
            case ResourceType::Music:
                musicHolder_.loadFromFile(filename);
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
        return *(fontsHolder_.get(fileName));
    }

    const sf::Texture &ResourceManager::getTexture(const std::string &fileName) {
        return *(texturesHolder_.get(fileName));
    }

    const sf::Image &ResourceManager::getImage(const std::string &fileName) {
        return *(imagesHolder_.get(fileName));
    }

    const sf::SoundBuffer &ResourceManager::getSoundBuffer(const std::string &fileName) {
        return *(soundBuffersHolder_.get(fileName));
    }

    std::shared_ptr<sf::Music> ResourceManager::getMusic(const std::string& filename){
        return musicHolder_.get(filename);
    }

    int ResourceManager::getUseCount(ResourceType type, const std::string &filename) {
        switch (type) {
            case ResourceType::Texture:
                return texturesHolder_.getUseCountFor(filename);
            case ResourceType::Font:
                return fontsHolder_.getUseCountFor(filename);
            case ResourceType::Image:
                return imagesHolder_.getUseCountFor(filename);
            case ResourceType::SoundBuffer:
                return soundBuffersHolder_.getUseCountFor(filename);
            case ResourceType::Music:
                return musicHolder_.getUseCountFor(filename);
        }
    }
}
