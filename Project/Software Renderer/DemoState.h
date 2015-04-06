#ifndef _DEMO_STATE_H_
#define _DEMO_STATE_H_
#include "Renderer.h"

namespace demoscene
{
	template <class T>
	class DemoState
	{
		public:

			// constructors
			DemoState<T>(void);
			DemoState<T>(T type, renderer::Renderer* renderer, renderer::Camera* camera);
			~DemoState<T>(void);

			// State managements
			T				GetType	(void) const	{ return m_type; }
			virtual bool	OnBegin	(void)			{ return true; }		// Called when the state begins
			virtual bool	OnEnd	(void)			{ return true; }		// Called when the state ends
			virtual T		Update	(float delta)	{ return m_type; }		// Called every update
			virtual T		Draw	(float delta)	{ return m_type; }		// Called every update

			void			SetNextState(T type)	{ m_nextState = type; }

		protected:
			// member variables
			T					m_type;
			T					m_nextState;
			renderer::Renderer* m_renderer;
			renderer::Camera*	m_camera;
	};

	#include "DemoState.inl"

} // end of namespace 

#endif // end of _DEMO_STATE_H_