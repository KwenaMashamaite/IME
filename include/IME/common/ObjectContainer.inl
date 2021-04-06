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

template <typename T>
inline ObjectContainer<T>::ObjectContainer() {
    static_assert(std::is_base_of<Object, T>::value,"An ObjectContainer class can only store instances of classes derived from Object class");
}

template <typename T>
inline void ObjectContainer<T>::addObject(ObjectPtr object, const std::string& group) {
    IME_ASSERT(object, "Cannot add a nullptr to an object container");

    // Prevent duplicates in the container
    if (findById(object->getObjectId())) {
        IME_PRINT_WARNING("Object ignored, it already exists in the container");
        return;
    }

    if (group == "none") {
        objects_.push_back(std::move(object));
    } else {
        if (hasGroup(group))
            groups_.at(group)->addObject(std::move(object));
        else {
            createGroup(group).addObject(std::move(object));
        }
    }
}

template<typename T>
inline typename ObjectContainer<T>::ObjectPtr ObjectContainer<T>::findByTag(const std::string& tag) {
    return std::as_const(*this).findByTag(tag);
}

template<typename T>
inline typename ObjectContainer<T>::ObjectPtr ObjectContainer<T>::findByTag(const std::string& tag) const {
    return findIf([&tag](const constObjectPtr object) {
        return object->getTag() == tag;
    });
}

template <typename T>
template <typename U>
inline std::shared_ptr<U> ObjectContainer<T>::findByTag(const std::string& tag) {
    return std::dynamic_pointer_cast<U>(std::as_const(*this).findByTag(tag));
}

template <typename T>
template <typename U>
inline std::shared_ptr<const U> ObjectContainer<T>::findByTag(const std::string& tag) const {
    return std::dynamic_pointer_cast<U>(std::as_const(*this).findByTag(tag));
}

template<typename T>
inline typename ObjectContainer<T>::ObjectPtr ObjectContainer<T>::findById(unsigned int id) {
    return std::as_const(*this).findById(id);
}

template<typename T>
inline typename ObjectContainer<T>::ObjectPtr ObjectContainer<T>::findById(unsigned int id) const {
    return findIf([id](const constObjectPtr object) {
        return object->getObjectId() == id;
    });
}

template <typename T>
template <typename U>
inline std::shared_ptr<U> ObjectContainer<T>::findById(unsigned int id) {
    return std::dynamic_pointer_cast<U>(std::as_const(*this).findById(id));
}

template <typename T>
template <typename U>
inline std::shared_ptr<const U> ObjectContainer<T>::findById(unsigned int id) const {
    return std::dynamic_pointer_cast<U>(std::as_const(*this).findById(id));
}

template <typename T>
inline typename ObjectContainer<T>::ObjectPtr ObjectContainer<T>::findIf(Predicate predicate) {
    return std::as_const(*this).findIf(predicate);
}

template <typename T>
inline const typename ObjectContainer<T>::ObjectPtr ObjectContainer<T>::findIf(Predicate predicate) const {
    auto found = std::find_if(objects_.begin(), objects_.end(), predicate);

    if (found != objects_.end())
        return *found;

    // Perform recursive search
    for (const auto& group : groups_) {
        auto object = group.second->findIf(predicate);
        if (object)
            return object;
    }

    return nullptr;
}

template <typename T>
inline bool ObjectContainer<T>::removeByTag(const std::string& tag) {
    return removeIf([&tag](const constObjectPtr object) {
        return object->getTag() == tag;
    });
}

template <typename T>
inline bool ObjectContainer<T>::removeById(unsigned int id) {
    return removeIf([id](const constObjectPtr object) {
        return object->getObjectId() == id;
    });
}

template <typename T>
inline bool ObjectContainer<T>::remove(ObjectPtr object) {
    if (object == nullptr)
        return false;

    if (auto found = std::find(objects_.begin(), objects_.end(), object); found != objects_.end()) {
        objects_.erase(found);
        return true;
    }

    // Perform recursive remove
    for (const auto& group : groups_) {
        auto removed = group.second->remove(object);
        if (removed)
            return true;
    }

    return false;
}

template <typename T>
inline void ObjectContainer<T>::removeIf(Predicate predicate) {
    objects_.erase(std::remove_if(objects_.begin(), objects_.end(), predicate), objects_.end());

    // Perform recursive remove
    for (const auto& group : groups_)
        group.second->removeIf(predicate);
}

template <typename T>
inline void ObjectContainer<T>::removeAll() {
    objects_.clear();
}

template <typename T>
inline std::size_t ObjectContainer<T>::getCount() const {
    return objects_.size();
}

template <typename T>
inline ObjectContainer<T>& ObjectContainer<T>::createGroup(const std::string& name) {
    IME_ASSERT(!hasGroup(name), "The group \"" + name + "\" already exists in the container");
    return *(groups_.insert({name, std::make_shared<ObjectContainer<T>>()}).first->second);
}

template <typename T>
inline ObjectContainer<T>& ObjectContainer<T>::getGroup(const std::string& name) const {
    IME_ASSERT(hasGroup(name), "The group \"" + name + "\" does exists in the container");
    return *(groups_.at(name));
}

template <typename T>
inline bool ObjectContainer<T>::hasGroup(const std::string& name) const {
    return groups_.find(name) != groups_.end();
}

template <typename T>
inline bool ObjectContainer<T>::removeGroup(const std::string& name) {
    if (hasGroup(name)) {
        groups_.erase(name);
        return true;
    }

    return false;
}

template <typename T>
inline void ObjectContainer<T>::removeAllGroups() {
    groups_.clear();
}

template <typename T>
inline void ObjectContainer<T>::forEach(Callback<ObjectPtr> callback) {
    std::for_each(objects_.begin(), objects_.end(), callback);
}

template <typename T>
inline void ObjectContainer<T>::forEachInGroup(const std::string& name, Callback<ObjectPtr> callback) {
    if (hasGroup(name))
        groups_.at(name)->forEach(std::move(callback));
}
