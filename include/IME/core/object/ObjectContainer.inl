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

template <typename T>
inline ObjectContainer<T>::ObjectContainer() {
    static_assert(std::is_base_of<Object, T>::value,"An ObjectContainer class can only store instances of classes derived from Object class");
}

template <typename T>
inline T* ObjectContainer<T>::addObject(ObjectPtr object, const std::string& group) {
    IME_ASSERT(object, "Object added to a container cannot be a nullptr");

    if (group == "none") {
        objects_.push_back(std::move(object));
        return objects_.back().get();
    } else {
        if (hasGroup(group))
            return groups_.at(group)->addObject(std::move(object));
        else {
            return createGroup(group).addObject(std::move(object));
        }
    }
}

template<typename T>
inline T* ObjectContainer<T>::findByTag(const std::string& tag) {
    return const_cast<T*>(std::as_const(*this).findByTag(tag));
}

template<typename T>
inline const T* ObjectContainer<T>::findByTag(const std::string& tag) const {
    return findIf([&tag](const T* object) {
        return object->getTag() == tag;
    });
}

template <typename T>
template <typename U>
inline U* ObjectContainer<T>::findByTag(const std::string& tag) {
    return dynamic_cast<U*>(const_cast<T*>(std::as_const(*this).findByTag(tag)));
}

template <typename T>
template <typename U>
inline const U* ObjectContainer<T>::findByTag(const std::string& tag) const {
    return dynamic_cast<U*>(const_cast<T*>(std::as_const(*this).findByTag(tag)));
}

template<typename T>
inline T* ObjectContainer<T>::findById(unsigned int id) {
    return const_cast<T*>(std::as_const(*this).findById(id));
}

template<typename T>
inline const T* ObjectContainer<T>::findById(unsigned int id) const {
    return findIf([id](const T* object) {
        return object->getObjectId() == id;
    });
}

template <typename T>
template <typename U>
inline U* ObjectContainer<T>::findById(unsigned int id) {
    return dynamic_cast<U*>(const_cast<T*>(std::as_const(*this).findById(id)));
}

template <typename T>
template <typename U>
inline const U* ObjectContainer<T>::findById(unsigned int id) const {
    return dynamic_cast<const U*>(std::as_const(*this).findById(id));
}

template <typename T>
inline T* ObjectContainer<T>::findIf(const Predicate& predicate) {
    return const_cast<T*>(std::as_const(*this).findIf(predicate));
}

template <typename T>
inline const T* ObjectContainer<T>::findIf(const Predicate& predicate) const {
    auto found = std::find_if(objects_.begin(), objects_.end(), [&predicate](const ObjectPtr& uniquePtr) {
        return predicate(uniquePtr.get());
    });

    if (found != objects_.end())
        return found->get();

    // Perform recursive search
    for (const auto& group : groups_) {
        auto object = group.second->findIf(predicate);
        if (object)
            return object;
    }

    return nullptr;
}

template <typename T>
inline void ObjectContainer<T>::removeByTag(const std::string& tag) {
    removeIf([&tag](const T* object) {
        return object->getTag() == tag;
    });
}

template <typename T>
inline void ObjectContainer<T>::removeById(unsigned int id) {
    removeIf([id](const T* object) {
        return object->getObjectId() == id;
    });
}

template <typename T>
inline bool ObjectContainer<T>::remove(T* object) {
    if (object == nullptr)
        return false;

    for (auto iter = objects_.begin(); iter != objects_.end(); ++iter) {
        if ((*iter)->getObjectId() == object->getObjectId()) {
            objects_.erase(iter);
            return true;
        }
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
inline void ObjectContainer<T>::removeIf(const Predicate& predicate) {
    objects_.erase(std::remove_if(objects_.begin(), objects_.end(), [&predicate](const ObjectPtr& uniquePtr) {
        return predicate(uniquePtr.get());
    }), objects_.end());

    // Perform recursive remove
    for (const auto& group : groups_)
        group.second->removeIf(predicate);
}

template <typename T>
inline void ObjectContainer<T>::removeAll() {
    objects_.clear();
    groups_.clear();
}

template <typename T>
inline std::size_t ObjectContainer<T>::getCount() const {
    std::size_t count = 0;
    for (const auto& group : groups_)
        count += group.second->getCount();

    return objects_.size() + count;
}

template <typename T>
inline ObjectContainer<T>& ObjectContainer<T>::createGroup(const std::string& name) {
    IME_ASSERT(!hasGroup(name), "The group \"" + name + "\" already exists in the container");
    return *(groups_.insert({name, std::make_unique<ObjectContainer<T>>()}).first->second);
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
inline void ObjectContainer<T>::forEach(const Callback<T*>& callback) const {
    forEachNotInGroup(callback);

    // Recursively apply callback
    std::for_each(groups_.begin(), groups_.end(), [&callback] (auto& pair) {
        pair.second->forEach(callback);
    });
}

template <typename T>
inline void ObjectContainer<T>::forEachInGroup(const std::string& name, const Callback<T*>& callback) const {
    if (hasGroup(name))
        groups_.at(name)->forEach(callback);
}

template <typename T>
inline void ObjectContainer<T>::forEachNotInGroup(const Callback<T*>& callback) const {
    std::for_each(objects_.begin(), objects_.end(), [&callback](const std::unique_ptr<T>& uniquePtr) {
        callback(uniquePtr.get());
    });
}
