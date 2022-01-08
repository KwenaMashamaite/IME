////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/core/resources/ResourceLoader.h"
#include "IME/core/resources/ResourceManager.h"

namespace ime {
    bool ResourceLoader::loadFromFile(ResourceType type, const std::string &filename) {
        return ResourceManager::getInstance()->loadFromFile(type, filename);
    }

    void ResourceLoader::setPath(ResourceType type, const std::string &path) {
        ResourceManager::getInstance()->setPathFor(type, path);
    }

    std::string ResourceLoader::getPath(ResourceType type) {
        return ime::ResourceManager::getInstance()->getPathFor(type);
    }

    void ResourceLoader::loadFromFile(ResourceType type,
        const ResourceLoader::FileNameList &filenames,
        const ResourceLoader::Callback& callback)
    {
        ResourceManager::getInstance()->loadFromFile(type, filenames, callback);
    }

    bool ResourceLoader::unload(ResourceType type, const std::string &filename) {
        return ResourceManager::getInstance()->unload(type, filename);
    }

    void ResourceLoader::unloadAll(ResourceType type) {
        ResourceManager::getInstance()->unloadAll(type);
    }

    void ResourceLoader::unloadAll() {
        ResourceManager::getInstance()->unloadAll();
    }
}

