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
inline void ObjectContainer<T>::addObject(ObjectPtr object) {
    IME_ASSERT(object, "Cannot add a nullptr to an object container");
    objects_.push_back(std::move(object));
}

template<typename T>
inline typename ObjectContainer<T>::ObjectPtr ObjectContainer<T>::findByName(const std::string& name) {
    return std::as_const(*this).findByName(name);
}

template<typename T>
inline typename ObjectContainer<T>::ObjectPtr ObjectContainer<T>::findByName(const std::string& name) const {
    return findIf([&name](const constObjectPtr object) {
        return object->getName() == name;
    });
}

template <typename T>
template <typename U>
inline std::shared_ptr<U> ObjectContainer<T>::findByName(const std::string& name) {
    return std::dynamic_pointer_cast<U>(std::as_const(*this).findByName(name));
}

template <typename T>
template <typename U>
inline std::shared_ptr<const U> ObjectContainer<T>::findByName(const std::string& name) const {
    return std::dynamic_pointer_cast<U>(std::as_const(*this).findByName(name));
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
    std::as_const(*this).findIf(predicate);
}

template <typename T>
inline const typename ObjectContainer<T>::ObjectPtr ObjectContainer<T>::findIf(Predicate predicate) const {
    auto found = std::find_if(objects_.begin(), objects_.end(), predicate);

    if (found != objects_.cend())
        return *found;

    return nullptr;
}

template <typename T>
inline bool ObjectContainer<T>::removeByName(const std::string& name) {
    return removeIf([&name](const constObjectPtr object) {
        return object->getName() == name;
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

    return false;
}

template <typename T>
inline bool ObjectContainer<T>::removeIf(Predicate predicate) {
    auto prevSize = objects_.size();
    objects_.erase(std::remove_if(objects_.begin(), objects_.end(), predicate), objects_.end());
    return objects_.size() < prevSize;
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
inline void ObjectContainer<T>::forEach(Callback<ObjectPtr> callback) {
    std::for_each(objects_.begin(), objects_.end(), callback);
}

template <typename T>
inline typename ObjectContainer<T>::constIterator ObjectContainer<T>::cbegin() const {
    return objects_.cbegin();
}

template <typename T>
inline typename ObjectContainer<T>::constIterator ObjectContainer<T>::cend() const {
    return objects_.cend();
}
