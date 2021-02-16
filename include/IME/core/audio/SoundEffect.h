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

#ifndef IME_SOUNDEFFECT_H
#define IME_SOUNDEFFECT_H

#include "IME/Config.h"
#include "Audio.h"
#include <memory>

namespace ime {
    namespace audio {
        /**
         * @brief Play sound effects (Short audio clips)
         *
         * This class loads the audio file to be played in memory.
         * Therefore, it is advised to use it with short audio files
         * that can be quickly loaded form the disk and into the
         * program. Example, gun shots and explosions. If long audio
         * files are used with this class you might experience audio
         * latency and other issues. It is advised to use Audio::Music
         * for long sounds such as background music.
         */
        class IME_API SoundEffect final : public Audio {
        public:
            /**
             * @brief Default constructor
             */
            SoundEffect();

            /**
             * @brief Set the sound effect file to be played
             * @param source Filename of an audio file
             *
             * The @a source must refer to an actual audio file on the
             * disk. This audio file is the one to be played, pitched and
             * done all sorts of things. This function doesn't start the
             * sound effect, it sets the sound effect that will be played
             * when play is called
             *
             * @see play
             */
            void setSource(const std::string &source) override;

            /**
             * @brief Get sound effect source
             * @return Filename of the actual sound effect file
             */
            const std::string& getSource() const override;

            /**
             * @brief Set the volume of the sound effect
             * @param volume Volume to set
             *
             * The volume is a value between 0 (mute) and 100 (full volume).
             *
             * The default value for the volume is 100
             */
            void setVolume(float volume) override;

            /**
             * @brief Get the volume of the sound effect
             * @return Volume of the sound effect, in the range [0, 100]
             */
            float getVolume() const override;

            /**
             * @brief Set the pitch of the sound effect
             * @param pitch The new pitch of the sound effect
             *
             * The pitch represents the perceived fundamental frequency
             * of a sound; thus you can make a sound more acute or grave
             * by changing its pitch. Changing the pitch also changes
             * the playing speed of the sound effect.
             *
             * The default value for the pitch is 1
             */
            void setPitch(float pitch) override;

            /**
             * @brief Get the pitch of the sound effect
             * @return The pitch of the sound effect
             */
            float getPitch() const override;

            /**
             * @brief Set whether or not the sound effect should loop after
             *        reaching the end
             * @param isLooped True to play in loop, false to play once
             */
            void setLoop(bool isLooped) override ;

            /**
             * @brief Check if sound effect is looped or not
             * @return True if sound effect is looped, otherwise false
             */
            bool isLooped() const override;

            /**
             * @brief Change the current playing position of the sound effect
             * @param position New playing position of the sound effect
             *
             * The playing position can be changed when the sound effect
             * is either paused or playing. Changing the playing position
             * when the sound effect is stopped has no effect, since playing
             * the sound effect would reset its position
             */
            void seek(Time position) override;

            /**
             * @brief Get the current playing position of the sound effect
             * @return Current playing position of the sound effect
             */
            Time getPlayingPosition() const override;

            /**
            * @brief Play sound effect
            *
            * This function starts the sound effect if it was stopped,
            * resumes it if it was paused, and restarts it from the
            * beginning if it was already playing. This function uses
            * its own thread so that it doesn't block the rest of the
            * program while the sound effect is played
            */
            void play() override;

            /**
             * @brief Pause sound effect
             *
             * This function pauses the stream if it was playing, otherwise
             * (sound effect already paused or stopped) it has no effect
             */
            void pause() override;

            /**
             * @brief Stop playing the sound effect
             *
             * This function stops the sound effect if it was playing or
             * paused, and does nothing if it was already stopped. It also
             * resets the playing position
             */
            void stop() override;

            /**
             * @brief Get the total duration of the sound effect
             * @return The total duration of the sound effect
             */
            Time getDuration() const override;

            /**
             * @brief Get the current status of the sound effect
             * @return Current status of the sound effect
             */
            Status getStatus() const override;

            /**
             * @brief Get the type of the audio
             * @return The type of the audio
             */
            std::string getType() override;

            /**
             * @brief Destructor
             */
            ~SoundEffect();

        private:
            struct Impl;
            std::unique_ptr<Impl> pImpl_;
        };
    }
}

#endif // IME_SOUNDEFFECT_H
