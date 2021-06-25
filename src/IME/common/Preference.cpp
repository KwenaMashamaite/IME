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

#include "IME/common/Preference.h"
#include "IME/core/exceptions/Exceptions.h"
#include "IME/utility/DiskFileReader.h"
#include <sstream>

namespace ime {
    namespace {
        std::string convertToString(Preference::Type type) {
            switch (type) {
                case Preference::Type::Bool:    return "BOOL";
                case Preference::Type::String:  return "STRING";
                case Preference::Type::Int:     return "INT";
                case Preference::Type::Double:  return "DOUBLE";
                case Preference::Type::Float:   return  "FLOAT";
                default:
                    return "UNSUPPORTED";
            }
        }

        std::string convertToString(Preference::Type type, const Preference& pref) {
            try {
                switch (type) {
                    case Preference::Type::Bool:    return std::to_string(pref.getValue<bool>());
                    case Preference::Type::String:  return pref.getValue<std::string>();
                    case Preference::Type::Int:     return std::to_string(pref.getValue<int>());
                    case Preference::Type::Double:  return std::to_string(pref.getValue<double>());
                    case Preference::Type::Float:   return std::to_string(pref.getValue<float>());
                    default:
                        return "UNSUPPORTED";
                }
            } catch (...) {
                throw InvalidArgument("The value of '" + pref.getKey() + "' is not a '" + convertToString(type) + "'");
            }
        }    
    }
    
    Preference::Preference(const std::string &key, Preference::Type type) :
        property_{key},
        type_{type}
    {
        if (property_.getName().empty())
            throw InvalidArgument("Preference key cannot be an an empty string");
        
        if (property_.getName().find_first_of(' ') != std::string::npos)
            throw InvalidArgument("Preference key must not have whitespaces");
    }

    Preference::Type Preference::getType() const {
        return type_;
    }

    const std::string &Preference::getKey() const {
        return property_.getName();
    }

    void Preference::setDescription(const std::string &description) {
        if (description.find_first_of('\n') != std::string::npos)
            throw InvalidArgument("Preference description must not be multiline");
        
        description_ = description;
    }

    const std::string &Preference::getDescription() const {
        return description_;
    }

    void savePref(const Preference &pref, const std::string &filename) {
        std::string entry{pref.getDescription().empty() ? "\n\n" : "\n\n# " + pref.getDescription() + "\n"};
        entry += pref.getKey() + ":" + convertToString(pref.getType()) + "=" + convertToString(pref.getType(), pref);
        auto configurations = std::stringstream{entry};
        utility::DiskFileReader().writeToFile(configurations, filename, utility::WriteMode::Append);
    }
}
