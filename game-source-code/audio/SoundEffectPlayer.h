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
    class SoundEffectPlayer final : public IAudioPlayer{
    public:
        /**
         * @brief Play sound
         * @param filename File name of the sound to play
         */
        void play(const std::string &filename) override;

        /**
         * @brief Stop sound effect
         */
        void stop() override;

        /**
         * @brief Pause sound effect
         */
        void pause() override;

        /**
         * @brief Resume sound effect
         */
        void play() override;

        /**
         * @brief Set the audio volume
         * @param volume Volume to set
         *
         * The volume must be between 0 (mute) and 100 (full volume)
         * The default volume is 100.
         */
        void setVolume(float volume) override;

        /**
         * @brief Loop/unloop sound effect
         * @param isLooped Set to true to loop audio, false to unloop audio
         *
         * The sund effect s not looped by default
         */
        void setLoop(bool isLooped) override;

        /**
         * @brief Get the current status of the audio file
         * @return Current status of the audio file
         */
        Status getStatus() const override;

        /**
         * @brief Get the volume of the sound effect
         * @return Volume of the sound effect
         */
        float getVolume() const override;

    private:
        //Currently playing sound
        sf::Sound soundEffect_;
    };
}

#endif