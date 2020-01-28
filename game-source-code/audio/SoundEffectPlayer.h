/**
 * @brief Play sound effects (Short audio clips)
 *
 * This class loads the audio file to be played in memory.
 * Therefore, it is advised to use it with short audio files
 * that can be quickly loaded form the disk and into the
 * program. Example, gun shots and explosions. If long audio
 * files are used with this class you might experience audio
 * latency and other issues. It is advised to use Audio::MusicPlayer
 * for long sounds such as background music.
 */

#ifndef SOUNDEFFECTPLAYER_H
#define SOUNDEFFECTPLAYER_H

#include "IAudioPlayer.h"
#include <string>
#include <SFML/Audio.hpp>

namespace Audio {
    class SoundEffectPlayer : public IAudioPlayer{
    public:
        /**
         * @brief play sound
         * @param filename File name of the sound to play
         */
        void play(const std::string &filename) override;

        /**
         * @brief Stop effect
         */
        void stop() override;

        /**
         * @brief Pause effect
         */
        void pause() override;

        /**
         * @brief Resume effect
         */
        void resume() override;

    private:
        //Currently playing sound
        sf::Sound soundEffect_;
    };
}

#endif