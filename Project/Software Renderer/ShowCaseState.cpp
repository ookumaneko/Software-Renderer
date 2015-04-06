#include "StdAfx.h"
#include "ShowCaseState.h"
#include <math.h>
#include "WinKeyboard.h"
using namespace renderer;
using namespace Maths;
using namespace Gdiplus;

namespace demoscene
{
	ShowCaseState::ShowCaseState(DEMOSCENE_STATE type, renderer::Renderer* renderer, renderer::Camera* camera) 
		: DemoState( type, renderer, camera ), m_rotateX( 0.0f ), m_rotateAddition( 100.0f ), m_camAngle( 0.0f )
	{
	}

	ShowCaseState::~ShowCaseState(void)
	{
		m_camera	= 0;
		m_renderer	= 0;
	}

	bool ShowCaseState::OnBegin()
	{
		m_timer = 0.0f;
		m_isEntrance = true;
		m_scale = 0.0f;
		m_renderState = RENDER_TEXTURE_SOLID;
		m_renderer->SetRenderState( RENDER_TEXTURE_SOLID );

		renderer::MD2Loader::LoadModel( "Models/eva.md2", m_eva.m_model, "Models/eva.pcx" );
		renderer::MD2Loader::LoadModel(  "Models/cloud.MD2", m_cloud.m_model, "Models/cloud.pcx" );

		m_eva.Initialize(  Vector3( -20.0f, 0.0f, 0.0f ), Vector3::ZERO, 1.0f );
		m_cloud.Initialize( Vector3( 40.0f, 0.0f, 0.0f ), Vector3::ZERO, 1.0f );

		m_camPos.X = 0.0f; 
		m_camPos.Y = 10.0f;
		m_camPos.Z = 80.0f;
		m_camPos.W = 1.0f;

		//initialize lights
		LightPoint light1( Vector4( 20.0f, 20.0f, 20.0f, 1.0f ), Vector4( 1.0f, 1.0f, 1.0f, 0.0f ), Color::Blue );
		LightPoint light2( Vector4( 20.0f, 20.0f, 20.0f, 1.0f ), Vector4( 0.5f, 0.5f, 0.5f, 0.0f ), Color::Crimson );
		LightPoint light3( Vector4( 20.0f, 20.0f, 15.0f, 1.0f ), Vector4( 1.0f, 1.0f, 1.0f, 0.0f ), Color::Green );

		m_pLights.push_back( light1 );
		m_pLights.push_back( light2 );
		m_pLights.push_back( light3 );
		//m_renderer->AddPointLight( light1 );
		m_renderer->AddPointLight( light2 );
		m_renderer->AddPointLight( light3 );
		m_renderer->EnableAmbientLight( false );
		m_renderer->SetLightMode( LIGHT_POINT );

		m_camera->BuildViewMatrix( m_camPos, Vector4( 0.0f, 0.0f, 0.0f, 1.0f ), Vector4( 0.0f, 1.0f, 0.0f, 1.0f ) );
		m_camera->BuildProjectionMatrix();

		m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		return true;	
	}

	DEMOSCENE_STATE ShowCaseState::Update(float delta)
	{
		if ( m_isEntrance )
		{
			m_scale += delta * 0.18f;
			m_rotateAddition -= delta * 7.0f;
			if ( m_scale > 1.0f )
			{
				m_rotateAddition = 30.0f;
				m_scale = 1.0f;
				m_isEntrance = false;
				m_renderState = 0;
			}
		}
		else
		{
			m_timer += delta;
			if ( m_timer >= 3.5f )
			{
				m_timer = 0.0f;
				m_renderState++;
				if ( m_renderState >= RENDER_PHONG )
				{
					m_renderState = 0;
				}
				m_renderer->SetRenderState( (RENDER_STATE)m_renderState );
			}
		}

		m_rotateX += m_rotateAddition * delta;	
		Vector3 rot( 0.0f, m_rotateX, 0.0f );

		m_eva.SetScale( m_scale );
		m_cloud.SetScale( m_scale );
		m_eva.SetRotation( rot );
		m_cloud.SetRotation( rot );

		m_eva.Update( delta );
		m_cloud.Update( delta );
		
		//// move camera
		//float distance = 75.0f;
		//float speed = 20.0f;

		//WinKeyboard& key = WinKeyboard::GetInstance();

		//if ( key.IsDown( V_W ) )
		//{
		//	m_camera->Translate( Vector4( 0.0f, 0.0f, -80.0f * delta, 0.0f ) );
		//	m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		//	m_renderer->SetViewPosition( m_camera->GetPosition() );
		//}
		//else if ( key.IsDown( V_S ) )
		//{
		//	m_camera->Translate( Vector4( 0.0f, 0.0f, 80.0f * delta, 0.0f ) );
		//	m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		//	m_renderer->SetViewPosition( m_camera->GetPosition() );
		//}
		//else if ( key.IsDown( V_D ) )
		//{
		//	m_camera->Translate( Vector4( 40.0f * delta, 0.0f, 0.0f, 0.0f ) );
		//	m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		//	m_renderer->SetViewPosition( m_camera->GetPosition() );
		//}
		//else if ( key.IsDown( V_A ) )
		//{
		//	m_camera->Translate( Vector4( -40.0f * delta, 0.0f, 0.0f, 0.0f ) );
		//	m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		//	m_renderer->SetViewPosition( m_camera->GetPosition() );
		//}

		//m_camAngle += delta * speed;
		//if ( m_camAngle >= 360.0f )
		//{
		//	m_camAngle -= 360.0f;
		//}

		//float rad = MathHelper::ToRadian( m_camAngle );
		//m_camPos.X = cosf( rad ) * distance;
		//m_camPos.Z = sinf( rad ) * distance;
		//m_camera->TranslateTo( m_camPos );
		//m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		//m_renderer->SetViewPosition( m_camPos );
		return m_type;
	}

	DEMOSCENE_STATE	ShowCaseState::Draw(float delta)
	{
		m_cloud.Render( m_renderer );
		m_eva.Render( m_renderer);
		return m_type;
	}

} // end of namespsace