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

#ifndef IME_OBJECTCONTAINER_H
#define IME_OBJECTCONTAINER_H

#include "IME/Config.h"
#include "IME/common/Object.h"
#include <memory>
#include <list>
#include <algorithm>
#include <functional>
#include <unordered_map>

namespace ime {
    /**
     * @brief A container for ime::Object instances
     */
    template <typename T>
    class ObjectContainer {
    public:
        template <typename... Args>
        using Callback = std::function<void(Args...)>;   //!< For each callback

        using Predicate = std::function<bool(const T*)>; //!< Predicate callback
        using ObjectPtr = std::unique_ptr<T>;            //!< Unique Object pointer

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
         * @param object The object to be added
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
         * the the given tag if the container has multiple objects with the
         * same tag
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
         * the the given tag if the container has multiple objects with the same
         * tag. You can use this function to get the derived class type U if T
         * is a base class:
         *
         * @code
         * // The type of rectangle is ime::Shape*
         * auto* rectangle = shapeContainer.findByTag("myRect");
         *
         * // The type of rectangle2 is ime::RectangleShape*
         * auto* rectangle2 = shapeContainer.findByTag<ime::RectangleShape>("myRect");
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
         * // The type of rectangle is ime::Shape*
         * auto rectangle = shapeContainer.findById(4);
         *
         * // The type of rectangle2 is ime::RectangleShape*
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
         * @param tag The tag of the objects to be removed
         *
         * @warning This function will invalidate any pointer(s) to the
         * object once it is removed from the container
         */
        void removeByTag(const std::string& tag);

        /**
         * @brief Remove an object with the given id
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
         * @warning The argument must not be a nullptr
         */
        bool remove(T* object);

        /**
         * @brief Conditionally remove objects from the container
         * @param predicate A function which returns true if the object should
         *                 be removed or false if it should not be removed
         *                 from the container
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
         * @return The created group
         *
         * This function is useful if you want to relate some objects and
         * refer to them as a whole using a common group name instead of
         * using a common tag name and looping though the container to find
         * which objects have a given tag. Note that the name of the group
         * must be unique
         *
         * @code
         * auto weapons = objectContainer.createGroup("weapons");
         * weapons.addObject(knife);
         * weapons.addObject(machete);
         * weapons.addObject(bat);
         * @endcode
         *
         * @see addObject
         */
        ObjectContainer<T>& createGroup(const std::string& name);

        /**
         * @brief Get a group in the container
         * @param name The name of the group
         * @return The requested group
         *
         * @warning The specified group must exist in the container before
         * this function is called otherwise undefined behavior
         *
         * @see createGroup and hasGroup
         */
        ObjectContainer<T>& getGroup(const std::string& name) const;

        /**
         * @brief Check whether or not the container has a given group
         * @param name The name of the group to be checked
         * @return True if the container has the specified group, otherwise
         *         false
         *
         * @see createGroup
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
         * @see createGroup and removeAllGroups
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
         * @brief Apply a callback function to each object in the container
         * @param callback The function to be applied to each object
         *
         * Note that the callback is applied to all objects, this includes
         * those that are assigned to groups
         *
         * @see forEachInGroup and forEachNotInGroup
         */
        void forEach(const Callback<T*>& callback) const;

        /**
         * @brief Apply a callback to each object in a specific group
         * @param name The name of the group to apply callback on
         * @param callback The function to be applied to each object in the
         *                 group
         *
         * This function is a shortcut for:
         *
         * @code
         * // It's undefined behaviour to call getGroup if the group does not exist
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
         * @param callback The function to be applied to each object in the
         *                 container that does not belong to any group
         *
         * @see forEach and forEachInGroup
         */
        void forEachNotInGroup(const Callback<T*>& callback) const;

        /**
         * @brief Destructor
         */
        virtual ~ObjectContainer() = default;

    private:
        std::list<ObjectPtr> objects_;
        std::unordered_map<std::string, std::unique_ptr<ObjectContainer<T>>> groups_;
    };

    #include "IME/common/ObjectContainer.inl"
}

/**
 * @class ime::ObjectContainer
 * @ingroup core
 *
 * This class is a storage facility for any instance of ime::Object
 *
 * Usage Example:
 * @code
 * /// Suppose @a MyClass is a child of @a ime::Object like so:
 * class AmericanDadCharacter : public ime::Object {...}
 *
 * /// Then we can instantiate a container for @a MyClass instances like so:
 * auto ADCContainer = ime::ObjectContainer<AmericanDadCharacter>();
 *
 * // From here onwards it can be used like a normal class instance
 * auto steve = std::make_unique<AmericanDadCharacter>();
 * steve.setTag("Steve");
 * ADCContainer.addObject(std::move(steve));
 *
 * auto stan = std::make_unique<AmericanDadCharacter>();
 * stan.setTag("Stan");
 * ADCContainer.addObject(std::move(stan), "Parents");
 *
 * ...
 *
 * AmericanDadCharacter* stan = ADCContainer.getGroup("Parents")->findByTag("Stan");
 * stan->assignMission("Kill Roger");
 * @endcode
 */

#endif //IME_OBJECTCONTAINER_H
