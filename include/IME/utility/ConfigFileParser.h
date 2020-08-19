/**
 *
 */

#ifndef CONFIGFILEPARSER_H
#define CONFIGFILEPARSER_H

#include "PropertiesContainer.h"

namespace IME {
    namespace Utility {
        class ConfigFileParser {
        public:
            /**
             * @brief Parse a config file
             * @param filename Name of the config fle to parse
             * @return List of properties found i the config file
             * @throw FileNotFound if the config file cannot be found on the disk
             */
            PropertyContainer parse(const std::string& filename);
        };
    } // namespace Utility
} // namespace IME

#endif
