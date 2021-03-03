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

#ifndef IME_OBJECT_H
#define IME_OBJECT_H

#include "IME/Config.h"
#include <unordered_map>
#include <functional>
#include <string>
#include <memory>

namespace ime {
    /**
     * @brief An abstract base class for entities in IME
     *
     * Note that some entities are standalone and do not inherit from
     * this class
     */
    class IME_API Object {
    public:
        using Ptr = std::shared_ptr<Object>; //!< Shared object pointer
        using DestructionCallback = std::function<void()>; //!< Destruction callback

        /**
         * @brief Default constructor
         */
        Object();

        /**
         * @brief Copy constructor
         */
        Object(const Object&);

        /**
         * @brief Copy assignment operator
         */
        Object& operator=(const Object&);

        /**
         * @brief Move constructor
         */
        Object(Object&&) noexcept = default;

        /**
         * @brief Move assignment operator
         */
        Object& operator=(Object&&) noexcept = default;

        /**
         * @brief Assign the object an alias
         * @param name The alias of the object
         *
         * This function is useful if you want to refer to the object
         * by name instead of its id. Unlike an object id, multiple
         * objects may have the same name.
         *
         * By default, the name is an empty string
         */
        void setName(const std::string& name);

        /**
         * @brief Get the alias of the object
         * @return The alias of the object
         *
         * @see setName and getObjectId
         */
        const std::string& getName() const;

        /**
         * @brief Get the id of the object
         * @return The id of the object
         *
         * Each object has a unique id
         */
        unsigned int getObjectId() const;

        /**
         * @brief Get the name of the concrete class
         * @return The name of the objects concrete class
         *
         * This function is implemented by all internal classes that inherit
         * from this class.
         *
         * @see getClassType
         */
        virtual std::string getClassName() const = 0;

        /**
         * @brief Get the name of the direct parent of an object instance
         * @return The name of the direct parent of an object instance
         *
         * In contrast to getClassName which returns the name of the concrete
         * class, this function returns the name of the concrete class's base
         * class. This function is implemented by all derived classes of Object
         * which also serve as base classes for other Objects. For classes
         * whose direct parent is this class, this function will return the
         * name of this class
         *
         * @code
         * auto rectangle = ime::RectangleShape(); // RectangleShape is derived from Shape
         * std::cout << rectangle->getClassName(); // Prints "RectangleShape"
         * std::cout << rectangle->getClassType(); // Prints "Shape"
         * @endcode
         *
         * @see getClassName
         *
         */
        virtual std::string getClassType() const;

        /**
         * @brief Add a destruction listener
         * @return The id of the destruction listener
         *
         *
         * Note that an object may have more than one destruction listeners,
         * however, you have to keep the returned id if you may want to remove
         * the callback at a later time
         *
         * @warning The callback is called when the object is destroyed. Do
         * not try to access the object in the callback. Doing so is undefined
         * behavior
         *
         * @see removeDestructionListener
         */
        int onDestruction(DestructionCallback);

        /**
         * @brief Remove a destruction listener form the object
         * @param The id of the destruction listener to be removed
         * @return True if the destruction listener was removed or false if
         *         the listener with the given id does not exist
         */
        bool removeDestructionListener(int id);

        /**
         * @brief Check if two objects are the same object or not
         * @param rhs Object to compare against this object
         * @return True if @a rhs is the same object as this object,
         *         otherwise false
         *
         * Two objects are the same object if they have the same object id.
         * Recall that each object instance has a unique id
         *
         * @see getObjectId and operator!=
         */
        bool operator==(const Object& rhs);

        /**
         * @brief Check if two objects are not the same object
         * @param rhs Object to compare against this object
         * @return True if @a rhs is NOT the same object as this object,
         *         otherwise false
         *
         * Two objects are different from each other if they have different
         * object id's
         *
         * @see getObjectId and operator==
         */
        bool operator!=(const Object& rhs);

        /**
         * @brief Destructor
         */
        virtual ~Object();

    private:
        unsigned int id_;  //!< The id of the object
        std::string name_; //!< Object alias
        std::unordered_map<int, DestructionCallback> destructionListeners_;
    };
}

#endif //IME_OBJECT_H