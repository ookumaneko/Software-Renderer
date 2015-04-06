#ifndef _EDGE_SPAN_H_
#define _EDGE_SPAN_H_

#include <windows.h>
#include <gdiplus.h>
#include "Vector4.h"
//#include "RendererLibDef.h"

namespace renderer
{
	class Vertex;

	struct Edge
	{
		Edge(int x1, int y1, int x2, int y2);
		Edge(int x1, int y1, float u1, float v1, int x2, int y2, float u2, float v2);
		Edge(int x1, int y1, const Gdiplus::Color& col1, int x2, int y2, const Gdiplus::Color& col2);
		//Edge(int x1, int y1, float u1, float v1, const Gdiplus::Color& col1,  int x2, int y2, float u2, float v2, const Gdiplus::Color& col2);
		Edge(const Vertex& v1, const Vertex& v2);
		
		// member variables
		Gdiplus::Color	Colour1, Colour2;
		Maths::Vector4	N1, N2;
		float			U1, V1, U2, V2, Z1, Z2;
		int				X1, Y1, X2, Y2;
	};

	struct Span
	{
		Span(int x1, float z1, int x2, float z2);
		Span(int x1, int u1, int v1, float z1, int x2, int u2, int v2, float z2);
		Span(int x1, const Gdiplus::Color& col1, float z1, int x2, const Gdiplus::Color& col2, float z2 );
		Span(int x1, const Gdiplus::Color& col1, int u1, int v1, float z1, int x2, const Gdiplus::Color& col2, int u2, int v2, float z2 );

		Span(int x1, const Gdiplus::Color& col1, float z1, const Maths::Vector4& n1, int x2, const Gdiplus::Color& col2, float z2, const Maths::Vector4& n2 ); //phong

		// member variables
		Gdiplus::Color	Colour1, Colour2;
		Maths::Vector4	N1, N2;
		float			Z1, Z2;
		int				U1, V1, U2, V2;
		int				X1, X2;		
	};
}

#endif