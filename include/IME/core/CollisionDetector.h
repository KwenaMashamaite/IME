#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "IME/graphics/Tile.h"
#include "IME/core/tilemap/TileMap.h"
#include "IME/graphics/Sprite.h"

namespace IME {
    class CollisionDetector{
    public:
        /**
         * @brief Check for a collision between two tiles
         * @param tileOne The first tile
         * @param tileTwo The second tile
         * @param callback Function to execute when a collision is detected
         *
         * The callback function is not invoked when a collision is not taking
         * place. When a collision is taking place, the colliding objects will
         * be passed as arguments to the callback in the same order in which
         * they are provided to this function
         */
        void tileVSTileCollision(Graphics::Tile& tileOne, Graphics::Tile& tileTwo,
            Callback<Graphics::Tile&, Graphics::Tile&> callback);

        /**
         * @brief Check a collision between two sprite objects
         * @param spriteOne First sprite object
         * @param spriteTwo Second sprite object
         * @param callback Function to execute when a collision is detected
         *
         * The callback function is not invoked when a collision is not taking
         * place. When a collision is taking place, the colliding objects will
         * be passed as arguments to the callback in the same order in which
         * they are provided to this function
         */
        void spriteVsSpriteCollision(Graphics::Sprite& spriteOne, Graphics::Sprite& spriteTwo,
            Callback<Graphics::Sprite&, Graphics::Sprite&> callback);

        /**
         * @brief Check for a collision between a sprite object and a tile object
         * @param sprite Sprite object
         * @param tile Tile object
         * @param callback Function to execute when a collision is detected
         *
         * The callback function is not invoked when a collision is not taking
         * place. When a collision is taking place, the colliding objects will
         * be passed as arguments to the callback in the same order in which
         * they are provided to this function
         */
        void spriteVsTileCollision(Graphics::Sprite& sprite, Graphics::Tile& tile,
            Callback<Graphics::Sprite&, Graphics::Tile&> callback);

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
        void spriteVsTileMapCollision(Graphics::Sprite& sprite, TileMap& tileMap,
            Callback<Graphics::Sprite&, Graphics::Tile&> callback);

    private:
        /**
         * @brief Check if two objects are colliding using the AABB method
         * @param objectOne The
         * @param objectTwo
         * @return True if the two objects are colliding, otherwise false
         */
        template<typename T1, typename T2>
        bool isCollideAABB(const T1& objectOne, const T2& objectTwo) const {
            return objectOne.getPosition().x + objectOne.getSize().width >= objectTwo.getPosition().x
                && objectOne.getPosition().x <= objectTwo.getPosition().x + objectTwo.getSize().width
                && objectOne.getPosition().y + objectOne.getSize().height >= objectTwo.getPosition().y
                && objectOne.getPosition().y <= objectTwo.getPosition().y + objectTwo.getSize().height;
        }

    private:

    };
} // namespace IME

#endif
