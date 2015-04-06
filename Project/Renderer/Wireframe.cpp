#include "Rasterizer.h"
#include "Mesh.h"
#include "EdgeSpan.h"
#include "Mesh.h"
#include "Vertex.h"
#include <math.h>
using namespace Gdiplus;

namespace renderer
{

// --------------------------WireFrame-----------------------------//

void Rasterizer::DrawSolidLines(Mesh *object, int p)
{
	Pen pen( Color(255, 0, 0, 255) );
	PointF stPoint(0, 0);
	PointF edPoint(0, 0);

	for ( int j = 0; j < 3; ++j )
	{
		int st = object->m_polys[p].Indices[j];
		int ep = 0;

		if ( j < 2 )
		{
			ep = object->m_polys[p].Indices[ j + 1 ];
		}
		else
		{
			ep = object->m_polys[p].Indices[0];
		}
			
		DrawLine( object->m_transformed[st].Position.X, object->m_transformed[st].Position.Y, object->m_transformed[st].Position.Z,
				  object->m_transformed[ep].Position.X, object->m_transformed[ep].Position.Y, object->m_transformed[ep].Position.Z );

		// GDI+ functions
		//stPoint.X = object->m_transformed[st]._position.X;
		//stPoint.Y = object->m_transformed[st]._position.Y;
		//edPoint.X = object->m_transformed[ep]._position.X;
		//edPoint.Y = object->m_transformed[ep]._position.Y;
		//_graphics->DrawLine( &pen, stPoint, edPoint);
	}
}

void Rasterizer::DrawLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float xdiff = ( x2 - x1 );
	float ydiff = ( y2 - y1 );
	Color col	= Color( 255, 0, 0, 255 );

	if( xdiff == 0.0f && ydiff == 0.0f ) 
	{
		m_pixels[ (int)y1 ][ (int)x1 ] = col.GetValue();
		//_bitmap->SetPixel( x1, y1, col );
		return;
	}

	float zmax, zmin;
	if( fabs( xdiff ) > fabs( ydiff ) ) 
	{
		float xmin, xmax;

		// set xmin to the lower x value given
		// and xmax to the higher value
		if( x1 < x2 ) 
		{
			xmin = x1;
			xmax = x2;
		} 
		else 
		{
			xmin = x2;
			xmax = x1;
		}

		// draw line in terms of y slope
		float slope = ydiff / xdiff;
		for( float x = xmin; x <= xmax; x += 1.0f ) 
		{
			float y = y1 + ( ( x - x1 ) * slope );

			// check x bound
			if ( x < 0 || x >= m_width || 
				 y < 0 || y >= m_height ) 
			{
				break;
			}

			m_pixels[ (int)y ][ (int)x ] = col.GetValue();
			//_bitmap->SetPixel( x, y, col );
		}
	} 
	else 
	{
		float ymin, ymax;

		// set ymin to the lower y value given
		// and ymax to the higher value
		if( y1 < y2 ) 
		{
			ymin = y1;
			ymax = y2;
		} 
		else 
		{
			ymin = y2;
			ymax = y1;
		}

		// draw line in terms of x slope
		float slope = xdiff / ydiff;
		for( float y = ymin; y <= ymax; y += 1.0f ) 
		{
			float x = x1 + ( ( y - y1 ) * slope );

			// check x bound
			if ( x < 0 || x >= m_width || 
				 y < 0 || y >= m_height ) 
				break;

			m_pixels[(int)y][(int)x] = col.GetValue();
			//_bitmap->SetPixel( x, y, col );
		}
	}
}

}