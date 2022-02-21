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

#ifndef IME_RESOURCEMANAGER_H
#define IME_RESOURCEMANAGER_H

#include "IME/Config.h"
#include "ResourceHolder.h"
#include "IME/core/resources/ResourceType.h"
#include <string>
#include <initializer_list>
#include <functional>

namespace sf {
    class Music;
    class SoundBuffer;
    class Texture;
    class Image;
    class Font;
}

namespace ime {
    /**
     * @brief Class for loading and storing resources (textures, fonts,
     *        sound buffers, images and music)
     */
    class ResourceManager final {
    public:
        using Ptr = std::shared_ptr<ResourceManager>; //!< Shared ResourceManager pointer

        template <typename... Args>
        using Callback = std::function<void(Args...)>; //!< Event listener

        /**
         * @brief Copy constructor
         */
        ResourceManager(const ResourceManager&) = delete;

        /**
         * @brief Assignment operator
         */
        ResourceManager& operator=(const ResourceManager&) = delete;

        /**
         * @brief Load a resource from the disk
         * @param type Type of the resource to be loaded
         * @param filename Filename of the resource to be loaded
         * @throws FileNotFoundException If the resource cannot be found on the disk
         * @return Returns true when the resource was loaded successfully
         *
         * This function will cache any resource that is successfully
         * loaded from the disk into the program such that is is not
         * reloaded the next time it is required
         */
        bool loadFromFile(ResourceType type, const std::string &filename);

        /**
         * @brief load multiple resources of the same type from the disk
         * @param type Type of the resources to be loaded
         * @param filenames Filenames of the resources to be loaded
         * @param callback Function to execute after successful load of each
         *        resource
         * @throws FileNotFoundException If one of the files cannot be found on the disk
         *
         * The callback is passed the name of the resource that was loaded
         */
        void loadFromFile(ResourceType type,
            const std::initializer_list<std::string> &filenames,
            const Callback<const std::string&>& callback = nullptr);

        /**
         * @brief Unload a resource from the resource manager
         * @param type Type of the resource to unload
         * @param filename Filename of the resource to remove
         * @return True if the resource was unloaded or false if the specified
         *         resource does not exist
         */
        bool unload(ResourceType type, const std::string& filename);

        /**
         * @brief Unload all resources of a given type
         * @param type The type of the resources to be unloaded
         */
        void unloadAll(ResourceType type);

        /**
         * @brief Unload all resources from the resource manager
         */
        void unloadAll();

        /**
         * @brief Set the path where resources are located on the disk
         * @param type Type of the resource to set path for
         * @param path New path to resources on th disk
         *
         * The engine will look in @a path when loading resources of the
         * specified type. Note that ime::ResourceType::Image and
         * ime::ResourceType::Texture always have the same path, so
         * changing either one of them changes the other
         */
        void setPathFor(ResourceType type, const std::string& path);

        /**
         * @brief Get the path where resources are located on the disk
         * @param type Type of the resource to get path for
         * @return The path where resources are located on the disk for the
         *          specified resource type
         */
        std::string getPathFor(ResourceType type) const;

        /**
         * @brief Get a font
         * @param fileName Filename of the font
         * @throws FileNotFoundException If the font cannot be found on the disk
         * @return Requested font
         */
        const sf::Font &getFont(const std::string &fileName);

        /**
         * @brief Get a texture
         * @param fileName Filename of the texture
         * @throws FileNotFoundException If the texture cannot be found on the disk
         * @return The requested texture
         */
        const Texture &getTexture(const std::string &fileName);

        /**
         * @brief Get a sound buffer
         * @param fileName File name of the sound buffer
         * @throws FileNotFoundException If the sound buffer cannot be found on the disk
         * @return The requested sound buffer
         */
        const sf::SoundBuffer &getSoundBuffer(const std::string &fileName);

        /**
         * @brief Get an image
         * @param fileName File name of the image
         * @throws FileNotFoundException If the image cannot be found on the disk
         * @return The requested image
         */
        const sf::Image &getImage(const std::string &fileName);

        /**
         * @brief Get music
         * @param fileName Filename of the music
         * @throws FileNotFoundException If the music cannot be found on the disk
         * @return Pointer to the requested music
         */
        std::shared_ptr<sf::Music> getMusic(const std::string &fileName);

        /**
         * @brief Get class instance
         * @return Shared pointer to class instance
         */
        static ResourceManager::Ptr getInstance();

        /**
         * @brief Destructor
         */
        ~ResourceManager() = default;

    private:
        /**
         * @brief Default constructor
         */
        ResourceManager();

    private:
        ResourceHolder<sf::Font> fonts_;   //!< Fonts container
        ResourceHolder<sf::Image> images_; //!< Images container
        TextureHolder textures_;           //!< Textures container
        ResourceHolder<sf::SoundBuffer> soundBuffers_; //!< Sound buffers container
        std::string musicPath_;
        std::unordered_map<std::string, std::shared_ptr<sf::Music>> musicHolder_;
    };
}

#endif // IME_RESOURCEMANAGER_H
