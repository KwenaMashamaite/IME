/**
 * @brief Class for managing resources (textures, fonts, sound buffers, images and music)
 *
 * The resources to be loaded must be placed in the executables folder as follows:
 *
 * 1. fonts = executables/resources/fonts
 * 2. textures = executables/resources/images
 * 3. images = executables/resources/images
 * 4. sound buffers = executables/resources/sounds
 * 5. music = executables/resources/music
*/

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "ResourceHolder.h"
#include <string>
#include <initializer_list>

/**
 * @brief Resource identifiers (Types of resources that can be handled by resource manager)
*/
enum class ResourceId{
    TEXTURE,
    FONT,
    IMAGE,
    SOUND_BUFFER,
    MUSIC
};

class ResourceManager final{
public:
    /**
     * @brief Load a resource from the disk into a cache
     * @param identifier Type of the resource to be loaded
     * @param filename File name of the resource to be loaded
     * @throws FileNotFound If the resource cannot be found on the disk
     *
     * Loading a resource from the disk prior to retrieving it later in the
     * program is much faster and efficient as the resource is cached (i.e, a
     * copy of the resource is stored in the program rather than having to
     * load it from the disk every time it's needed.
     */
    static void load(ResourceId identifier, const std::string &filename);

    /**
     * @brief load multiple resources of the same type from the disk and
     *        store them in a cache
     * @param identifier Type of the resource to be loaded
     * @param filenames File names of the resources to be loaded
     * @throws FileNotFound If one of the files cannot be found on the disk
     */
    static void load(ResourceId identifier, const std::initializer_list<std::string> &filenames);

    /**
     * @brief Get a font
     * @param fileName File name of the font (without path)
     * @throws FileNotFound If the font cannot be found on the disk
     * @return Constant reference to a sf::font
     *
     * If the requested font is not cached, an attempt will be made to
     * load it from the disk
     */
    static const sf::Font &getFont(const std::string &fileName);

    /**
     * @brief Get a texture
     * @param fileName File name of the texture (without path)
     * @throws FileNotFound If the texture cannot be found on the disk
     * @return Constant reference to a sf::Texture
     *
     * If the requested texture is not cached, an attempt will be made
     * to load it from the disk
     */
    static const sf::Texture &getTexture(const std::string &fileName);

    /**
     * @brief Get a sound buffer
     * @param fileName File name of the sound buffer (without path)
     * @throws FileNotFound If the sound buffer cannot be found on the disk
     * @return Constant reference to a sf::SoundBuffer
     *
     * If the requested sound buffer is not cached, an attempt will be made
     * to load it from the disk
     */
    static const sf::SoundBuffer &getSoundBuffer(const std::string &fileName);

    /**
     * @brief Get an image
     * @param fileName File name of the image (without path)
     * @throws FileNotFound If the image cannot be found on the disk
     * @return constant reference to an sf::Image
     *
     * If the requested image is not cached, an attempt will be made to load
     * it from the disk
     */
    static const sf::Image &getImage(const std::string &fileName);

    /**
     * @brief Get music
     * @param fileName File name of the music (without path)
     * @throws FileNotFound If the music cannot be found on the disk
     * @return A shared pointer to sf::music
     */
    static std::shared_ptr<sf::Music> getMusic(const std::string &fileName);

private:
    //Stores textures
    static ResourceHolder<sf::Texture> texturesHolder_;
    //Stores sound buffers
    static ResourceHolder<sf::SoundBuffer> soundBuffersHolder_;
    //Stores fonts
    static ResourceHolder<sf::Font> fontsHolder_;
    //Stores images
    static ResourceHolder<sf::Image> imagesHolder_;
    //Stores music
    static ResourceHolder<sf::Music> musicHolder_;

    // Resource file path
    struct FilePath{
        static constexpr auto TEXTURES_PATH = "resources/images/";
        static constexpr auto SOUNDS_PATH = "resources/sounds/";
        static constexpr auto MUSIC_PATH = "resources/music/";
        static constexpr auto FONTS_PATH = "resources/fonts/";
    };
};

#endif