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

#include "IME/core/resources/ResourceManager.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>
#include <algorithm>

namespace ime {
    ResourceManager::ResourceManager() :
        fonts_(""),
        images_(""),
        textures_(""),
        soundBuffers_("")
    {}

    bool ResourceManager::loadFromFile(ResourceType type, const std::string &filename){
        switch (type) {
            case ResourceType::Texture:
                return textures_.loadFromFile(filename);
            case ResourceType::SoundEffect:
                return soundBuffers_.loadFromFile(filename);
            case ResourceType::Image:
                return images_.loadFromFile(filename);
            case ResourceType::Font:
                return fonts_.loadFromFile(filename);
            case ResourceType::Music:{
                // We can't use ResourceHolder<sf::Music> because it doesnt support loadFromFile
                if (musicHolder_.find(filename) != musicHolder_.end()) //File already loaded
                    return true;

                auto music = std::make_shared<sf::Music>();
                if (!music->openFromFile(musicPath_ + filename))
                    throw FileNotFound("cannot find file \"" + musicPath_ + filename + "\"");

                return musicHolder_.insert({filename, std::move(music)}).second;
            } default:
                return false;
        }
    }

    void ResourceManager::loadFromFile(ResourceType type,
        const std::initializer_list<std::string>& filenames,
        const Callback<const std::string&>& callback)
    {
        std::for_each(filenames.begin(), filenames.end(),
            [=](const std::string& filename) {
                if (loadFromFile(type, filename) && callback)
                    callback(filename);
        });
    }

    const sf::Font &ResourceManager::getFont(const std::string &fileName) {
        return *(fonts_.get(fileName));
    }

    const Texture &ResourceManager::getTexture(const std::string &fileName) {
        return *(textures_.get(fileName));
    }

    const sf::Image &ResourceManager::getImage(const std::string &fileName) {
        return *(images_.get(fileName));
    }

    const sf::SoundBuffer &ResourceManager::getSoundBuffer(const std::string &fileName) {
        return *(soundBuffers_.get(fileName));
    }

    std::shared_ptr<sf::Music> ResourceManager::getMusic(const std::string &fileName) {
        try {
            return musicHolder_.at(fileName);
        } catch (...) {
            loadFromFile(ResourceType::Music, fileName);
            return musicHolder_[fileName];
        }
    }

    bool ResourceManager::unload(ResourceType type, const std::string &filename) {
        switch (type) {
            case ResourceType::Texture:
                return textures_.unload(filename);
            case ResourceType::Font:
                return fonts_.unload(filename);
            case ResourceType::Image:
                return images_.unload(filename);
            case ResourceType::SoundEffect:
                return soundBuffers_.unload(filename);
            case ResourceType::Music:
                if (musicHolder_.find(filename) != musicHolder_.end()) {
                    musicHolder_.erase(filename);
                    return true;
                }
                return false;
            default:
                return false;
        }
    }

    void ResourceManager::unloadAll(ResourceType type) {
        switch (type) {
            case ResourceType::Texture:
                textures_.unloadAll();
                break;
            case ResourceType::Font:
                fonts_.unloadAll();
                break;
            case ResourceType::Image:
                images_.unloadAll();
                break;
            case ResourceType::SoundEffect:
                soundBuffers_.unloadAll();
                break;
            case ResourceType::Music:
                musicHolder_.clear();
                break;
        }
    }

    void ResourceManager::unloadAll() {
        fonts_.unloadAll();
        textures_.unloadAll();
        images_.unloadAll();
        soundBuffers_.unloadAll();
        musicHolder_.clear();
    }

    std::string ResourceManager::getPathFor(ResourceType type) const {
        switch (type) {
            case ResourceType::Texture:
                return textures_.getPath();
            case ResourceType::Font:
                return fonts_.getPath();
            case ResourceType::Image:
                return images_.getPath();
            case ResourceType::SoundEffect:
                return soundBuffers_.getPath();
            case ResourceType::Music:
                return musicPath_;
            default:
                return "";
        }
    }

    void ResourceManager::setPathFor(ResourceType type, const std::string& path) {
        switch (type) {
            case ResourceType::Font:
                fonts_.setPath(path);
                break;
            case ResourceType::Texture:
            case ResourceType::Image:
                images_.setPath(path);
                textures_.setPath(path);
                break;
            case ResourceType::SoundEffect:
                soundBuffers_.setPath(path);
                break;
            case ResourceType::Music:
                musicPath_ = path;
                break;
            default:
                return;
        }
    }

    std::shared_ptr<ResourceManager> ResourceManager::getInstance() {
        static std::weak_ptr<ResourceManager> instance_;
        if (const auto result = instance_.lock())
            return result;
        return (instance_ = std::shared_ptr<ResourceManager>(new ResourceManager())).lock();
    }
}
