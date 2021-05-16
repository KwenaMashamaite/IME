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

#ifndef IME_OBJECTCONTAINER_H
#define IME_OBJECTCONTAINER_H

#include "IME/Config.h"
#include "IME/common/Object.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>

namespace ime {
    /**
     * @brief A container for Object instances
     */
    template <typename T>
    class ObjectContainer {
    public:
        using ObjectPtr = std::unique_ptr<T>; //!< Unique object pointer

        template <typename... Args>
        using Callback = std::function<void(Args...)>;
        using Predicate = std::function<bool(const T*)>;

        /**
         * @brief Default constructor
         */
        ObjectContainer();

        /**
         * @brief Copy constructor
         */
        ObjectContainer(const ObjectContainer&) = delete;

        /**
         * @brief Copy assignment operator
         */
        ObjectContainer& operator=(const ObjectContainer&) = delete;

        /**
         * @brief Move constructor
         */
        ObjectContainer(ObjectContainer&&) noexcept = default;

        /**
         * @brief Move assignment operator
         */
        ObjectContainer& operator=(ObjectContainer&&) noexcept = default;
        
        /**
         * @brief Add an object to the container
         * @param object object to be added
         * @param group The name of the group to add the object to
         * @return A pointer to the object after its added to the container
         *
         * If the @a group is not found, it will be created and the @a object
         * will be the first member of it. Groups are useful if you want to
         * refer to objects that are the same or similar as a whole
         *
         * By default the object does not belong to any group
         *
         * @see createGroup
         */
        T* addObject(ObjectPtr object, const std::string& group = "none");

        /**
         * @brief Get an object with a given tag
         * @param tag The tag of the object to be searched
         * @return The object with the given tag or a nullptr if the object
         *         could not be found in the container
         *
         * Note that this function will return the first object it finds with
         * the the given tag
         */
        T* findByTag(const std::string& tag);
        const T* findByTag(const std::string& tag) const;

        /**
         * @brief Get an object with a given tag
         * @param tag The tag of the object to be searched
         * @return The object with the given tag or a nullptr if the object
         *         could not be found in the container or the the object is
         *         found but it is not convertible to type U
         *
         * Note that this function will return the first object it finds with
         * the the given tag. You can use this function to get the derived
         * class type U if T is a base class:
         *
         * @code
         * // The type of rectangle is std::shared_ptr<ime::Shape>
         * auto rectangle = shapeContainer.findByTag("myRect");
         *
         * // The type of rectangle2 is std::shared_ptr<ime::RectangleShape>
         * auto rectangle2 = shapeContainer.findByTag<ime::RectangleShape>("myRect");
         * @endcode
         */
        template<typename U>
        U* findByTag(const std::string& tag);

        template<typename U>
        const U* findByTag(const std::string& tag) const;

        /**
         * @brief Get an object with the given id
         * @param id The id of the object to be retrieved
         * @return The object with the given id or a nullptr if the object
         *         could not be found in the container
         */
        T* findById(unsigned int id);
        const T* findById(unsigned int id) const;

        /**
         * @brief Get an object with the given id
         * @param id The id of the object to be retrieved
         * @return The object with the given id or a nullptr if the object
         *         could not be found in the container or the the object is
         *         found but it is not convertible to type U
         *
         * You can use this function to get the derived class type U if T is
         * a base class
         *
         * @code
         * // The type of rectangle is std::shared_ptr<ime::Shape>
         * auto rectangle = shapeContainer.findById(4);
         *
         * // The type of rectangle2 is std::shared_ptr<ime::RectangleShape>
         * auto rectangle2 = shapeContainer.findById<ime::RectangleShape>(4);
         * @endcode
         */
        template<typename U>
        U* findById(unsigned int id);

        template<typename U>
        const U* findById(unsigned int id) const;

        /**
         * @brief Conditionally find an object in the container
         * @param predicate A function which returns true if the object should
         *                  be returned or false if the search should continue
         * @return The object that matches the found condition or a nullptr if
         *         an object that matches the success condition could not be
         *         found in the container
         */
        T* findIf(const Predicate& predicate);
        const T* findIf(const Predicate& predicate) const;

        /**
         * @brief Remove all objects with the given tag
         * @param tag Tag of the objects to be removed
         *
         * @warning This function will invalidate any pointer(s) to the
         * object once it is removed from the container
         */
        void removeByTag(const std::string& tag);

        /**
         * @brief Remove a game object with the given id
         * @param id The id of the object to be removed
         *
         * @warning This function will invalidate any pointer(s) to the
         * object once it is removed from the container
         */
        void removeById(unsigned int id);

        /**
         * @brief Remove an object from the container
         * @param object The object to be removed
         * @return True if the object was removed or false if the object does
         *         not exist in the container
         *
         * @warning This function will invalidate any pointer(s) to the
         * object once it is removed from the container
         */
        bool remove(T* object);

        /**
         * @brief Conditionally remove objects from the container
         * @param predicate A function which returns true if the object should
         *                 be removed or false if it should not be removed
         *                 from the container
         * @return True if the objects were removed from the container or false
         *         if no objects matched the remove condition
         *
         * Note that this function will remove all objects for which the
         * predicate return true
         *
         * @warning This function will invalidate any pointer(s) to the
         * object once it is removed from the container
         */
        void removeIf(const Predicate& predicate);

        /**
         * @brief Remove all objects from the container
         *
         * @warning This function will invalidate any pointer(s) to the
         * objects once they are removed from the container
         */
        void removeAll();

        /**
         * @brief Get the number of objects in the container
         * @return The number of objects in the container
         */
        std::size_t getCount() const;

        /**
         * @brief Create a group to add objects to
         * @param name The name of the group
         *
         * This function is useful if you want to relate some objects and
         * refer to them as a whole using a common group name instead of
         * using a common tag name and looping though the container to find
         * which objects have a given tag
         *
         * @code
         * auto weapons = objectContainer.createGroup("weapons");
         * weapons.add(knife);
         * weapons.add(machete, 5);
         * weapons.add(pistol, 0, "pistols");
         * @endcode
         *
         * @note The name of the groups must be unique
         *
         * @see addObject
         */
        ObjectContainer<T>& createGroup(const std::string& name);

        /**
         * @brief Get objects in a group
         * @param name The name of the group
         *
         * @warning The specified group must exist first before calling this
         * function otherwise undefined behavior
         *
         * @see hasGroup
         */
        ObjectContainer<T>& getGroup(const std::string& name) const;

        /**
         * @brief Check whether or not the container has a given group
         * @param name The name of the group to be checked
         * @return True if the container has the specified group, otherwise
         *         false
         */
        bool hasGroup(const std::string& name) const;

        /**
         * @brief Remove a group from the container
         * @param name The name of the group to be removed
         * @return True if the group was removed or false if the specified
         *         group does not exist in the container
         *
         * @warning This function will remove all objects in the given group
         * from the container, therefore any pointers to the objects will be
         * invalidated
         *
         * @see addObject and removeAllGroups
         */
        bool removeGroup(const std::string& name);

        /**
         * @brief Remove all groups from the container
         *
         * This function will remove all objects that belong to a group
         * from the container, leaving only objects that do not belong
         * to a group if any. Note that pointers to the removed objects
         * will be invalidated
         *
         * @see removeGroup
         */
        void removeAllGroups();

        /**
         * @brief Execute a callback function for each object in the container
         * @param callback The function to be executed
         *
         * @see forEachInGroup and forEachInGroup
         */
        void forEach(const Callback<T*>& callback) const;

        /**
         * @brief Execute a callback for each object in a group
         * @param name The name of the group to execute callback on
         * @param callback The function to be executed for each object in
         *                 the group
         *
         * This function is a shortcut for:
         *
         * @code
         * //It's undefined behaviour to call getGroup if the group does not exist
         * if (container.hasGroup(name)) {
         *     container.getGroup(name)->forEach(...);
         * }
         * @endcode
         *
         * @see forEach and forEachNotInGroup
         */
        void forEachInGroup(const std::string& name, const Callback<T*>& callback) const;

        /**
         * @brief Apply a callback to all objects that do not belong to a group
         * @param callback The function to be executed for each object in not
         *                 in a group
         *
         * @see forEach and forEachInGroup
         */
        void forEachNotInGroup(const Callback<T*>& callback) const;

        /**
         * @brief Destructor
         */
        virtual ~ObjectContainer() = default;

    private:
        std::vector<ObjectPtr> objects_;
        std::unordered_map<std::string, std::unique_ptr<ObjectContainer<T>>> groups_;
    };

    #include "IME/common/ObjectContainer.inl"
}

#endif //IME_OBJECTCONTAINER_H
