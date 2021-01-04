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

#ifndef IME_MUSIC_H
#define IME_MUSIC_H

#include "IME/Config.h"
#include "Audio.h"
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

namespace IME {
    namespace Audio {
        /**
         * @brief Stream music files from disk
         *
         * This class is ideal for playing long and big audio file such
         * as background music. The audio file is not loaded in memory
         * but rather streamed from the disk. Therefore, The file must remain
         * accessible on the disk for as long as its being used. You can
         * use Audio::SoundEffect to play short sounds such as gun shots
         * and explosions
         */
        class IME_API Music final : public Audio {
        public:
            /**
             * @brief Set the music file to be played
             * @param source Filename of an audio file
             *
             * The @a source must refer to an actual music file on the
             * disk. This music file is the one to be played, pitched and
             * done all sorts of things. This function doesn't start the
             * music, it sets the music that will be played when play() is
             * called
             *
             * @see play
             *
             * @warning The music is not loaded but rather streamed continuously
             * from the disk. Therefore the the specified music file must
             * remain accessible for as long as its being used
             */
            void setSource(const std::string &source) override;

            /**
             * @brief Get music source
             * @return Filename of the actual music file
             */
            const std::string& getSource() const override;

            /**
             * @brief Set the volume of the music
             * @param volume Volume to set
             *
             * The volume is a value between 0 (mute) and 100 (full volume).
             *
             * The default value for the volume is 100
             */
            void setVolume(float volume) override;

            /**
             * @brief Get the volume of the music
             * @return Volume of the music, in the range [0, 100]
             */
            float getVolume() const override;

            /**
             * @brief Set the pitch of the music
             * @param pitch The new pitch of the music
             *
             * The pitch represents the perceived fundamental frequency
             * of a sound; thus you can make a sound more acute or grave
             * by changing its pitch. Changing the pitch also changes
             * the playing speed of the music.
             *
             * The default value for the pitch is 1
             */
            void setPitch(float pitch) override;

            /**
             * @brief Get the pitch of the music
             * @return The pitch of the music
             */
            float getPitch() const override;

            /**
             * @brief Set whether or not the music should loop after reaching
             *        the end
             * @param isLooped True to play in loop, false to play once
             */
            void setLoop(bool isLooped) override ;

            /**
             * @brief Check if music is looped or not
             * @return True if music is looped, otherwise false
             */
            bool isLooped() const override;

            /**
             * @brief Change the current playing position of the music
             * @param position New playing position of the music
             *
             * The playing position can be changed when the music is
             * either paused or playing. Changing the playing position
             * when the music is stopped has no effect, since playing
             * the music would reset its position
             */
            void seek(float position) override;

            /**
             * @brief Get the current playing position of the music
             * @return Current playing position of the music
             */
            Duration getPlayingPosition() const override;

            /**
            * @brief Play music
            *
            * This function starts the music if it was stopped, resumes
            * it if it was paused, and restarts it from the beginning if
            * it was already playing. This function uses its own thread
            * so that it doesn't block the rest of the program while the
            * music is played
            */
            void play() override;

            /**
             * @brief Pause music
             *
             * This function pauses the stream if it was playing, otherwise
             * (music already paused or stopped) it has no effect
             */
            void pause() override;

            /**
             * @brief Stop playing the music
             *
             * This function stops the music if it was playing or paused,
             * and does nothing if it was already stopped. It also resets
             * the playing position
             */
            void stop() override;

            /**
             * @brief Get the total duration of the music
             * @return The total duration of the music
             */
            Duration getDuration() const override;

            /**
             * @brief Get the current status of the music (stopped, paused, playing)
             * @return Current status of the music
             */
            Status getStatus() const override;

            /**
             * @brief Get the type of the music
             * @return The type of the music
             */
            std::string getType() override;

        private:
            std::shared_ptr<sf::Music> song_; //!< Music to be played
            std::string sourceFilename_;      //!< Filename of the music file being played
        };
    }
}

#endif // IME_MUSIC_H
