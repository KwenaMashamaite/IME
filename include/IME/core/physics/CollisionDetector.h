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

#ifndef IME_COLLISIONDETECTOR_H
#define IME_COLLISIONDETECTOR_H

#include "IME/Config.h"
#include "IME/graphics/Tile.h"
#include "IME/core/tilemap/TileMap.h"
#include "IME/graphics/Sprite.h"
#include "IME/core/entity/Entity.h"

namespace ime {
    /**
     * @brief Class for checking a collision between two objects
     */
    class IME_API CollisionDetector {
    public:
        /**
         * @brief Check for a collision between two tiles
         * @param tileOne The first tile
         * @param tileTwo The second tile
         * @param callback Function to execute when a collision is detected
         *
         * When a collision is taking place, the colliding objects will
         * be passed as arguments to the callback in the same order in which
         * they are provided to this function
         */
        void tileVSTileCollision(Tile& tileOne, Tile& tileTwo,
            Callback<Tile&, Tile&> callback);

        /**
         * @brief Check a collision between two sprite objects
         * @param spriteOne First sprite object
         * @param spriteTwo Second sprite object
         * @param callback Function to execute when a collision is detected
         *
         * When a collision is taking place, the colliding objects will
         * be passed as arguments to the callback in the same order in which
         * they are provided to this function
         */
        void spriteVsSpriteCollision(Sprite& spriteOne, Sprite& spriteTwo,
            Callback<Sprite&, Sprite&> callback);

        /**
         * @brief Check for a collision between a sprite object and a tile object
         * @param sprite Sprite object
         * @param tile Tile object
         * @param callback Function to execute when a collision is detected
         *
         * When a collision is taking place, the colliding objects will
         * be passed as arguments to the callback
         */
        void spriteVsTileCollision(Sprite& sprite, Tile& tile,
            Callback<Sprite&, Tile&> callback);

        /**
         * @brief Check for collision between a sprite object and a tilemap tile
         * @param sprite Sprite object to check
         * @param tileMap Tilemap to check
         * @param callback Function to execute when a collision is detected
         *
         * The callback function is not invoked when a collision is not taking
         * place. When a collision is taking place, the colliding objects will
         * be passed as arguments to the callback in the same order in which
         * they are provided to this function
         */
        void spriteVsTileMapCollision(Sprite& sprite, TileMap& tileMap,
            Callback<Sprite&, Tile&> callback);

    private:
        /**
         * @brief Check if two objects are colliding using the AABB method
         * @param objectOne The
         * @param objectTwo
         * @return True if the two objects are colliding, otherwise false
         */
        template<typename T1, typename T2>
        bool isCollideAABB(const T1& objectOne, const T2& objectTwo) const {
            return objectOne.getPosition().x + objectOne.getSize().x >= objectTwo.getPosition().x
                && objectOne.getPosition().x <= objectTwo.getPosition().x + objectTwo.getSize().x
                && objectOne.getPosition().y + objectOne.getSize().y >= objectTwo.getPosition().y
                && objectOne.getPosition().y <= objectTwo.getPosition().y + objectTwo.getSize().y;
        }

    private:

    };
}

#endif // IME_COLLISIONDETECTOR_H
