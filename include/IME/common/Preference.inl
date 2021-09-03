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

template<typename T>
Preference::Preference(const std::string& key, Type type, T value, const std::string& description) :
    Preference(key, type)
{
    setDescription(description);
    setValue(value);
}

template <typename T>
void Preference::setValue(T value) {
    static auto throwException = [](const std::string& key, const std::string& type) {
        throw InvalidArgument("IME Type Mismatch: The preference \"" + key + "\" can only store values of type \"" + type + "\"");
    };

    switch (type_) {
        case Type::Bool:
            if constexpr (!std::is_same_v<bool, T>)
                throwException(getKey(), "bool");
            break;
        case Type::String:
            if constexpr (!std::is_same_v<std::string, T> || std::is_same_v<const char*, T> || std::is_same_v<char*, T>)
                throwException(getKey(), "std::string");
            break;
        case Type::Int:
            if constexpr (!std::is_same_v<int, T>)
                throwException(getKey(), "int");
            break;
        case Type::UInt:
            if constexpr (!std::is_same_v<unsigned int, T>)
                throwException(getKey(), "unsigned int");
            break;
        case Type::Double:
            if constexpr (!std::is_same_v<double, T>)
                throwException(getKey(), "double");
            break;
        case Type::Float:
            if constexpr (!std::is_same_v<float, T>)
                throwException(getKey(), "float");
            break;
    }

    property_.setValue(T{value});
}

template<typename T>
T Preference::getValue() const {
    return property_.getValue<T>();
}