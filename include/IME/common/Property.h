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

#ifndef IME_PROPERTY_H
#define IME_PROPERTY_H

#include "IME/Config.h"
#include "IME/core/exceptions/Exceptions.h"
#include "IME/core/event/EventEmitter.h"
#include <string>
#include <any>

namespace ime {
    /**
     * @brief Class that can store a value of any type
     */
    class IME_API Property {
    public:
        /**
         * @brief Constructor
         * @param name Name of the property
         *
         * The property will be created without a value
         *
         * @see setValue
         */
        explicit Property(const std::string& name);

        /**
         * @brief Constructor
         * @param name Name of the property
         * @param value Value of the property
         *
         * The value can be of any type (Primitive or custom).
         *
         * @warning the type of T must be remembered in order to retrieve
         * the value later
         *
         * @see getValue
         */
        template<typename T>
        Property(const std::string& name, T&& value);

        /**
         * @brief Get the name of the property
         * @return Name of the property
         */
        const std::string& getName() const;

        /**
         * @brief Set the value of the property
         * @param value New value of the property
         *
         * This function will overwrite the previous value. The new value
         * need not be the same type as the previous value and it can be
         * of any type (Primitive or custom). However, the type of T
         * must be remembered in order to retrieve the value later
         *
         * @see getValue
         */
        template<typename T>
        void setValue(T&& value);

        /**
         * @brief Get the value of the property
         * @throws ime::InvalidArgument if the stored value is not of type T
         * @return Value of the property
         *
         * @warning Don't call this function if the property does not have
         * a value, otherwise it will throw an exception. In addition, always
         * make sure that the template argument T matches the type of the
         * stored value when calling this function
         */
        template<typename T>
        T getValue() const;

        /**
         * @brief Check if the property has a value or not
         * @return True if the property contains a value or false
         *         if it does not contain a value
         */
        bool hasValue() const;

        /**
         * @brief Subscribe a callback to a value change event
         * @param callback The function to be executed when the value changes
         * @return The unique identification of the callback
         *
         * Since the value can be of any type, the callback is passed a
         * const pointer to the property instead of the new value, so that
         * you can retrieve it
         *
         * @see getValue and unsubscribe
         */
        int onValueChange(const Callback<Property* const>& callback);

        /**
         * @brief Remove a callback from a value change event
         * @param id The unique identifier of the callback
         * @return True if the callback was removed or false a callback
         *         with the given id does not exist
         *
         * @see onValueChange
         */
        bool unsubscribe(int id);

    private:
        std::string name_;      //!< Name of the property
        std::any value_;        //!< Value of the property
        EventEmitter emitter_;  //!< Dispatches value change events
    };

    #include "IME/common/Property.inl"
}

#endif // IME_PROPERTY_H
