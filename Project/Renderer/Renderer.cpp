#include "Renderer.h"
#include "Mesh.h"

//using namespace Gdiplus;
using namespace Common;

namespace renderer
{

Renderer::Renderer() : Singleton(), m_graphics(0), m_rasterizer( 0 )
{
}

Renderer::~Renderer(void)
{
	//Shutdown();
}

void Renderer::Initialize(HWND hWnd, int width, int height)
{
	m_graphics		= new Gdiplus::Graphics( hWnd );
	m_rasterizer	= new Rasterizer( true, width, height );
	m_screenWidth	= width;
	m_screenHeight	= height;
	m_cullMode		= CULL_BACKFACE;
	m_renderState	= RENDER_FLAT; //RENDER_TEXTURED;
	m_lightMode		= LIGHT_POINT; //LIGHT_DIRECTIONAL; //;
	m_ambientEnabled = false;
	BuildScreenMatrix();
}

void Renderer::Shutdown()
{
	if ( m_graphics )
	{
		delete m_graphics;
		m_graphics = 0;
	}

	if ( m_rasterizer )
	{
		delete m_rasterizer;
		m_rasterizer = 0;
	}
}

void Renderer::BuildScreenMatrix()
{
	float w = (float)m_screenWidth - 1.0f;
	float h = (float)m_screenHeight - 1.0f;

	w /= 2;
	h /= 2;

	m_screenMatrix( 0, 0 ) = w;
	m_screenMatrix( 0, 3 ) = w;
	m_screenMatrix( 1, 1 ) = -h;
	m_screenMatrix( 1, 3 ) = h;
}

void Renderer::Clear(const Gdiplus::Color &colour)
{
	if ( m_renderState == RENDER_FLAT_GDI )
	{
		m_rasterizer->Clear( colour );
	}
	else
	{
		m_rasterizer->Begin( colour );
	}
}

void Renderer::Begin()
{
	m_numPolys		= 0;
	m_numVerts		= 0;
	m_numPolyDrawn	= 0;
}

void Renderer::End()
{
	if ( m_renderState != RENDER_FLAT_GDI )
	{
		m_rasterizer->End();
	}
}

void Renderer::FlipBuffer()
{
	// copy backbuffer to screen buffer
	m_graphics->DrawImage( m_rasterizer->GetBitmap(), Gdiplus::PointF( 0.0f, 0.0f ) );
}

void Renderer::RenderMesh(Mesh &mesh)
{
	// reseting colours
	mesh.ResetPolyColours();
	mesh.ResetVertsColours();

	// increment counters
	m_numPolys += mesh.GetNumPolys();
	m_numVerts += mesh.GetNumVerts();

	// local transform
	mesh.Transform( m_worldMatrix, TRANSFORM_LOCAL );

	// backface culling
	if ( m_cullMode == CULL_BACKFACE )
	{
		mesh.CalculateBackfaces( m_view );
	}

	// lighting
	if ( m_lightMode != LIGHT_NONE )
	{
		Lighting( mesh );
	}

	// transform to camera space
	mesh.Transform( m_viewMatrix, TRANSFORM_TRANSFORMED );

	// culling 
	if ( mesh.CullPolygons( m_frustum, m_view ) )
	{
		// entire model is culled
		return;
	}

	//depth sort polygons
	mesh.Sort();

	//apply projection transform
	mesh.Transform( m_projection, TRANSFORM_PROJECTION );
	
	// Dehomogenis model
	mesh.Dehomogenise();

	// transform to screen space
	mesh.Transform( m_screenMatrix, TRANSFORM_TRANSFORMED );

	// render model
	switch( m_renderState )
	{
		case RENDER_WIREFRAME:
			m_rasterizer->DrawWireframe( &mesh );
			break;

		case RENDER_FLAT_GDI:
			m_rasterizer->DrawSolidGDI( &mesh, mesh.GetNumVerts() );
			break;

		case RENDER_FLAT:
			m_rasterizer->DrawSolidFlat( &mesh );
			break;

		case RENDER_GOURAUD:
			m_rasterizer->DrawSolidGouraud( &mesh );
			break;

		case RENDER_TEXTURED:
		case RENDER_TEXTURE_SOLID:
			m_rasterizer->DrawTexturedFlat( &mesh );
			break;

		case RENDER_TEXTURE_GOURAUD:
			m_rasterizer->DrawTextureGouraud( &mesh );
			break;
	}

	m_numPolyDrawn += mesh.GetNumPolysOnScreen();
}

void Renderer::Lighting(Mesh& mesh)
{
	if ( m_renderState == RENDER_FLAT_GDI || m_renderState == RENDER_FLAT ||
		 m_renderState == RENDER_TEXTURE_SOLID )
	{
		if ( m_lightMode == LIGHT_DIRECTIONAL )
		{
			mesh.CalculateFlatLightingDirectional( m_directionalLight, 1, m_view, m_viewMatrix );
		}

		else if ( m_lightMode == LIGHT_POINT )
		{
			mesh.CalculateFlatLightingPoint( m_pointLights, m_pointLights.size(), m_view );
		}
	}
	
	else if ( m_renderState == RENDER_GOURAUD || m_renderState == RENDER_TEXTURE_GOURAUD )
	{
		mesh.CalculateVertsNormals();
		if ( m_lightMode == LIGHT_DIRECTIONAL )
		{
			mesh.CalculateLightingDirectional( m_directionalLight, 1, m_view );
		}

		else if ( m_lightMode == LIGHT_POINT )
		{
			mesh.CalculateLightingPoint( m_pointLights, m_pointLights.size(), m_view );
		}
	}

	if ( m_ambientEnabled )
	{
		mesh.CalculateLightingAmbient( m_ambientLight );
	}
}

void Renderer::RenderText(TCHAR mes[], float &x, float &y)
{
	m_rasterizer->DrawTextW( mes, x, y );
}

void Renderer::RenderTextArea(const Gdiplus::RectF& bound, const Gdiplus::Color& col)
{
	m_rasterizer->DrawTextArea( bound, col );
}

}