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

#include "IME/common/Object.h"
#include "IME/utility/Helpers.h"

namespace ime {
    namespace {
        auto objectIdCounter = 0u;
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
        return utility::addEventListener(eventEmitter_, property + "Change", callback, oneTime);
    }

    int Object::onPropertyChange(const Callback<Property> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "propertyChange", callback, oneTime);
    }

    int Object::onEvent(const std::string &event, const Callback<> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, event, callback, oneTime);
    }

    void Object::suspendedEventListener(int id, bool suspend) {
        eventEmitter_.suspendEventListener(id, suspend);
    }

    bool Object::isEventListenerSuspended(int id) const {
        return eventEmitter_.isEventListenerSuspended(id);
    }

    bool Object::unsubscribe(const std::string &event, int id) {
        if (eventEmitter_.removeEventListener(event + "Change", id))
            return true;
        else
            return eventEmitter_.removeEventListener(event, id);
    }

    bool Object::unsubscribeAll(const std::string &event) {
        if (eventEmitter_.removeAllEventListeners(event + "Change"))
            return true;
        else
            return eventEmitter_.removeAllEventListeners(event);
    }

    int Object::onDestruction(const Callback<>& callback) {
        return eventEmitter_.addEventListener("destruction", callback);
    }

    int Object::onDestruction(const Callback<> &callback) const {
        return eventEmitter_.addEventListener("destruction", callback);
    }

    bool Object::removeDestructionListener(int id) {
        return eventEmitter_.removeEventListener("destruction", id);
    }

    bool Object::removeDestructionListener(int id) const {
        return eventEmitter_.removeEventListener("destruction", id);
    }

    bool Object::isSameObjectAs(const Object &other) const {
        return id_ == other.id_;
    }

    void Object::emitChange(const Property &property) {
        eventEmitter_.emit(property.getName() + "Change", property);
        eventEmitter_.emit("propertyChange", property);
    }

    void Object::emit(const std::string &event) {
        eventEmitter_.emit(event);
    }

    Object::~Object() = default;
}
