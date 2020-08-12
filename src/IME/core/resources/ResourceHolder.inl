#include "IME/core/exceptions/Exceptions.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <utility>

namespace IME {
    template<class T>
    ResourceHolder<T>::ResourceHolder(const std::string &filePath, PassKey)
        : filePath_(filePath) {}

    template<class T>
    void ResourceHolder<T>::loadFromFile(const std::string &filename) {
        auto resource = std::make_shared<T>();
        if (!(*resource).loadFromFile(filePath_ + filename))
            throw FileNotFound("cannot find file " + filePath_ + filename);
        resourceHolder_.insert(std::make_pair(filename, std::move(resource)));
    }

    //sf::Music is streamed directly from the hard drive
    template<>
    inline void ResourceHolder<sf::Music>::loadFromFile(const std::string &filename) {
        auto music = std::make_shared<sf::Music>();
        if (!(*music).openFromFile(filePath_ + filename))
            throw FileNotFound("cannot find file " + filePath_ + filename);
        resourceHolder_.insert(std::make_pair(filename, std::move(music)));
    }

    template<typename T>
    std::shared_ptr<T> ResourceHolder<T>::get(const std::string &filename) {
        auto found = resourceHolder_.find(filename);
        if (found != resourceHolder_.end())
            return found->second;
        else {
            loadFromFile(filename); //Either throws an exception or succeeds
            return get(filename); //Return resource that just got loaded
        }
    }

    template<class T>
    bool ResourceHolder<T>::remove(const std::string &filename) {
        auto found = resourceHolder_.find(filename);
        if (found != resourceHolder_.end() && found->second.use_count() == 1) {
            resourceHolder_.erase(found);
            return true;
        }
        return false;
    }

    template<class T>
    unsigned int ResourceHolder<T>::getSize() const {
        return resourceHolder_.size();
    }
}