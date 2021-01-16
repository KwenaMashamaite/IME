////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
#include "IME/core/audio/Music.h"
#include "IME/core/audio/SoundEffect.h"
#include "IME/core/event/EventEmitter.h"
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <string>

namespace ime {
    namespace audio {
        /**
         * @brief Types of audio files managed by the audio manager
         */
        enum class Type {
            Sfx,    //!< Sound Effects
            Music   //!< Music
        };

        /**
         * @brief Class for managing audio
         *
         * This class allows us to play multiple audio files at the same time.
         * This class can play multiple sound effects at the same time as one
         * music file. Playing another music file while there is a music file
         * playing will replace it. Each audio file is played in a separate
         * thread
         *
         * @see Music and SoundEffect
         */
        class IME_API AudioManager {
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
             * The audio files are played in a separate thread. This means
             * that, the main thread is not blocked and other audio file may
             * be played simultaneously.
             */
            void play(Type audioType, const std::string &filename,
                  bool isLooped = false);

            /**
             * @brief Set the volume for an audio type
             * @param audioType Type of the audio file to set volume for
             * @param volume Volume to set, in the range (mute) 0 <= volume <= 100 (max)
             *
             * The default volume is 100 (max) for all audio types
             */
            void setVolumeFor(Type audioType, float volume);

            /**
             * @brief Get the volume of an audio type
             * @param audioType Type of the audio to get volume for
             * @return The volume for a given audio type
             */
            float getVolumeFor(Type audioType);

            /**
             * @brief Set the maximum volume for all audio types
             * @param volume The new maximum volume
             *
             * This function will overwrite the previous volume The
             * maximum volume for all audio players is 100 by default
             *
             * @see adjustMasterVolume
             */
            void setMasterVolume(float volume);

            /**
             * @brief Offset the maximum volume for all audio players
             * @param offset Volume offset
             *
             * This function will add/subtract to/from the current volume
             *
             * @see setMasterVolume
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
             * @brief Mute or unmute all audio players
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
             * @brief Remove audio that has finished playing
             *
             * The number of audio that played and stopped must not be left
             * to reach 255, otherwise an error would occur and audio will
             * stop playing
             */
            void removePlayedAudio();

        private:
            float masterVolume_;        //!< Maximum volume all audio players
            float sfxVolume_;           //!< Sound effect volume
            float musicVolume_;         //!< Music volume
            bool isMuted_;              //!< Mute state
            EventEmitter eventEmitter_; //!< Event emitter
            std::vector<std::unique_ptr<Audio>> playingAudio_; //!< Playing audio container
        };
    }
}

#endif // IME_AUDIOMANAGER_H
