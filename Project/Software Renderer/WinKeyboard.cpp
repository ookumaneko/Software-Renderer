#include "stdafx.h"
#include "WinKeyboard.h"
#include <windows.h>
#include <assert.h>

namespace demoscene
{

WinKeyboard::WinKeyboard(void) : Singleton()
{
	ZeroMemory( &m_state, sizeof( unsigned char ) * KEY_SIZE );
	ZeroMemory( &m_prevState, sizeof( unsigned char ) * KEY_SIZE );

	GetKeyboardState( m_prevState );
	GetKeyboardState( m_state );
}

WinKeyboard::~WinKeyboard(void)
{
}

void WinKeyboard::Initialize()
{
	ZeroMemory( &m_state, sizeof( unsigned char ) * KEY_SIZE );
	ZeroMemory( &m_prevState, sizeof( unsigned char ) * KEY_SIZE );
	assert( GetKeyboardState( m_prevState ) );
	assert( GetKeyboardState( m_state ) );
}

void WinKeyboard::Shutdown()
{
	ZeroMemory( &m_state, sizeof( unsigned char ) * KEY_SIZE );
	ZeroMemory( &m_prevState, sizeof( unsigned char ) * KEY_SIZE );
}

void WinKeyboard::Update()
{
	// copy state from previous frame to previous state
	memcpy( m_prevState, m_state, sizeof( unsigned char ) * KEY_SIZE );
	ZeroMemory( &m_state, sizeof( unsigned char ) * KEY_SIZE );

	// get keyboard states
	GetKeyboardState( m_state ); //assert(  );
}

bool WinKeyboard::IsDown(VIRTUAL_KEYS key) const
{
	return ( m_state[key] & 0x80 );
}

bool WinKeyboard::IsUp(VIRTUAL_KEYS key) const
{
	return ( !( m_state[key] & 0x80 ) );
}

bool WinKeyboard::IsPressed(VIRTUAL_KEYS key) const
{
	return ( ( m_state[key] & 0x80) && !( m_prevState[key] & 0x80) );
}

bool WinKeyboard::IsReleased(VIRTUAL_KEYS key) const
{
	return ( !( m_state[key] & 0x80 ) && ( m_prevState[key] & 0x80 ) );
}

}