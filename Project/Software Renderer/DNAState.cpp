#include "StdAfx.h"
#include "DNAState.h"
#include <math.h>
using namespace renderer;
using namespace Maths;
using namespace Gdiplus;

namespace demoscene
{
	DNAState::DNAState(DEMOSCENE_STATE type, renderer::Renderer* renderer, renderer::Camera* camera)
		: DemoState( type, renderer, camera ), m_rotation( 0.0f ), m_rotateAddition( 30.0f) 
	{
	}

	DNAState::~DNAState(void)
	{
		m_DNAobjects.clear();
		m_sideObjects.clear();
	}

	bool DNAState::OnBegin()
	{
		float angle = 0.0f;
		float radius = 100.0f;
		int numObjects = 100;
		int hDistance = 10;
		int half = numObjects / 2;
		float st = 500.0f;
		float speed = 24.0f;

		// load model
		Mesh cube;
		MD2Loader::LoadModel( "Models/cube.md2", cube );

		// initialize DNA objects
		for ( int i = 0; i < half; ++i )
		{
			Vector3 pos( sinf( MathHelper::ToRadian( angle ) ) * radius, 
						 500.0f + st + ( -i * hDistance ), 
						 cosf( MathHelper::ToRadian( angle ) ) * radius );

			m_DNAobjects.push_back( DNAObject( cube, pos, Vector3::ZERO, 1.0f, angle, -speed, 1.0f, 0.0f, 0.0f ) );

			// increase angle
			angle += 22.5f;
			if ( angle > 360.0f )
			{
				angle -= 360.0f;
			}
		}
	
		angle = 180.0f;
		for ( int i = 0; i < half; ++i )
		{
			Vector3 pos( sinf( MathHelper::ToRadian( angle ) ) * radius, 
						 -st + ( -i * hDistance ), 
						 cosf( MathHelper::ToRadian( angle ) ) * radius );

			m_DNAobjects.push_back( DNAObject( cube, pos, Vector3::ZERO, 1.0f, angle, speed, 0.0f, 0.0f, 1.0f ) );
	
			// increase angle
			angle -= 22.5f;
			if ( angle < 0.0f )
			{
				angle -= 0.0f;
			}
		}

		// initialize side spiral objects
		angle = 0.0f;
		hDistance = 25;
		speed = 50.0f;
		for ( int i = 0; i < half; ++i )
		{
			Vector3 pos( 1650.0f + st + ( -i * hDistance ),  
						 sinf( MathHelper::ToRadian( angle ) ) * radius, 
						 cosf( MathHelper::ToRadian( angle ) ) * radius );

			m_sideObjects.push_back( SideSpiralObject( cube, pos, Vector3::ZERO, 1.0f, angle, -speed, 1.0f, 0.2f, 0.1f ) );

			// increase angle
			angle += 22.5f;
			if ( angle > 360.0f )
			{
				angle -= 360.0f;
			}
		}

		angle = 0.0f;
		for ( int i = 0; i < half; ++i )
		{
			Vector3 pos( -1500.0f + st + ( -i * hDistance ),  
						 sinf( MathHelper::ToRadian( angle ) ) * radius, 
						 cosf( MathHelper::ToRadian( angle ) ) * radius );

			m_sideObjects.push_back( SideSpiralObject( cube, pos, Vector3::ZERO, 1.0f, angle, speed, 0.1f, 0.2f, 1.0f ) );
	
			// increase angle
			angle -= 22.5f;
			if ( angle < 0.0f )
			{
				angle -= 0.0f;
			}
		}

		//float yPos = -240.0f;
		//for ( int yy = 0; yy < 10; ++yy )
		//{
		//	float xPos = -140.0f;
		//	for ( int xx = 0; xx < 10; ++xx )
		//	{
		//		if ( yy % 2 == 0 )
		//		{
		//			xPos = -1640.0f + ( xx * 80.0f );
		//		}
		//		else 
		//		{
		//			xPos = 1640.0f - ( xx * 80.0f );
		//		}

		//		Vector3 pos( xPos, yPos, -200.0f );
		//		m_objects.push_back( RenderObject( cube, pos, Vector3::ZERO, 1.0f ) );
		//	}

		//	yPos += 80.0f;
		//}

		// reset camera
		m_timer = 0.0f;
		m_camera->BuildViewMatrix( Vector4( 0.0f, 0.0f, 400.0f, 1.0f ), Vector4( 0.0f, 0.0f, 0.0f, 1.0f ), Vector4( 0.0f, 1.0f, 0.0f, 1.0f ) );
		m_camera->BuildProjectionMatrix();

		m_renderer->SetViewMatrix( m_camera->GetViewMatrix() );
		m_renderer->SetViewPosition( m_camera->GetPosition() );

		m_renderer->SetDirectionalLight( LightDirectional( Vector4( 0.0f, 0.0f, 1.0f, 1.0f ), Vector4::ONE, Color::DarkGray ) );
		m_renderer->SetAmbientLight( LightAmbient( Color::White ) );
		m_renderer->EnableAmbientLight( true );
		m_renderer->SetLightMode( LIGHT_DIRECTIONAL );
		m_renderer->SetRenderState( RENDER_FLAT );
		return true;	
	}

	bool DNAState::OnEnd()
	{
		m_DNAobjects.clear();
		return true;
	}

	DEMOSCENE_STATE DNAState::Update(float delta)
	{
		m_timer += delta;
		if ( m_timer > 1.5f )
		{
			m_rotation += m_rotateAddition * delta;	
			Vector3 rot( 0.0f, m_rotation, 0.0f );

			int size = m_DNAobjects.size();
			for ( int i = 0; i < size; ++i )
			{
				m_DNAobjects[i].SetRotation( rot );
				m_DNAobjects[i].Update( delta );
			}

			size = m_sideObjects.size();
			for ( int i = 0; i < size; ++i )
			{
				m_sideObjects[i].Update( delta );
			}
		}
		//size = m_objects.size();
		//Vector3 right( 32.0f * delta, 0.0f, 0.0f );
		//Vector3 left( -32.0f * delta, 0.0f, 0.0f );

		//int count = 0;
		//for ( int i = 0; i < size; ++i )
		//{
		//	if ( count < 10 )
		//	{
		//		m_objects[i].Translate( right );
		//	}
		//	else
		//	{
		//		m_objects[i].Translate( left );
		//	}
		//	m_objects[i].Update( delta );
		//	count++;
		//	if ( count >= 20 )
		//	{
		//		count = 0;
		//	}
		//}
		return m_type;
	}

	DEMOSCENE_STATE	DNAState::Draw(float delta)
	{
		if ( m_timer > 1.5f )
		{
			int size = m_DNAobjects.size();
			for ( int i = 0; i < size; ++i )
			{
				m_DNAobjects[i].Render( m_renderer );
			}

			size = m_sideObjects.size();
			for ( int i = 0; i < size; ++i )
			{
				m_sideObjects[i].Render( m_renderer );
			}
			//size = m_objects.size();
			//for ( int i = 0; i < size; ++i )
			//{
			//	m_objects[i].Render( m_renderer );
			//}

			if ( m_timer >= 5.0f && m_renderer->GetNumberOfPolygonOnScreen() <= 0 )
			{
				m_nextState = DS_SHOW_CASE;
			}
			else
			{
				m_nextState = m_type;
			}
		}

		return m_nextState;
	}

} // end of names