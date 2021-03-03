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

namespace ime {
    /**
     * @brief A container for Object instances
     */
    template <typename T>
    class ObjectContainer {
    public:
        using ObjectPtr = std::shared_ptr<T>; //!< Shared object pointer
        using constObjectPtr = std::shared_ptr<const T>; //!< Const shared object pointer
        using constIterator = typename std::vector<ObjectPtr>::const_iterator;

        template <typename... Args>
        using Callback = std::function<void(Args...)>;
        using Predicate = std::function<bool(const constObjectPtr)>;

        /**
         * @brief Default constructor
         */
        ObjectContainer();
        
        /**
         * @brief Add an object to the container
         * @param object object to be added
         */
        void addObject(ObjectPtr object);

        /**
         * @brief Get an object with a given name
         * @param name The name of the game object to retrieve
         * @return The object with the given name or a nullptr if the object
         *         could not be found in the container
         *
         * Note that this function will return the first object it finds with
         * the the given name
         */
        ObjectPtr findByName(const std::string& name);
        ObjectPtr findByName(const std::string& name) const;

        /**
         * @brief Get an object with a given name
         * @param name The name of the game object to retrieve
         * @return The object with the given name or a nullptr if the object
         *         could not be found in the container or the the object is
         *         found but it is not of type U
         *
         * Note that this function will return the first object it finds with
         * the the given name. You can use this function to get the derived
         * class type U if T is a base class:
         *
         * @code
         * // The type of rectangle is std::shared_ptr<ime::Shape>
         * auto rectangle = shapeContainer.findByName("myRect");
         *
         * // The type of rectangle2 is std::shared_ptr<ime::RectangleShape>
         * auto rectangle2 = shapeContainer.findByName<ime::RectangleShape>("myRect");
         * @endcode
         */
        template<typename U>
        std::shared_ptr<U> findByName(const std::string& name);

        /**
         * @brief Get an object with a given name
         * @param name The name of the game object to retrieve
         * @return The object with the given name or a nullptr if the object
         *         could not be found in the container or the the object is
         *         found but it is not of type U
         *
         * Note that this function will return the first object it finds with
         * the the given name. You can use this function to get the derived
         * class type U if T is a base class:
         *
         * @code
         * // The type of rectangle is std::shared_ptr<ime::Shape>
         * auto rectangle = shapeContainer.findByName("myRect");
         *
         * // The type of rectangle2 is std::shared_ptr<ime::RectangleShape>
         * auto rectangle2 = shapeContainer.findByName<ime::RectangleShape>("myRect");
         * @endcode
         */
        template<typename U>
        std::shared_ptr<const U> findByName(const std::string& name) const;

        /**
         * @brief Get an object with the given id
         * @param id The id of the object to be retrieved
         * @return The object with the given id or a nullptr if the object
         *         could not be found in the container
         */
        ObjectPtr findById(unsigned int id);
        ObjectPtr findById(unsigned int id) const;

        /**
         * @brief Get an object with the given id
         * @param id The id of the object to be retrieved
         * @return The object with the given id or a nullptr if the object
         *         could not be found in the container or the the object is
         *         found but it is not of type U
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
        std::shared_ptr<U> findById(unsigned int id);

        /**
         * @brief Get an object with the given id
         * @param id The id of the object to be retrieved
         * @return The object with the given id or a nullptr if the object
         *         could not be found in the container or the the object is
         *         found but it is not of type U
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
        std::shared_ptr<const U> findById(unsigned int id) const;

        /**
         * @brief Conditionally find an object in the container
         * @param predicate A function which returns true if the object should
         *                  be returned or false if the search should continue
         * @return The object that matches the found condition or a nullptr if
         *         an object that matches the success condition could not be
         *         found in the container
         */
        ObjectPtr findIf(Predicate predicate);
        const ObjectPtr findIf(Predicate predicate) const;

        /**
         * @brief Remove all objects with the given name
         * @param name Name of the objects to be removed
         * @return True if the objects were removed or false an object with
         *          the the given name does not exist in the container
         *
         * This function will all objects that have been assigned the given
         * name
         */
        bool removeByName(const std::string& name);

        /**
         * @brief Remove a game object with the given id
         * @param id The id of the object to be removed
         * @return True if the object was removed or false if an object with
         *         the the given name does not exist in the container
         */
        bool removeById(unsigned int id);

        /**
         * @brief Remove an object from the container
         * @param object The object to be removed
         * @return True if the object was removed or false if the object does
         *         not exist in the container
         */
        bool remove(ObjectPtr object);

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
         */
        bool removeIf(Predicate predicate);

        /**
         * @brief Remove all objects from the container
         */
        void removeAll();

        /**
         * @brief Get the number of objects in the container
         * @return The number of objects in the container
         */
        std::size_t getCount() const;

        /**
         * @brief Execute a callback function for each object in the container
         * @param callback The function to be executed
         */
        void forEach(Callback<ObjectPtr> callback);

        /**
         * @brief Get a constant iterator that points to the first element in
         *         the container
         * @return A constant iterator to the first element
         */
        constIterator cbegin() const;

        /**
         * @brief Get a constant iterator that points one past the last element
         *         in the container
         * @return A constant iterator one past the last element
         */
        constIterator cend() const;

        /**
         * @brief Destructor
         */
        virtual ~ObjectContainer() = default;

    private:
        std::vector<ObjectPtr> objects_;
    };

    #include "IME/common/ObjectContainer.inl"
}

#endif //IME_OBJECTCONTAINER_H
