#ifndef _MY_APP_H_
#define _MY_APP_H_

#include <windows.h>
#include "WinKeyboard.h"
#include "StateMachine.h"
#include "HashTable.h"
#include "StateInfo.h"
#include "RenderObject.h"

namespace demoscene
{
	class MyApp
	{
		public:
			MyApp	(void);
			~MyApp	(void);

			// basic methods
			void Init		(HWND hWnd);
			void Update		(void);
			void Render		(void);
			void Shutdown	(void);

			// debug text rendering
			void DrawText		 (void);
			void GetDrawModeText (WCHAR buff[]);
			void GetLightModeText (WCHAR buff[]);

			// member variables
			renderer::Renderer				m_renderer;
			StateMachine<DEMOSCENE_STATE>	m_stateManager;
			WinKeyboard						m_keyboard;
			renderer::Camera*				m_camera;
			FPSCounter						m_fpsCounter;
			float							m_totalTime;
			int								m_totalPolys;
			int								m_totalVerts;
			int								m_numPolys;
			int								m_numVerts;
			int								m_polysDrawn;
	};
} // end of namespace
#endif // end of _MY_APP_H_