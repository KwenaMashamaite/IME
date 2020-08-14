/**
 * @brief Class for creating animations
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include "IME/common/Definitions.h"
#include <SFML/Graphics/Rect.hpp>
#include <string>
#include <vector>

namespace IME {
    using Definitions::Dimensions;
    using Definitions::Position;

    class Animation {
    public:
        /**
         * @brief Create a new animation
         * @param name Name of the animation
         * @param spriteSheetFilename Texture file with animation frames
         * @param frameSize Size of each animation frame
         * @param startPos Position of the first frame on the sprite sheet
         * @param numOfFrames Number of animation frames
         * @param duration How long the animation plays before it
         *        stops/loops around
         *
         * The starting position must lie on the sprite sheet. In addition, the
         * sprite sheet must be large enough to accommodate all the animation
         * frames. In other words, the dimensions of a frame and the number of
         * frames must be such that none of the frames extend beyond the width
         * and height of the sprite sheet. Lastly, all animation frames must
         * be the same size otherwise, incorrect frames will be animated
         */
        Animation(const std::string &name,
                  const std::string &spriteSheetFilename,
                  Dimensions frameSize,
                  Position startPos,
                  unsigned int numOfFrames,
                  float duration);

        /**
         * @brief Get the filename of the animation sprite sheet
         * @return Filename of the animation sprite sheet
         */
        std::string getSpriteSheet() const;

        /**
         * @brief Loop/unloop animation
         * @param isLooped True to loop animation, otherwise set to false
         *
         * Animation is not looped by default
         */
        void setLoop(bool isLooped);

        /**
         * @brief Check if animation is looped or not
         * @return True if animation is looped, false if the animation
         *         is not looped
         */
        bool isLooped() const;

        /**
         * @brief Get the duration of the animation
         * @return Animation duration
         */
        float getDuration() const;

        /**
         * @brief Get the frame at a specific location
         * @param Index location of the frame to retrieve
         * @return The frame at the specified location
         * @throw std::out_of_range if the specified index is invalid
         *
         * The returned frame is not textured. It only specifies the position
         * and the size of the sprite sheet area that should be displayed. In
         * other words, the presentation sprite must be textured with the
         * appropriate sprite sheet before displaying it, otherwise a white
         * rectangle will be displayed instead.
         */
        sf::IntRect getFrameAt(unsigned int frameNumber) const;

        /**
         * @brief Get the total number of frames
         * @return Number of animation frames
         */
        unsigned int getNumOfFrames() const;

        /**
         * @brief Get the name of the animation
         * @return Name of the animation
         */
        const std::string &getName() const;

    private:
        //Animation frames
        std::vector<sf::IntRect> frames_;
        //Name of the animation
        std::string name_;
        //Animation spritesheet filename
        std::string spriteSheet_;
        //Total duration time of the animation
        float duration_;
        //Looping state
        bool isLooped_;

        /**
         * @brief Create animation frames
         * @param numOfFrames Number of frames to create
         * @param startingPos Position of the first frame on the sprite sheet
         * @param frameSize Size of each frame
         *
         * This function creates empty frames (not textured) contiguously.
         */
        void createFrames(unsigned int numOfFrames, Position startingPos,
              Dimensions frameSize);
    };
} // namespace IME

#endif
