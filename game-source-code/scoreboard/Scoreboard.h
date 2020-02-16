/**
 * @brief Stores highscores from previous game plays
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "utility/FileReader.h"
#include <vector>

/**
 * @brief Defines entities that are worth points and their corresponding points
 *
 * The entries provided below are placeholders for illustration purposes. Please
 * remove this comment after adding the appropriate entries to the enum. You may
 * leave the "@brief" tag as it is or update it
 */
enum class DestroyedEntity{
    EnemyBullet = 10, //Adds 10 points to current score
    InvisibleEnemy = 50,
    FlyingEnemy = 100
};

class Scoreboard{
public:
    using ScoreContainer = std::vector<unsigned int>;
	using constIterator = ScoreContainer::const_iterator;
	/**
	 * @brief Constructor
     * @param filepath File name of the file that contains the scores
     * @throw FileNotFound If the file cannot be found on the disk
     *
     * The file name must be preceded by the path to the file. In addition,
	 * the file that contains the highscores must be in the same folder as
	 * the generated executable file (or be in a subfolder of the generated
	 * executable file's folder), otherwise a "FileNotFound" exception will
	 * be thrown
     *
     * (e.g executables/resources/highscores/highscore.txt)
	 */
	explicit Scoreboard(const std::string& filename);

	/**
	 * @brief Add points to the current score
	 * @param destroyedEntity Score to add to current score
	 *
	 * The integer value associated with the provided argument determines the
	 * amount of points that are added to the current score
 	 */
    void addPoints(DestroyedEntity destroyedEntity);

    /**
     * @brief Add points to the current score
     * @param points Points to add
     */
    void addPoints(unsigned int points);

	/**
	 * @brief Write scores to disk file
	 *
	 * The disk file is only updated if the current score is greater than the lowest
	 * highscore from the last file read
	 */
	void updateHighScore();

	/**
	 * @brief Reset the current score to zero
	 */
	void reset();

	/**
	 * @brief Get the current score
	 * @return Current score
	 */
	unsigned int getScore() const;

	/**
	 * @brief Get the highest score
	 * @return Highest score
	 */
	unsigned int getTopScore() const;

	/**
	 * @brief Get a constant iterator that points to the first element in a
	 *        high scores container
	 * @return A constant iterator that points to the first element in a high
	 *         scores container
	 */
	constIterator cBegin() const;

	/**
	 * @brief Get a constant iterator that points one past the last element in a
	 *        high scores container
	 * @return A constant iterator that points one past the last element in a
	 *         high scores container
	 */
	constIterator cEnd() const;

private:
	//Reads/writes high scores from/to disk file
	Utility::FileReader fileReader_;
	//stores high scores read from disk file
	ScoreContainer highScores_;
	//Stores current score
	unsigned int score_;
	//highscores file path on the disk
	std::string highScoresFilename_;
};

#endif
