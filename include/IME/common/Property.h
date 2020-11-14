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
 * @brief Class for defining attributes
 */

#ifndef IME_PROPERTY_H
#define IME_PROPERTY_H

#include<string>

namespace IME {
    class Property {
    public:
        /**
         * @brief Constructor
         * @param name NAme of the property
         * @param type Type of the property
         * @param value Value of the property
         * @param isReadOnly Set true if property must be modified after
         *        construction, otherwise false
         */
        Property(const std::string& name, const std::string& type, const std::string& value,
             bool isReadOnly = false);

        /**
         * @brief Copy constructor
         */
        Property(const Property&) = default;

        /**
         * @brief Set the value of the property
         * @param value New value of the property
         */
        void setValue(const std::string& value);

        /**
         * @brief Get the name of the property
         * @return The name of the property
         */
        const std::string& getName() const;

        /**
         * @brief Get the value of the property
         * @return The value of the property
         */
        const std::string& getValue() const;

        /**
         * @brief Get the type of the property
         * @return The type of the property
         */
        const std::string& getType() const;

        /**
         * @brief Check if property is modifiable or not
         * @return True if property is not modifiable, otherwise false
         */
        bool isReadOnly() const;

        /**
         * @brief Assignment operator
         */
        Property& operator=(const Property&) = default;

        /**
         * @brief Check if a property is the same as this property
         * @param other The property to check against for equality
         * @return True if the properties are the same, otherwise false
         */
        bool operator==(const Property& other);

        /**
         * @brief Check if a property is not the same as this property
         * @param other The property to check against for inequality
         * @return True if the properties are not the same, otherwise false
         */
        bool operator!=(const Property& other);

    private:
        //Name of the property
        std::string name_;
        //Value of the property
        std::string value_;
        //Type of the property
        std::string type_;
        //Immutability state
        bool isReadOnly_;
    };
}

#endif
