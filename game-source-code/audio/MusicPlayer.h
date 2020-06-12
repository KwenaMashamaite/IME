/**
 * @brief Stream audio files from disk
 *
 * This class is ideal for playing long and big audio file such
 * as background music. The audio file is not loaded in memory
 * but rather streamed from the disk. The file must remain
 * accessible on the disk for as long as its being used. You can
 * use Audio::SoundEffectPLayer to play short sounds such as
 * gun shots and explosions
 */

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "IAudioPlayer.h"
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

namespace Audio {
    class MusicPlayer final : public IAudioPlayer{
    public:
        /**
         * @brief play music file
         * @param filename File name of the Music to play
         */
        void play(const std::string &filename) override;

        /**
         * @brief Loop/unloop music
         * @param isLoop Set to true to loop music, false to unloop music
         */
        void setLoop(bool isLoop);

        /**
         * @brief Pause the Music
         */
        void pause() override;

        /**
         * @brief Resume paused music
         */
        void resume() override;

        /**
         * @brief Stop playing or paused music
         */
        void stop() override;

        /**
         * @brief Set the audio volume
         * @param volume Volume to set
         *
         * The volume must be between 0 (mute) and 100 (full volume)
         * The default volume is 100.
         *
         * @note The volume must be set after playing the song
         */
        void setVolume(float volume) override;

        /**
         * @brief Get the current status of the audio file
         * @return Current status of the audio file
         */
        Status getStatus() const override;

    private:
        //pointer to playing music
        std::shared_ptr<sf::Music> song_;
    };
}

#endif