#include "IME/core/audio/AudioManager.h"

namespace IME::Audio{
    AudioManager::AudioManager(const std::string &musicFilePath,
        const std::string &soundEffectFilePath)
        : musicPlayer_(musicFilePath), sfxPlayer_(soundEffectFilePath),
          maxVolume_(100.0f), isMuted_(false)
        {}

    void AudioManager::loadAudioFiles(AudioType audioType,
         std::initializer_list<std::string> filenames)
     {
        if (audioType == AudioType::Music)
            musicPlayer_.loadFromFile(filenames);
        else if (audioType == AudioType::SoundEffect)
            sfxPlayer_.loadFromFile(filenames);
    }

    void AudioManager::play(const AudioType &audioType, const std::string &filename) {
        if (audioType == AudioType::Music)
            musicPlayer_.play(filename);
        else if (audioType == AudioType::SoundEffect)
            sfxPlayer_.play(filename);
    }

    void AudioManager::pauseAll(const AudioType &audioType) {
        if (audioType == AudioType::Music)
            musicPlayer_.pause();
        else if (audioType == AudioType::SoundEffect)
            sfxPlayer_.pause();
    }

    void AudioManager::stopAll(const AudioType &audioType) {
        if (audioType == AudioType::Music)
            musicPlayer_.stop();
        else if (audioType == AudioType::SoundEffect)
            sfxPlayer_.stop();
    }

    void AudioManager::setVolumeFor(const AudioType &audioType, float volume) {
        if (volume > maxVolume_)
            volume = maxVolume_;
        if (audioType == AudioType::Music)
            musicPlayer_.setVolume(volume);
        else if (audioType == AudioType::SoundEffect)
            sfxPlayer_.setVolume(volume);
    }

    void AudioManager::setLoopFor(const AudioType &audioType, bool isLooped) {
        if (audioType == AudioType::Music)
            musicPlayer_.setLoop(isLooped);
        else if (audioType == AudioType::SoundEffect)
            sfxPlayer_.setLoop(isLooped);
    }

    void AudioManager::playAllAudio() {
        musicPlayer_.play();
        sfxPlayer_.play();
    }

    void AudioManager::pauseAllAudio() {
        musicPlayer_.pause();
        sfxPlayer_.stop();
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
            case AudioType::SoundEffect:
                return sfxPlayer_.getVolume();
            case AudioType::Music:
                return musicPlayer_.getVolume();
        }
    }

    void AudioManager::setMaxVolume(float volume) {
        if (maxVolume_ != volume) {
            if (volume > 100.0f)
                maxVolume_ = 100.0f;
            else if (volume < 0.0f)
                maxVolume_ = 0.0f;
            else
                maxVolume_ = volume;
            eventEmitter_.emit("volumeChanged", maxVolume_);
        }
    }

    void AudioManager::adjustMaxVolume(float offset) {
        setMaxVolume(getMaxVolume() + offset);
    }

    float AudioManager::getMaxVolume() const {
        return maxVolume_;
    }

    void AudioManager::playAll(AudioType audioType) {
        if (audioType == AudioType::Music)
            musicPlayer_.play();
        else if (audioType == AudioType::SoundEffect)
            sfxPlayer_.play();
    }

    void AudioManager::onMute(Callback<bool> callback) {
        eventEmitter_.addEventListener("muteChanged", std::move(callback));
    }

    void AudioManager::onVolumeChanged(Callback<float> callback) {
        eventEmitter_.addEventListener("volumeChanged", std::move(callback));
    }
}
