#include "ResourceHolder.h"
#include "exceptions/Exceptions.h"
#include <utility>

template <class T>
ResourceHolder<T>::ResourceHolder(const std::string& filePath, PassKey)
    : filePath_(filePath)
{}

template <class T>
void ResourceHolder<T>::load(const std::string& filename){
    auto resource = std::make_shared<T>();
    if (!(*resource).loadFromFile(filePath_ + filename))
        throw FileNotFound("cannot find file " + filePath_ + filename);
    resourceHolder_.insert(std::make_pair(filename, std::move(resource)));
}

template <> //Function template specialization (sf::Music is streamed from disk rather than loaded into memory)
inline void ResourceHolder<sf::Music>::load(const std::string &filename){
    auto music = std::make_shared<sf::Music>();
    if(!(*music).openFromFile(filePath_ + filename))
        throw FileNotFound("cannot find file " + filePath_ + filename);
    resourceHolder_.insert(std::make_pair(filename, std::move(music)));
}

template <typename T>
std::shared_ptr<T> ResourceHolder<T>::get(const std::string &filename) {
    auto found = resourceHolder_.find(filename);
    if (found != resourceHolder_.end())
        return found->second;
    else{
        load(filename); //Either throws an exception or succeeds
        return get(filename); //Return resource that just got loaded
    }
}
