#include "IME/core/CollisionDetector.h"

namespace IME {
    void CollisionDetector::TileVSTileCollision(Tile &tileOne, Tile &tileTwo, Callback<Tile &, Tile &> callback) {
        if (tileOne.isCollideable() && tileTwo.isCollideable())
            if (isCollideAABB(tileOne, tileTwo)) {
                callback(tileOne, tileTwo);
            }
    }
}