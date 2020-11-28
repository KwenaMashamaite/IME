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

#include "IME/core/managers/AudioManager.h"
#include "IME/utility/Helpers.h"

namespace IME::Audio{
    AudioManager::AudioManager()
        : masterVolume_{100.0f}, sfxVolume_{100.0f}, musicVolume_{100.0f}, isMuted_(false)
    {}

    void AudioManager::play(AudioType audioType, const std::string &filename, bool isLooped) {
        std::unique_ptr<AudioPlayer> audioPlayer;
        if (audioType == AudioType::Music) {
            audioPlayer = std::move(std::make_unique<MusicPlayer>());
            audioPlayer->setVolume(musicVolume_);
        } else if (audioType == AudioType::Sfx) {
            audioPlayer = std::move(std::make_unique<SoundEffectPlayer>());
            audioPlayer->setVolume(sfxVolume_);
        }
        audioPlayer->setLoop(isLooped);
        audioPlayer->play(filename);
        playingAudio_.push_back(std::move(audioPlayer));
    }

    void AudioManager::setVolumeFor(AudioType audioType, float volume) {
        if (volume > masterVolume_)
            volume = masterVolume_;

        if (audioType == AudioType::Music)
            musicVolume_ = volume;
        else if (audioType == AudioType::Sfx)
            sfxVolume_ = volume;
    }

    void AudioManager::playAllAudio() {
        for (auto& audioPlayer : playingAudio_)
            audioPlayer->play();
    }

    void AudioManager::pauseAllAudio() {
        for (auto& audioPlayer : playingAudio_)
            audioPlayer->pause();
    }

    void AudioManager::stopAllAudio() {
        for (auto& audioPlayer : playingAudio_)
            audioPlayer->stop();
    }

    void AudioManager::setMute(bool isMuted) {
        if (isMuted_ == isMuted)
            return;
        isMuted_ = isMuted;
        for (auto& audioPlayer : playingAudio_)
            audioPlayer->setMute(isMuted);
        eventEmitter_.emit("muteChanged", isMuted_);
    }

    float AudioManager::getVolumeFor(AudioType audioType) {
        switch (audioType) {
            case AudioType::Sfx:
                return sfxVolume_;
            case AudioType::Music:
                return musicVolume_;
        }
        return masterVolume_;
    }

    void AudioManager::setMasterVolume(float volume) {
        if (masterVolume_ != volume) {
            auto wasMusicVolumeSameAsMaster = musicVolume_ == masterVolume_;
            auto wasSfxVolumeSameAsMaster = sfxVolume_ == masterVolume_;
            if (volume > 100.0f)
                masterVolume_ = 100.0f;
            else if (volume < 0.0f)
                masterVolume_ = 0.0f;
            else
                masterVolume_ = volume;

            if (musicVolume_ > masterVolume_ || wasMusicVolumeSameAsMaster)
                musicVolume_ = masterVolume_;

            if (sfxVolume_ > masterVolume_ || wasSfxVolumeSameAsMaster)
                sfxVolume_ = masterVolume_;

            std::for_each(playingAudio_.begin(), playingAudio_.end(),
                [this](auto& audioPlayer) {
                    if (audioPlayer->getType() == "MusicPlayer")
                        audioPlayer->setVolume(musicVolume_);
                    else
                        audioPlayer->setVolume(sfxVolume_);
            });

            eventEmitter_.emit("volumeChanged", masterVolume_);
        }
    }

    void AudioManager::adjustMasterVolume(float offset) {
        setMasterVolume(getMasterVolume() + offset);
    }

    float AudioManager::getMasterVolume() const {
        return masterVolume_;
    }

    void AudioManager::onMute(Callback<bool> callback) {
        eventEmitter_.addEventListener("muteChanged", std::move(callback));
    }

    void AudioManager::onVolumeChanged(Callback<float> callback) {
        eventEmitter_.addEventListener("volumeChanged", std::move(callback));
    }

    void AudioManager::update() {
        playingAudio_.erase(std::remove_if(playingAudio_.begin(), playingAudio_.end(),
            [] (auto& audioPLayer) {
                return audioPLayer->getStatus() == Status::Stopped;
        }), playingAudio_.end());
    }
}
