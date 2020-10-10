/**
 * @brief Tile map Tile
 */

#ifndef TILE_H
#define TILE_H

#include "IME/common/Position.h"
#include "IME/common/Dimensions.h"
#include "IDrawable.h"
#include "Sprite.h"
#include "IME/core/event/EventEmitter.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <unordered_map>
#include <memory>

namespace IME {
    /**
     * @brief
     */
    struct Index {
        int row;
        int colm;

        bool operator==(const Index& rhs) const {
            return row == rhs.row && colm == rhs.colm;
        }
    };

    namespace Graphics {
        /**
         * @brief Defines the borders of the tile
         */
        enum class Border {
            Left,
            Right,
            Top,
            Bottom,
        };

        enum class TileType {
            Empty,
            Obstacle,
            Collectable,
            Player,
            Enemy
        };

        class Tile : public IDrawable {
        public:
            /**
             * @brief Construct a tile
             * @param size Size of the tile
             * @param position Position of the tile
             * @param tileSet Tile set file that contains the graphical representation
             *        of the tie
             */
            Tile(const Dimensions &size, const Position &position);

            /**
             * @brief Construct a tile from an existing tile
             * @param other Tile to construct 'this' tile from
             */
            Tile(const Tile &other) = default;

            /**
             * @brief Assignment operator
             */
            Tile &operator=(const Tile &other) = default;

            /**
             * @brief Move constructor
             */
            Tile(Tile &&other) = default;

            /**
             * @brief Move assignment operator
             */
            Tile &operator=(Tile &&other) = default;

            /**
             * @brief Get the position of the tile
             * @return The position of the tile
             */
            Position getPosition() const;

            /**
             * @brief Set the texture of the tile
             * @param filename Filename of the texture to set
             *
             * The texture must be the same size as the tile or only the section
             * corresponding to the texture rectangle size and texture rect
             */
            void setTexture(const std::string &filename);

            /**
             * @brief Set the fill colour of the tile
             * @param colour New fill colour of the tile
             */
            void setFillColour(const Colour& colour);

            /**
             * @brief Get the tiles fill colour
             * @return The tiles fill colour
             */
            Colour getFillColour() const;

            /**
             * @brief Set the position of the tile
             * @param x X coordinate of the tile
             * @param y Y coordinate of the tile
             */
            void setPosition(float x, float y);

            /**
             * @brief Set the position of the tile in coordinates
             * @param position Position to set
             */
            void setPosition(const Position &position);

            /**
             * @brief Set the size of the tile
             * @param width The horizontal size
             * @param height The vertical size
             */
            void setSize(float width, float height);

            /**
             * @brief Set the size of the tile
             * @param size New tile size
             */
            void setSize(Dimensions size);

            /**
             * @brief Get the size of the tile
             * @return The size of the tile
             */
            Dimensions getSize() const;

            /**
             * @brief Set the texture rect of the tile
             * @param position Position of the texture rect
             * @param size Size of the texture rect
             *
             * The size of the texture rectangle must not be larger than the
             * size of the tile, otherwise it will automatically be reduced
             * to the tile size
             *
             * The texture rectangle is (0, 0, tileWidth, tileHeight) by default
             */
            void setTextureRect(Position position, Dimensions size);

            /**
             * @brief Set the visibility of the tile border
             * @param isVisible True to set visible, otherwise false
             */
            void setBorderVisible(bool isVisible);

            /**
             * @brief Set the index of the tile in the tilemap
             * @param index The index of the tile in the tilemap
             *
             * The index corresponds to the position of the tile i the tilemap
             */
            void setIndex(Index index);

            /**
             * @brief Get the index of the tile in the tilemap
             * @return The index of the tile in the tilemap
             */
            Index getIndex() const;

            /**
             * @brief Assign the tile an identification token
             * @param id Identification token to assign
             *
             * The id is an empty character by default
             */
            void setId(const char &id);

            /**
             * @brief Set all the sides of the tile as collidable or not
             * @param isCollidable True to set tile as collidable, otherwise false
             *
             * The tile is not collidable on all sides by default
             */
            void setCollidable(bool isCollidable);

            /**
             * @brief Set a tile border as collideable or not
             * @param border The tile border to set
             * @param isCollidable True to set border as collidable, otherwise false
             */
            void setCollidable(const Border &border, bool isCollidable);

            /**
             * @brief Check if a tile border is collideable or not
             * @param border Border to be checked
             * @return True if border is collideable, otherwise false
             */
            bool isCollidable(const Border &border) const;

            /**
             * @brief Set the tile type
             * @param tileType The tile type
             *
             * The tile type corresponds to the object that is in this tile
             */
            void setType(const TileType& tileType);


            /**
             * @brief Get the type of this tile
             * @return The type of this tile
             */
            TileType getType() const;

            /**
             * @brief Get the tiles id
             * @return The tiles id
             */
            const char &getId() const;

            /**
             * @brief Draw tile
             * @param renderTarget
             */
            void draw(Window &renderTarget) override;

            /**
             * @brief Hide tile content
             */
            void hide() override;

            /**
             * @brief Show tile
             */
            void show() override;

            /**
             * @brief Check if tile is hidden or not
             * @return True if tile is hidden or not
             */
            bool isHidden() const override;

            /**
             * @brief Check if tile is collidable on all sides or not
             * @return True if tile is collidable on all sides, otherwise false
             */
            bool isCollidable() const;

            /**
             * @brief Check if tile contains pixel coordinates
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return True if the tile contains the pixel coordinates, otherwise
             *         false
             */
            bool contains(float x, float y) const;

            /**
             * @brief Add an event listener to a tile collision event
             * @param callback Function to execute when a collision occurs
             * @return Event listeners identification number
             *
             * The callback function is invoked each time the tile is collided with.
             * The tile and the border hit will be provided as arguments to the
             * callback function when publishing the collision event
             */
            int onCollision(Callback<Tile &, Border> callback);

            /**
             * @brief Collide with this tiles border
             * @param border Border to collide with
             */
            void hit(const Border &border);

            /**
             * @brief
             * @return
             */
            Sprite &getSprite();

            /**
             * @brief Destructor
             */
            ~Tile() = default;

        private:
            //Collision flag
            bool isCollideable_;
            //Stores the type of the object that will be in this tile
            TileType tileType_;
            //Stores the id of the actual object that will be in this tile
            char id_;
            //The position of the tile in the tilemap
            Index index_;
            //Tile representation
            Sprite sprite_;
            //Tile border
            sf::RectangleShape tileBoarder_;
            //Collision flags for tile sides
            std::unordered_map<Border, bool> borderCollisionFlags_;
            //Event publisher
            EventEmitter eventEmitter_;
        };
    }
}

#endif
