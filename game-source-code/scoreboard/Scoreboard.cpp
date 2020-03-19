#include "Scoreboard.h"
#include <algorithm>
#include <sstream>

using constIterator = std::vector<unsigned int>::const_iterator;

Scoreboard::Scoreboard(const std::string& filename)
    : score_(0u), highScoresFilename_(filename)
{
    auto scoreListBuffer = std::stringstream();
    fileReader_.readFileInto(scoreListBuffer, highScoresFilename_);
    auto line = std::string();
    while(std::getline(scoreListBuffer, line))
        highScores_.push_back(std::stoi(line));
}

void Scoreboard::addPoints(DestroyedEntity destroyedEntity) {
    score_ += static_cast<int>(destroyedEntity);
}

void Scoreboard::addPoints(unsigned int points) {
    score_ += points;
}

void Scoreboard::updateHighScore(){
    if (score_ > highScores_.back()){//Highscores stored in descending order
        highScores_.pop_back();
        highScores_.push_back(score_);
        std::sort(std::begin(highScores_), std::end(highScores_), std::greater<>());
        auto scoreListBuffer = std::stringstream();
        std::for_each(highScores_.begin(), highScores_.end() - 2, [&](unsigned int score){
            scoreListBuffer << std::to_string(score) + "\n";
        });
        scoreListBuffer << std::to_string(highScores_.back()); //No "\n" for last score
        fileReader_.writeToFile(scoreListBuffer, highScoresFilename_);
    }
}

void Scoreboard::reset(){
    score_ = 0u;
}

unsigned int Scoreboard::getScore() const{
    return score_;
}

unsigned int Scoreboard::getTopScore() const{
    return highScores_.front();
}

constIterator Scoreboard::cBegin() const{
    return highScores_.cbegin();
}

constIterator Scoreboard::cEnd() const{
    return highScores_.cend();
}
