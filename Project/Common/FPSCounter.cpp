#include "FPSCounter.h"

namespace Common
{

FPSCounter::FPSCounter(void)
{
	m_ticksPerSecond	= 0.0f;
	m_timeAtGameStart	= 0.0f;
	m_lastUpdate        = 0.0f;
	m_fpsUpdateInterval = 0.5f;
	m_numFrames         = 0;
	m_fps               = 0.0f;
	m_elapsed			= 0.0f;
	m_previous			= 0.0f;
}

FPSCounter::~FPSCounter(void)
{
}

void FPSCounter::InitGameTime()
{
	// We need to know how often the clock is updated
	if( !QueryPerformanceFrequency( (LARGE_INTEGER *)&m_ticksPerSecond ) )
		m_ticksPerSecond = 1000;

	// If m_timeAtGameStart is 0 then we get the time since
	// the start of the computer when we call GetGameTime()
	m_timeAtGameStart = 0;
	m_timeAtGameStart = GetGameTime();
	m_previous = m_timeAtGameStart;
}

// Called every time you need the current game time
float FPSCounter::GetGameTime()
{
	UINT64 ticks;
	float time;

	// This is the number of clock ticks since start
	if( !QueryPerformanceCounter( (LARGE_INTEGER *)&ticks ) )
		ticks = (UINT64)timeGetTime();

	// Divide by frequency to get the time in seconds
	time = (float)(__int64)ticks / (float)(__int64)m_ticksPerSecond;

	// Subtract the time at game start to get
	// the time since the game started
	time -= m_timeAtGameStart;

	m_elapsed = time - m_previous;
	m_previous = time;

	return time;
}

// Called once for every frame
void FPSCounter::Update()
{
	m_numFrames++;
	float currentUpdate = GetGameTime();
	if( currentUpdate - m_lastUpdate > m_fpsUpdateInterval )
	{
		m_fps = m_numFrames / ( currentUpdate - m_lastUpdate );
		m_lastUpdate = currentUpdate;
		m_numFrames = 0;
	}
}

}