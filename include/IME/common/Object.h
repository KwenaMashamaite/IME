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
#include "IME/core/event/EventEmitter.h"
#include "IME/common/Property.h"
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
         * by tag instead of its id. Unlike an object id, multiple
         * objects may have the same tag.
         *
         * By default, the tag is an empty string
         */
        void setTag(const std::string& tag);

        /**
         * @brief Get the alias of the object
         * @return The alias of the object
         *
         * @see setTag and getObjectId
         */
        const std::string& getTag() const;

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
         * @brief Add an event listener to a specific property change event
         * @param property The name of the property to listen for
         * @param callback The function to be executed when the property changes
         * @return The unique id of the event listener
         *
         * A property change event is triggered by any function that begins
         * with @a set, where the the text after @a set is the name of the
         * property. For example, for the setTag function, the property that
         * the function modifies is @a Tag.
         *
         * Note that when adding a property change event listener, the name of
         * the property must be in lowercase:
         *
         * @code
         * // Prints the tag of the player object to the console everytime it changes
         * player.onPropertyChange("tag", [](const Property& property) {
         *      cout << "New tag: " <<  property.getValue<std::string>() << endl;
         * });
         *
         * ...
         * //Sets tag = "player1" and invokes event listener(s)
         * player.setTag("player1");
         * @endcode
         *
         * Unlike onPropertyChange(const Callback&) you can add multiple event
         * listeners to the same property using this function. However you must
         * store the unique id of the event listener if you wish to remove it
         * at a later time
         *
         * @see unsubscribe and onPropertyChange(Callback)
         */
        int onPropertyChange(const std::string& property,
            const Callback<Property>& callback);

        /**
         * @brief Add an event listener to a property change event
         * @param callback The function to be executed when the property changes
         * @return The unique id of the event listener
         *
         * Note that only one callback function may be registered with this
         * function. This means that adding a new event listener overwrites
         * the previous event listener. To remove the callback, pass a nullptr
         * as an argument. The function may be useful if you want to write
         * the logic for property changes in one function.
         *
         * @see onPropertyChange(std::string, Callback)
         */
        void onPropertyChange(const Callback<Property>& callback);

        /**
         * @brief Add an event listener to an event
         * @param event The name of the event to add an an event listener to
         * @param callback The function to be executed when the event takes place
         * @return The unique identification number of the event listener
         *
         * Unlike onPropertyChange, this function registers event listeners
         * to events that occur when something happens to the object, or when
         * the object does something (action events). Usually the name of the
         * event/action is the name of the function:
         *
         * @code
         * // Add event listeners to the object
         * object.onEvent("attachRigidBody", [] {
         *     std::cout << "Rigid body attached to object << std::endl;
         * });
         *
         * object.onEvent("removeRigidBody", [] {
         *     std::cout << "Rigid body removed from object << std::endl;
         * });
         *
         * // Invokes event listener(s)
         * object.attachRigidBody(body);
         * object.removeRigidBody();
         * @endcode
         *
         * @see onPropertyChange and unsubscribe
         */
        int onEvent(const std::string& event, const Callback<>& callback);

        /**
         * @brief Remove an event listener from an event
         * @param event The name of the event to remove event listener from
         * @param id The unique id of the event listener to be removed
         * @return True if the event listener was removed or false if the
         *         event or the event listener is does not exist
         *
         * @code
         * // Display the name of the object to console every time it changes
         * auto nameChangeId = object.onPropertyChange("name", [](Property name) {
         *      std::cout << name.getValue<std::string>() << std::endl;
         * });
         *
         * // Stop displaying the name of the object when it changes
         * object.unsubscribe("name", id);
         * @endcode
         */
        bool unsubscribe(const std::string& event, int id);

        /**
         * @brief Add a destruction listener
         * @param callback Function to be executed when the object is destroyed
         * @return The id of the destruction listener
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
        int onDestruction(const Callback<>& callback);

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
        bool operator==(const Object& rhs) const;

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
        bool operator!=(const Object& rhs) const;

        /**
         * @brief Destructor
         */
        virtual ~Object();

    protected:
        /**
         * @brief Dispatch a property change event
         * @param property The property that changed
         *
         * This function will invoke all the event listeners of the specified
         * property
         *
         * @see emit
         */
        void emitChange(const Property& property);

        /**
         * @brief Dispatch an action event
         * @param event The name of the event to be dispatched
         *
         * This function will invoke all event listeners of the specified
         * event. The function should be used for events that represent an
         * action, rather than those that represent a property change
         * (Use emitChange for that)
         *
         * @see emitChange
         */
        void emit(const std::string& event);

    private:
        unsigned int id_;           //!< The id of the object
        std::string tag_;           //!< Object's tag
        EventEmitter eventEmitter_; //!< Dispatch object events
        Callback<Property> onPropertyChange_;
    };
}

#endif //IME_OBJECT_H
