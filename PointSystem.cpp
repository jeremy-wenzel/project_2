#include "PointSystem.h"


PointSystem::PointSystem():_currentScore(0), _scoreTotal(0){}


void PointSystem::updateCurrentScore() {
	_currentScore ++;
}

void PointSystem::updateTotalScore() {
	_scoreTotal += _currentScore;
}

int PointSystem::getScore() {
	return _scoreTotal;
}