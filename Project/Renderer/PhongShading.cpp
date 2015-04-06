#include "Rasterizer.h"
#include "EdgeSpan.h"
#include "Mesh.h"
#include "Vertex.h"
using namespace Gdiplus;

namespace renderer
{

void Rasterizer::FillPhong(const Mesh *obj, const Vertex &v1, const Vertex &v2, const Vertex &v3)
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
	DrawSpansGouraud( edge[longEdge], edge[shortEdge1] ); 
	DrawSpansGouraud( edge[longEdge], edge[shortEdge2] );
}

void Rasterizer::DrawSpansPhong(const Edge &e1, const Edge &e2, const Mesh *obj)
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
		if ( y < 0 || y >= m_height )
			break;

		// create and draw span
		Maths::Vector4 v1, v2;
		v1 = Maths::Vector4::Lerp( e1.N1, e1.N2, factor1 );
		v2 = Maths::Vector4::Lerp( e2.N1, e2.N2, factor2 );

		Span span( e1.X1 + (int)( e1xdiff * factor1 ), Lerp( e1.Colour1, e1.Colour2, factor1 ), Lerp( e1.Z1, e1.Z2, factor1 ), v1,
				   e2.X1 + (int)( e2xdiff * factor2 ), Lerp( e2.Colour1, e2.Colour2, factor2 ), Lerp( e2.Z1, e2.Z2, factor2 ), v2 );
		
		DrawSpan( span, y );

		// increase factor
		factor1 += factorStep1;
		factor2 += factorStep2;		 
	}
}

void Rasterizer::DrawPhong(const Span &span, int y, const Mesh *obj)
{
	int xdiff = span.X2 - span.X1;
	if ( xdiff == 0 )
		return;

	float factor = 0.0f;
	float factorStep = 1.0f / (float)xdiff;
	float depth = 0.0f;

	// draw each pixel in span
	for ( int x = span.X1; x < span.X2; ++x )
	{
		// check x bound
		if ( x < 0 )
			continue;

		if ( x >= m_width ) 
			break;

		m_pixels[y][x] = Lerp( span.Colour1, span.Colour2, factor ).GetValue();
		factor += factorStep;
	}
}

} // end of namespace