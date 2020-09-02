/**
 * @brief Tile map Tile
 */

#ifndef TILE_H
#define TILE_H

#include "IME/common/Definitions.h"
#include "IME/common/IDrawable.h"
#include "IME/utility/PropertiesContainer.h"
#include "IME/core/Sprite.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace IME {
    using Definitions::Dimensions;
    using Definitions::Position;
    using Definitions::Property;

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
         */
        void setTextureRect(const std::string& filename, Position position, Dimensions size);

        /**
         * @brief Assign tile a token
         * @param Token to assign to be assigned
         *
         * This token will be used by the tile map renderer to figure out
         * which tile from the tilset to display for this tile
         */
        void setToken(const char &token);

        /**
         * @brief Get the tiles token
         * @return The tiles token
         */
        const char& getToken() const;

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
         * @brief Destructor
         */
        ~Tile() = default;

    private:
        //Tiles token
        char token_;
        //
        std::string textureFile_;
        //Tile representation
        Sprite sprite_;
        //Tile border
        sf::RectangleShape tileBoarder_;
        //Tetxure for the tile
        std::shared_ptr<sf::Texture> texture_;
    };
}

#endif
