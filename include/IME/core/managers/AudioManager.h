////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Class for managing audio
 *
 * This class allows us to play multiple audio files of different types
 * (Music or Sfx, @see @class Music and @class SoundEffectPlayer)
 * simultaneously. Each audio file is played in a separate thread
 */

#ifndef IME_AUDIOMANAGER_H
#define IME_AUDIOMANAGER_H

#include "IME/Config.h"
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
