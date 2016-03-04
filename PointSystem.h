#pragma once

class PointSystem {
private:
	int _scoreCurrent;
	int _scoreTotal;
	int _highScore;
public:
	bool gameEnds;
	void updateCurrentScore();
	void resetCurrent();
	void resetTotal();
	int getScore();
	PointSystem();
	int getCurrentScore();
	int getHighScore();
	void updateHighScore();
};