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

#include "IME/utility/ConfigFileParser.h"
#include "IME/utility/DiskFileReader.h"
#include "IME/utility/ConsoleLogger.h"
#include "IME/core/exceptions/Exceptions.h"
#include <sstream>

namespace IME::Utility {
    std::pair<bool, std::size_t> hasCharacter(const std::string& str, char character) {
        if (auto found = str.find_first_of(character); found != std::string::npos)
            return {true, found};
        return {false, std::string::npos};
    }

    bool hasWhiteSpace(const std::string& str){
        return hasCharacter(str, ' ').first;
    }

    bool isFundamentalType(const std::string& type) {
        return (type == "string" || type == "int" || type == "char" || type == "float"
            || type == "double" || type == "bool");
    }

    PropertyContainer ConfigFileParser::parse(const std::string &filename) {
        auto properties = PropertyContainer();
        auto configurations = std::stringstream();
        DiskFileReader().readFileInto(filename, configurations);
        auto configEntry = std::string();
        while (std::getline(configurations, configEntry)) {
            static auto errorMessage = [&](const std::string& errorMessage) {
                return R"(The entry ")" + configEntry + R"(" in ")" + filename
                       + R"(" is invalid because ")" + errorMessage + R"(")";
            };

            ////Skip lines that are empty or begin with a comment or whitespaces
            if (configEntry.empty() || configEntry[0] == '#' || configEntry[0] == ' ')
                continue;

            if (auto [foundColon, colonPos] = hasCharacter(configEntry, ':'); foundColon) {
                auto key = configEntry.substr(0, colonPos);
                auto typeAndValue = configEntry.substr(colonPos + 1);
                if (auto[found, equalSignPos] = hasCharacter(typeAndValue,'='); found) {
                    auto type = typeAndValue.substr(0, equalSignPos);
                    auto value = typeAndValue.substr(equalSignPos + 1);
                    if (hasWhiteSpace(key) || hasWhiteSpace(type))
                        throw InvalidArgument(errorMessage("key or type contains whitespace(s)"));
                    if (!isFundamentalType(type))
                        throw InvalidArgument(errorMessage("'" + type + "'" + " is not a fundamental type"));
                    if(hasWhiteSpace(value) && type != "string")
                        throw InvalidArgument(errorMessage("the value contains whitespace(s) and its not of type string"));
                    properties.addProperty(key, type, value);
                } else
                    throw InvalidArgument(errorMessage(R"(type and value not separated by '=')"));
            } else
                throw InvalidArgument(errorMessage(R"(key and type are not separated by ':')"));
        }

        return properties;
    }
}