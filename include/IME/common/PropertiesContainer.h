////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief A container for a group of properties
 */

#ifndef IME_PROPERTIES_H
#define IME_PROPERTIES_H

#include "IME/Config.h"
#include "IME/common/Property.h"
#include <string>
#include <vector>

namespace IME {
    class IME_API PropertyContainer {
    public:
        /**
         * @brief Default constructor
         */
        PropertyContainer() = default;

        /**
         * @brief Copy constructor
         */
        PropertyContainer(const PropertyContainer &other);

        /**
         * @brief Add a property
         * @param Property Property to add
         * @return True if the property was added or false if a property
         *         with the same name already exits
         */
        bool addProperty(const Property &Property);

        /**
         * @brief add a property
         * @param name Name of the property
         * @param value Value of the property
         * @return True if the property was added or false if a property
         *         with the same name already exits
         *
         * The name, value and type of the property cannot be empty
         */
        bool addProperty(const std::string &name, const std::string &type,
                         const std::string &key);

        /**
         * @brief Set the value of a property
         * @param name Name of the property
         * @param value New value of the property
         */
        void setValueFor(const std::string &name, const std::string &value);

        /**
         * @brief Get a property
         * @param name Name of the property to retrieve
         * @return Specified property or an empty property if a property with
         *         the specified name doesnt exist
         */
        Property getProperty(const std::string &name) const;

        /**
         * @brief Get the value of a property
         * @param name Name of the property to get value for
         * @return The value of a property if such a property exists, otherwise
         *         an empty string
         */
        std::string getValueFor(const std::string name) const;

        /**
         * @brief Get the type of a property
         * @param name Name of the property to get type for
         * @return The type of the property if such a property exists, otherwise
         *          an empty string
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
         * @brief Check if container has property
         * @param name Name of the property to check
         * @return True if property exists otherwise false
         */
        bool hasProperty(const std::string &name) const;

        /**
         * @brief Get the number of properties in the container
         * @return The number of properties in the container
         */
        int getSize() const;

    private:
        /**
         * @brief Check if container has a property
         * @param name Name of the property
         * @return True if property exists otherwise false
         */
        std::pair<bool, int> hasProperty_(const std::string &name) const;

        /**
         * @brief Get a property attribute
         * @param name Name of the property
         * @param what Type of the attribute
         * @return The value of the property attribute if it exists, otherwise
         *          an empty string
         */
        std::string getAttributeFor(const std::string &name,
                const std::string &what) const;

    private:
        //Container for the properties
        std::vector<Property> properties_;
    };
}

#endif
