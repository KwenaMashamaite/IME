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
 * @brief Interface for audio players
 */

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "IME/core/event/EventEmitter.h"
#include <initializer_list>
#include <string>

namespace IME {
    namespace Audio {
        /**
         * @brief Audio status
         */
        enum class Status{
            Stopped,
            Paused,
            Playing
        };

        struct Duration {
            float Seconds;
            float Milliseconds;
            float Microseconds;
        };

        class AudioPlayer : public EventEmitter{
        public:
            /**
             * @brief Default constructor
             */
            AudioPlayer();

            /**
             * @brief Play audio
             * @param filename Filename of the audio to play
             */
            virtual void play(const std::string &filename) = 0;

            /**
             * @brief Stop the currently playing or paused audio
             */
            virtual void stop() = 0;

            /**
             * @brief Pause the currently playing audio
             */
            virtual void pause() = 0;

            /**
             * @brief Play paused or stopped audio file
             */
            virtual void play() = 0;

            /**
             * @brief Set the volume of the audio
             * @param volume Volume to set
             *
             * This function completely overrides the current volume. To adjust the
             * volume by a certain offset @see setVolumeOffset
             */
            virtual void setVolume(float volume) = 0;

            /**
             * @brief Set the pitch of the audio file
             * @param pitch The new pitch of the audio file
             *
             * The default pitch is 1
             */
            virtual void setPitch(float pitch) = 0;

            /**
             * @brief Get the pitch of the audio file
             * @return The pitch of the audio file
             */
            virtual float getPitch() const = 0;

            /**
             * @brief Loop/unloop audio
             * @param isLooped Set to true to loop audio, false to unloop audio
             */
            virtual void setLoop(bool isLooped) = 0;

            /**
             * @brief Check if playing audio file is looped or not
             * @return True if audio file is looped, false if audio file is not
             *          looped
             */
            virtual bool isLooped() const = 0;

            /**
             * @brief Check if audio player is muted or not
             * @return True if audio player is muted or false if audio player is
             *         not muted
             */
            bool isMuted() const;

            /**
             * @brief Turn the volume up/down by a given offset
             * @param offset Value to increase/decrease the volume by
             *
             * This function adds on to the current volume of the audio player.
             * A positive offset increases the volume while a negative offset
             * decreases the volume. This function will unmmute the audio player
             * if its muted
             */
            void adjustVolume(float offset);

            /**
             * @brief Get the duration of the current audio file
             * @return Duration of the current audio file
             *
             * The duration is in seconds
             */
            virtual Duration getDuration() const = 0;

            /**
             * @brief Get the current playing position of the audio file
             * @return Current playing position of the audio file
             */
            virtual Duration getPlayingPosition() const = 0;

            /**
             * @brief Change the current playing position of the audio file
             * @param position New playing position of the audio file
             *
             * The new position must be between zero and the duration of the song
             */
            virtual void seek(float position) = 0;

            /**
             * @brief Get the current status of the audio file
             * @return Current status of the audio file
             */
            virtual Status getStatus() const = 0;

            /**
             * @brief Get the volume of an audio file
             * @return Volume of an audio file
             */
            virtual float getVolume() const = 0;

            /**
             * @brief Get the name of the current audio file
             * @return Name of the current audio file
             */
            virtual const std::string& getCurrentAudioFileName() const = 0;

            /**
             * @brief Get the type of the audio player
             * @return The type of the audio player
             */
            virtual std::string getType() = 0;

            /**
             * @brief Mute or ummute the audio
             * @param mute True to mute the audio or false to unmute the audio
             */
            void setMute(bool mute);

            /**
             * @brief Reset the playing position to the beginning (zero)
             */
            void restart();

            /**
             * @brief Destructor
             */
            virtual ~AudioPlayer() = default;

        protected:
            /**
             * @brief Prevent external publishing of events
             *
             * Only the class knows the conditions under which an event may be
             * fired. Therefore, events must not be raised externally as this
             * may result in events being raised at the wong time, resulting
             * in undesired and incorrect behavior
             */
            using EventEmitter::emit;

        private:
            //Muted state
            bool isMuted_;
            //Volume of the music player before it was muted
            float volumeBeforeMute_;
        };
    }
}

#endif
