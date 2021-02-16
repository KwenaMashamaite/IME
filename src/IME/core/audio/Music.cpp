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

#include "IME/core/audio/Music.h"
#include "IME/core/resources/ResourceManager.h"
#include <SFML/Audio/Music.hpp>

namespace ime::audio {
    //////////////////////////////////////////////////////////////////////////
    // Music implementation
    //////////////////////////////////////////////////////////////////////////
    struct Music::Impl : public Audio {
        Impl() :
            song_{std::make_shared<sf::Music>()}
        {}

        void setSource(const std::string &source) override {

            if (sourceFilename_ != source) {
                if (!(*song_).openFromFile(source))
                    throw FileNotFound(R"(cannot find file ")" + source + R"(")");
                sourceFilename_ = source;
            }
        }

        const std::string &getSource() const override {
            return sourceFilename_;
        }

        void setVolume(float volume) override {
            if (song_ && song_->getVolume() != volume
                && (volume >=0 && volume <= 100)) {
                if (isMuted())
                    setMute(false);
                song_->setVolume(volume);
                emit("volumeChanged", volume);
            }
        }

        float getVolume() const override {
            if (song_)
                return song_->getVolume();
            return 100.0f; //Default volume is maximum
        }

        void setPitch(float pitch) override {
            if (song_)
                song_->setPitch(pitch);
        }

        float getPitch() const override {
            if (song_)
                return song_->getPitch();
            return 1;
        }

        void setLoop(bool isLooped) override {
            if (song_ && song_->getLoop() != isLooped) {
                song_->setLoop(isLooped);
                emit("loopChanged", isLooped);
            }
        }

        bool isLooped() const override {
            if (song_)
                return song_->getLoop();
            return false;
        }

        void seek(Time position) override {
            if (song_) {
                song_->setPlayingOffset(sf::microseconds(position.asMicroseconds()));
                emit("playingPositionChanged", position);
            }
        }

        Time getPlayingPosition() const override {
            if (song_)
                return microseconds(song_->getPlayingOffset().asMicroseconds());
            return Time::Zero;
        }

        void play() override {
            if (song_) {
                song_->play();
                emit("playing", sourceFilename_);
            }
        }

        void pause() override {
            if (song_ && song_->getStatus() == sf::Music::Status::Playing) {
                song_->pause();
                emit("paused");
            }
        }

        void stop() override {
            if (song_ && song_->getStatus() == sf::Music::Status::Playing) {
                song_->stop();
                emit("stopped");
            }
        }

        Time getDuration() const override {
            if (song_)
                return microseconds(song_->getDuration().asMicroseconds());
            return Time::Zero;
        }

        Status getStatus() const override {
            if (song_) {
                switch (song_->getStatus()) {
                    case sf::Music::Status::Playing:
                        return Status::Playing;
                    case sf::Music::Status::Paused:
                        return Status::Paused;
                    case sf::Music::Status::Stopped:
                        return Status::Stopped;
                }
            }
            return Status::Stopped;
        }

        std::string getType() override {
            return "Music";
        }

        ~Impl() override = default;

    private:
        std::shared_ptr<sf::Music> song_; //!< Music to be played
        std::string sourceFilename_;      //!< Filename of the music file being played
    }; // class Impl

    //////////////////////////////////////////////////////////////////////////
    // Delegation
    //////////////////////////////////////////////////////////////////////////

    Music::Music() :
        pImpl_{std::make_unique<Impl>()}
    {}

    void Music::setSource(const std::string &source) {
        pImpl_->setSource(source);
    }

    const std::string &Music::getSource() const {
        return pImpl_->getSource();
    }

    void Music::setVolume(float volume) {
        pImpl_->setVolume(volume);
    }

    float Music::getVolume() const {
        return pImpl_->getVolume();
    }

    void Music::setPitch(float pitch) {
        pImpl_->setPitch(pitch);
    }

    float Music::getPitch() const {
        return pImpl_->getPitch();
    }

    void Music::setLoop(bool isLooped) {
        pImpl_->setLoop(isLooped);
    }

    bool Music::isLooped() const {
        return pImpl_->isLooped();
    }

    void Music::play() {
        pImpl_->play();
    }

    void Music::pause(){
        pImpl_->pause();
    }

    void Music::stop() {
        pImpl_->stop();
    }

    Status Music::getStatus() const {
        return pImpl_->getStatus();
    }

    Time Music::getDuration() const {
        return pImpl_->getDuration();
    }

    void Music::seek(Time position) {
        pImpl_->seek(position);
    }

    Time Music::getPlayingPosition() const {
        return pImpl_->getPlayingPosition();
    }

    std::string Music::getType() {
        return pImpl_->getType();
    }

    Music::~Music() = default;
}
