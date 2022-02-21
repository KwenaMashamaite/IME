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

#ifndef IME_PREFERENCE_H
#define IME_PREFERENCE_H

#include "IME/Config.h"
#include "IME/common/Property.h"
#include "IME/core/exceptions/Exceptions.h"
#include <string>
#include <type_traits>

namespace ime {
    /**
     * @brief A key-value pair that can be saved to a file on the disk
     *
     * A Preference is very similar to a Property. What sets them apart is
     * that a Preference can only store objects whose type are known to it
     * whereas a Property can store objects of any type. In addition, the
     * contents of a Preference can be saved to a file on the disk
     */
    class IME_API Preference {
    public:
        /**
         * @brief The type of the value in the key-value pair
         */
        enum class Type {
            Bool,    //!< bool
            String,  //!< std::string type (NOT "const char*")
            Int,     //!< int
            UInt,    //!< unsigned int
            Double,  //!< double
            Float    //!< float
        };

        /**
         * @brief Constructor
         * @param key The unique identifier of the preference
         * @param type The type of the value in the key-value pair
         *
         * Note that once set, the @a key and @a type of the preference
         * cannot be changed later
         */
        Preference(const std::string& key, Type type);

        /**
         * @brief Constructor
         * @param key The unique identifier of the preference
         * @param type The type of the value in the key-value pair
         * @param value The value of the preference
         * @param description An optional message describing the key-value pair
         * @throws InvalidArgumentException If the type of the @a value argument does not
         *                         correspond to the type specified by @a type
         *                         argument
         *
         * Note that once set, the @a key and @a type cannot be changed later.
         *
         * A @a description is an optional short message describing what the
         * preference is. When saved to the disk, it will be preceded by a
         * hashtag sign (#), indicating that it is a comment
         */
        template<typename T>
        Preference(const std::string& key, Type type, T value, const std::string& description = "");

        /**
         * @brief Set the value of the preference
         * @param value The value to be set
         * @throws InvalidArgumentException if the type of @a value does not correspond
         *                         to the ime::Preference::Type given in the
         *                         constructor
         *
         * @see getValue, hasValue and getType
         */
        template<typename T>
        void setValue(T value);

        /**
         * @brief Check if the preference has a value or not
         * @return True if the preference contains a value or false
         *         if it does not contain a value
         *
         * @see setValue
         */
        bool hasValue() const;

        /**
         * @brief Get the value of the preference
         * @throws InvalidArgumentException if @a T is not the same as the ime::Preference::Type
         *                         given in the constructor or the preference does
         *                         not have a value
         *
         * @see setValue, hasValue and getType
         */
        template<typename T>
        T getValue() const;

        /**
         * @brief Get the type of the preference
         * @return The type of the preference
         */
        Type getType() const;

        /**
         * @brief Get the key/name of the preference
         * @return The key of the preference
         */
        const std::string& getKey() const;

        /**
         * @brief Set the text to be displayed above the key-value pair
         * @param description The description to be set
         *
         * A description is an optional short message describing what the
         * preference is. When saved to the disk, it will be preceded by a
         * hashtag sign (#), indicating that it is a comment
         *
         * By default, the description is an empty string
         *
         * @warning The description must not contain new line characters
         */
        void setDescription(const std::string& description);

        /**
         * @brief Get the preference description
         * @return The preference description
         */
        const std::string& getDescription() const;

    private:
        Property property_;       //!< Stores the key-value pair
        Type type_;               //!< The type of the preference
        std::string description_; //!< A description of the preference
    };

    #include "IME/common/Preference.inl"

    using PrefType = Preference::Type; //!< ime::Preference::Type alias

    /**
     * @brief Save a Preference to the disk
     * @param pref The preference to be saved
     * @param filename The name of the file to save the preference to
     * @throws FileNotFoundException if the specified file cannot be opened for
     *                      writing
     *
     * The preference will be saved using the following format:
     *
     * @code
     * # Description (optional)
     * Key:Type=Value
     * @endcode
     *
     * Note that the preference will be appended at the end of the file.
     * In addition, the file to append data to is searched relative to the
     * game executable
     */
    void IME_API savePref(const Preference& pref, const std::string& filename);
}

#endif //IME_PREFERENCE_H
