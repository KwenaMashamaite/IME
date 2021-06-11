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

#include "IME/common/PrefContainer.h"
#include "IME/utility/DiskFileReader.h"
#include "IME/core/exceptions/Exceptions.h"

namespace ime {
    namespace {
        std::pair<bool, std::size_t> hasCharacter(const std::string& str, char character) {
            if (auto found = str.find_first_of(character); found != std::string::npos)
                return {true, found};
            return {false, std::string::npos};
        }

        bool hasWhiteSpace(const std::string& str){
            return hasCharacter(str, ' ').first;
        }

        Preference::Type convertStrToType(const std::string& type) {
            if (type == "BOOL")
                return Preference::Type::Bool;
            else if (type == "STRING")
                return Preference::Type::String;
            else if (type == "INT")
                return Preference::Type::Int;
            else if (type == "DOUBLE")
                return Preference::Type::Double;
            else if (type == "FLOAT")
                return Preference::Type::Float;

            throw InvalidArgument("Invalid preference entry: (The type ')" + type + "' is not a supported type");
        }

        std::string convertTypeToStr(Preference::Type type) {
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

        std::string convertPrefValueToString(Preference::Type type, const Preference& pref) {
            switch (type) {
                case Preference::Type::Bool:    return std::to_string(pref.getValue<bool>());
                case Preference::Type::String:  return pref.getValue<std::string>();
                case Preference::Type::Int:     return std::to_string(pref.getValue<int>());
                case Preference::Type::Double:  return std::to_string(pref.getValue<double>());
                case Preference::Type::Float:   return std::to_string(pref.getValue<float>());
                default:
                    return {};
            }
        }

        Preference createPref(const std::string& key, const std::string& strType, const std::string& value, const std::string& description) {
            Preference::Type type = convertStrToType(strType);
            Preference preference = Preference(key, type);
            preference.setDescription(description);

            switch (type) {
                case Preference::Type::Bool:
                    preference.setValue(static_cast<bool>(std::stoi(value)));
                    break;
                case Preference::Type::String:
                    preference.setValue(value);
                    break;
                case Preference::Type::Int:
                    preference.setValue(std::stoi(value));
                    break;
                case Preference::Type::Double:
                    preference.setValue(std::stod(value));
                    break;
                case Preference::Type::Float:
                    preference.setValue(std::stof(value));
                    break;
            }

            return preference;
        }
    } // anonymous namespace

    //------------------------ PrefContainer class --------------------------//
    void PrefContainer::load(const std::string &filename) {
        auto properties = PrefContainer();
        auto configurations = std::stringstream();
        utility::DiskFileReader().readFileInto(filename, configurations);
        filename_ = filename;

        auto configEntry = std::string();
        auto prefDescription = std::string();
        while (std::getline(configurations, configEntry)) {
            static auto errorMessage = [&](const std::string& errorMsg) {
                return "The entry \"" + configEntry + "\" in \"" + filename
                       + "\" is invalid because \"" + errorMsg + "\"";
            };

            // Skip lines that are empty or begin with a comment or whitespaces
            if (configEntry.empty() || configEntry[0] == '/' || configEntry[0] == ' ')
                continue;
            else if (configEntry[0] == '#') {
                prefDescription = configEntry.substr(1);
                continue;
            }

            if (auto [foundColon, colonPos] = hasCharacter(configEntry, ':'); foundColon) {
                auto key = configEntry.substr(0, colonPos);
                auto typeAndValue = configEntry.substr(colonPos + 1);
                if (auto [found, equalSignPos] = hasCharacter(typeAndValue,'='); found) {
                    auto type = typeAndValue.substr(0, equalSignPos);
                    auto value = typeAndValue.substr(equalSignPos + 1);
                    if (key.empty())
                        throw InvalidArgument(errorMessage("It's missing a key"));
                    if (value.empty() && type != "STRING")
                        throw InvalidArgument(errorMessage(R"(Only values of type 'STRING' can be left unspecified)"));
                    if (hasWhiteSpace(key) || hasWhiteSpace(type))
                        throw InvalidArgument(errorMessage("key or type contains whitespace(s)"));
                    if (hasWhiteSpace(value) && type != "STRING")
                        throw InvalidArgument(errorMessage("the value contains whitespace(s) and its not of type STRING"));

                    if (!addPref(createPref(key, type, value, prefDescription)))
                        throw InvalidArgument(errorMessage("The key '" + key + "' is a duplicate, keys must be unique"));
                } else
                    throw InvalidArgument(errorMessage(R"(type and value not separated by '=')"));
            } else
                throw InvalidArgument(errorMessage(R"(key and type are not separated by ':')"));

            prefDescription.clear();
        }
    }

    bool PrefContainer::addPref(const Preference &pref) {
        if (hasPref(pref.getKey()))
            return false;

        prefs_.push_back(pref);
        return true;
    }

    bool PrefContainer::addPref(Preference && pref) {
        if (hasPref(pref.getKey()))
            return false;

        prefs_.push_back(std::move(pref));
        return true;
    }

    Preference &PrefContainer::getPref(const std::string &key) {
        return const_cast<Preference&>(std::as_const(*this).getPref(key));
    }

    const Preference &PrefContainer::getPref(const std::string &key) const {
        try {
            return prefs_.at(getIndex(key).value());
        } catch (...)  {
            throw InvalidArgument("A preference with the key \'" + key + "\" does not exist in the container");
        }
    }

    bool PrefContainer::hasPref(const std::string &key) {
        return getIndex(key).has_value();
    }

    void PrefContainer::removePref(const std::string &key) {
        auto index = getIndex(key);
        if (index.has_value())
            prefs_.erase(prefs_.begin() + index.value());
    }

    void PrefContainer::clear() {
        prefs_.clear();
    }

    std::size_t PrefContainer::getCount() const {
        return prefs_.size();
    }

    PropertyContainer PrefContainer::asPropertyContainer() const {
        PropertyContainer container{};

        std::for_each(prefs_.begin(), prefs_.end(), [&container](const Preference& preference) {
            Property property{preference.getKey()};

            switch (preference.getType()) {
                case Preference::Type::Bool:
                    property.setValue(preference.getValue<bool>());
                    break;
                case Preference::Type::String:
                    property.setValue(preference.getValue<std::string>());
                    break;
                case Preference::Type::Int:
                    property.setValue(preference.getValue<int>());
                    break;
                case Preference::Type::Double:
                    property.setValue(preference.getValue<double>());
                    break;
                case Preference::Type::Float:
                    property.setValue(preference.getValue<float>());
                    break;
            }

            container.addProperty(std::move(property));
        });

        return container;
    }

    std::optional<int> PrefContainer::getIndex(const std::string &key) const {
        for (std::size_t index = 0; index < prefs_.size(); index++) {
            if (prefs_[index].getKey() == key)
                return std::make_optional(index);
        }

        return std::nullopt;
    }

    void PrefContainer::save(const std::string &filename) {
        auto static IME_Version = "v" + std::to_string(IME_VERSION_MAJOR) + "."
                                + std::to_string(IME_VERSION_MINOR) + "."
                                + std::to_string(IME_VERSION_PATCH);

        auto static tag = "//################################################## "
                          "\n// This file was generated by IME " + IME_Version +
                          "\n//";

        auto static headerText = R"(
// Lines that start with '//' are comments and will be
// ignored by IME whilst lines that begin with '#' are
// optional config descriptions and must appear directly
// above a config entry when used. For example:
//
// ----------------------------------------------------
//    # Height of the game window
//    WINDOW_HEIGHT:INT=600
// ----------------------------------------------------
// The syntax for this file is as follows:
//
// 	    KEY:TYPE=value
//
// KEY is the name of a variable, TYPE is the type of
// the KEY value (Supported types are STRING, BOOL, INT,
// FLOAT and DOUBLE) and VALUE is the current value of
// the KEY. The KEY must not contain any whitespaces or
// special characters except underscores. For BOOL types
// use 1 for true and 0 for false.
//
// This file may be edited directly at any time, however
// changes are not automatically detected
//
//###################################################)";

        std::string output{tag + headerText};

        // Append key-value pairs to outfile
        std::for_each(prefs_.begin(), prefs_.end(), [&output](const Preference& pref) {
            output += (pref.getDescription().empty() ? "\n\n" : "\n\n#" + pref.getDescription() + "\n");
            output += pref.getKey() + ":" + convertTypeToStr(pref.getType()) + "=" + convertPrefValueToString(pref.getType(), pref);
        });

        // Save key-value pairs to file
        auto file = std::string{};
        if (filename == "sameAsLoadFile")
            file = filename_;
        else
            file = filename;

        utility::DiskFileReader().writeToFile(std::stringstream{output}, file, utility::WriteMode::Overwrite);
    }
}
