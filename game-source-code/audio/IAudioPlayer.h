/**
 * @brief Interface for audio players
 */

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <string>

namespace Audio {
    class IAudioPlayer {
    public:
        /**
         * @brief Play audio
         * @param filename Filename of the audio to play
         */
        virtual void play(const std::string &filename) = 0;

        /**
         * @brief Stop the currently playing or paused audio
         */
        virtual void stop() = 0;

        /**
         * @brief Pause the currently playing audio
         */
        virtual void pause() = 0;

        /**
         * @brief Resume paused audio
         */
        virtual void resume() = 0;
    };
}

#endif
