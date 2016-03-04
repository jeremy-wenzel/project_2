#pragma once

class PointSystem {
private:
	int _scoreCurrent;
	int _scoreTotal;
	int _highScore;
public:
	PointSystem();
	void updateCurrentScore();
	void resetCurrent();
	void resetTotal();
	int getScore();
	int getCurrentScore();
	int getHighScore();
	void updateHighScore();
};