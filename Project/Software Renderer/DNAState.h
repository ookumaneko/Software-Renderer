#ifndef _DNA_STATE_H_
#define _DNA_STATE_H_
#include "DemoState.h"
#include "StateInfo.h"
#include "Mesh.h"
#include <vector>
#include "DNAObject.h"
#include "SideSpiralObject.h"

namespace demoscene
{
	class DNAState : public DemoState<DEMOSCENE_STATE> 
	{
		public:
			DNAState(DEMOSCENE_STATE type, renderer::Renderer* renderer, renderer::Camera* camera);
			~DNAState(void);

			bool			OnBegin	(void);
			bool			OnEnd	(void);
			DEMOSCENE_STATE	Update	(float delta);
			DEMOSCENE_STATE	Draw	(float delta);	

		private:
			DNAState(void) {};

			// member variable
			std::vector<DNAObject>				m_DNAobjects;
			std::vector<SideSpiralObject>		m_sideObjects;
			renderer::LightDirectional			m_dLight;
			Maths::Vector4						m_camPos;
			float								m_rotation;
			float								m_rotateAddition;
			float								m_timer;
	};
} // end of namespace
#endif // end of _DNA_STATE_H_