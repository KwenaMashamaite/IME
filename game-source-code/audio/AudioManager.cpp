#include "AudioManager.h"
#include "resources/ResourceManager.h"
#include <algorithm>

void Audio::AudioManager::loadAudioFiles(AudioType audioType,
     std::initializer_list<std::string> filenames)
 {
    std::for_each(filenames.begin(), filenames.end(), [=](const auto& filename){
        if (audioType == AudioType::Music)
            ResourceManager::load(ResourceId::MUSIC, filename);
        else
             ResourceManager::load(ResourceId::SOUND_BUFFER, filename);

        audioFilenames_.insert(std::pair(filename, audioType));
    });
}

void Audio::AudioManager::play(const std::string& filename) {
    if (audioPlayers_.find(filename) != audioPlayers_.end()) {
        audioPlayers_[filename]->play(filename);
        return;
    }

    auto found = audioFilenames_.find(filename);
    if (found != audioFilenames_.end()) {
        std::unique_ptr<IAudioPlayer> audioPlayer;
        if (found->second == AudioType::Music)
            audioPlayer = std::make_unique<MusicPlayer>();
        else
            audioPlayer = std::make_unique<SoundEffectPlayer>();

        audioPlayer->play(filename);
        audioPlayers_.insert(std::pair(filename, std::move(audioPlayer)));
    }
}

void Audio::AudioManager::pause(const std::string& filename) {
    auto found = audioPlayers_.find(filename);
    if (found != audioPlayers_.end())
        found->second->pause();
}

void Audio::AudioManager::stop(const std::string& filename) {
    auto found = audioPlayers_.find(filename);
    if (found != audioPlayers_.end()) {
        found->second->stop();
    }
}

void Audio::AudioManager::remove(const std::string &filename) {
    auto found = audioPlayers_.find(filename);
    if (found != audioPlayers_.end()) {
        found->second->stop();
        audioPlayers_.erase(found);
    }
}

void Audio::AudioManager::setVolumeFor(const std::string &filename, float volume) {
    auto found = audioPlayers_.find(filename);
    if (found != audioPlayers_.end())
        found->second->setVolume(volume);
}

void Audio::AudioManager::setLoopFor(const std::string &filename, bool isLooped) {
    auto found = audioPlayers_.find(filename);
    if (found != audioPlayers_.end())
        found->second->setLoop(isLooped);
}

void Audio::AudioManager::playAll() {
    std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
        [](const auto& audioPlayer) {
            audioPlayer.second->resume();
    });
}

void Audio::AudioManager::pauseAll() {
    std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
        [](const auto& audioPlayer) {
            audioPlayer.second->pause();
        }
    );
}

void Audio::AudioManager::stopAll() {
    std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
        [](const auto& audioPlayer) {
            audioPlayer.second->stop();
        }
    );
}

float Audio::AudioManager::getVolumeFor(const std::string &filename) {
    auto found = audioPlayers_.find(filename);
    if (found != audioPlayers_.end())
        return found->second->getVolume();
    return 0.0f;
}
