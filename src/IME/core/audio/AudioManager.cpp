#include "IME/core/audio/AudioManager.h"
#include <algorithm>

namespace IME::Audio{
    AudioManager::AudioManager(const std::string &musicFilePath,
        const std::string &soundEffectFilePath)
        : musicFilesPath_(musicFilePath),
        soundEffectFilesPath_(soundEffectFilePath)
        {}

    void AudioManager::loadAudioFiles(AudioType audioType,
         std::initializer_list<std::string> filenames)
     {
        std::for_each(filenames.begin(), filenames.end(), [=](const auto& filename){
            if (audioType == AudioType::Music)
                ResourceManager::loadFromFile(ResourceType::Music, filename);
            else
                ResourceManager::loadFromFile(ResourceType::SoundBuffer, filename);

            audioFilenames_.insert(std::pair(filename, audioType));
        });
    }

    void AudioManager::play(const std::string& filename) {
        if (audioPlayers_.find(filename) != audioPlayers_.end()) {
            audioPlayers_[filename]->play(filename);
            return;
        }

        auto found = audioFilenames_.find(filename);
        if (found != audioFilenames_.end()) {
            std::unique_ptr<AudioPlayer> audioPlayer;
            if (found->second == AudioType::Music)
                audioPlayer = std::make_unique<Audio::MusicPlayer>(musicFilesPath_);
            else
                audioPlayer = std::make_unique<Audio::SoundEffectPlayer>(soundEffectFilesPath_);

            audioPlayer->play(filename);
            audioPlayers_.insert(std::pair(filename, std::move(audioPlayer)));
        }
    }

    void AudioManager::pause(const std::string& filename) {
        auto found = audioPlayers_.find(filename);
        if (found != audioPlayers_.end())
            found->second->pause();
    }

    void AudioManager::stop(const std::string& filename) {
        auto found = audioPlayers_.find(filename);
        if (found != audioPlayers_.end()) {
            found->second->stop();
        }
    }

    void AudioManager::remove(const std::string &filename) {
        auto found = audioPlayers_.find(filename);
        if (found != audioPlayers_.end()) {
            found->second->stop();
            audioPlayers_.erase(found);
        }
    }

    void AudioManager::setVolumeFor(const std::string &filename, float volume) {
        auto found = audioPlayers_.find(filename);
        if (found != audioPlayers_.end())
            found->second->setVolume(volume);
    }

    void AudioManager::setLoopFor(const std::string &filename, bool isLooped) {
        auto found = audioPlayers_.find(filename);
        if (found != audioPlayers_.end())
            found->second->setLoop(isLooped);
    }

    void AudioManager::playAll() {
        std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
            [](const auto& audioPlayer) {
                audioPlayer.second->play();
        });
    }

    void AudioManager::pauseAll() {
        std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
            [](const auto& audioPlayer) {
                audioPlayer.second->pause();
            }
        );
    }

    void AudioManager::stopAll() {
        std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
            [](const auto& audioPlayer) {
                audioPlayer.second->stop();
            }
        );
    }

    float AudioManager::getVolumeFor(const std::string &filename) {
        auto found = audioPlayers_.find(filename);
        if (found != audioPlayers_.end())
            return found->second->getVolume();
        return 0.0f;
    }
}
