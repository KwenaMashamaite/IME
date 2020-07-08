#include "Scoreboard.h"
#include "resources/FileReader.h"
#include <algorithm>
#include <sstream>

Scoreboard::Scoreboard(const std::string& filename)
    : currentScore_(0u), highScoresFile_(filename)
{
    auto highScores = std::stringstream();
    Utility::FileReader().readFileInto(highScores, highScoresFile_);
    auto highscore = std::string();
    while(std::getline(highScores, highscore))
        highScores_.push_back(std::stoi(highscore));
}

void Scoreboard::addPoints(int points) {
    currentScore_ += points;
}

void Scoreboard::updateHighScoreFile(){
    if (currentScore_ > highScores_.back()){//Highscores stored in descending order
        highScores_.pop_back();
        highScores_.push_back(currentScore_);
        std::sort(std::begin(highScores_), std::end(highScores_), std::greater<>());
        auto newHighscoreList = std::stringstream();
        newHighscoreList << std::to_string(highScores_.front());
        std::for_each(++highScores_.begin(), highScores_.end(), [&](unsigned int score){
            newHighscoreList << "\n" + std::to_string(score);
        });
        Utility::FileReader().writeToFile(newHighscoreList, highScoresFile_);
    }
}

void Scoreboard::resetCurrentScore(){
    currentScore_ = 0;
}

int Scoreboard::getCurrentScore() const{
    return currentScore_;
}

int Scoreboard::getTopScore() const{
    return highScores_.front();
}

Scoreboard::constIterator Scoreboard::cBegin() const{
    return highScores_.cbegin();
}

Scoreboard::constIterator Scoreboard::cEnd() const{
    return highScores_.cend();
}
