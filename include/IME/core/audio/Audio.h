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

#ifndef IME_AUDIO_H
#define IME_AUDIO_H

#include "IME/Config.h"
#include "IME/common/Object.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/core/time/Time.h"
#include <string>

namespace ime {
    namespace audio {
        /**
         * @brief Audio status
         */
        enum class Status {
            Stopped, //!< Audio is not playing
            Paused,  //!< Audio is paused
            Playing  //!< Audio is playing
        };

        /**
         * @brief Abstract base class for audio
         */
        class IME_API Audio : public Object {
        public:
            /**
             * @brief Default constructor
             */
            Audio();

            /**
             * @brief Get the name of this class
             * @return The name of this class
             *
             * Note that this function is only implemented by child classes
             * of Object which also serve as a base class for other classes
             *
             * @see getClassName
             */
            std::string getClassType() const override;

            /**
             * @brief Set audio source to be manipulated
             * @param filename Filename of an audio file
             *
             * The @a filename must refer to an actual audio file on
             * the disk. This audio file is the one to be played,
             * pitched and done all sorts of things
             */
            virtual void setSource(const std::string &filename) = 0;

            /**
             * @brief Get audio source
             * @return Filename of the actual audio file
             */
            virtual const std::string& getSource() const = 0;

            /**
             * @brief Set the volume of the audio
             * @param volume Volume to set
             *
             * The volume is a value between 0 (mute) and 100 (full volume).
             *
             * The default value for the volume is 100
             */
            virtual void setVolume(float volume) = 0;

            /**
             * @brief Turn the volume up/down by a given offset
             * @param offset Value to increase/decrease the volume by
             *
             * This function adds on to the current volume. A positive
             * offset increases the volume while a negative offset
             * decreases the volume. This function will unmmute the
             * audio if its muted
             *
             * @see setMute
             */
            void adjustVolume(float offset);

            /**
             * @brief Get the volume of the audio
             * @return Volume of the audio, in the range [0, 100]
             */
            virtual float getVolume() const = 0;

            /**
             * @brief Set whether or not the audio should be audible
             * @param mute True to make audio inaudible, or false to make
             *             audio audible
             *
             * When set to true the audio will not be audible but will
             * continue to play if currently playing
             */
            void setMute(bool mute);

            /**
             * @brief Check if audio is muted or not
             * @return True if audio is muted or false if audio is not muted
             */
            bool isMuted() const;

            /**
             * @brief Set the pitch of the audio
             * @param pitch The new pitch of the audio
             *
             * The pitch represents the perceived fundamental frequency
             * of a sound; thus you can make a sound more acute or grave
             * by changing its pitch. Changing the pitch also changes
             * the playing speed of the audio.
             *
             * The default value for the pitch is 1
             */
            virtual void setPitch(float pitch) = 0;

            /**
             * @brief Get the pitch of the audio
             * @return The pitch of the audio
             */
            virtual float getPitch() const = 0;

            /**
             * @brief Set whether or not the audio should loop after reaching
             *        the end
             * @param isLooped True to play in loop, false to play once
             */
            virtual void setLoop(bool isLooped) = 0;

            /**
             * @brief Check if audio is looped or not
             * @return True if audio is looped, otherwise false
             */
            virtual bool isLooped() const = 0;

            /**
             * @brief Change the current playing position of the audio
             * @param position New playing position of the audio
             *
             * The playing position can be changed when the audio is
             * either paused or playing. Changing the playing position
             * when the audio is stopped has no effect, since playing
             * the audio would reset its position
             */
            virtual void seek(const Time& position) = 0;

            /**
            * @brief Get the current playing position of the audio
            * @return Current playing position of the audio
            */
            virtual Time getPlayingPosition() const = 0;

            /**
             * @brief Play audio
             *
             * This function starts the audio if it was stopped, resumes
             * it if it was paused, and restarts it from the beginning if
             * it was already playing. This function uses its own thread
             * so that it doesn't block the rest of the program while the
             * audio is played
             */
            virtual void play() = 0;

            /**
             * @brief Pause audio
             *
             * This function pauses the stream if it was playing, otherwise
             * (audio already paused or stopped) it has no effect
             */
            virtual void pause() = 0;

            /**
             * @brief Stop playing the audio
             *
             * This function stops the audio if it was playing or paused,
             * and does nothing if it was already stopped. It also resets
             * the playing position
             */
            virtual void stop() = 0;

            /**
             * @brief Reset the playing position to the beginning
             *
             * This function will reset the playing position without stopping
             * the audio (unlike stop function), which would require play to
             * be called to get the audio to play again
             */
            void restart();

            /**
             * @brief Get the total duration of the audio
             * @return The total duration of the audio
             */
            virtual Time getDuration() const = 0;

            /**
             * @brief Get the current status of the audio (stopped, paused, playing)
             * @return Current status of the audio
             */
            virtual Status getStatus() const = 0;

        private:
            bool isMuted_;           //!< Mute state
            float volumeBeforeMute_; //!< Volume before audio was muted
        };
    }
}

#endif // IME_AUDIO_H

/**
 * @class ime::Audio
 * @ingroup core
 */
