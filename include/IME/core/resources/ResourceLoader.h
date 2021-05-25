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

#ifndef IME_RESOURCELOADER_H
#define IME_RESOURCELOADER_H

#include "IME/Config.h"
#include "IME/core/resources/ResourceType.h"
#include <functional>

namespace ime {
    /**
     * @brief Load resources from the disk into the program
     */
    class IME_API ResourceLoader final {
        public:
        using FileNameList = std::initializer_list <std::string>; //!< List of filenames to be loaded
        using Callback = std::function<void(const std::string&)>; //!< Resource load completion callback

        /**
         * @brief Load a resource from the disk
         * @param type Type of the resource to be loaded
         * @param filename Filename of the resource to be loaded
         * @throws FileNotFound If the resource cannot be found on the disk
         * @return Returns true when the resource was loaded successfully
         *
         * This function will cache any resource that is successfully
         * loaded from the disk into the program such that is is not
         * reloaded the next time it is required
         */
        static bool loadFromFile(ResourceType type, const std::string &filename);

        /**
         * @brief load multiple resources of the same type from the disk
         * @param type Type of the resources to be loaded
         * @param filenames Filenames of the resources to be loaded
         * @param callback Function to execute after successful load of each
         *        resource
         * @throws FileNotFound If one of the files cannot be found on the disk
         *
         * The callback is passed the name of the resource that was loaded
         */
        static void loadFromFile(ResourceType type, const FileNameList& filenames,
            const Callback& callback = nullptr);

        /**
         * @brief Unload a resource from the program
         * @param type The type of the resource to be unloaded
         * @param filename Filename of the resource to be removed
         * @return True if the resource was successfully removed, or false
         *         if the resource with the given filename does not exist
         *
         * @note The resource will only be removed from the program once its
         * not being used. In other words, if the resource is currently being
         * used, this function only flags it for removal at a later time
         */
        static bool unload(ResourceType type, const std::string& filename);

        /**
         * @brief Unload all resources of a given type from the program
         * @param type The type of the resources to be unloaded
         *
         * @note The resources will only be removed from the program once they
         * are no longer being used. In other words, if the resource is currently
         * being used, this function only flags it for removal at a later time
         */
        static void unloadAll(ResourceType type);

        /**
         * @brief Remove all resources from the resource holder
         *
         * @note The resources will only be removed from the program once they
         * are no longer being used. In other words, if the resource is currently
         * being used, this function only flags it for removal at a later time
         */
        static void unloadAll();
    };
}

#endif //IME_RESOURCELOADER_H
