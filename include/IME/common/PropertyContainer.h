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
#include <cassert>
#include <string>
#include <unordered_map>

namespace IME {
    /**
     * @brief A container for a group of properties
     */
    class IME_API PropertyContainer {
    public:
        /**
         * @brief Add a property
         * @param Property Property to add
         * @return True if the property was added or false if a property
         *         with the same name already exits
         */
        bool addProperty(const Property &Property);
        bool addProperty(Property&&);

        /**
         * @brief Set the value of a property
         * @param name Name of the property to set value for
         * @param value New value of the property
         *
         * The type of @tparam T must be remembered in order to retrieve
         * the value later
         *
         * @see getValueFor
         */
        template<typename T>
        void setValueFor(const std::string &name, T&& value);

        /**
         * @brief Get the value of a property
         * @param name Name of the property to get value for
         * @throws std::bad_any_cast if the value stored by the property is
         *         not of type @tparam T
         * @return Value of a property
         *
         * This function will throw an exception if the template argument
         * @tparam T and the type of the stored value don't match. This
         * means that the property must always have a value before calling
         * this function
         *
         * @see propertyHasValue
         * @see setValueFor
         */
        template<typename T>
        T getValueFor(const std::string name) const;

        /**
         * @brief Get the type of a property
         * @param name Name of the property to get type for
         * @return The type of the property if such a property exists,
         *         otherwise an empty string
         */
        std::string getTypeFor(const std::string &name) const;

        /**
         * @brief Remove a property
         * @param name Name of the property to remove
         * @return True if the property was removed or false if the specified
         *         property doesnt exist
         */
        bool removeProperty(const std::string &name);

        /**
         * @brief Check if container has a given property
         * @param name Name of the property to check
         * @return True if property exists, otherwise false
         */
        bool hasProperty(const std::string &name) const;

        /**
         * @brief Check if a property has a value or not
         * @param name Name of the property to be checked
         * @return True if property has value or false if the property does
         *         not have a value or does not exist
         *
         * @see hasProperty
         */
        bool propertyHasValue(const std::string& name) const;

        /**
         * @brief Get the number of properties in the container
         * @return The number of properties in the container
         */
        int getSize() const;

    private:
        std::unordered_map<std::string, Property> properties_; //!< Container for the properties
    };

    #include "IME/common/PropertyContainer.inl"
}

#endif // IME_PROPERTYCONTAINER_H
