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

#include "AudioPlayer.h"
#include "resources/ResourceHolder.h"
#include <string>
#include <SFML/Audio.hpp>

namespace IME{
    namespace Audio {
        class SoundEffectPlayer final : public AudioPlayer{
        public:
            /**
             * @brief Constructor
             * @param path Path to where sounds are located on the hard drive
             */
            explicit SoundEffectPlayer(const std::string& path);

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

            /**
             * @brief Load sound effects from the hard drive into the player
             * @param soundEffectNames Names of the sound effects to load
             */
            void loadFromFile(const std::initializer_list<std::string>& soundEffectNames) override;

            /**
             * @brief Check if the sound effect is looped or not
             * @return True if sound effect is looped, false if sound effect is
             *         not looped
             */
            bool isLooped() const override;

            /**
             * @brief Get the duration of the sound effect
             * @return Duration of the sound effect
             */
            float getDuration() const override;

            /**
             * @brief Change the playing position of the sound effect
             * @param position New playing position
             *
             * The playing position must be between zero and the duration
             */
            void seek(float position) override;

            /**
             * @brief Get the name of the currently sound effect
             * @return The name of the current sound effect
             *
             * The current sound effect is the one that is currently playing, paused
             * or stopped
             */
            const std::string& getCurrentAudioFileName() const override;

            /**
             * @brief Get the current playing position of the sound effect
             * @return Current playing position of the sound effect
             */
            float getPlayingPosition() const override;

            /**
             * @brief Play the next music file
             */
            void next() override;

            /**
             * @brief Play the previous music file
             */
            void prev() override;

        private:
            //Stores sound effects to be played
            ResourceHolder<sf::SoundBuffer> soundEffects_;
            //Currently playing sound
            sf::Sound currentSoundEffect_;
            //Nam eof the current sound effect
            std::string currentEffectName_;
        };
    }
}

#endif
