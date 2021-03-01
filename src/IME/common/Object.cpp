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

#include "IME/common/Object.h"

namespace ime {
    namespace {
        auto static objectIdCounter = 0u;
    }

    Object::Object() :
        id_{objectIdCounter++}
    {}

    Object::Object(const Object& other) :
        id_{objectIdCounter++},
        name_{other.name_},
        destructionListeners_{other.destructionListeners_}
    {}

    Object &Object::operator=(const Object & other) {
        // We don't want to assign the object id, each must have a unique one
        if (this != &other) {
            name_ = other.name_;
            destructionListeners_ = other.destructionListeners_;
        }

        return *this;
    }

    void Object::setName(const std::string &name) {
        name_ = name;
    }

    const std::string &Object::getName() const {
        return name_;
    }

    unsigned int Object::getObjectId() const {
        return id_;
    }

    std::string Object::getClassType() const {
        return "Object";
    }

    int Object::onDestruction(Object::DestructionCallback callback) {
        static auto callbackIdCounter = 0u;
        destructionListeners_.insert({++callbackIdCounter, std::move(callback)});
        return callbackIdCounter;
    }

    bool Object::removeDestructionListener(int id) {
        if (destructionListeners_.find(id) != destructionListeners_.end()) {
            destructionListeners_.erase(id);
            return true;
        }

        return false;
    }

    bool Object::operator==(const Object &rhs) {
        return id_ == rhs.id_;
    }

    bool Object::operator!=(const Object &rhs) {
        return id_ != rhs.id_;
    }

    Object::~Object() {
        for (auto& callback : destructionListeners_)
            callback.second();
    }
}
