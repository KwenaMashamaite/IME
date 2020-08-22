template<class T>
ResourceHolder<T>::ResourceHolder(const std::string &filePath)
    : filePath_(filePath) {}

template<class T>
void ResourceHolder<T>::setPath(const std::string &filepath) {
    filePath_ = filepath;
}

template<class T>
bool ResourceHolder<T>::loadFromFile(const std::string &filename) {
    auto resource = std::make_shared<T>();
    if (!(*resource).loadFromFile(filePath_ + filename))
        throw FileNotFound(R"(cannot find file ")" + filePath_ + filename + R"(")");
    return resourceHolder_.insert({filename, std::move(resource)}).second;
}

//sf::Music doesn't support "loadFromFile". The music is streamed directly from the disk
template<>
inline bool ResourceHolder<sf::Music>::loadFromFile(const std::string &filename) {
    auto music = std::make_shared<sf::Music>();
    if (!(*music).openFromFile(filePath_ + filename))
        throw FileNotFound(R"(cannot find file ")" + filePath_ + filename + R"(")");
    return resourceHolder_.insert({filename, std::move(music)}).second;
}

template<class T>
bool ResourceHolder<T>::unload(const std::string &filename) {
    if (getUseCountFor(filename) == 0) //Destroy resource only if its not being used outside the class
        return resourceHolder_.erase(filename);
    return false;
}

template<class T>
std::shared_ptr<T> ResourceHolder<T>::get(const std::string &filename) {
    if (!hasResource(filename))
        loadFromFile(filename); //Either throws an exception or succeeds
    return resourceHolder_.at(filename);
}

template<class T>
unsigned int ResourceHolder<T>::getSize() const {
    return resourceHolder_.size();
}

template<class T>
int ResourceHolder<T>::getUseCountFor(const std::string &filename) const {
    if (hasResource(filename)) {
        auto useCount = resourceHolder_.at(filename).use_count();
        if (useCount == 1) // No external pointers to the resource, only the internal pointer
            return 0;
        return useCount;
    }
    return -1;
}

template<class T>
const std::string &ResourceHolder<T>::getPath() const {
    return filePath_;
}

template<class T>
bool ResourceHolder<T>::hasResource(const std::string &filename) const {
    return Utility::findIn(resourceHolder_, filename);
}
