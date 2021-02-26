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

#ifndef IME_GAMEOBJECTCONTAINER_H
#define IME_GAMEOBJECTCONTAINER_H

#include "IME/Config.h"
#include "Container.h"
#include "IME/core/game_object/GameObject.h"

namespace ime {
    /**
     * @brief GameObject container
     */
    class IME_API GameObjectContainer : public Container<GameObject> {
    public:
        /**
         * @brief Get a game object by its id
         * @param id The id of the game object to get
         * @return The game object with the given id or a nullptr if
         *         the container does not have a game object with the
         *         given id
         */
        GameObject::Ptr getObjectById(unsigned int id);
        GameObject::Ptr getObjectById(unsigned int id) const;

        /**
         * @brief Get a game object by its name
         * @param name The name of the game object to get
         * @return The game object with the given name or a nullptr if
         *         the container does not have a game object with the
         *         given name
         *
         * Note that multiple game objects can have the same name, therefore
         * this function will return the first game object it finds if there
         * is any
         */
        GameObject::Ptr getObjectByName(const std::string& name);
        const GameObject::Ptr getObjectByName(const std::string& name) const;

        /**
         * @brief Remove a game object with a given id from the container
         * @param id The id of the game object to remove from the container
         * @return True if the game object was removed or false if the game
         *          object was not found
         *
         * Game objects have unique id numbers therefore this function will
         * always remove a single game object with the given id
         *
         * @see removeObjectWithName
         */
        bool removeObjectWithId(unsigned int id);

        /**
         * @brief Remove a game object with a given name from the container
         * @param name The name of the game object to remove
         * @param multiple True to remove all the game object with the given name
         *                 or false to only remove the first game object that is
         *                 found in the container
         * @return True if the game object was removed or false if the game
         *         object was not found
         *
         * Note that multiple game objects can have the same name, therefore
         * this function will remove all the game objects with the given name
         *
         * @see removeObjectWithId
         */
        bool removeObjectWithName(const std::string& name);
    };
}

#endif //IME_GAMEOBJECTCONTAINER_H
