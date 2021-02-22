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

#include "IME/core/scene/GameObjectContainer.h"

namespace ime {
    GameObject::sharedPtr GameObjectContainer::getObjectById(unsigned int id) {
        return std::as_const(*this).getObjectById(id);
    }

    GameObject::sharedPtr GameObjectContainer::getObjectById(unsigned int id) const {
        return findIf([id](const constItemPtr gameObject) {
            return gameObject->getObjectId() == id;
        });
    }

    GameObject::sharedPtr GameObjectContainer::getObjectByName(const std::string &name) {
        return std::as_const(*this).getObjectByName(name);
    }

    const GameObject::sharedPtr GameObjectContainer::getObjectByName(const std::string &name) const {
        return findIf([&name](const constItemPtr gameObject) {
            return gameObject->getName() == name;
        });
    }

    bool GameObjectContainer::removeObjectWithId(unsigned int id) {
        return removeIf([id](const constItemPtr gameObject) {
            return gameObject->getObjectId() == id;
        });
    }

    bool GameObjectContainer::removeObjectWithName(const std::string &name) {
        return removeIf([&name](const constItemPtr gameObject) {
            return gameObject->getName() == name;
        });
    }
}

