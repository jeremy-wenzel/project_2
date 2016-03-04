#pragma once

class PointSystem {
private:
	int _scoreCurrent;
	int _scoreTotal;
	int _highScore;
public:
	PointSystem();
	bool gameEnds;
	bool gameStarts;
	bool gamePaused;
	void updateCurrentScore();
	void resetCurrent();
	void resetTotal();
	int getScore();
	int getCurrentScore();
	int getHighScore();
	bool updateHighScore();
};