/**
 * @brief Drawable representation of a texture
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "IME/common/Position.h"
#include "IME/common/Dimensions.h"
#include "IDrawable.h"
#include "Colour.h"
#include "IME/core/animation/Animation.h"
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <memory>

namespace IME {
    namespace Graphics {
        class Sprite : public IDrawable {
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
            void setTexture(const std::string &filename);

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

            /**
             * @brief Set the colour of the sprite
             * @param colour New colour opf the sprite
             */
            void setColour(Colour colour);

            /**
             * @brief Set the local origin of the object
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin defines the center point for all transformations (position,
             * scale, rotation). The coordinates of this point must be relative to
             * the top-left corner of the object, and ignore all transformations
             * (position, scale, rotation). The origin is (0, 0) by default
             */
            void setOrigin(float x, float y);

            /**
             * @brief Get the objects origin
             * @return The objects origin
             */
            Position getOrigin() const;

            /**
             * @brief Move the sprite by an offset
             * @param xOffset Horizontal offset
             * @param yOffset Vertical offset
             */
            void move(float xOffset, float yOffset);

            /**
             * @brief Scale sprite by an offset
             * @param xFactor Horizontal offset
             * @param yFactor Vertical offset
             */
            void scale(float xFactor, float yFactor);

            /**
             * @brief Get the position of the object
             * @return Position of the object
             */
            Position getPosition() const;

            /**
             * @brief Get the name of the texture used by the sprite
             * @return Name of the texture used by the sprite
             */
            const std::string& getTexture() const;

            /**
             * @brief Get the size of the object
             * @return The size of the object
             */
            Dimensions getSize() const;

            /**
             * @brief Get the colour of the sprite
             * @return The colour of the sprite
             */
            Colour getColour() const;

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
            void draw(Window &renderTarget) override;

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
            //Filename of the texture used by the object
            std::string textureFileName_;
            //Hidden state
            bool isHidden_;
            // Sprite colour
            Colour prevSpriteColour;
        };
    }
} // namespace IME

#endif