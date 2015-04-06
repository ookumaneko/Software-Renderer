#include "EdgeSpan.h"
#include "Vertex.h"

namespace renderer
{

//-------------------------------------------------------//
//-----------------------Edge class----------------------//
//-------------------------------------------------------//

Edge::Edge(int x1, int y1, int x2, int y2)
{
	if ( y1 < y2 )
	{
		X1 = x1;
		Y1 = y1;
		X2 = x2;
		Y2 = y2;
	}
	else
	{
		X1 = x2;
		Y1 = y2;
		X2 = x1;
		Y2 = y1;
	}
}

Edge::Edge(int x1, int y1, float u1, float v1, int x2, int y2, float u2, float v2)
{
	if ( y1 < y2 )
	{
		X1 = x1;
		Y1 = y1;
		X2 = x2;
		Y2 = y2;

		U1 = u1;
		V1 = v1;
		U2 = u2;
		V2 = v2;
	}
	else
	{
		X1 = x2;
		Y1 = y2;
		X2 = x1;
		Y2 = y1;

		U1 = u2;
		V1 = v2;
		U2 = u1;
		V2 = v1;
	}
}

Edge::Edge(int x1, int y1, const Gdiplus::Color& col1, int x2, int y2, const Gdiplus::Color& col2)
{
	if ( y1 < y2 )
	{
		Colour1 = col1;
		X1 = x1;
		Y1 = y1;
		Colour2 = col2;
		X2 = x2;
		Y2 = y2;
	}
	else
	{
		Colour1 = col2;
		X1 = x2;
		Y1 = y2;
		Colour2 = col1;
		X2 = x1;
		Y2 = y1;
	}
}

Edge::Edge(const renderer::Vertex &v1, const renderer::Vertex &v2)
{
	if ( v1.Position.Y < v2.Position.Y )
	{
		Colour1 = v1.Colour;
		X1		= (int)v1.Position.X;
		Y1		= (int)v1.Position.Y;
		U1		= v1.U;
		V1		= v1.V;	
		Colour2 = v2.Colour;
		X2		= (int)v2.Position.X;
		Y2		= (int)v2.Position.Y;
		U2		= v2.U;
		V2		= v2.V;
		Z1		= v1.SavedZ;
		Z2		= v2.SavedZ;
		N1		= v1.Normal;
		N2		= v2.Normal;
	}
	else
	{
		Colour1 = v2.Colour;
		X1		= (int)v2.Position.X;
		Y1		= (int)v2.Position.Y;
		U1		= (int)v2.U;
		V1		= (int)v2.V;
		Colour2 = v1.Colour;
		X2		= (int)v1.Position.X;
		Y2		= (int)v1.Position.Y;
		U2		= (int)v1.U;
		V2		= (int)v1.V;
		Z1		= v2.SavedZ;
		Z2		= v1.SavedZ;
		N1		= v2.Normal;
		N2		= v1.Normal;
	}
}

//-------------------------------------------------------//
//-----------------------Span class----------------------//
//-------------------------------------------------------//

// flat shading
Span::Span( int x1, float z1, int x2, float z2)
{
	if ( x1 < x2 )
	{
		X1 = x1;
		X2 = x2;
		Z1 = z1;
		Z2 = z2;
	}	
	else
	{
		X1 = x2;
		X2 = x1;
		Z1 = z2;
		Z2 = z1;
	}
}

// flat shading
Span::Span(int x1, int u1, int v1, float z1, int x2, int u2, int v2, float z2)
{
	if ( x1 < x2 )
	{
		X1		= x1;
		X2		= x2;

		U1		= u1;
		V1		= v1;
		U2		= u2;
		V2		= v2;
		Z1		= z1;
		Z2		= z2;
	}	
	else
	{
		X1		= x2;
		X2		= x1;

		U1		= u2;
		V1		= v2;
		U2		= u1;
		V2		= v1;
		Z1		= z2;
		Z2		= z1;
	}
}

// gouraud shading
Span::Span(int x1, const Gdiplus::Color& col1, float z1, int x2, const Gdiplus::Color& col2, float z2 )
{
	if ( x1 < x2 )
	{
		X1		= x1;
		Colour1 = col1;
		X2		= x2;
		Colour2 = col2;
		Z1		= z1;
		Z2		= z2;
	}	
	else
	{
		X1		= x2;
		Colour1 = col2;
		X2		= x1;
		Colour2 = col1;
		Z1		= z2;
		Z2		= z1;
	}
}

// textured gauroud
Span::Span(int x1, const Gdiplus::Color& col1, int u1, int v1, float z1, int x2, const Gdiplus::Color& col2, int u2, int v2, float z2 )
{
	if ( x1 < x2 )
	{
		X1		= x1;
		Colour1 = col1;
		X2		= x2;
		Colour2 = col2;
		U1		= u1;
		V1		= v1;
		U2		= u2;
		V2		= v2;
		Z1		= z1;
		Z2		= z2;
	}	
	else
	{
		X1		= x2;
		Colour1 = col2;
		X2		= x1;
		Colour2 = col1;
		U1		= u2;
		V1		= v2;
		U2		= u1;
		V2		= v1;
		Z1		= z2;
		Z2		= z1;
	}
}


//phong shading
Span::Span(int x1, const Gdiplus::Color& col1, float z1, const Maths::Vector4& n1, int x2, const Gdiplus::Color& col2, float z2, const Maths::Vector4& n2 )
{
	if ( x1 < x2 )
	{
		X1		= x1;
		Colour1 = col1;
		X2		= x2;
		Colour2 = col2;
		Z1		= z1;
		Z2		= z2;
		N1		= n1;
		N2		= n2;
	}	
	else
	{
		X1		= x2;
		Colour1 = col2;
		X2		= x1;
		Colour2 = col1;
		Z1		= z2;
		Z2		= z1;
		N1		= n2;
		N2		= n1;
	}
}

} // end of namespace