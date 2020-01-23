/**
* @brief Class template for a resource container
*/

#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <unordered_map>

class ResourceManager; //Forward declaration

template <class T>
class ResourceHolder : sf::NonCopyable {
private:
    /**
	 * @brief Ensures only selected classes/functions can access selected parts
     *        of ResourceHolder (Attorney-Client idiom).
     *
	 * A class/function can obtain limited access to the class ResourceHolder
     * by becoming a friend of class PassKey. PassKey has access to all the members
     * (public, protected and private) of ResourceHolder but friends of PassKey only
     * have access to member functions that are exposed by PassKey.
	 */
    class PassKey{
        friend class ResourceManager;
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
     * @param filename File name of the resource to load
     * @throws FileNotFound If the file cannot be found on the disk
     *
     * If the path of the resource matches the one provided in the constructor
     * then the file name can be specified without the path (e.g textureOne.png),
     * otherwise the file path is required (e.g resources/textures/textureOne.png).
     */
    void load(const std::string& filename);

    /**
     * @brief Get a resource
     * @param filename File name of the resource to be retrieved
     * @throws FileNotFound If the the file cannot be found on the disk
     * @return Shared pointer to a resource in a buffer
     *
     * If the requested resource is not found in the buffer, an attempt
     * will be made to load it from the disk. If it cannot be loaded from
     * the disk, then a "FileNotFound" exception will be thrown. This implies
     * that the returned pointer can never be a nullptr. Therefore, nullptr
     * checks are not necessary, but they can be put in place for robustness
     */
    std::shared_ptr<T> get(const std::string& filename);

private:
    //Resource container
    std::unordered_map<std::string, std::shared_ptr<T> > resourceHolder_;
    //path to the resource
    std::string filePath_;
};

#include "ResourceHolder.inl"

#endif