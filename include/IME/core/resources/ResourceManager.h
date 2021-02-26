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

#ifndef IME_RESOURCEMANAGER_H
#define IME_RESOURCEMANAGER_H

#include "IME/Config.h"
#include "IME/core/resources/ResourceHolder.h"
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
     * @brief Resource identifiers (Types of resources that can be handled
     *        by resource manager)
    */
    enum class ResourceType {
        Texture,     //!< Texture
        Font,        //!< Font
        Image,       //!< Image
        SoundBuffer, //!< Sound buffer
        Music        //!< Music
    };

    /**
     * @brief Class for loading and storing resources (textures, fonts,
     *        sound buffers, images and music)
     */
    class IME_API ResourceManager final {
    public:
        using Ptr = std::shared_ptr<ResourceManager>; //!< Shared ResourceManager pointer

        template <typename... Args>
        using Callback = std::function<void(Args...)>; //!< Event listener

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
        bool loadFromFile(ResourceType type, const std::string &filename);

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
        void loadFromFile(ResourceType type,
            const std::initializer_list<std::string> &filenames,
            Callback<const std::string&> callback = nullptr);

        /**
         * @brief Unload a resource from the resource manager
         * @param type Type of the resource to unload
         * @param filename Filename of the resource to remove
         * @return True if the resource was unloaded or false if the specified
         *         resource does not exist
         */
        bool unload(ResourceType type, const std::string& filename);

        /**
         * @brief Set the path where resources are located on the disk
         * @param type Type of the resource to set path for
         * @param path New path to resources on th disk
         *
         * The class will look for resources of the specified type in the
         * new path when loading them
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
         * @throws FileNotFound If the font cannot be found on the disk
         * @return Requested font
         */
        const sf::Font &getFont(const std::string &fileName);

        /**
         * @brief Get a texture
         * @param fileName Filename of the texture
         * @throws FileNotFound If the texture cannot be found on the disk
         * @return The requested texture
         */
        const Texture &getTexture(const std::string &fileName);

        /**
         * @brief Get a sound buffer
         * @param fileName File name of the sound buffer
         * @throws FileNotFound If the sound buffer cannot be found on the disk
         * @return The requested sound buffer
         */
        const sf::SoundBuffer &getSoundBuffer(const std::string &fileName);

        /**
         * @brief Get an image
         * @param fileName File name of the image
         * @throws FileNotFound If the image cannot be found on the disk
         * @return The requested image
         */
        const sf::Image &getImage(const std::string &fileName);

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

        /**
         * @brief Copy constructor
         */
        ResourceManager(const ResourceManager&) = delete;

        /**
         * @brief Assignment operator
         */
        ResourceManager& operator=(const ResourceManager&) = delete;

    private:
        ResourceHolder<sf::Font> fonts_;   //!< Fonts container
        ResourceHolder<sf::Image> images_; //!< Images container
        TextureHolder textures_;           //!< Textures container
        ResourceHolder<sf::SoundBuffer> soundBuffers_; //!< Sound buffers container
    };
}

#endif // IME_RESOURCEMANAGER_H
