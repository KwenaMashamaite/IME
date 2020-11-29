////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

#include "IME/core/physics/CollisionDetector.h"

namespace IME {
    using namespace Graphics;

    void CollisionDetector::entityVsEntityCollision(Entity &entityOne,Entity &entityTwo,
        Callback<Entity &, Entity &> callback)
    {
        if (entityOne.isCollidable() && entityTwo.isCollidable()
            && isCollideAABB(entityOne, entityTwo))
        {
            callback(entityOne, entityTwo);
        }
    }

    void CollisionDetector::tileVSTileCollision(Tile &tileOne, Tile &tileTwo,
        Callback<Tile &, Tile &> callback)
    {
        if (tileOne.isCollidable() && tileTwo.isCollidable()
            && isCollideAABB(tileOne, tileTwo))
        {
            callback(tileOne, tileTwo);
        }
    }

    void CollisionDetector::spriteVsSpriteCollision(Sprite &spriteOne, Sprite &spriteTwo,
        Callback<Sprite &, Sprite &> callback)
    {
        if (spriteOne.getPosition().x + spriteOne.getGlobalBounds().width >= spriteTwo.getPosition().x
               && spriteOne.getPosition().x <= spriteTwo.getPosition().x + spriteTwo.getGlobalBounds().width
               && spriteOne.getPosition().y + spriteOne.getGlobalBounds().height >= spriteTwo.getPosition().y
               && spriteOne.getPosition().y <= spriteTwo.getPosition().y + spriteTwo.getGlobalBounds().height)
        {
            callback(spriteOne, spriteTwo);
        }
    }

    void CollisionDetector::spriteVsTileCollision(Sprite &sprite,
        Tile &tile,Callback<Sprite &, Tile &> callback)
    {
        if (sprite.getPosition().x + sprite.getGlobalBounds().width >= tile.getPosition().x
            && sprite.getPosition().x <= tile.getPosition().x + tile.getSize().x
            && sprite.getPosition().y + sprite.getGlobalBounds().height >= tile.getPosition().y
            && sprite.getPosition().y <= tile.getPosition().y + tile.getSize().y)
        {
            callback(sprite, tile);
        }
    }

    void CollisionDetector::spriteVsTileMapCollision(Sprite &sprite, TileMap &tileMap,
        Callback<Sprite&, Tile&> callback)
    {
        tileMap.forEachTile([&, this](Tile& tile) {
            spriteVsTileCollision(sprite, tile, callback);
        });
    }
}