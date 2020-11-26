template<typename T>
void PropertyContainer::setValueFor(const std::string &name, T&& value) {
    if (hasProperty(name))
        properties_.at(name).setValue<T>(std::forward<T>(value));
}

template<typename T>
T PropertyContainer::getValueFor(const std::string name) const {
    assert(hasProperty(name) && "Cannot get value for non-existent property");
    return properties_.at(name).getValue<T>();
}