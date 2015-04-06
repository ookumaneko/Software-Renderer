#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "DemoState.h"
#include "HashTable.h"

namespace demoscene
{
	template <class T>
	class StateMachine
	{
		//constructor and destructor
		public:
			StateMachine<T>(void);
			virtual ~StateMachine<T>(void);

			//states methods
			bool AddState(T id, DemoState<T>* state);
			bool SetState(T newState);
			void Clear(void);

			// Accessors
			DemoState<T>*	GetState(T state);
			DemoState<T>*	GetActiveState(void)		{ return m_activeState; }
			const T&		GetCurrentState(void) const { return m_currentState; }			

			// routine methods
			void Update	(float delta);
			void Draw	(float delta);

		//members
		protected:
			DemoState<T>*						m_activeState;
			HashTable<T, DemoState<T>*>			m_states;
			T									m_currentState;
	};

	#include "StateMachine.inl"

} // end of namespace
#endif // end of _STATE_MACHINE_H_


