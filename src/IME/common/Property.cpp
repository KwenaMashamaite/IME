#include "IME/common/Property.h"

namespace IME {
    Property::Property(const std::string &name, const std::string &type,
        const std::string &value, bool isReadOnly)
            : name_(name), type_(type), value_(value), isReadOnly_(isReadOnly)
    {}

    void Property::setValue(const std::string &value) {
        if (!isReadOnly_)
            value_ = value;
    }

    const std::string &Property::getName() const {
        return name_;
    }

    const std::string &Property::getValue() const {
        return value_;
    }

    const std::string &Property::getType() const {
        return type_;
    }

    bool Property::isReadOnly() const {
        return isReadOnly_;
    }

    bool Property::operator==(const Property &other) {
        return name_ == other.name_
               && type_ == other.type_
               && value_ == other.value_;
    }

    bool Property::operator!=(const Property &other) {
        return !(*this == other);
    }
}