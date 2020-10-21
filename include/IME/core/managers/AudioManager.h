/**
 * @brief Class for managing audio
 *
 * This class allows us to play multiple audio files of different types
 * (Music or Sfx, @see @class Music and @class SoundEffectPlayer)
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
            Sfx,
            Music
        };

        class AudioManager {
        public:
            /**
             * @brief Default constructor
             */
            AudioManager();

            /**
             * @brief Play an audio file
             * @param audioType Type of the audio file to play
             * @param filename Filename of the audio to play
             * @param isLooped True if audio should be looped, otherwise false
             * @throws FileNotFound if the audio file cannot be found on the disk
             *
             * The audio file are played in a separate thread. This means
             * that, the main thread is not blocked and other audio file may be
             * played simultaneously. @note It's much faster to preload the audio
             * files with the @class ResourceManager rather than having the audio
             * manager load each individual file from the disk before playing it
             */
            void play(AudioType audioType, const std::string &filename,
                      bool isLooped = false);

            /**
             * @brief Set the volume for an audio file
             * @param audioType Type of the audio file to set volume for
             * @param volume Volume to set, in the range (mute) 0 <= volume <= 100 (max)
             *
             * The default volume is 100 (max)
             */
            void setVolumeFor(AudioType audioType, float volume);

            /**
             * @brief Get the volume of an audio file
             * @param audioType Type of the audio file to get volume for
             * @return Volume of an audio file
             */
            float getVolumeFor(AudioType audioType);

            /**
             * @brief Set the maximum volume for all audio players
             * @param volume The new maximum volume
             *
             * This function will overwrite the previous volume. To offset
             * the volume by a constant @see adjustMasterVolume(float). The
             * maximum volume for all audio players is 100.0 by default
             */
            void setMasterVolume(float volume);

            /**
             * @brief Offset the maximum volume for all audio players
             * @param offset Volume offset
             *
             * This function will add/subtract to/from the current volume.
             * To overwrite the volume @see setMasterVolume(float)
             */
            void adjustMasterVolume(float offset);

            /**
             * @brief Get the maximum volume for all audio players
             * @return The maximum volume for all audio players
             */
            float getMasterVolume() const;

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
             * @param isMuted True to mute all audio, otherwise false
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

            /**
             * @brief Update the audio manager
             */
            void update();

        private:
            //Maximum volume all audio players
            float masterVolume_;
            //Sound effect volume
            float sfxVolume_;
            //Music volume
            float musicVolume_;
            //Mute state
            bool isMuted_;
            //Event emitter
            EventEmitter eventEmitter_;
            //Audio players
            std::vector<std::unique_ptr<AudioPlayer>> playingAudio_;
        };
    }
}

#endif
