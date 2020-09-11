#include "IME/core/CollisionDetector.h"

namespace IME {
    void CollisionDetector::tileVSTileCollision(Tile &tileOne, Tile &tileTwo,
        Callback<Tile &, Tile &> callback)
    {
        if (tileOne.isCollideable() && tileTwo.isCollideable()
            && isCollideAABB(tileOne, tileTwo))
        {
            callback(tileOne, tileTwo);
        }
    }

    void CollisionDetector::spriteVsTileCollision(Sprite &sprite,
        Tile &tile,Callback<Sprite &, Tile &> callback)
    {
        if (tile.isCollideable() && isCollideAABB(sprite, tile))
            callback(sprite, tile);
    }
}