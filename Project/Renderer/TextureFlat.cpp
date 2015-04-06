#include "Rasterizer.h"
#include "Mesh.h"
#include "EdgeSpan.h"
#include "Mesh.h"
#include "Vertex.h"
using namespace Gdiplus;

namespace renderer
{

// ---------------------Textured Flat Shading------------------------//

void Rasterizer::FillTextureFlat(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Color &col, const Mesh* obj)
{
	Edge edge[3] = { Edge( v1, v2 ), Edge( v2, v3 ), Edge( v3, v1 ) };

	int maxLength = 0;
	int longEdge = 0;

	// find edge with longest y length
	for ( int i = 0; i < 3; ++i )
	{
		int length = edge[i].Y2 - edge[i].Y1;
		if ( length > maxLength )
		{
			maxLength = length;
			longEdge = i;
		}
	}

	// get the index of other 2 edges
	int shortEdge1 = ( longEdge + 1 ) % 3;
    int shortEdge2 = ( longEdge + 2 ) % 3;

	// draw
	DrawSpansTextured( edge[longEdge], edge[shortEdge1], col, obj ); 
	DrawSpansTextured( edge[longEdge], edge[shortEdge2], col, obj );
}

void Rasterizer::DrawSpansTextured(const Edge &e1, const Edge &e2, const Color& col, const Mesh* obj)
{
	// calculate difference between the y coordinates of the first edge and return if 0
	float e1ydiff = (float)( e1.Y2 - e1.Y1 );
	if ( e1ydiff == 0.0f )
		return;

	// calculate the difference between y
	float e2ydiff = (float)( e2.Y2 - e2.Y1 );
	if ( e2ydiff == 0.0f )
		return;

	// calculate between x and colour
	float e1xdiff = (float)( e1.X2 - e1.X1 );
	float e2xdiff = (float)( e2.X2 - e2.X1 );

	// calculate factors to use for interpolation
	float factor1 = (float)( e2.Y1 - e1.Y1) / e1ydiff;
	float factorStep1 = 1.0f / e1ydiff;
	float factor2 = 0.0f;
	float factorStep2 = 1.0f / e2ydiff;

	// loop through the line between edges and draw spans
	for ( int y = e2.Y1; y < e2.Y2; ++y )
	{
		// check y bounds
		if ( y < 0 )
		{
			continue;
		}

		if ( y >= m_height )
		{
			break;
		}

		// create and draw span
		Span span( e1.X1 + (int)( e1xdiff * factor1 ), 
				   Lerp( e1.U1, e1.U2, factor1 ), 
				   Lerp( e1.V1, e1.V2, factor1 ),
				   Lerp( e1.Z1, e1.Z2, factor1 ),
				   e2.X1 + (int)( e2xdiff * factor2 ), 
				   Lerp( e2.U1, e2.U2, factor2 ), 
				   Lerp( e2.V1, e2.V2, factor2 ),
				   Lerp( e2.Z1, e2.Z2, factor2 )
				   );

		DrawSpan( span, y, col, obj );
		
		// increase factor
		factor1 += factorStep1;
		factor2 += factorStep2;		 
	}
}


void Rasterizer::DrawSpan(const Span& span, int y, const Color& col, const Mesh* obj)
{
	int xdiff = span.X2 - span.X1;
	if ( xdiff == 0 )
		return;

	float factor = 0.0f;
	float factorStep = 1.0f / (float)xdiff;

	// draw each pixel in span
	for ( int x = span.X1; x < span.X2; ++x )
	{
		// check x bound
		if ( x < 0 )
			continue;

		if ( x >= m_width ) 
			break;

		// check depth
		float z = Lerp( span.Z1, span.Z2, factor );
		if ( m_zbuffer.Get( x, y ) > z )
		{
			factor += factorStep;
			continue;
		}

		int u = Lerp( span.U1, span.U2, factor );
		int v = Lerp( span.V1, span.V2, factor );
		float r, g, b;

		if ( !obj->m_noLight )
		{
			r = obj->m_palette[ obj->m_texture[ v * obj->m_textureWidth + u ] ].GetR() + col.GetR();
			g = obj->m_palette[ obj->m_texture[ v * obj->m_textureWidth + u ] ].GetG() + col.GetG();
			b = obj->m_palette[ obj->m_texture[ v * obj->m_textureWidth + u ] ].GetB() + col.GetB();
		}
		else
		{
			r = obj->m_palette[ obj->m_texture[ v * obj->m_textureWidth + u ] ].GetR();
			g = obj->m_palette[ obj->m_texture[ v * obj->m_textureWidth + u ] ].GetG();
			b = obj->m_palette[ obj->m_texture[ v * obj->m_textureWidth + u ] ].GetB();
		}

		if ( r < 0.0f )	  r = 0.0f;
		if ( g < 0.0f )	  g = 0.0f;
		if ( b < 0.0f )	  b = 0.0f;
		if ( r > 255.0f ) r = 255.0f;
		if ( g > 255.0f ) g = 255.0f;
		if ( b > 255.0f ) b = 255.0f;

		//_bitmap->SetPixel( x, y, Gdiplus::Color( (BYTE)r, (BYTE)g, (BYTE)b ) );
		m_pixels[y][x] = Gdiplus::Color( (BYTE)r, (BYTE)g, (BYTE)b ).GetValue();
		m_zbuffer.Set( x, y, z );
		factor += factorStep;
	}
}

} // end of namespace