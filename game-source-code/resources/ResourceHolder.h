/**
* @brief Class template for a resource container
*/

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <unordered_map>

namespace IME {
    class ResourceManager; //Forward declaration

    namespace Audio{ //Forward declaration
        class SoundEffectPlayer;
        class MusicPlayer;
    }

    template <class T>
    class ResourceHolder : sf::NonCopyable {
    private:
        /**
         * @brief Ensures only selected classes/functions can access
         *        selected parts of ResourceHolder (Attorney-Client idiom).
         *
         * A class/function can obtain limited access to the class
         * ResourceHolder by becoming a friend of class PassKey.
         * PassKey has access to all the members (public, protected
         * and private) of ResourceHolder but friends of PassKey only
         * have access to member functions that are exposed by PassKey.
         */
        class PassKey{
            friend class ResourceManager;
            friend class Audio::MusicPlayer;
            friend class Audio::SoundEffectPlayer;
            PassKey(){}
            PassKey(const PassKey&){}
            PassKey& operator=(const PassKey&) = delete;
        };

    public:
        /**
         * @brief Ensures resources can be located
         * @param filePath Path of the resource to store
         * @param passKey Access key to the constructor
         *
         * The file path must be relative to the generated executable file's
         * root directory (folder in which the .exe file sits).
         */
        ResourceHolder(const std::string& filePath, PassKey passKey);

        /**
         * @brief Load a resource from the disk and store it in a buffer
         * @param filename File name of the resource to loadFromFile
         * @throws FileNotFound If the file cannot be found on the disk
         *
         * This function will look for the resource in the directory specified
         * during instantiation. A FileNotFound exception will be raised if the
         * resource cannot be found
         */
        void loadFromFile(const std::string& filename);

        /**
         * @brief Remove the resource from the resource holder
         * @param filename File name of the resource to be removed
         * @return True if the resource was successfully removed, false if the
         *         resource with the specified file name does not exist
         */
        bool remove(const std::string& filename);

        /**
         * @brief Get a resource
         * @param filename File name of the resource to be retrieved
         * @throws FileNotFound If the the file cannot be found on the disk
         * @return Shared pointer to a resource in a buffer
         *
         * If the requested resource is not found in the buffer, an
         * attempt will be made to loadFromFile it from the disk. If it cannot
         * be loaded from the disk, then a "FileNotFound" exception will
         * be thrown. This implies that the returned pointer can never be
         * a nullptr. Therefore, nullptr checks are not necessary
         */
        std::shared_ptr<T> get(const std::string& filename);

        /**
         * @brief Get the number of stored resources
         * @return The number of stored resources
         */
        unsigned int getSize() const;

    private:
        //Resource container
        std::unordered_map<std::string, std::shared_ptr<T> > resourceHolder_;
        //path to the resource
        std::string filePath_;
    };
}

#include "ResourceHolder.inl"

#endif
