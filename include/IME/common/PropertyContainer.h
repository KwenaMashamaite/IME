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

#ifndef IME_PROPERTYCONTAINER_H
#define IME_PROPERTYCONTAINER_H

#include "IME/Config.h"
#include "IME/common/Property.h"
#include <string>
#include <functional>
#include <unordered_map>

namespace ime {
    /**
     * @brief A container for ime::Property instances
     */
    class IME_API PropertyContainer {
    public:
        template <typename... Args>
        using Callback = std::function<void(Args...)>; //!< Event listener

        /**
         * @brief Add a property to the container
         * @param Property The property to be added
         * @return True if the property was added or false if a property
         *         with the same name already exits in the container
         */
        bool addProperty(const Property &Property);
        bool addProperty(Property&&);

        /**
         * @brief Change the value of a property
         * @param name The name of the property to set a value for
         * @param value The new value of the property
         *
         * Note that the type of the value of the property need not match the
         * previous value type
         *
         * @see getValue
         */
        template<typename T>
        void setValue(const std::string &name, T&& value);

        /**
         * @brief Get the value of a property
         * @param name The name of the property to get the value for
         * @throws std::bad_any_cast if the value stored by the property is
         *         not of type T
         * @return Value of a property
         *
         * This function will throw an exception if the template argument
         * T and the type of the stored value don't match. This means that
         * the property must always have a value before calling this function
         *
         * @see setValue and propertyHasValue
         */
        template<typename T>
        T getValue(const std::string& name) const;

        /**
         * @brief Remove a property from the container
         * @param name The name of the property to be removed
         * @return True if the property was removed or false if the specified
         *         property doesn't exist
         *
         * @see addProperty
         */
        bool removeProperty(const std::string &name);

        /**
         * @brief Check if the container has a given property
         * @param name The name of the property to be checked
         * @return True if the property exists or false if the container does
         *         not have a property with the given name
         *
         * @see addProperty
         */
        bool hasProperty(const std::string &name) const;

        /**
         * @brief Check if a property in the container has a value or not
         * @param name The name of the property to be checked
         * @return True if property has value or false if the property does
         *         not have a value or the property does not exist in the
         *         container
         *
         * @see hasProperty
         */
        bool propertyHasValue(const std::string& name) const;

        /**
         * @brief Get the number of properties in the container
         * @return The number of properties in the container
         */
        std::size_t getCount() const;

        /**
         * @brief Apply a callback to each property in the container
         * @param callback The function to be applied
         */
        void forEachProperty(const Callback<Property&>& callback) const;

        /**
         * @brief Subscribe a callback to a value change event
         * @param The name of the property to add the callback to
         * @param callback The function to be executed when the value changes
         * @return The unique identification of the callback
         *
         * Since the value can be of any type, the callback is passed a
         * const pointer to the property instead of the new value, so that
         * you can retrieve it
         *
         * @see getValue and unsubscribe
         */
        int onValueChange(const std::string& name, const Callback<Property* const>& callback);

        /**
         * @brief Remove a callback from a value change event
         * @param name The name of the property to remove the callback from
         * @param id The unique identifier of the callback
         * @return True if the callback was removed or false a callback
         *         with the given id does not exist
         *
         * @see onValueChange
         */
        bool unsubscribe(const std::string& name, int id);

        /**
         * @brief Remove all properties from the container
         */
        void clear();

    private:
        std::unordered_map<std::string, Property> properties_; //!< Container for the properties
    };

    #include "IME/common/PropertyContainer.inl"
}

/**
 * @class ime::PropertyContainer
 * @ingroup core
 *
 * Usage example:
 * @code
 * ime::PropertyContainer settings;
 * settings.addProperty(Property("masterVolume", 100.0f));
 * settings.addProperty({"musicVolume", 80.0f});
 * settings.addProperty({"sfxVolume"});
 *
 * ...
 *
 * settings.setValue("sfxVolume", 20.0f);
 * @endcode
 */

#endif // IME_PROPERTYCONTAINER_H
