#pragma once

class PointSystem {
private:
	int _scoreCurrent;
	int _scoreTotal;
public:
	void updateCurrentScore();
	void updateTotalScore();
	int getScore();
	PointSystem();
	int getCurrentScore();
};