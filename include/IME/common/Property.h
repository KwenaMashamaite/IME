
#ifndef PROPERTY_H
#define PROPERTY_H

#include<string>

namespace IME {
    class Property {
    public:
        /**
         * @brief Constructor
         * @param name NAme of the property
         * @param type Type of the property
         * @param value Value of the property
         * @param isModifiable Set true if modifiable otherwise false
         */
        Property(const std::string& name, const std::string& type, const std::string& value,
             bool isModifiable = true);

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
         * @return True if modifiable otherwise false
         */
        bool isModifiable () const;

    private:
        //Name of the property
        std::string name_;
        //Value of the property
        std::string value_;
        //Type of the property
        std::string type_;
        //Immutability state
        bool isModifiable_;
    };
}
#endif
