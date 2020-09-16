#include "IME/core/physics/CollisionDetector.h"

namespace IME {
    using namespace Graphics;

    void CollisionDetector::entityVsEntityCollision(Entity &entityOne,Entity &entityTwo,
        Callback<Entity &, Entity &> callback)
    {
        if (entityOne.isCollidable() && entityTwo.isCollidable()) {
            if (entityOne.getPosition().x + entityOne.getBoundingRect().width >= entityTwo.getPosition().x
                   && entityOne.getPosition().x <= entityTwo.getPosition().x + entityTwo.getBoundingRect().width
                   && entityOne.getPosition().y + entityOne.getBoundingRect().height >= entityTwo.getPosition().y
                   && entityOne.getPosition().y <= entityTwo.getPosition().y + entityTwo.getBoundingRect().height)
            {
                callback(entityOne, entityTwo);
            }
        }
    }

    void CollisionDetector::tileVSTileCollision(Tile &tileOne, Tile &tileTwo,
        Callback<Tile &, Tile &> callback)
    {
        if (tileOne.isCollideable() && tileTwo.isCollideable()
            && isCollideAABB(tileOne, tileTwo))
        {
            callback(tileOne, tileTwo);
        }
    }

    void CollisionDetector::spriteVsSpriteCollision(Sprite &spriteOne, Sprite &spriteTwo,
        Callback<Sprite &, Sprite &> callback)
    {
        if (isCollideAABB(spriteOne, spriteTwo))
            callback(spriteOne, spriteTwo);
    }

    void CollisionDetector::spriteVsTileCollision(Sprite &sprite,
        Tile &tile,Callback<Sprite &, Tile &> callback)
    {
        if (tile.isCollideable() && isCollideAABB(sprite, tile))
            callback(sprite, tile);
    }

    void CollisionDetector::spriteVsTileMapCollision(Sprite &sprite, TileMap &tileMap,
        Callback<Sprite&, Tile&> callback)
    {
        tileMap.forEachTile([&, this](Tile& tile) {
            spriteVsTileCollision(sprite, tile, callback);
        });
    }
}