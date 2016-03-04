#include "PointSystem.h"
#include <iostream>



PointSystem::PointSystem()
:_scoreCurrent(0), _scoreTotal(0), _highScore(0), gameEnds(false){}


void PointSystem::updateCurrentScore() {
	_scoreCurrent++;
	_scoreTotal++;
}

void PointSystem::resetCurrent() {
	_scoreCurrent = 0;
}

void PointSystem::resetTotal() {
	_scoreTotal = 0;
}

// Returns true if highScore is updated
// Returns false if not
bool PointSystem::updateHighScore() {
	if (_highScore < _scoreTotal) {
		_highScore = _scoreTotal;
		return true;
	}
	return false;
}

int PointSystem::getScore() {
	return _scoreTotal;
}


int PointSystem::getCurrentScore() {
	return _scoreCurrent;
}


int PointSystem::getHighScore() {
	return _highScore;
}

