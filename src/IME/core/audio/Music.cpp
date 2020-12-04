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

#include "IME/core/audio/Music.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::Audio {
    void Music::setSource(const std::string &source) {
        if (sourceFilename_ != source) {
            song_ = ResourceManager::getInstance()->getMusic(source);
            sourceFilename_ = source;
        }
    }

    const std::string &Music::getSource() const {
        return sourceFilename_;
    }

    void Music::setLoop(bool isLooped) {
        if (song_ && song_->getLoop() != isLooped) {
            song_->setLoop(isLooped);
            emit("loopChanged", isLooped);
        }
    }

    void Music::pause(){
        if (song_ && song_->getStatus() == sf::Music::Status::Playing) {
            song_->pause();
            emit("paused");
        }
    }

    void Music::play() {
        if (song_) {
            song_->play();
            emit("playing", sourceFilename_);
        }
    }

    void Music::stop() {
        if (song_ && song_->getStatus() == sf::Music::Status::Playing) {
            song_->stop();
            emit("stopped");
        }
    }

    void Music::setVolume(float volume) {
        if (song_ && song_->getVolume() != volume
            && (volume >=0 && volume <= 100)) {
            if (isMuted())
                setMute(false);
            song_->setVolume(volume);
            emit("volumeChanged", volume);
        }
    }

    Status Music::getStatus() const {
        if (song_) {
            switch (song_->getStatus()) {
                case sf::Sound::Status::Playing:
                    return Status::Playing;
                case sf::Sound::Status::Paused:
                    return Status::Paused;
                case sf::Sound::Status::Stopped:
                    return Status::Stopped;
            }
        }
        return Status::Stopped;
    }

    float Music::getVolume() const {
        if (song_)
            return song_->getVolume();
        return 100.0f; //Default volume is maximum
    }

    bool Music::isLooped() const {
        if (song_)
            return song_->getLoop();
        return false;
    }

    Duration Music::getDuration() const {
        if (song_)
            return {song_->getDuration().asSeconds(),
                    static_cast<float>(song_->getDuration().asMilliseconds()),
                    static_cast<float>(song_->getDuration().asMicroseconds())};
        return {0.0f, 0.0f, 0.0f};
    }

    void Music::seek(float position) {
        if (song_) {
            song_->setPlayingOffset(sf::microseconds(position));
            emit("playingPositionChanged", position);
        }
    }

    Duration Music::getPlayingPosition() const {
        if (song_)
            return {song_->getPlayingOffset().asSeconds(),
                    static_cast<float>(song_->getPlayingOffset().asMicroseconds()),
                    static_cast<float>(song_->getPlayingOffset().asMicroseconds())};
        return {0.0f, 0.0f, 0.0f};
    }

    std::string Music::getType() {
        return "Music";
    }

    void Music::setPitch(float pitch) {
        if (song_)
            song_->setPitch(pitch);
    }

    float Music::getPitch() const {
        if (song_)
            return song_->getPitch();
        return 1;
    }
}