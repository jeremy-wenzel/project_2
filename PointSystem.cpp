#include "PointSystem.h"
#include <iostream>


PointSystem::PointSystem():_scoreCurrent(0), _scoreTotal(0), gameEnds(false){}


void PointSystem::updateCurrentScore() {
	_scoreCurrent ++;
}

void PointSystem::updateTotalScore() {
	_scoreTotal += _scoreCurrent;
	_scoreCurrent = 0;
}

int PointSystem::getScore() {
	return _scoreTotal;
}


int PointSystem::getCurrentScore() {
	return _scoreCurrent;
}
