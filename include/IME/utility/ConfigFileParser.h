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

#ifndef IME_CONFIGFILEPARSER_H
#define IME_CONFIGFILEPARSER_H

#include "IME/Config.h"
#include "IME/common/PropertyContainer.h"

namespace ime {
    namespace utility {
        /**
         * @deprecated Since v2.1.0, will be removed in v2.2.0. Use
         *             ime::PrefContainer instead
         *
         * @brief Class for parsing config files
         */
        class IME_API ConfigFileParser {
        public:
            /**
             * @deprecated Since v2.1.0, will be removed in v2.2.0. Use
             *             ime::PrefContainer::load instead.
             *
             * @brief Parse a config file
             * @param filename Name of the config file to be parsed
             * @return List of properties found in the config file
             * @throws FileNotFound if the config file cannot be found on
             *        the disk
             */
            [[deprecated("Use 'void ime::PrefContainer::load(const std::string&)' instead.")]]
            static PropertyContainer parse(const std::string& filename);
        };
    }
}

#endif // IME_CONFIGFILEPARSER_H
