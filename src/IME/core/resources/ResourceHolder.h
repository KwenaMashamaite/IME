////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_RESOURCEHOLDER_H
#define IME_RESOURCEHOLDER_H

#include "IME/core/exceptions/Exceptions.h"
#include "IME/graphics/Texture.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <utility>

namespace ime {
    /**
     * @brief Class template for a resource container
     */
    template <class T>
    class ResourceHolder {
    public:
        using Ptr = std::shared_ptr<T>; //!< Shared T pointer

        /**
         * @brief Construct a resource holder
         * @param filePath Path to the resource to store
         */
        explicit ResourceHolder(const std::string &filePath);

        /**
         * @brief Copy constructor
         */
        ResourceHolder(const ResourceHolder<T>&) = delete;

        /**
         * @brief Copy assignment operator
         */
        ResourceHolder<T>& operator=(const ResourceHolder<T>&) = delete;

        /**
         * @brief Change the path where resources are located on the disk
         * @param filepath Path to the resources to store
         *
         * This new path is where the program will search for resources when
         * loading them
         */
        void setPath(const std::string& filepath);

        /**
         * @brief Get the path to the resources being held
         * @return The path to the resource on the disk
         *
         * This path is where the program looks for the specified resources
         * when loading them
         */
        const std::string& getPath() const;

        /**
         * @brief Load a resource from the disk and store it in a buffer
         * @param filename Filename of the resource to load
         * @throws FileNotFoundException If the file cannot be found on the disk
         * @return True if resource was loaded successfully, otherwise false
         *
         * This function will look for the resource in the file path specified
         * during instantiation. A FileNotFound exception will be raised if the
         * resource with the specified filename cannot be found
         */
        bool loadFromFile(const std::string& filename);

        /**
         * @brief Remove a resource from the resource holder
         * @param filename Filename of the resource to be removed
         * @return True if the resource was successfully removed, or false
         *         if the resource with the given filename does not exist
         */
        bool unload(const std::string& filename);

        /**
         * @brief Remove all resources from the resource holder
         * @return True if all the resource were removed or false if the
         *         resource holder is already empty
         */
        bool unloadAll();

        /**
         * @brief Get a resource
         * @param filename Filename of the resource to be retrieved
         * @throws FileNotFoundException If the the file cannot be found on the disk
         * @return Shared pointer to a resource in a buffer
         *
         * If the specified resource does not exist in the resource holder, an
         * attempt will be made to load it from the disk. If it cannot be loaded
         * from the disk, a "FileNotFound" exception will be raised. This means
         * that the returned pointer can never be a nullptr
         */
        [[nodiscard]] ResourceHolder::Ptr get(const std::string& filename);

        /**
         * @brief Get the number of resources in the resource holder
         * @return The number of resources in the resource holder
         */
        std::size_t getSize() const;

        /**
         * @brief Check if a resource exists or not
         * @param filename Filename of the resource to check
         * @return True if the resource exists, otherwise false
         */
        bool hasResource(const std::string& filename) const;

    private:
        std::unordered_map<std::string, ResourceHolder::Ptr> resourceHolder_; //!< Resources container
        std::string filePath_;                                      //!< File path to resources
    };

    #include "IME/core/resources/ResourceHolder.inl"

    using TextureHolder = ResourceHolder<Texture>; //!< Texture holder
}

#endif // IME_RESOURCEHOLDER_H
