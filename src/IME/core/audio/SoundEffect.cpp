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
    struct SoundEffect::SoundEffectImpl {
        SoundEffectImpl() :
            parent_{nullptr}
        {}

        void setParent(SoundEffect* parent) {
            IME_ASSERT(parent, "Parent cannot be a nullptr")
            parent_ = parent;
        }

        void setSource(const std::string &filename) {
            if (sfxName_ != filename) {
                soundEffect_.setBuffer(ResourceManager::getInstance()->getSoundBuffer(filename));
                sfxName_ = filename;
                parent_->emitChange(Property{"source", sfxName_});
            }
        }

        const std::string &getSource() const {
            return sfxName_;
        }

        void setVolume(float volume) {
            if (volume != soundEffect_.getVolume()
                && (volume >=0 && volume <= 100)) {
                soundEffect_.setVolume(volume);
                parent_->emitChange(Property{"volume", volume});
            }
        }

        float getVolume() const {
            return soundEffect_.getVolume();
        }

        void setPitch(float pitch) {
            soundEffect_.setPitch(pitch);
        }

        float getPitch() const {
            return soundEffect_.getPitch();
        }

        void setLoop(bool isLooped) {
            if (soundEffect_.getLoop() != isLooped) {
                soundEffect_.setLoop(isLooped);
                parent_->emitChange(Property{"loop", isLooped});
            }
        }

        bool isLooped() const {
            return soundEffect_.getLoop();
        }

        void seek(const Time& position) {
            soundEffect_.setPlayingOffset(sf::microseconds(position.asMicroseconds()));
        }

        Time getPlayingPosition() const {
            return microseconds(soundEffect_.getPlayingOffset().asMicroseconds());
        }

        void play() {
            soundEffect_.play();
            parent_->emit("play");
        }

        void pause() {
            if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
                soundEffect_.pause();
                parent_->emit("pause");
            }
        }

        void stop() {
            if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
                soundEffect_.stop();
                parent_->emit("stop");
            }
        }

        Time getDuration() const {
            if (soundEffect_.getBuffer())
                return microseconds(soundEffect_.getPlayingOffset().asMicroseconds());
            return Time::Zero;
        }

        Status getStatus() const {
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

    private:
        sf::Sound soundEffect_; //!< Sound to be played
        std::string sfxName_;   //!< Filename of the audio source
        SoundEffect* parent_;   //!< Backward pointer
    }; // class Impl

    //////////////////////////////////////////////////////////////////////////
    // Delegation
    //////////////////////////////////////////////////////////////////////////

    SoundEffect::SoundEffect() :
        pImpl_{std::make_unique<SoundEffectImpl>()}
    {
        pImpl_->setParent(this);
    }

    SoundEffect::SoundEffect(const SoundEffect& other) :
        Audio(other),
        pImpl_{std::make_unique<SoundEffectImpl>(*other.pImpl_)}
    {
        pImpl_->setParent(this);
    }

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

    std::string SoundEffect::getClassName() const {
        return "SoundEffect";
    }

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

    void SoundEffect::seek(const Time& position) {
       pImpl_->seek(position);
    }

    Time SoundEffect::getPlayingPosition() const {
        return pImpl_->getPlayingPosition();
    }
    
    void SoundEffect::setPitch(float pitch) {
        pImpl_->setPitch(pitch);
    }

    float SoundEffect::getPitch() const {
        return pImpl_->getPitch();
    }

    SoundEffect::~SoundEffect() = default;
}
