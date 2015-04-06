///////////////////////////////////////////////////////////////////
//-------------------------Constructors--------------------------//
///////////////////////////////////////////////////////////////////

template <class T> 
StateMachine<T>::StateMachine(void)
{
	m_activeState = 0;
}

template <class T> 
StateMachine<T>::~StateMachine(void)
{
	Clear();
}

///////////////////////////////////////////////////////////////////
//--------------------State Management Methods-------------------//
///////////////////////////////////////////////////////////////////

template <class T> 
DemoState<T>* StateMachine<T>::GetState(T state)
{
	return m_states.GetValue( state );
}

template <class T> 
void StateMachine<T>::Clear()
{
	if ( m_states.GetSize() > 0 )
	{
		m_states.Clear( true );
	}
}

template <class T> 
bool StateMachine<T>::AddState(T id, DemoState<T> *state)
{
	int count = m_states.GetSize();
	m_states.Add( id, state );
	
	if ( count == m_states.GetSize() )
	{
		//error, could not add state
		return false;
	}

	//if there is no other states, set this one to the current state
	if ( !m_activeState )
	{
		m_activeState = state;
		m_activeState->OnBegin();
		m_currentState = id;
	}

	return true;
}

template <class T> 
bool StateMachine<T>::SetState(T newState)
{
	//search for the sent state
	DemoState<T>* pState = 0; // = m_states[ newState ];//.GetValue( newState );
	m_states.TryGetValue( newState, pState );

	if ( pState == 0 )
	{
		//not found
		return false;
	}

	//end current state
	if ( !m_activeState->OnEnd() )
	{
		//error - could not end state
		return false;
	}

	//start new state
	if ( !pState->OnBegin() )
	{
		//error - could not start new state
		return false;
	}

	//set new state
	m_activeState = pState;
	m_currentState = newState;

	return true;
}	

///////////////////////////////////////////////////////////////////
//----------------------Routine Methods--------------------------//
///////////////////////////////////////////////////////////////////

template <class T> 
void StateMachine<T>::Update(float delta)
{
	if ( m_activeState )
	{
		T newState = m_activeState->Update(delta);
		if ( newState != m_activeState->GetType() )
		{
			m_activeState->SetNextState( m_activeState->GetType() );
			SetState( newState );
		}
	}
}

template <class T> 
void StateMachine<T>::Draw(float delta)
{
	if ( m_activeState )
	{
		T newState = m_activeState->Draw(delta);
		if ( newState != m_activeState->GetType() )
		{
			m_activeState->SetNextState( m_activeState->GetType() );
			SetState( newState );
		}
	}
}