#include "StdAfx.h"
#include "GameTime.h"

GameTime::GameTime(void)
{
	this->_elapsedTime = 0;
	this->_totalTime = 0;
}

GameTime::~GameTime(void)
{
}

void GameTime::Update()
{
	_elapsedTime = _totalTime;
	_totalTime = timeGetTime();
	_elapsedTime = _totalTime - _elapsedTime;
}

//Returnd the seconds from last frame
double GameTime::GetElapsedTime() const
{
	return double( this->_elapsedTime );
}

double GameTime::GetTotalTime() const
{
	return double( _totalTime );
}