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

template<class T>
ResourceHolder<T>::ResourceHolder(const std::string &filePath)
    : filePath_(filePath) {}

template<class T>
void ResourceHolder<T>::setPath(const std::string &filepath) {
    filePath_ = filepath;
}

template<class T>
bool ResourceHolder<T>::loadFromFile(const std::string &filename) {
    if (hasResource(filename))
        return true;
    auto resource = std::make_shared<T>();
    if (!(*resource).loadFromFile(filePath_ + filename))
        throw FileNotFound(R"(cannot find file ")" + filePath_ + filename + R"(")");
    return resourceHolder_.insert({filename, std::move(resource)}).second;
}

//sf::Music doesn't support "loadFromFile". The music is streamed directly from the disk
template<>
inline bool ResourceHolder<sf::Music>::loadFromFile(const std::string &filename) {
    if (hasResource(filename))
        return true;
    auto music = std::make_shared<sf::Music>();
    if (!(*music).openFromFile(filePath_ + filename))
        throw FileNotFound(R"(cannot find file ")" + filePath_ + filename + R"(")");
    return resourceHolder_.insert({filename, std::move(music)}).second;
}

template<class T>
bool ResourceHolder<T>::unload(const std::string &filename) {
    return resourceHolder_.erase(filename);
}

template<class T>
bool ResourceHolder<T>::unloadAll() {
    if (resourceHolder_.empty())
        return false;

    resourceHolder_.clear();
    return true;
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
const std::string &ResourceHolder<T>::getPath() const {
    return filePath_;
}

template<class T>
bool ResourceHolder<T>::hasResource(const std::string &filename) const {
    return utility::findIn(resourceHolder_, filename);
}
