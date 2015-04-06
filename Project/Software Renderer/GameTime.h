#pragma once
#include <windows.h>

class GameTime
{
	public:
		GameTime(void);
		~GameTime(void);
	public:
		void Update(void);
	public:
		double GetTotalTime() const;
		double GetElapsedTime() const;
	private:
		DWORD _totalTime;
		DWORD _elapsedTime;
};
