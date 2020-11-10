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