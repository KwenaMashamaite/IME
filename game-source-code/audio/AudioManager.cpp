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
    auto found = audioFilenames_.find(filename);
    if (found != audioFilenames_.end()){
        std::unique_ptr<IAudioPlayer> audioPlayer;
        if (found->second == AudioType::Music)
            audioPlayer = std::make_unique<MusicPlayer>();
        else
            audioPlayer = std::make_unique<SoundEffectPlayer>();

        audioPlayers_.insert(std::pair(filename, std::move(audioPlayer)));
        audioPlayers_[filename]->play(filename);
    }
}

void Audio::AudioManager::pause(const std::string& filename) {
    auto found = audioPlayers_.find(filename);
    if (found != audioPlayers_.end())
        found->second->pause();
}

void Audio::AudioManager::resume(const std::string &filename) {
    auto found = audioPlayers_.find(filename);
    if (found != audioPlayers_.end())
        found->second->resume();
}

void Audio::AudioManager::stop(const std::string& filename) {
    auto found = audioPlayers_.find(filename);
    if (found != audioPlayers_.end()) {
        audioPlayers_.erase(found);
    }
}

void Audio::AudioManager::pauseAll() {
    std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
        [](const auto& audioPlayer) {
            audioPlayer.second->pause();
        }
    );
}

void Audio::AudioManager::resumeAll() {
    std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
        [](const auto& audioPlayer) {
            audioPlayer.second->resume();
        }
    );
}

void Audio::AudioManager::stopAll() {
    audioPlayers_.clear();
}