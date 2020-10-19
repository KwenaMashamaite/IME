#include "IME/core/managers/AudioManager.h"

namespace IME::Audio{
    AudioManager::AudioManager()
        : masterVolume_(100.0f), isMuted_(false)
    {}

    void AudioManager::play(const AudioType &audioType, const std::string &filename,
        bool isLooped)
    {
        if (audioType == AudioType::Music)
            musicPlayer_.play(filename);
        else if (audioType == AudioType::Sfx)
            sfxPlayer_.play(filename);
    }

    void AudioManager::pauseAll(const AudioType &audioType) {
        if (audioType == AudioType::Music)
            musicPlayer_.pause();
        else if (audioType == AudioType::Sfx)
            sfxPlayer_.pause();
    }

    void AudioManager::stopAll(const AudioType &audioType) {
        if (audioType == AudioType::Music)
            musicPlayer_.stop();
        else if (audioType == AudioType::Sfx)
            sfxPlayer_.stop();
    }

    void AudioManager::setVolumeFor(const AudioType &audioType, float volume) {
        if (volume > masterVolume_)
            volume = masterVolume_;
        if (audioType == AudioType::Music)
            musicPlayer_.setVolume(volume);
        else if (audioType == AudioType::Sfx)
            sfxPlayer_.setVolume(volume);
    }

    void AudioManager::playAllAudio() {
        musicPlayer_.play();
        sfxPlayer_.play();
    }

    void AudioManager::pauseAllAudio() {
        musicPlayer_.pause();
        sfxPlayer_.pause();
    }

    void AudioManager::stopAllAudio() {
        musicPlayer_.stop();
        sfxPlayer_.stop();
    }

    void AudioManager::setMute(bool isMuted) {
        if (isMuted_ == isMuted)
            return;
        musicPlayer_.setMute(isMuted);
        sfxPlayer_.setMute(isMuted);
        eventEmitter_.emit("muteChanged", isMuted_);
    }

    float AudioManager::getVolumeFor(const AudioType &audioType) {
        switch (audioType) {
            case AudioType::Sfx:
                return sfxPlayer_.getVolume();
            case AudioType::Music:
                return musicPlayer_.getVolume();
        }
    }

    void AudioManager::setMasterVolume(float volume) {
        if (masterVolume_ != volume) {
            if (volume > 100.0f)
                masterVolume_ = 100.0f;
            else if (volume < 0.0f)
                masterVolume_ = 0.0f;
            else
                masterVolume_ = volume;
            eventEmitter_.emit("volumeChanged", masterVolume_);
        }
    }

    void AudioManager::adjustMasterVolume(float offset) {
        setMasterVolume(getMasterVolume() + offset);
    }

    float AudioManager::getMasterVolume() const {
        return masterVolume_;
    }

    void AudioManager::playAll(AudioType audioType) {
        if (audioType == AudioType::Music)
            musicPlayer_.play();
        else if (audioType == AudioType::Sfx)
            sfxPlayer_.play();
    }

    void AudioManager::onMute(Callback<bool> callback) {
        eventEmitter_.addEventListener("muteChanged", std::move(callback));
    }

    void AudioManager::onVolumeChanged(Callback<float> callback) {
        eventEmitter_.addEventListener("volumeChanged", std::move(callback));
    }
}
