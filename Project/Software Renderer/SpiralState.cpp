#include "StdAfx.h"
#include "SpiralState.h"
#include <math.h>
#include "WinKeyboard.h"
using namespace renderer;
using namespace Maths;
using namespace Gdiplus;

namespace demoscene
{
	SpiralState::SpiralState(DEMOSCENE_STATE type, renderer::Renderer* renderer, renderer::Camera* camera)
		: DemoState( type, renderer, camera ), m_rotation( 0.0f ), m_rotateAddition( 20.0f) 
	{
	}

	SpiralState::~SpiralState(void)
	{
		m_objects.clear();
	}

	bool SpiralState::OnBegin()
	{
		float angle = 270.0f;
		float radius = 140.0f;
		int depthDistance = 7;
		m_numObjects = 180;
		int half = m_numObjects / 2;
	
		Mesh cube;
		MD2Loader::LoadModel( "Models/cube.md2", cube );
		
		for ( int i = 0; i < half; ++i )
		{
			Vector3 pos( cosf( MathHelper::ToRadian( angle ) ) * radius, sinf( MathHelper::ToRadian( angle ) ) * radius, 400 + (-i * depthDistance) );
			m_objects.push_back( RenderObject( cube, pos, Vector3::ZERO, 0.5f ) );
	
			// increase angle
			if ( radius > 40.0f )
			{
				radius--;
			}
	
			angle += 22.5f;
			if ( angle >= 360.0f )
			{
				angle -= 360.0f;
			}
		}

		angle = 90.0f;
		radius = 240.0f;
		for ( int i = 0; i < half; ++i )
		{
			Vector3 pos( cosf( MathHelper::ToRadian( angle ) ) * radius, sinf( MathHelper::ToRadian( angle ) ) * radius, 400 + (-i * depthDistance) );
			RenderObject obj( cube, pos, Vector3::ZERO, 0.5f );
			obj.m_model.SetDiffuseReflection( 1.0f, 0.0f, 0.0f );
			//m_objects.push_back( RenderObject( cube, pos, Vector3::ZERO, 0.5f ) );
			m_objects.push_back( obj );

			// increase angle
			if ( radius > 10.0f )
			{
				radius--;
			}
	
			angle -= 22.5f;
			if ( angle <= 0.0f )
			{
				angle += 360.0f;
			}
		}

		m_camPos.X = 0.0f; 
		m_camPos.Y = 00.0f;
		m_camPos.Z = 600.0f;
		m_camPos.W = 1.0f;

		m_camera->BuildViewMatrix( m_camPos, Vector4( 0.0f, 0.0f, 0.0f, 1.0f ), Vector4( 0.0f, 1.0f, 0.0f, 1.0f ) );
		m_camera->BuildProjectionMatrix();

		m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		m_renderer->SetViewPosition( m_camPos );

		//m_pLights.push_back( light3 );
		m_renderer->SetDirectionalLight( LightDirectional( Vector4( 0.0f, 0.0f, 1.0f, 1.0f ), Vector4::ONE, Color::CornflowerBlue ) );
		m_renderer->SetLightMode( LIGHT_DIRECTIONAL );
		m_renderer->SetRenderState( RENDER_FLAT );

		m_renderer->SetAmbientLight( LightAmbient( Color( 25, 25, 25 ) ) );
		m_renderer->EnableAmbientLight( true );

		return true;	
	}

	bool SpiralState::OnEnd()
	{
		m_objects.clear();
		return true;
	}

	DEMOSCENE_STATE SpiralState::Update(float delta)
	{
		float endpoint = -288.0f;
		float speed = 900.0f * delta;
		m_rotation += m_rotateAddition * delta;	
		Vector3 rot( m_rotation, m_rotation, m_rotation );

		// move camera
		m_camera->Translate( Vector4( 0.0f, 0.0f, -speed * delta, 0.0f ) );
		m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		m_renderer->SetViewPosition( m_camera->GetPosition() );

		//WinKeyboard& key = WinKeyboard::GetInstance();
		//if ( key.IsDown( V_W ) )
		//{
		//	m_camera->Translate( Vector4( 0.0f, 0.0f, -speed * delta, 0.0f ) );
		//	m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		//	m_renderer->SetViewPosition( m_camera->GetPosition() );
		//}
		//else if ( key.IsDown( V_S ) )
		//{
		//	m_camera->Translate( Vector4( 0.0f, 0.0f, speed * delta, 0.0f ) );
		//	m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		//	m_renderer->SetViewPosition( m_camera->GetPosition() );
		//}

		for ( int i = 0; i < m_numObjects; ++i )
		{
			m_objects[i].SetRotation( rot );
			m_objects[i].Update( delta );
		}

		return m_type;
	}

	DEMOSCENE_STATE	SpiralState::Draw(float delta)
	{
		for ( int i = 0; i < m_numObjects; ++i )
		{
			m_objects[i].Render( m_renderer );
		}

		if ( m_renderer->GetNumberOfPolygonOnScreen() <= 0 )
		{
			m_nextState = DS_DNA;
		}
		else
		{
			m_nextState = m_type;
		}

		return m_nextState;
	}

} // end of namespace