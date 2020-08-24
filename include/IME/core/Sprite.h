/**
 * @brief Drawable representation of a texture
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "IME/common/Definitions.h"
#include "IME/gui/common/IDrawable.h"
#include "IME/gui/common/Colour.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace IME {
    using Definitions::Position;
    using Definitions::Dimensions;

    class Sprite : public Gui::IDrawable {
    public:
        /**
         * @brief Default constructor
         */
        Sprite();

        /**
         * @brief Set the position of the object
         * @param x New x coordinate of the object
         * @param y New y coordinate of the object
         */
        void setPosition(float x, float y);

        /**
         * @brief Set the position of the object
         * @param position New position of the object
         */
        void setPosition(Position position);

        /**
         * @brief Set the texture of the object
         * @param filename Filename of the texture to set
         */
        void setTexture(const std::string& filename);

        /**
         * @brief Set the sub-rectangle of the texture that the sprite will display
         * @param left horizontal starting position
         * @param top Vertical starting position
         * @param width Width of the sub-rectangle
         * @param height Height of the sub-rectangle
         * @param size The width and height of the sub-rectangle
         *
         * This function will set the texture that the sprite displays to a
         * portion of the entire texture. The displaying will start at the
         * specified starting position. By default, the sprite displays the
         * entire texture
         */
        void setTextureRect(int left, int top, int width, int height);

        void setColour(Gui::Colour colour);

        /**
         * @brief Get the position of the object
         * @return Position of the object
         */
        Position getPosition() const;

        /**
         * @brief Get the size of the object
         * @return The size of the object
         */
        Dimensions getSize() const;

        Gui::Colour getColour() const;

        /**
         * @brief Rotate object
         * @param angle Angle of rotation
         *
         * This function adds to the current angle of rotation
         */
        void rotate(float angle);

        /**
         * @brief Draw object on a render target
         * @param renderTarget Target to draw object on
         */
        void draw(Gui::Window &renderTarget) override;

        /**
         * @brief Hide object
         */
        void hide() override;

        /**
         * @brief Reveal object
         */
        void show() override;

        /**
         * @brief Check if object is hidden or not
         * @return True if object is hidden, otherwise false
         */
        bool isHidden() const override;

    private:
        //Internal sprite
        sf::Sprite sprite_;
        //Hidden state
        bool isHidden_;
        // Sprite colour
        Gui::Colour spriteColour_;
    };
} // namespace IME

#endif