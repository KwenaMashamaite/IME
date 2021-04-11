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

#include "IME/core/audio/SoundEffect.h"
#include "IME/core/resources/ResourceManager.h"
#include <SFML/Audio/Sound.hpp>

namespace ime::audio {
    //////////////////////////////////////////////////////////////////////////
    // SoundEffect implementation
    //////////////////////////////////////////////////////////////////////////
    struct SoundEffect::Impl : public Audio {
        void setSource(const std::string &filename) override {
            if (sfxName_ != filename) {
                soundEffect_.setBuffer(ResourceManager::getInstance()->getSoundBuffer(filename));
                sfxName_ = filename;
            }
        }

        const std::string &getSource() const override {
            return sfxName_;
        }

        void setVolume(float volume) override {
            if (volume != soundEffect_.getVolume()
                && (volume >=0 && volume <= 100)) {
                soundEffect_.setVolume(volume);
                emit("volumeChanged", volume);
            }
        }

        float getVolume() const override {
            return soundEffect_.getVolume();
        }

        void setPitch(float pitch) override {
            soundEffect_.setPitch(pitch);
        }

        float getPitch() const override {
            return soundEffect_.getPitch();
        }

        void setLoop(bool isLooped) override {
            if (soundEffect_.getLoop() != isLooped) {
                soundEffect_.setLoop(isLooped);
                emit("loopChanged", isLooped);
            }
        }

        bool isLooped() const override {
            return soundEffect_.getLoop();
        }

        void seek(Time position) override {
            soundEffect_.setPlayingOffset(sf::microseconds(position.asMicroseconds()));
        }

        Time getPlayingPosition() const override {
            return microseconds(soundEffect_.getPlayingOffset().asMicroseconds());
        }

        void play() override {
            soundEffect_.play();
            emit("playing", sfxName_);
        }

        void pause() override {
            if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
                soundEffect_.pause();
                emit("paused");
            }
        }

        void stop() override {
            if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
                soundEffect_.stop();
                emit("stopped");
            }
        }

        Time getDuration() const override {
            if (soundEffect_.getBuffer())
                return microseconds(soundEffect_.getPlayingOffset().asMicroseconds());
            return Time::Zero;
        }

        Status getStatus() const override {
            switch (soundEffect_.getStatus()) {
                case sf::SoundSource::Status::Playing:
                    return Status::Playing;
                case sf::SoundSource::Status::Paused:
                    return Status::Paused;
                case sf::SoundSource::Status::Stopped:
                    return Status::Stopped;
            }
            return Status::Stopped;
        }

        std::string getType() override {
            return "SoundEffect";
        }

    private:
        sf::Sound soundEffect_; //!< Sound to be played
        std::string sfxName_;   //!< Filename of the audio source
    }; // class Impl

    //////////////////////////////////////////////////////////////////////////
    // Delegation
    //////////////////////////////////////////////////////////////////////////

    SoundEffect::SoundEffect() :
        pImpl_{std::make_unique<Impl>()}
    {}

    SoundEffect::SoundEffect(const SoundEffect& other) :
        Audio(other),
        pImpl_{std::make_unique<Impl>(*other.pImpl_)}
    {}

    SoundEffect &SoundEffect::operator=(const SoundEffect& rhs) {
        if (this != &rhs) {
            Audio::operator=(rhs);
            auto temp{rhs};
            std::swap(pImpl_, temp.pImpl_);
        }

        return *this;
    }

    SoundEffect::SoundEffect(SoundEffect &&) noexcept = default;
    SoundEffect &SoundEffect::operator=(SoundEffect &&) noexcept = default;

    void SoundEffect::setSource(const std::string &filename){
        pImpl_->setSource(filename);
    }

    const std::string &SoundEffect::getSource() const {
        return pImpl_->getSource();
    }

    void SoundEffect::play() {
        pImpl_->play();
    }

    void SoundEffect::pause() {
        pImpl_->pause();
    }

    void SoundEffect::stop() {
        pImpl_->stop();
    }

    void SoundEffect::setVolume(float volume) {
        pImpl_->setVolume(volume);
    }

    void SoundEffect::setLoop(bool isLooped) {
        pImpl_->setLoop(isLooped);
    }

    Status SoundEffect::getStatus() const {
        return pImpl_->getStatus();
    }

    float SoundEffect::getVolume() const {
        return pImpl_->getVolume();
    }

    bool SoundEffect::isLooped() const {
        return pImpl_->isLooped();
    }

    Time SoundEffect::getDuration() const {
        return pImpl_->getDuration();
    }

    void SoundEffect::seek(Time position) {
       pImpl_->seek(position);
    }

    Time SoundEffect::getPlayingPosition() const {
        return pImpl_->getPlayingPosition();
    }

    std::string SoundEffect::getType() {
        return pImpl_->getType();
    }

    void SoundEffect::setPitch(float pitch) {
        pImpl_->setPitch(pitch);
    }

    float SoundEffect::getPitch() const {
        return pImpl_->getPitch();
    }

    SoundEffect::~SoundEffect() = default;
}
