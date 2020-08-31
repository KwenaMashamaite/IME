/**
 * @brief
 */

#ifndef TILE_H
#define TILE_H

#include "IME/common/Definitions.h"
#include "IME/gui/common/IDrawable.h"
#include "IME/utility/PropertiesContainer.h"
#include "IME/core/Sprite.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace IME {
    using Definitions::Dimensions;
    using Definitions::Position;
    using Definitions::Property;

    class Tile : public Gui::IDrawable {
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
         * @brief Get the position of the tile
         * @return The position of the tile
         */
        Position getPosition() const;

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
         * @brief Set a tile property
         * @param property Property to set
         */
        void setProperty(const Property& property);

        /**
         * @brief Get a tile property
         * @param name Name of the property to retrieve
         * @return Specified property or an empty property if a property with
         *         the specified name doesnt exist
         */
        Property getProperty(const std::string& name);

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
         * @brief Set the texture rect of the tile
         * @param position Position of the texture rect
         * @param size Size of the texture rect
         */
        void setTextureRect(Position position, Dimensions size);

        /**
         * @brief Destructor
         */
        ~Tile() = default;

    private:
        Utility::PropertyContainer properties_;
        std::string textureFile_;
        //Tile representation
        Sprite sprite_;
        sf::RectangleShape tileBoarder_;
    };
}

#endif
