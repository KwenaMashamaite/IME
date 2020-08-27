/**
 * @brief Class for loading and storing resources (textures, fonts, sound buffers,
 *        images and music)
*/

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "ResourceHolder.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <initializer_list>

namespace IME {
    /**
     * @brief Resource identifiers (Types of resources that can be handled
     *        by resource manager)
    */
    enum class ResourceType {
        Texture,
        Font,
        Image,
        SoundBuffer,
        Music
    };

    class ResourceManager final {
    public:
        /**
         * @brief Load a resource from the hard drive
         * @param type Type of the resource to be loaded
         * @param filename File name of the resource to be loaded
         * @throws FileNotFound If the resource cannot be found on the disk
         *
         * Loading a resource from the disk prior to retrieving it
         * later in the program is much faster and efficient as the
         * resource is cached (i.e, a copy of the resource is stored
         * in the program rather than having to loadFromFile it from the disk
         * every time it's needed).
         */
        void loadFromFile(ResourceType type, const std::string &filename);

        /**
         * @brief  loadFromFile multiple resources of the same type from
         *         the hard drive
         * @param  type Type of the resource to be loaded
         * @param  filenames File names of the resources to be loaded
         * @throws FileNotFound If one of the files cannot be found
         *         on the disk
         */
        void loadFromFile(ResourceType type,
            const std::initializer_list<std::string> &filenames);

        /**
         * @brief Unload a resource
         * @param type  Type of the resource to unload
         * @param filename Filename of the resource to remove
         * @return True if the unloading succeeded otherwise false
         *
         * The unloading will fail if the resource is still referenced somewhere
         * in the program or the resource does not exist in the ResourceManager
         * This function is destructive. This means that the resource will be
         * completely destroyed and must be reloaded from the disk if required
         */
        bool unload(ResourceType type, const std::string& filename);

        /**
         * @brief Set the path where resources are located on the disk
         * @param type Type of the resource to set path for
         * @param path New path to resources on th disk
         *
         * The class will look for resources of the specified type in the new path
         * when loading them
         */
        void setPathFor(ResourceType type, const std::string& path);

        /**
         * @brief Get the path where resources are located on the disk
         * @param type Type of the resource to get path for
         * @return The path where resources are located on the disk
         */
        const std::string& getPathFor(ResourceType type) const;

        /**
         * @brief Get the number of objects currently using a resource
         * @param type Type of the resource
         * @param filename Filename of the resource
         * @return The number of objects currently using a resource or
         *         -1 if the resource does not exist
         */
        int getUseCount(ResourceType type, const std::string& filename);

        /**
         * @brief Get a font
         * @param fileName File name of the font (without path)
         * @throws FileNotFound If the font cannot be found on the disk
         * @return Constant reference to a sf::font
         *
         * If the requested font is not cached, an attempt will be
         * made to loadFromFile it from the disk
         */
        const sf::Font &getFont(const std::string &fileName);

        /**
         * @brief Get a texture
         * @param fileName File name of the texture
         * @throws FileNotFound If the texture cannot be found on
         *         the disk
         * @return Constant reference to a sf::Texture
         *
         * If the requested texture is not cached, an attempt will
         * be made to loadFromFile it from the disk
         */
        const sf::Texture &getTexture(const std::string &fileName);

        /**
         * @brief  Get a sound buffer
         * @param  fileName File name of the sound buffer
         * @throws FileNotFound If the sound buffer cannot
         *         be found on the disk
         * @return Constant reference to a sf::SoundBuffer
         *
         * If the requested sound buffer is not cached, an attempt will
         * be made to loadFromFile it from the disk
         */
        const sf::SoundBuffer &getSoundBuffer(const std::string &fileName);

        /**
         * @brief Get an image
         * @param fileName File name of the image
         * @throws FileNotFound If the image cannot be found on the disk
         * @return constant reference to an sf::Image
         *
         * If the requested image is not cached, an attempt will be made
         * to loadFromFile it from the disk
         */
        const sf::Image &getImage(const std::string &fileName);

        /**
         * @brief Get music
         * @param fileName File name of the music (without path)
         * @throws FileNotFound If the music cannot be found on the disk
         * @return A shared pointer to sf::music
         */
        std::shared_ptr<sf::Music> getMusic(const std::string &fileName);

        /**
         * @brief Get class instance
         * @return Shared pointer to class instance
         */
        static std::shared_ptr<ResourceManager> getInstance();

        /**
         * @brief Destructor
         */
        ~ResourceManager() = default;

    private:
        /**
         * @brief Default constructor
         */
        ResourceManager();

        /**
         * @brief Copy constructor
         */
        ResourceManager(const ResourceManager&) = delete;

        /**
         * @brief Assignment operator
         */
        ResourceManager& operator=(const ResourceManager&) = delete;

    private:
        //Stores textures
        TextureHolder textures_;
        //Stores sound buffers
        SoundBufferHolder soundBuffers_;
        //Stores fonts
        FontHolder fonts_;
        //Stores images
        ImageHolder images_;
        //Stores music
        MusicHolder music_;
    };
}

#endif
