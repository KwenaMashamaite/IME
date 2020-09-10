#include "IME/common/PropertiesContainer.h"
#include "IME/utility/Helpers.h"

namespace IME {
    bool PropertyContainer::addProperty(const Property &property) {
        properties_.push_back(property);
        return true;
    }

    bool PropertyContainer::addProperty(const std::string &name,
        const std::string &type, const std::string &value)
    {
        properties_.push_back({name, type, value});
        return true;
    }

    Property PropertyContainer::getProperty(const std::string &name) const {
        if (auto [found, index] = hasProperty_(name); found)
            return properties_.at(index);
        return {"", "", ""};
    }

    std::string PropertyContainer::getValueFor(const std::string name) const {
        return getAttributeFor(name, "value");
    }

    std::string PropertyContainer::getTypeFor(const std::string &name) const {
        return getAttributeFor(name, "type");
    }

    bool PropertyContainer::removeProperty(const std::string &name) {
        if (auto [found, index] = hasProperty_(name); found) {
            properties_.erase(properties_.begin() + index);
            return true;
        }
        return false;
    }

    std::pair<bool, int> PropertyContainer::hasProperty_(const std::string& name) const {
        auto found = std::find_if(properties_.begin(), properties_.end(),
            [=](const Property& property) {return property.getName() == name;});

        if (found != properties_.end())
            return {true, std::distance(properties_.begin(), found)};
        return {false, -1};
    }

    std::string PropertyContainer::getAttributeFor(const std::string &name,
        const std::string &what) const
    {
        if (auto [found, index] = hasProperty_(name); found) {
            if (what == "value")
                return properties_.at(index).getValue();
            else if (what == "type")
                return properties_.at(index).getType();
        }
        return "";
    }

    void PropertyContainer::setValueFor(const std::string &name, const std::string &value) {
        if (auto [found, index] = hasProperty_(name); found)
            properties_.at(index).setValue(value);
    }

    int PropertyContainer::getSize() const {
        return properties_.size();
    }

    PropertyContainer::PropertyContainer(const PropertyContainer &other) {
        properties_ = other.properties_;
    }

    bool PropertyContainer::hasProperty(const std::string &name) const {
        return hasProperty_(name).first;
    }
}
