/**
 * @brief Tile map Tile
 */

#ifndef TILE_H
#define TILE_H

#include "IME/common/Position.h"
#include "IME/common/Dimensions.h"
#include "IME/common/IDrawable.h"
#include "IME/event/EventEmitter.h"
#include "IME/core/Sprite.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <unordered_map>
#include <memory>

namespace IME {
    /**
     * @brief Defines the borders of the tile
     */
    enum class Border {
        Left,
        Right,
        Top,
        Bottom,
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
        Tile(const Dimensions& size, const Position& position);

        /**
         * @brief Construct a tile from an existing tile
         * @param other Tile to construct 'this' tile from
         */
        Tile(const Tile& other) = default;

        /**
         * @brief Assignment operator
         */
        Tile& operator=(const Tile& other) = default;

        /**
         * @brief Move constructor
         */
        Tile(Tile&& other) = default;

        /**
         * @brief Move assignment operator
         */
        Tile& operator=(Tile&& other) = default;

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
        void setTexture(const std::string& filename);

        /**
         * @brief Set the position of the tile in coordinates
         * @param position Position to set
         */
        void setPosition(const Position& position);

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
         * @brief Assign the tile an identification token
         * @param id Identification token to assign
         *
         * The id is an empty character by default
         */
        void setId(const char &id);

        /**
         * @brief Set all the sides of the tile as collideable or not
         * @param isCollideable True to set tile as collideable, otherwise false
         *
         * The tile is not collideable on all sides by default
         */
        void setCollideable(bool isCollideable);

        /**
         * @brief Set a tile border as collideable or not
         * @param border The tile border to set
         * @param isCollideable True to set border as collideable, otherwise false
         */
        void setCollideable(const Border& border, bool isCollideable);

        /**
         * @brief Check if a tile border is collideable or not
         * @param border Border to be checked
         * @return True if border is collideable, otherwise false
         */
        bool isCollideable(const Border& border) const;

        /**
         * @brief Get the tiles id
         * @return The tiles id
         */
        const char& getId() const;

        /**
         * @brief Draw tile
         * @param renderTarget
         */
        void draw(Gui::Window &renderTarget) override;

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
         * @brief Check if tile is collideable on all sides or not
         * @return True if tile is collideable on all sides, otherwise false
         */
        bool isCollideable() const;

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
        int onCollision(Callback<Tile&, Border> callback);

        /**
         * @brief Collide with this tiles border
         * @param border Border to collide with
         */
        void hit(const Border& border);

        /**
         * @brief
         * @return
         */
        Sprite& getSprite();

        /**
         * @brief Destructor
         */
        ~Tile() = default;

    private:
        bool isCollideable_;
        //Tiles id
        char id_;
        //Tile representation
        Sprite sprite_;
        //Tile border
        sf::RectangleShape tileBoarder_;
        //
        std::unordered_map<Border, bool> borderCollisionFlags_;
        //Event publisher
        EventEmitter eventEmitter_;
    };
}

#endif
