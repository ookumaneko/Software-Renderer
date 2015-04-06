//Code Based on tutorial at: 
//http://www.angelcode.com/dev/timefps/timefps.asp

#ifndef _FPS_COUNTER_H_
#define _FPS_COUNTER_H_
#include <windows.h>
#include "CommonLibDef.h"

namespace Common 
{
	class DECLSPEC FPSCounter
	{
		public:
			FPSCounter(void);
			~FPSCounter(void);

			// Accessors
			inline float GetFPS			(void) const { return m_fps; }
			inline float GetElapsedTime	(void) const { return m_elapsed; }

			// Time management
			void		InitGameTime	(void);
			void		Update			(void);
			float		GetGameTime		(void);


		private:
			// member variables
			float	m_timeAtGameStart;
			float	m_lastUpdate;
			float	m_fpsUpdateInterval;
			float	m_fps;
			float	m_previous;
			float	m_elapsed;
			UINT64	m_ticksPerSecond;
			int		m_numFrames;
	};

} // end of namespace Common

#endif// end of ifndef _FPS_COUNTER_H_