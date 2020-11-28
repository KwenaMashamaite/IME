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

#include "IME/core/audio/SoundEffectPlayer.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::Audio{
    void SoundEffectPlayer::play(const std::string &filename){
        if (currentEffectName_ != filename) {
            soundEffect_.setBuffer(ResourceManager::getInstance()->getSoundBuffer(filename));
            currentEffectName_ = filename;
        }
        play();
    }

    void SoundEffectPlayer::stop() {
        if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
            soundEffect_.stop();
            emit("stopped");
        }
    }

    void SoundEffectPlayer::pause() {
        if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
            soundEffect_.pause();
            emit("paused");
        }
    }

    void SoundEffectPlayer::play() {
        soundEffect_.play();
        emit("playing", currentEffectName_);
    }

    void SoundEffectPlayer::setVolume(float volume) {
        if (volume != soundEffect_.getVolume()
            && (volume >=0 && volume <= 100)) {
            soundEffect_.setVolume(volume);
            emit("volumeChanged", volume);
        }
    }

    void SoundEffectPlayer::setLoop(bool isLooped) {
        if (soundEffect_.getLoop() != isLooped) {
            soundEffect_.setLoop(isLooped);
            emit("loopChanged", isLooped);
        }
    }

    Status SoundEffectPlayer::getStatus() const {
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

    float SoundEffectPlayer::getVolume() const {
        return soundEffect_.getVolume();
    }

    bool SoundEffectPlayer::isLooped() const {
        return soundEffect_.getLoop();
    }

    Duration SoundEffectPlayer::getDuration() const {
        if (soundEffect_.getBuffer())
            return {soundEffect_.getPlayingOffset().asSeconds(),
                    static_cast<float>(soundEffect_.getBuffer()->getDuration().asMilliseconds()),
                    static_cast<float>(soundEffect_.getPlayingOffset().asMicroseconds())};
        return {0.0f, 0.0f, 0.0f};
    }

    void SoundEffectPlayer::seek(float position) {
        soundEffect_.setPlayingOffset(sf::milliseconds(position));
    }

    const std::string &SoundEffectPlayer::getCurrentAudioFileName() const {
        return currentEffectName_;
    }

    Duration SoundEffectPlayer::getPlayingPosition() const {
        return {soundEffect_.getPlayingOffset().asSeconds(),
                static_cast<float>(soundEffect_.getPlayingOffset().asMilliseconds()),
                static_cast<float>(soundEffect_.getPlayingOffset().asMicroseconds())};
    }

    std::string SoundEffectPlayer::getType() {
        return "SfxPlayer";
    }

    void SoundEffectPlayer::setPitch(float pitch) {
        soundEffect_.setPitch(pitch);
    }

    float SoundEffectPlayer::getPitch() const {
        return soundEffect_.getPitch();
    }
}
