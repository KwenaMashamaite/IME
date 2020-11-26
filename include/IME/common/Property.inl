template<typename T>
Property::Property(const std::string& name, const std::string& type, T&& value) :
    name_(name),
    type_(type),
    value_{std::forward<T>(value)}
{}

template<typename T>
void Property::setValue(T&& value) {
    value_.emplace<T>(std::forward<T>(value));
};

template<typename T>
T Property::getValue() const {
    return std::any_cast<T>(value_);
}