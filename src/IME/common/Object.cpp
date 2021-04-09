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
        tag_{other.tag_},
        eventEmitter_{other.eventEmitter_}
    {}

    Object &Object::operator=(const Object & other) {
        // We don't want to assign the object id, each must have a unique one
        if (this != &other) {
            tag_ = other.tag_;
            eventEmitter_ = other.eventEmitter_;
        }

        return *this;
    }

    void Object::setTag(const std::string &tag) {
        tag_ = tag;
        emitChange(Property{"tag", tag_});
    }

    const std::string &Object::getTag() const {
        return tag_;
    }

    unsigned int Object::getObjectId() const {
        return id_;
    }

    std::string Object::getClassType() const {
        return "Object";
    }

    int Object::onPropertyChange(const std::string &property, const Callback<Property>& callback) {
        return eventEmitter_.on(property + "Change", callback);
    }

    int Object::onEvent(const std::string &event, const Callback<> &callback) {
        return eventEmitter_.on(event, callback);
    }

    void Object::onPropertyChange(const Callback<Property> &callback) {
        onPropertyChange_ = callback;
    }

    bool Object::unsubscribe(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }

    int Object::onDestruction(const Callback<>& callback) {
        return eventEmitter_.addEventListener("destruction", callback);
    }

    bool Object::removeDestructionListener(int id) {
        return eventEmitter_.removeEventListener("destruction", id);
    }

    bool Object::operator==(const Object &rhs) const {
        return id_ == rhs.id_;
    }

    bool Object::operator!=(const Object &rhs) const {
        return id_ != rhs.id_;
    }

    void Object::emitChange(const Property &property) {
        eventEmitter_.emit(property.getName() + "Change", property);
        if (onPropertyChange_)
            onPropertyChange_(property);
    }

    void Object::emit(const std::string &event) {
        eventEmitter_.emit(event);
    }

    Object::~Object() {
        eventEmitter_.emit("destruction");
    }
}
