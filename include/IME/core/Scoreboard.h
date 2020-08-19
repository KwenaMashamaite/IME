/**
 * @brief Class for managing game scores
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>
#include <string>

namespace IME {
    class Scoreboard {
    public:
        using ScoreContainer = std::vector<int>;
        using constIterator = ScoreContainer::const_iterator;

        /**
         * @brief Constructor
         * @param filename The file name (including path) of the file that
         *        contains the highscores
         * @throw FileNotFound If the file cannot be found on the disk
         */
        explicit Scoreboard(const std::string &filename);

        /**
         * @brief Add points to the current score
         * @param points Points to add
         *
         * This function does not overwrite the existing current score,
         * it adds to it. Providing a negative score subtracts from the
         * current score
         */
        void addPoints(int points);

        /**
         * @brief Write scores to highscores file on disk
         *
         * The file is only updated if the current score is greater than
         * the lowest highscore from the last file read
         */
        void updateHighScoreFile();

        /**
         * @brief Reset the current score to zero
         */
        void resetCurrentScore();

        /**
         * @brief Get the current score
         * @return Current score
         */
        int getCurrentScore() const;

        /**
         * @brief Get the highest score
         * @return Highest score
         */
        int getTopScore() const;

        /**
         * @brief  Get a constant iterator that points to the first element
         *         in a high scores container
         * @return A constant iterator that points to the first element in
         *         a high scores container
         */
        constIterator cBegin() const;

        /**
         * @brief  Get a constant iterator that points one past the last
         *         element in a high scores container
         * @return A constant iterator that points one past the last
         *         element in a high scores container
         */
        constIterator cEnd() const;

    private:
        //stores high scores read from disk file
        ScoreContainer highScores_;
        //Stores current score
        int currentScore_;
        //highscores file path on the disk
        std::string highScoresFile_;
    };
} // namespace IME

#endif
