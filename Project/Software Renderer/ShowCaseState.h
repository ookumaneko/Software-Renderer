#ifndef _SHOW_CASE_STATE_H_
#define _SHOW_CASE_STATE_H_
#include "DemoState.h"
#include "StateInfo.h"
#include "Mesh.h"
#include "RenderObject.h"

namespace demoscene
{
	class Camera;

	class ShowCaseState : public DemoState<DEMOSCENE_STATE>
	{
		public:
			ShowCaseState(DEMOSCENE_STATE type, renderer::Renderer* renderer, renderer::Camera* camera);
			~ShowCaseState(void);

			bool			OnBegin	(void);
			bool			OnEnd	(void)			{ return true; }	
			DEMOSCENE_STATE	Update	(float delta);
			DEMOSCENE_STATE	Draw	(float delta);	

		private:
			ShowCaseState(void) {};

			// member variable
			RenderObject						m_eva;
			RenderObject						m_cloud;
			renderer::Mesh						m_evaModel;
			renderer::Mesh						m_cloudModel;
			std::vector<renderer::LightPoint>	m_pLights;
			Maths::Vector4						m_camPos;
			float								m_rotateX;
			float								m_rotateAddition;
			float								m_camAngle;
			float								m_scale;
			float								m_timer;
			unsigned int						m_renderState;
			bool								m_isEntrance;
	};

} // end of namespace

#endif // end of _SHOW_CASE_STATE_H_ 