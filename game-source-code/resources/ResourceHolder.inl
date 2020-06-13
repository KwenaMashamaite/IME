#include "ResourceHolder.h"
#include "exceptions/Exceptions.h"
#include <utility>

template <class T>
ResourceHolder<T>::ResourceHolder(const std::string& filePath, PassKey)
    : filePath_(filePath)
{}

template <class T>
void ResourceHolder<T>::load(const std::string& filename){
    auto resource = T();
    if (!resource.loadFromFile(filePath_ + filename))
        throw FileNotFound("cannot find file " + filePath_ + filename);
    resourceHolder_.insert(
        std::make_pair(filename, std::move(std::make_shared<T>(resource)))
    );
}

template <>
inline void ResourceHolder<sf::Music>::load(const std::string &filename){
    auto music = std::make_shared<sf::Music>();
    if(!(*music).openFromFile(filePath_ + filename))
        throw FileNotFound("cannot find file " + filePath_ + filename);
    resourceHolder_.insert(std::make_pair(filename, std::move(music)));
}

template <typename T>
std::shared_ptr<T> ResourceHolder<T>::get(const std::string &filename) {
    auto pairFound = resourceHolder_.find(filename);
    if(pairFound != resourceHolder_.end())
        return (pairFound->second);
    else{
        load(filename); //Either throws an exception or succeeds
        return get(filename); //Return resource that just got loaded
    }
}
