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

    PropertyContainer ConfigFileParser::parse(const std::string &filename) {
        auto properties = PropertyContainer();
        auto configurations = std::stringstream();
        DiskFileReader().readFileInto(filename, configurations);
        auto configEntry = std::string();
        while (std::getline(configurations, configEntry)) {
            static auto errorMessage = [&](const std::string& errorMessage) {
                return R"(The entry ')" + configEntry + R"(')" + " in " + filename
                       + " is invalid because " + errorMessage;
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
                    properties.addProperty(key, type, value);
                } else
                    throw InvalidArgument(errorMessage(R"(type and value not separated by '=')"));
            } else
                throw InvalidArgument(errorMessage(R"(key and type are not separated by ':')"));
        }

        return properties;
    }
}