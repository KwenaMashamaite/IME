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

#include "IME/core/object/Object.h"
#include "IME/utility/Helpers.h"

namespace ime {
    namespace {
        unsigned int objectIdCounter = 0u;
    }

    Object::Object() :
        id_{objectIdCounter++}
    {}

    Object::Object(const Object& other) :
        eventEmitter_{other.eventEmitter_},
        id_{objectIdCounter++},
        tag_{other.tag_}
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
        if (tag_ != tag) {
            tag_ = tag;
            emitChange(Property{"tag", tag_});
        }
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

    int Object::onPropertyChange(const std::string &property, const Callback<Property>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "Object_" + property + "Change", callback, oneTime);
    }

    int Object::onPropertyChange(const Callback<Property> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "Object_propertyChange", callback, oneTime);
    }

    void Object::suspendedEventListener(int id, bool suspend) {
        eventEmitter_.suspendEventListener(id, suspend);
    }

    bool Object::isEventListenerSuspended(int id) const {
        return eventEmitter_.isEventListenerSuspended(id);
    }

    bool Object::removeEventListener(const std::string &event, int id) {
        if ((eventEmitter_.removeEventListener("Object_" + event, id)) ||
            (eventEmitter_.removeEventListener("Object_" + event + "Change", id)))
        {
            return true;
        }
        else
            return eventEmitter_.removeEventListener(event, id);
    }

    bool Object::removeEventListener(int id) {
        return eventEmitter_.removeEventListener(id);
    }

    int Object::onDestruction(const Callback<>& callback) {
        return eventEmitter_.addOnceEventListener("Object_destruction", callback);
    }

    bool Object::isSameObjectAs(const Object &other) const {
        return id_ == other.id_;
    }

    void Object::emitChange(const Property &property) {
        eventEmitter_.emit("Object_" + property.getName() + "Change", property);
        eventEmitter_.emit("Object_propertyChange", property);
    }

    void Object::emitDestruction() {
        eventEmitter_.emit("Object_destruction");
    }

    Object::~Object() {
        emitDestruction();
    }
}
