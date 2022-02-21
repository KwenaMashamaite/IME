////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef IME_AUDIOMANAGER_H
#define IME_AUDIOMANAGER_H

#include "IME/Config.h"
#include "IME/core/audio/Audio.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/core/object/ObjectContainer.h"
#include <string>

namespace ime {
    namespace audio {
        /**
         * @brief Types of audio files played by the audio manager
         */
        enum class Type {
            Sfx,    //!< Sound Effects (Short audio clips, loaded in memory)
            Music   //!< Music (Long audio clips, streamed directly from the drive)
        };

        /**
         * @brief Manages audio playback
         */
        class IME_API AudioManager {
        public:
            /**
             * @brief Default constructor
             */
            AudioManager();

            /**
             * @brief Copy constructor
             */
            AudioManager(const AudioManager&) = delete;

            /**
             * @brief Copy assignment operator
             */
            AudioManager& operator=(const AudioManager&) = delete;

            /**
             * @brief Move constructor
             */
            AudioManager(AudioManager&&) noexcept = default;

            /**
             * @brief Move assignment operator
             */
            AudioManager& operator=(AudioManager&&) noexcept = default;

            /**
             * @brief Play an audio file
             * @param audioType Type of the audio file to play
             * @param filename The filename of the audio to play
             * @throws FileNotFoundException if the audio file cannot be found on the disk
             * @return Pointer to the audio file after it starts playing
             *
             * The audio files are played in a separate thread. This means
             * that, the main thread is not blocked and other audio file may
             * be played simultaneously.
             *
             * Note that the returned pointer may be used to manipulate properties
             * of the audio file such as volume, pitch, loop state etc. However,
             * it must not be kept alive as it will be invalidated when the
             * audio file stops playing. Trying to access the audio file after
             * it has stopped playing is undefined behavior
             */
            Audio* play(Type audioType, const std::string &filename);

            /**
             * @brief Set the volume for an audio type
             * @param audioType The audio type to set the volume for
             * @param volume Volume to set, in the range 0 <= volume <= 100
             *               where 0 is mute and 100 is maximum volume
             *
             * The default volume is 100 (max) for all audio types
             */
            void setVolume(Type audioType, float volume);

            /**
             * @brief Get the volume of an audio type
             * @param audioType The audio type to get the volume for
             * @return The current volume for audio files of the specified type
             */
            float getVolumeFor(Type audioType) const;

            /**
             * @brief Set the maximum volume for all audio types
             * @param volume The new maximum volume
             *
             * By default, the maximum volume for all audio types is 100 (max)
             *
             * @see adjustMasterVolume
             */
            void setMasterVolume(float volume);

            /**
             * @brief Offset the master volume
             * @param offset The value to offset the volume by
             *
             * A positive offset increases the master volume whilst a negative
             * offset decreases it. Note that the master volume cannot be lower
             * that zero (min) or higher than 100 (max)
             *
             * @see setMasterVolume
             */
            void adjustMasterVolume(float offset);

            /**
             * @brief Get the master volume
             * @return The master volume
             *
             * @see setMasterVolume
             */
            float getMasterVolume() const;

            /**
             * @brief Play all paused audio files
             *
             * @see pauseAll and stopAll
             */
            void playAll();

            /**
             * @brief Pause all playing audio files
             *
             * @see playAll and stopAll
             */
            void pauseAll();

            /**
             * @brief Stop all playing audio files
             *
             * @warning When an audio file is stopped (explicitly or when it
             * reaches the end of its playback), it automatically gets removed
             * from the audio manager. This invalidates all pointers to the
             * audio instance
             */
            void stopAll();

            /**
             * @brief Mute or unmute all audio
             * @param isMuted True to mute all audio, otherwise false
             */
            void setMute(bool isMuted);

            /**
             * @brief Add an event listener to a mute event
             * @param callback Function to be executed audio is muted or unmuted
             */
            void onMute(Callback<bool> callback);

            /**
             * @brief Add an event listener to a master volume change event
             * @param callback Function to be executed when the master volume changes
             */
            void onVolumeChanged(Callback<float> callback);

            /**
             * @internal
             * @brief Remove audio that has finished playing
             *
             * @warning This function is intended for internal use only and
             * should never be called outside of IME
             */
            void removePlayedAudio();

        private:
            float masterVolume_;                  //!< Maximum volume for all audio instances
            float sfxVolume_;                     //!< Maximum volume for ime::audio::SoundEffect instances
            float musicVolume_;                   //!< Maximum volume for ime::audio::Music instances
            bool isMuted_;                        //!< A flag indicating whether or not audio is muted
            EventEmitter eventEmitter_;           //!< Publishes audio manager events
            ObjectContainer<Audio> playingAudio_; //!< Playing audio container
        };
    }
}

/**
 * @class ime::AudioManager
 * @ingroup core
 *
 * ime::audio::AudioManager allows us to play multiple audio files at the same
 * time. Each audio file is played in a separate thread.
 *
 * Note that ime::audio::AudioManager is not meant to be instantiated directly,
 * each ime::Scene instance has its own audio manager which can be accessed with
 * ime::Scene::audio. To play audio globally (Audio that keeps playing regardless
 * of which scene is currently active) use ime::Engine::getAudioManager
 *
 * @see ime::audio::Music and ime::audio::SoundEffect
 */

#endif // IME_AUDIOMANAGER_H
