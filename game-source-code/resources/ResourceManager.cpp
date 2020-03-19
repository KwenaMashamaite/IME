#include "ResourceManager.h"
#include <algorithm>

ResourceHolder<sf::Texture> ResourceManager::texturesHolder_{FilePath::TEXTURES_PATH, {}};
ResourceHolder<sf::SoundBuffer> ResourceManager::soundBuffersHolder_{FilePath::SOUNDS_PATH, {}};
ResourceHolder<sf::Font> ResourceManager::fontsHolder_{FilePath::FONTS_PATH, {}};
ResourceHolder<sf::Image> ResourceManager::imagesHolder_{FilePath::TEXTURES_PATH, {}};
ResourceHolder<sf::Music> ResourceManager::musicHolder_{FilePath::MUSIC_PATH, {}};

void ResourceManager::load(ResourceId identifier, const std::string &filename){
    switch (identifier){
        case ResourceId::TEXTURE:
            texturesHolder_.load(filename);
            break;
        case ResourceId::SOUND_BUFFER:
            soundBuffersHolder_.load(filename);
            break;
        case ResourceId::IMAGE:
            imagesHolder_.load(filename);
            break;
        case ResourceId::FONT:
            fontsHolder_.load(filename);
            break;
        case ResourceId::MUSIC:
            musicHolder_.load(filename);
            break;
    }
}

void ResourceManager::load(ResourceId identifier,
    const std::initializer_list<std::string>& filenames)
{
    std::for_each(filenames.begin(), filenames.end(),
        [=](const std::string& filename) {
            load(identifier, filename);
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