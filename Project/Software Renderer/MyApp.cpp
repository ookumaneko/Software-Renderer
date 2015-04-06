#include "StdAfx.h"
#include "MyApp.h"
#include "ShowCaseState.h"
#include "SpiralState.h"
#include "DNAState.h"

using namespace demoscene;
using namespace GameDef;
using namespace Maths;
using namespace renderer;

MyApp::MyApp(void)
{
}

MyApp::~MyApp(void)
{
	// will call explicitly in shutdowns
}

void MyApp::Shutdown(void)
{
	// delete members
	delete m_camera;

	m_camera = 0;
	m_stateManager.Clear();
	m_renderer.Shutdown();
}

void MyApp::Init(HWND hWnd)
{
	m_totalTime = 0.0f;

	//initialize game time
	m_fpsCounter.InitGameTime();

	//Initialize the camera
	m_camera = new renderer::Camera( SCREEN_WIDTH, SCREEN_HEIGHT, 90.0f, 10.0f, 500.0f );
	m_camera->BuildViewMatrix( Vector4( 0, 40.0f, 50.0f, 1.0f ), Vector4( 0.0f, 0.0f, 0.0f, 1.0f ), Vector4( 0.0f, 1.0f, 0.0f, 1.0f ) );
	m_camera->BuildProjectionMatrix();

	m_fpsCounter.Update();

	m_renderer.Initialize( hWnd, SCREEN_WIDTH, SCREEN_HEIGHT );
	m_renderer.SetViewMatrix( m_camera->GetViewMatrix() );
	m_renderer.SetProjection( m_camera->GetProjectionMatrix() );
	m_renderer.SetViewPosition( m_camera->GetPosition() );
	m_renderer.SetViewFrustum( m_camera->GetFrustum() );

	m_stateManager.AddState( DS_SHOW_CASE, new ShowCaseState( DS_SHOW_CASE, &m_renderer, m_camera ) );
	m_stateManager.AddState( DS_SPIRAL, new SpiralState( DS_SPIRAL, &m_renderer, m_camera ) );
	m_stateManager.AddState( DS_DNA, new DNAState( DS_DNA, &m_renderer, m_camera ) );
	m_stateManager.SetState( DS_SPIRAL );
	//m_stateManager.SetState( DS_SHOW_CASE ); 
	//m_stateManager.SetState( DS_DNA );
}

void MyApp::Update()
{
	m_keyboard.Update();
	m_fpsCounter.Update();
	float delta = m_fpsCounter.GetElapsedTime();
	m_totalTime += delta;

	m_stateManager.Update( m_fpsCounter.GetElapsedTime() );
}

void MyApp::Render()
{
	// clear screen
	m_renderer.Clear( Gdiplus::Color::Black );

	// render
	m_renderer.Begin();	
	m_stateManager.Draw( m_fpsCounter.GetElapsedTime() );
	m_renderer.End();

	// draw info text
	DrawTextW();

	// copy back buffer onto screen buffer
	m_renderer.FlipBuffer();

}

void MyApp::DrawTextW()
{
	float x = 2;
	float y = 0;

	if ( DEBUG_MODE )
	{
		m_renderer.RenderTextArea( Gdiplus::RectF(0, 0, SCREEN_WIDTH, 110 ), Gdiplus::Color(100, 0, 0, 0) );

		WCHAR s[64];
		for (int i = 0; i < 64; i++)
		{
			s[i] = ' ';
		}
		
		wsprintf(s, TEXT("Draw Mode:") );
		m_renderer.RenderText( s, x, y);

		GetDrawModeText(s);
		m_renderer.RenderText( s, x, y );

		//polys and verts
		wsprintf(s, TEXT("Polys:         ") );
		m_renderer.RenderText( s, x, y);

		wsprintf(s, TEXT("%d") , m_renderer.GetNumberOfPolygons() );
		m_renderer.RenderText( s, x, y);

		wsprintf(s, TEXT("Verts:") );
		m_renderer.RenderText( s, x, y);

		wsprintf(s, TEXT("%d  ") ,m_renderer.GetNumberOfVerts() );
		m_renderer.RenderText( s, x, y);

		wsprintf(s, TEXT("Polys drawn:") );
		m_renderer.RenderText( s, x, y);

		wsprintf(s, TEXT("%d         ") , m_renderer.GetNumberOfPolygonOnScreen() );
		m_renderer.RenderText( s, x, y);

		wsprintf(s, TEXT("Light Mode:   ") );
		m_renderer.RenderText( s, x, y);
		
		GetLightModeText( s );
		m_renderer.RenderText( s, x, y);

		wsprintf(s, TEXT("Backface Culling:"));			
		m_renderer.RenderText( s, x, y);

		if ( GameDef::BACKFACE_CULLLING )
		{
			wsprintf(s, TEXT("On                     "));
		}
		else
		{
			wsprintf(s, TEXT("Off                      "));			
		}
		m_renderer.RenderText( s, x, y);

		y = 120;
		x = 10;

		wsprintf(s, TEXT("FPS: %d                      "), (int)m_fpsCounter.GetFPS() );
		m_renderer.RenderText( s, x, y);

		//wsprintf(s, TEXT("Total Time: %d"), (int)m_totalTime );
		//y = 140;
		//x = 10;
		//m_renderer.RenderText( s, x, y );
	}
}

void MyApp::GetLightModeText(WCHAR buff[])
{
	switch ( m_renderer.GetLightMode() )
	{
		case LIGHT_NONE:
			wsprintf(buff, TEXT("No Light") );
			break;
		case LIGHT_DIRECTIONAL:
			wsprintf(buff, TEXT("Directional Light") );
			break;
		case LIGHT_POINT:
			wsprintf(buff, TEXT("Point Lights") );
			break;
	}

}

void MyApp::GetDrawModeText(WCHAR buff[])
{
	switch( m_renderer.GetRenderState() )
	{
		case RENDER_WIREFRAME:
			wsprintf(buff, TEXT("Wireframe") );
			break;
		case RENDER_FLAT_GDI:
			wsprintf(buff, TEXT("GDI Flat Shading") );
			break;
		case RENDER_FLAT:
			wsprintf(buff, TEXT("Flat Shading") );
			break;
		case RENDER_GOURAUD:
			wsprintf(buff, TEXT("Gouraud Shading") );
			break;
		case RENDER_TEXTURED:
			wsprintf(buff, TEXT("Textured") );
			break;
		case RENDER_TEXTURE_SOLID:
			wsprintf(buff, TEXT("Textured Flat") );
			break;
		case RENDER_TEXTURE_GOURAUD:
			wsprintf(buff, TEXT("Textured Gouraud") );
			break;
	}
}
