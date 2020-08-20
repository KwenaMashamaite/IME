/**
* @brief Class template for a resource container
*/

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include "IME/core/exceptions/Exceptions.h"
#include "IME/utility/NonCopyable.h"
#include "IME/utility/Helpers.h"
#include <SFML/Audio/Music.hpp>
#include <unordered_map>
#include <memory>
#include <utility>

namespace IME {
    template <class T>
    class ResourceHolder : public Utility::NonCopyable {
    public:
        /**
         * @brief Ensures resources can be located
         * @param filePath Path to the resource to store
         */
        ResourceHolder(const std::string &filePath);

        /**
         * @brief Change the path where resources are located on the disk
         * @param filepath Path to the resources to store
         *
         * This new path is where the program will search for resources when
         * loading them
         */
        void setPath(const std::string& filepath);

        /**
         * @brief Load a resource from the disk and store it in a buffer
         * @param filename File name of the resource to loadFromFile
         * @throws FileNotFound If the file cannot be found on the disk
         *
         * This function will look for the resource in the file path specified
         * during instantiation. A FileNotFound exception will be raised if the
         * resource cannot be found
         */
        bool loadFromFile(const std::string& filename);

        /**
         * @brief Remove a resource from the resource holder
         * @param filename File name of the resource to be removed
         * @return True if the resource was successfully removed, false if the
         *         resource with the specified file name does not exist or the
         *         resource is still used elsewhere @see get(const std::string&)
         */
        bool unload(const std::string& filename);

        /**
         * @brief Get a resource
         * @param filename File name of the resource to be retrieved
         * @throws FileNotFound If the the file cannot be found on the disk
         * @return Shared pointer to a resource in a buffer
         *
         * If the specified resource does not exist in the resource holder, an
         * attempt will be made to load it from the disk. If it cannot be loaded
         * from the disk, a "FileNotFound" exception will be raised. This means
         * that the returned pointer can never be a nullptr.
         *
         * @warning The returned pointer must be kept alive for as long as the
         * resource is being used, otherwise the resource might be unloaded from
         * the program while its in use. The outcome of such an event is undefined
         */
        [[nodiscard]] std::shared_ptr<T> get(const std::string& filename);

        /**
         * @brief Check if a resource exists or not
         * @param filename Name of the file to check
         * @return True if the resource exists, otherwise false
         */
        bool hasResource(const std::string& filename) const;

        /**
         * @brief Get the number of objects currently using a resource
         * @param filename Filename of the resource to get use count for
         * @return The number of objects currently using the specified resource
         *         or -1 if the resource does not exist
         */
        int getUseCountFor(const std::string& filename) const;

        /**
         * @brief Get the disk path to the resources being held
         * @return Disk path to the resource
         *
         * This path is where the program looks for the specified resources when
         * loading them. @note Whether the path is absolute or relative depends
         * on the argument given to the constructor during instantiation
         */
        const std::string& getPath() const;

        /**
         * @brief Get the number of resources in the resource holder
         * @return The number of resources in the resource holder
         */
        unsigned int getSize() const;

    private:
        //Resources container
        std::unordered_map<std::string, std::shared_ptr<T>> resourceHolder_;
        //File path to resources
        std::string filePath_;
    };

    #include "IME/core/resources/ResourceHolder.inl"
} // namespace IME

#endif
