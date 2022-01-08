////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "doctest.h"
#include "IME/core/tilemap/TileMap.h"
#include "IME/core/entity/GameObject.h"

//////////////////////////////////////////////////////
// General tests
//////////////////////////////////////////////////////

TEST_CASE("A tilemap's grid is visible by default") {
    auto tilemap = ime::TileMap(10, 10);
    CHECK(tilemap.isGridVisible());
}

TEST_CASE("A tilemap's grid can be hidden") {
    auto tilemap = ime::TileMap(10, 10);
    tilemap.setGridVisible(false);
    CHECK_FALSE(tilemap.isGridVisible());
}

TEST_CASE("A tilemap is created with the specified tile size") {
    auto tilemap = ime::TileMap(10, 10);
    CHECK_EQ(tilemap.getTileSize(), ime::Vector2u{10, 10});
}

TEST_CASE("A tilemap has a default position of (0, 0)") {
    auto tilemap = ime::TileMap(10, 10);
    CHECK_EQ(tilemap.getPosition(), ime::Vector2f{0, 0});
}

TEST_CASE("A tilemap can be placed anywhere") {
    auto tilemap = ime::TileMap(10, 10);
    tilemap.setPosition(241, 10);
    CHECK_EQ(tilemap.getPosition(), ime::Vector2f{241, 10});
}

TEST_CASE("The first tile in the tilemap has the same position as the tilemap") {
    auto tilemap = ime::TileMap(10, 10);
    ime::Map tilemapData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    tilemap.loadFromVector(tilemapData);
    tilemap.setPosition(20, 10);
    CHECK_EQ(tilemap.getPosition(), tilemap.getTile(ime::Index{0, 0}).getPosition());
}

TEST_CASE("All tiles in a tilemap are not solid tiles by default") {
    auto tilemap = ime::TileMap(10, 10);
    ime::Map tilemapData = {
        {'#', '#'},
        {'#', '#'}};

    tilemap.loadFromVector(tilemapData);
    tilemap.forEachTile([](ime::Tile& tile) {
        CHECK_FALSE(tile.isSolid());
    });
}

TEST_CASE("All tiles in a tilemap are shown by default") {
    auto tilemap = ime::TileMap(10, 10);
    ime::Map tilemapData = {
        {'#', '#'},
        {'#', '#'}};

    tilemap.loadFromVector(tilemapData);
    tilemap.forEachTile([](ime::Tile& tile) {
        CHECK_FALSE(tile.isHidden());
    });
}

TEST_CASE("Tiles in a tilemap are separated by 1 pixel by default") {
    auto tilemap = ime::TileMap();
    CHECK_EQ(tilemap.getSpaceBetweenTiles(), 1);
}

TEST_CASE("The size of the tilemap in tiles is the same as that of the vector it was created from") {
    auto tilemap = ime::TileMap(10, 10);
    ime::Map tilemapData = {
        {'#', '#'},
        {'#', '#'},
        {'#', '#'},
        {'#', '#'}};

    tilemap.loadFromVector(tilemapData);
    CHECK_EQ(tilemap.getSizeInTiles().x, 2); //X component is num of columns
    CHECK_EQ(tilemap.getSizeInTiles().y, 4); //Y component is number of rown
}

SCENARIO("A tiles adjacent neighbors can be retrieved in all directions") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#'},
        {'#', '#', '#'},
        {'#', '#', '#'}};

    grid.loadFromVector(gridData);
    REQUIRE(grid.isIndexValid(ime::Index{1, 1}));
    auto middleTile = grid.getTile(ime::Index{1, 1});

    SUBCASE("A tile to the left has the same row but its column is one less") {
        CHECK_EQ(grid.getTileLeftOf(middleTile).getIndex(), ime::Index{1, 0});
    }

    SUBCASE("A tile to the right has the same row but its column is one more") {
        CHECK_EQ(grid.getTileRightOf(middleTile).getIndex(), ime::Index{1, 2});
    }

    SUBCASE("A tile above has the same column but its row is one less") {
        CHECK_EQ(grid.getTileAbove(middleTile).getIndex(), ime::Index{0, 1});
    }

    SUBCASE("A tile below has the same column but its row is one more") {
        CHECK_EQ(grid.getTileBelow(middleTile).getIndex(), ime::Index{2, 1});
    }
}

//////////////////////////////////////////////////////
// Collision flag tests
//////////////////////////////////////////////////////

TEST_CASE("All tiles in a tilemap are not collidable by default") {
    auto tilemap = ime::TileMap(10, 10);
    ime::Map tilemapData = {
        {'#', '#'},
        {'#', '#'}};

    tilemap.loadFromVector(tilemapData);
    tilemap.forEachTile([](ime::Tile& tile) {
        CHECK_FALSE(tile.isCollidable());
    });
}

TEST_CASE("A tile can be set collidable using its index in the tilemap") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#'},
        {'#', '#', '#'},
        {'#', '#', '#'}};

    grid.loadFromVector(gridData);
    REQUIRE(grid.isIndexValid(ime::Index{1, 1}));
    REQUIRE_FALSE(grid.isCollidable(ime::Index{1, 1}));
    grid.setCollidableByIndex(ime::Index{1, 1}, true);
    CHECK(grid.isCollidable(ime::Index{1, 1}));
}

TEST_CASE("Multiple tiles can be set collidable using their indexes") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#'},
        {'#', '#', '#'},
        {'#', '#', '#'}};

    grid.loadFromVector(gridData);
    REQUIRE(grid.isIndexValid(ime::Index{0, 0}));
    REQUIRE(grid.isIndexValid(ime::Index{0, 1}));
    REQUIRE(grid.isIndexValid(ime::Index{0, 2}));
    REQUIRE_FALSE(grid.isCollidable(ime::Index{0, 0}));
    REQUIRE_FALSE(grid.isCollidable(ime::Index{0, 1}));
    REQUIRE_FALSE(grid.isCollidable(ime::Index{0, 2}));
    grid.setCollidableByIndex({ime::Index{0, 0}, ime::Index{0, 1}, ime::Index{0, 2}}, true);
    CHECK(grid.isCollidable(ime::Index{0, 0}));
    CHECK(grid.isCollidable(ime::Index{0, 1}));
    CHECK(grid.isCollidable(ime::Index{0, 2}));
}

TEST_CASE("Tiles can be set collidable using their id's") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'.', '#', '#'},
        {'#', '.', '#'},
        {'#', '#', '#'}};

    grid.loadFromVector(gridData);
    REQUIRE_FALSE(grid.isCollidable(ime::Index{0, 0}));
    REQUIRE_FALSE(grid.isCollidable(ime::Index{1, 1}));
    grid.setCollidableById('.', true);
    CHECK(grid.isCollidable(ime::Index{0, 0}));
    CHECK(grid.isCollidable(ime::Index{1, 1}));
}

TEST_CASE("Tiles can be set collidable by id exclusion") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'.', '#'},
        {'#', '.',}};

    grid.loadFromVector(gridData);
    grid.setCollidableByExclusion('.', true);
    CHECK_FALSE(grid.isCollidable(ime::Index{0, 0}));
    CHECK_FALSE(grid.isCollidable(ime::Index{1, 1}));
    CHECK(grid.isCollidable(ime::Index{0, 1}));
    CHECK(grid.isCollidable(ime::Index{1, 0}));
}

//////////////////////////////////////////////////////
// Adding children tests
//////////////////////////////////////////////////////

class TestObject : public ime::Entity {
public:
    std::string getClassType() override {
        return "TestObject";
    }
};

TEST_CASE("An entity can be added to a tilemap") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    CHECK(grid.addChild(child, ime::Index{0, 0}));
    CHECK(grid.hasChild(child));
}

TEST_CASE("An entity cannot be added to a non-existent tile") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    REQUIRE_FALSE(grid.hasChild(child));
    REQUIRE_FALSE(grid.isIndexValid(ime::Index{4, 12}));
    CHECK_FALSE(grid.addChild(child, ime::Index{4, 12}));
}

TEST_CASE("A tile without children is not occupied") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    REQUIRE(grid.isIndexValid(ime::Index{0, 0}));
    CHECK_FALSE(grid.isTileOccupied(grid.getTile(ime::Index{0, 0})));
}

TEST_CASE("A tile with at least one child is occupied") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    REQUIRE(grid.isIndexValid(ime::Index{0, 0}));
    auto child = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{0, 0});
    REQUIRE(grid.hasChild(child));
    CHECK(grid.isTileOccupied(grid.getTile(ime::Index{0, 0})));
}

TEST_CASE("Function getTileOccupiedByChild() returns the correct tile") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{1, 4});
    CHECK_EQ(grid.getTileOccupiedByChild(child).getIndex(), ime::Index{1, 4});
}

TEST_CASE("A tiles number of occupants increases by 1 when an entity is added") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    CHECK_EQ(grid.getNumOfOccupants(grid.getTile(ime::Index{0, 0})), 0);
    grid.addChild(child, ime::Index{0, 0});
    CHECK_EQ(grid.getNumOfOccupants(grid.getTile(ime::Index{0, 0})), 1);
}

TEST_CASE("An entity cannot be added twice to a tilemap") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    REQUIRE(grid.addChild(child, ime::Index{0, 0}));
    CHECK_FALSE(grid.addChild(child, {0, 0}));
}

TEST_CASE("Multiple entities can be added to a tilemap") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    auto child2 = std::make_shared<TestObject>();
    auto child3 = std::make_shared<TestObject>();
    CHECK(grid.addChild(child, ime::Index{0, 0}));
    CHECK(grid.addChild(child2, ime::Index{0, 1}));
    CHECK(grid.addChild(child3, ime::Index{0, 2}));
}

TEST_CASE("Multiple entities can be added to the same tile") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    auto child2 = std::make_shared<TestObject>();
    auto child3 = std::make_shared<TestObject>();
    CHECK(grid.addChild(child, ime::Index{0, 0}));
    CHECK(grid.addChild(child2, ime::Index{0, 0}));
    CHECK(grid.addChild(child3, ime::Index{0, 0}));
    CHECK_EQ(grid.getNumOfOccupants(grid.getTile(ime::Index{0, 0})), 3);
}

TEST_CASE("A tile has visitors if it has more than one child") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{0, 0});
    CHECK_FALSE(grid.tileHasVisitors(grid.getTile(ime::Index{0, 0})));
    auto child2 = std::make_shared<TestObject>();
    grid.addChild(child2, ime::Index{0, 0});
    CHECK(grid.tileHasVisitors(grid.getTile(ime::Index{0, 0})));
}

TEST_CASE("Function getOccupant() returns the first child to enter a tile") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    auto child2 = std::make_shared<TestObject>();
    auto child3 = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{0, 0});
    grid.addChild(child2, ime::Index{0, 0});
    grid.addChild(child3, ime::Index{0, 0});
    CHECK_EQ(grid.getOccupant(grid.getTile(ime::Index{0, 0})), child);
}

TEST_CASE("Function getOccupant() returns nullptr when a tile is not occupied") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    CHECK_EQ(grid.getOccupant(grid.getTile(ime::Index{0, 0})), nullptr);
}

TEST_CASE("A child can be retrieved from a tilemap using its id") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    auto child2 = std::make_shared<TestObject>();
    auto child3 = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{0, 1});
    grid.addChild(child2, ime::Index{2, 3});
    grid.addChild(child3, ime::Index{1, 4});
    CHECK_EQ(grid.getChildWithId(child->getObjectId()), child);
    CHECK_NE(grid.getChildWithId(child->getObjectId()), child2);
    CHECK_EQ(grid.getChildWithId(child2->getObjectId()), child2);
}

TEST_CASE("A child can be moved from its current tile to another tile") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{0, 0});
    grid.moveChild(child, ime::Index{2, 5});
    CHECK_EQ(grid.getTileOccupiedByChild(child).getIndex(), ime::Index{2, 5});
}

TEST_CASE("A child cannot be moved to an invalid tile (out of bounds)") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{0, 0});
    REQUIRE_FALSE(grid.isIndexValid(ime::Index{2, 6}));
    grid.moveChild(child, ime::Index{2, 6});
    CHECK_EQ(grid.getTileOccupiedByChild(child).getIndex(), ime::Index{0, 0});
}

//////////////////////////////////////////////////////
// Removing children tests
//////////////////////////////////////////////////////

TEST_CASE("An entity can be removed from a tilemap") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{1, 0});
    REQUIRE(grid.hasChild(child));
    REQUIRE(grid.isTileOccupied(grid.getTile(ime::Index{1, 0})));
    REQUIRE_FALSE(grid.tileHasVisitors(grid.getTile(ime::Index{1, 0}))); //Only one entity occupies the tile

    grid.removeChild(child);
    CHECK_FALSE(grid.hasChild(child));
    CHECK_FALSE(grid.isTileOccupied(grid.getTile(ime::Index{1, 0})));
}

TEST_CASE("An entity can be removed from a tilemap using it's id") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{1, 0});
    REQUIRE(grid.hasChild(child));
    REQUIRE(grid.isTileOccupied(grid.getTile(ime::Index{1, 0})));
    REQUIRE_FALSE(grid.tileHasVisitors(grid.getTile(ime::Index{1, 0}))); //Only one entity occupies the tile

    grid.removeChildWithId(child->getObjectId());
    CHECK_FALSE(grid.hasChild(child));
    CHECK_FALSE(grid.isTileOccupied(grid.getTile(ime::Index{1, 0})));
}

TEST_CASE("An entity can be removed from a tilemap using the tile it occupies") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{1, 0});
    REQUIRE(grid.hasChild(child));
    REQUIRE(grid.isTileOccupied(grid.getTile(ime::Index{1, 0})));
    REQUIRE_FALSE(grid.tileHasVisitors(grid.getTile(ime::Index{1, 0}))); //Only one entity occupies the tile
    REQUIRE_EQ(grid.getTileOccupiedByChild(child).getIndex(), ime::Index{1, 0});

    grid.removeChildFromTile(grid.getTileOccupiedByChild(child), child);
    CHECK_FALSE(grid.hasChild(child));
    CHECK_FALSE(grid.isTileOccupied(grid.getTile(ime::Index{1, 0})));
}

//In this context, occupant refers to the first entity to occupy a child, while
//subsequent children are considered visitors
TEST_CASE("An entity can be removed from a tilemap if it is the occupant of a tile") {
    auto grid = ime::TileMap();
    ime::Map gridData = {
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#'}};

    grid.loadFromVector(gridData);
    auto child = std::make_shared<TestObject>();
    grid.addChild(child, ime::Index{1, 0});
    REQUIRE(grid.hasChild(child));
    REQUIRE(grid.isTileOccupied(grid.getTile(ime::Index{1, 0})));
    REQUIRE_FALSE(grid.tileHasVisitors(grid.getTile(ime::Index{1, 0}))); //Only one entity occupies the tile
    REQUIRE_EQ(grid.getTileOccupiedByChild(child).getIndex(), ime::Index{1, 0});

    grid.removeOccupant(grid.getTileOccupiedByChild(child));
    CHECK_FALSE(grid.hasChild(child));
    CHECK_FALSE(grid.isTileOccupied(grid.getTile(ime::Index{1, 0})));
}