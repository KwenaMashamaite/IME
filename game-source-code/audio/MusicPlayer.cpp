#include "resources/ResourceManager.h"
#include "MusicPlayer.h"

void Audio::MusicPlayer::play(const std::string &song){
    song_ = ResourceManager::getMusic(song);
    if (song_ != nullptr)
        song_->play();
}

void Audio::MusicPlayer::setLoop(bool isLoop){
    if(song_ != nullptr)
        song_->setLoop(isLoop);
}

void Audio::MusicPlayer::pause(){
    if(song_ != nullptr)
        song_->pause();
}

void Audio::MusicPlayer::resume(){
    if(song_ != nullptr && song_->getStatus() == sf::Music::Status::Paused)
        song_->play();
}

void Audio::MusicPlayer::stop() {
    if (song_ != nullptr)
        song_->stop();
}