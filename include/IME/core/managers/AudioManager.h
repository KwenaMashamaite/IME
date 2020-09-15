/**
 * @brief Class for managing audio
 *
 * This class allows us to play multiple audio files of different types
 * (Music or SoundEffect, @see @class Music and @class SoundEffectPlayer)
 * simultaneously. Each audio file is played in a separate thread
 */

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "IME/core/audio/AudioPlayer.h"
#include "IME/core/audio/MusicPlayer.h"
#include "IME/core/audio/SoundEffectPlayer.h"
#include "IME/core/event/EventEmitter.h"
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <string>

namespace IME {
    namespace Audio {
        /**
         * @brief Types of audio files managed by the audio manager
         */
        enum class AudioType{
            SoundEffect,
            Music
        };

        class AudioManager {
        public:
            AudioManager(const std::string& musicFilePath, const std::string& soundEffectFilePath);

            /**
             * @brief Load audio files
             * @param audioType The type of audio file to be loaded
             * @param filenames File names of the audio files to be loaded
             * @throw FileNotFound if the specified audio files cannot be
             *        found on disk
             *
             * Use AudioType::Music for long and big audio files and
             * AudioType::SoundEffect for small, short audio files.
             * @see @class MusicPlayer and @class SoundEffectPlayer
             */
            void loadAudioFiles(AudioType audioType, std::initializer_list<std::string> filenames);

            /**
             * @brief Play an audio file
             * @param audioType Type of the audio file to play
             * @param filename Filename of the audio to play
             *
             * The audio file must be loaded first otherwise nothing will play
             * @see loadAudioFiles(AudioType, std::initializer_list<std::string>)
             * The audio file will be played in a separate thread. This means
             * that, the main thread is not blocked and other audio file may be
             * played simultaneously
             */
            void play(const AudioType &audioType, const std::string &filename);

            /**
             * @brief Play all audio files of a certain type
             * @param audioType Type of the audio files to play
             */
            void playAll(AudioType audioType);

            /**
             * @brief Pause all playing audio files of a certain type
             * @param audioType Type of the audio files to pause
             */
            void pauseAll(const AudioType &audioType);

            /**
             * @brief Stop all playing/paused audio files of a certain type
             * @param audioType Type of the audio file to stop
             *
             * Stopping an audio file (playing/paused) will reset the current
             * playing position to the beginning
             */
            void stopAll(const AudioType &audioType);

            /**
             * @brief Loop/unloop an audio file
             * @param audioType Type of the audio to set loop for
             * @param isLooped Set true to loop and false to unloop
             *
             * All audio files are not looped by default
             */
            void setLoopFor(const AudioType &audioType, bool isLooped);

            /**
             * @brief Set the volume for an audio file
             * @param audioType Type of the audio file to set volume for
             * @param volume Volume to set, (mute) 0 <= volume <= 100 (max)
             *
             * The default volume is 100 (max)
             */
            void setVolumeFor(const AudioType &audioType, float volume);

            /**
             * @brief Get the volume of an audio file
             * @param audioType Type of the audio file to get volume for
             * @return Volume of an audio file
             */
            float getVolumeFor(const AudioType &audioType);

            /**
             * @brief Set the maximum volume for all audio players
             * @param volume The new maximum volume
             *
             * This function will overwrite the previous volume. To offset
             * the volume by a constant @see adjustMaxVolume(float). The
             * maximum volume for all audio players is 100.0 by default
             */
            void setMaxVolume(float volume);

            /**
             * @brief Offset the maximum volume for all audio players
             * @param offset Volume offset
             *
             * This function will add/subtract to/from the current volume.
             * To overwrite the volume @see setMaxVolume(float)
             */
            void adjustMaxVolume(float offset);

            /**
             * @brief Get the maximum volume for all audio players
             * @return The maximum volume for all audio players
             */
            float getMaxVolume() const;

            /**
             * @brief Play all paused/stopped audio files
             */
            void playAllAudio();

            /**
             * @brief Pause all playing audio files
             */
            void pauseAllAudio();

            /**
             * @brief Stop all playing audio files
             *
             * Stopping an audio file (playing/paused) will reset the current
             * playing position to the beginning
             */
            void stopAllAudio();

            /**
             * @param Mute or unmute all audio players
             *
             * Muted audio files will continue playing
             */
            void setMute(bool isMuted);

            /**
             * @brief Add an event listener to a mute event
             * @param callback Function to execute when mute state changes
             */
            void onMute(Callback<bool> callback);

            /**
             * @brief Add an event listener to a volume change event
             * @param callback Function to execute when volume changes
             */
            void onVolumeChanged(Callback<float> callback);

        private:
            //Maximum volume all audio players
            float maxVolume_;
            //Mute state
            bool isMuted_;
            //Handles music
            MusicPlayer musicPlayer_;
            //Handles sound effects
            SoundEffectPlayer sfxPlayer_;
            //Event emitter
            EventEmitter eventEmitter_;
        };
    } // namespace Audio
} // namespace IME

#endif
