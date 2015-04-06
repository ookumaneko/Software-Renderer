#ifndef _SPIRAL_STATE_H_
#define _SPIRAL_STATE_H_
#include "DemoState.h"
#include "StateInfo.h"
#include "Mesh.h"
#include <vector>
#include "RenderObject.h"

namespace demoscene
{
	class SpiralState : public DemoState<DEMOSCENE_STATE> 
	{
		public:
			SpiralState(DEMOSCENE_STATE type, renderer::Renderer* renderer, renderer::Camera* camera);
			~SpiralState(void);

			bool			OnBegin	(void);
			bool			OnEnd	(void);
			DEMOSCENE_STATE	Update	(float delta);
			DEMOSCENE_STATE	Draw	(float delta);	

		private:
			SpiralState(void) {};

			// member variable
			std::vector<RenderObject>			m_objects;
			renderer::LightDirectional			m_dLight;
			Maths::Vector4						m_camPos;
			float								m_rotation;
			float								m_rotateAddition;
			int									m_numObjects;
	};
} // end of namespace
#endif // end of _SPIRAL_STATE_H_