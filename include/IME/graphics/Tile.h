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
     * @brief Represents a position in the tilemap
     */
    struct Index {
        int row;
        int colm;

        bool operator==(const Index& rhs) const {
            return row == rhs.row && colm == rhs.colm;
        }

        bool operator!=(const Index& rhs) const {
            return !(*this == rhs);
        }
    };

    namespace Graphics {
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
             */
            Tile(const Dimensions &size, const Position &position);

            /**
             * @brief Construct a tile from an existing tile
             * @param other Tile to construct this tile from
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
             * @brief Add a sprite to the tile
             * @param sprite Sprite to be added
             *
             * The tile can only contain a single sprite. Therefore, subsequent
             * calls to this function will replace the previous sprite
             */
            void addSprite(Sprite sprite);

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
             * @brief Set the position of the sprite within the tile
             * @param x X coordinate of the sprite
             * @param y Y coordinate of the sprite
             *
             * The sprite will be moved to the new position immediately. Nothing
             * will happen if the specified position lies outside the tile
             * borders. @note This function will not check if the entire sprite
             * lies in within the borders of the tile, it only checks if the
             * sprites origin lies within the tile borders or not. The sprite
             * has the same position as the tile by default
             */
            void setSpritePosition(float x, float y);

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
            void setId(char id);

            /**
             * @brief Set all the sides of the tile as collidable or not
             * @param isCollidable True to set tile as collidable, otherwise false
             *
             * The tile is not collidable on all sides by default
             */
            void setCollidable(bool isCollidable);

            /**
             * @brief Set the tile type
             * @param tileType The tile type
             *
             * The tile type corresponds to the object that is in this tile
             */
            void setType(TileType tileType);

            /**
             * @brief Get the type of this tile
             * @return The type of this tile
             */
            TileType getType() const;

            /**
             * @brief Get the tiles id
             * @return The tiles id
             */
            char getId() const;

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
             * The callback function is invoked each time this tile is collided
             * with. The tile will be passed as an argument to the callback
             */
            int onCollision(Callback<Tile &> callback);

            /**
             * @brief Collide with this tile
             */
            void hit();

            /**
             * @brief Get the sprite set on the tile
             * @return Sprite on the tile
             */
            Sprite &getSprite();

            /**
             * @brief Destructor
             */
            ~Tile() = default;

        private:
            //Collision flag
            bool isCollidable_;
            //Stores the type of the object that will be in this tile
            TileType tileType_;
            //Stores the id of the actual object that will be in this tile
            char id_;
            //The position of the tile in the tilemap
            Index index_;
            //Tile representation
            Sprite sprite_;
            //Tile border
            sf::RectangleShape tile_;
            //Event publisher
            EventEmitter eventEmitter_;
            //For hiding purposes
            sf::Color prevFillColour_;
        };
    }
}

#endif
