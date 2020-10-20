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

#include "AudioPlayer.h"
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

namespace IME {
    namespace Audio {
        class MusicPlayer final : public AudioPlayer{
        public:
            /**
             * @brief play music file
             * @param filename File name of the Music to play
             *
             * This function will play an audio file if currently there's no audio
             * file playing. The function will change the audio file if
             */
            void play(const std::string &filename) override;

            /**
             * @brief Loop/unloop music
             * @param isLoop Set to true to loop music, false to unloop music
             *
             * The music is not looped by default
             */
            void setLoop(bool isLoop) override ;

            /**
             * @brief Get the type of the audio player
             * @return The type of the audio player
             */
            std::string getType() override;

            /**
             * @brief Pause the Music
             */
            void pause() override;

            /**
             * @brief Resume paused music
             */
            void play() override;

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

            /**
             * @brief Get the volume of the music
             * @return Volume of the music
             */
            float getVolume() const override;

            /**
             * @brief Check if the music is looped or not
             * @return True if song is looped, false if song is not looped
             */
            bool isLooped() const override;

            /**
             * @brief Get the name of the song that's currently selected
             * @return Name of the currently selected song
             *
             * A song is selected if its playing, paused or stopped. This function
             * will return an empty string if there's no selected song
             */
            const std::string &getCurrentAudioFileName() const override;

            /**
             * @brief Get the duration of the current song
             * @return Duration of the current song
             */
            Duration getDuration() const override;

            /**
             * @brief Change the playing position of the current song
             * @param position New playing position
             *
             * The position must be between the start of the song and the end (duration)
             */
            void seek(float position) override;

            /**
             * @brief Get the current playing position
             * @return Current playing position
             */
            Duration getPlayingPosition() const override;

            /**
             * @brief Set the pitch of the audio file
             * @param pitch The new pitch of the audio file
             *
             * The default pitch is 1
             */
            void setPitch(float pitch) override;

            /**
             * @brief Get the pitch of the audio file
             * @return The pitch of the audio file
             */
            float getPitch() const override;

        private:
            //pointer to playing music
            std::shared_ptr<sf::Music> song_;
            //Name of the current audio file
            std::string currentMusicFileName_;
        };
    }
}

#endif
